#include <gtk/gtk.h>
#include <cairo.h>
#include <stdlib.h>
#include <string.h>

/* Structure to represent the Paint application state */
typedef struct {
    GtkWidget *window;
    GtkWidget *drawing_area;
    GtkWidget *size_slider;
    
    cairo_surface_t *surface;
    cairo_surface_t *history[100];
    int history_count;

    char *tool;
    double color_r, color_g, color_b;
    double start_x, start_y;
    gboolean dragging;
} Paint;

/* Function prototypes */
static void clear_surface(cairo_surface_t *surface);
static void save_history(Paint *app);
static void set_tool(GtkWidget *widget, gpointer data);
static void pick_color(GtkWidget *widget, gpointer data);
static void save_file(GtkWidget *widget, gpointer data);
static void open_file(GtkWidget *widget, gpointer data);
static void undo(GtkWidget *widget, gpointer data);
static void clear_canvas(GtkWidget *widget, gpointer data);

/* Initialize the drawing surface */
static void clear_surface(cairo_surface_t *surface) {
    cairo_t *cr = cairo_create(surface);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    cairo_destroy(cr);
}

/* Save current state to history for Undo */
static void save_history(Paint *app) {
    if (app->history_count < 100) {
        cairo_surface_t *copy = cairo_image_surface_create(CAIRO_FORMAT_RGB24, 900, 600);
        cairo_t *cr = cairo_create(copy);
        cairo_set_source_surface(cr, app->surface, 0, 0);
        cairo_paint(cr);
        cairo_destroy(cr);
        app->history[app->history_count++] = copy;
    }
}

/* Callback for drawing the surface to the widget */
static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    Paint *app = (Paint *)data;
    cairo_set_source_surface(cr, app->surface, 0, 0);
    cairo_paint(cr);
    return FALSE;
}

/* Handle mouse button press */
static gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    Paint *app = (Paint *)data;
    if (event->button == GDK_BUTTON_PRIMARY) {
        save_history(app);
        app->start_x = event->x;
        app->start_y = event->y;
        app->dragging = TRUE;
    }
    return TRUE;
}

/* Handle mouse motion (brush and eraser) */
static gboolean on_motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer data) {
    Paint *app = (Paint *)data;
    if (app->dragging && (strcmp(app->tool, "brush") == 0 || strcmp(app->tool, "eraser") == 0)) {
        cairo_t *cr = cairo_create(app->surface);
        double size = gtk_range_get_value(GTK_RANGE(app->size_slider));
        
        if (strcmp(app->tool, "eraser") == 0) {
            cairo_set_source_rgb(cr, 1, 1, 1);
        } else {
            cairo_set_source_rgb(cr, app->color_r, app->color_g, app->color_b);
        }
        
        cairo_set_line_width(cr, size);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
        cairo_move_to(cr, app->start_x, app->start_y);
        cairo_line_to(cr, event->x, event->y);
        cairo_stroke(cr);
        cairo_destroy(cr);

        app->start_x = event->x;
        app->start_y = event->y;
        gtk_widget_queue_draw(app->drawing_area);
    }
    return TRUE;
}

/* Handle mouse button release (shapes and text) */
static gboolean on_button_release(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    Paint *app = (Paint *)data;
    if (event->button == GDK_BUTTON_PRIMARY) {
        double size = gtk_range_get_value(GTK_RANGE(app->size_slider));
        cairo_t *cr = cairo_create(app->surface);
        cairo_set_source_rgb(cr, app->color_r, app->color_g, app->color_b);
        cairo_set_line_width(cr, size);

        if (strcmp(app->tool, "line") == 0) {
            cairo_move_to(cr, app->start_x, app->start_y);
            cairo_line_to(cr, event->x, event->y);
            cairo_stroke(cr);
        } else if (strcmp(app->tool, "rect") == 0) {
            cairo_rectangle(cr, app->start_x, app->start_y, event->x - app->start_x, event->y - app->start_y);
            cairo_stroke(cr);
        } else if (strcmp(app->tool, "oval") == 0) {
            cairo_save(cr);
            cairo_translate(cr, app->start_x + (event->x - app->start_x) / 2.0, app->start_y + (event->y - app->start_y) / 2.0);
            cairo_scale(cr, (event->x - app->start_x) / 2.0, (event->y - app->start_y) / 2.0);
            cairo_arc(cr, 0, 0, 1, 0, 2 * G_PI);
            cairo_restore(cr);
            cairo_stroke(cr);
        } else if (strcmp(app->tool, "text") == 0) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(app->window), GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_OK_CANCEL, "입력:");
            GtkWidget *entry = gtk_entry_new();
            gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), entry);
            gtk_widget_show_all(dialog);
            if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
                const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
                cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
                cairo_set_font_size(cr, size * 2);
                cairo_move_to(cr, event->x, event->y);
                cairo_show_text(cr, text);
            }
            gtk_widget_destroy(dialog);
        }

        cairo_destroy(cr);
        app->dragging = FALSE;
        gtk_widget_queue_draw(app->drawing_area);
    }
    return TRUE;
}

/* Tool selection callback */
static void set_tool(GtkWidget *widget, gpointer data) {
    struct { Paint *app; char *name; } *params = data;
    params->app->tool = params->name;
}

/* Color picker callback */
static void pick_color(GtkWidget *widget, gpointer data) {
    Paint *app = (Paint *)data;
    GtkWidget *dialog = gtk_color_chooser_dialog_new("Select Color", GTK_WINDOW(app->window));
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
        GdkRGBA color;
        gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(dialog), &color);
        app->color_r = color.red;
        app->color_g = color.green;
        app->color_b = color.blue;
    }
    gtk_widget_destroy(dialog);
}

/* Save image callback */
static void save_file(GtkWidget *widget, gpointer data) {
    Paint *app = (Paint *)data;
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(app->window), GTK_FILE_CHOOSER_ACTION_SAVE, "_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        cairo_surface_write_to_png(app->surface, filename);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

/* Open image callback */
static void open_file(GtkWidget *widget, gpointer data) {
    Paint *app = (Paint *)data;
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(app->window), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(filename, 900, 600, FALSE, NULL);
        if (pixbuf) {
            cairo_t *cr = cairo_create(app->surface);
            gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
            cairo_paint(cr);
            cairo_destroy(cr);
            g_object_unref(pixbuf);
        }
        g_free(filename);
        gtk_widget_queue_draw(app->drawing_area);
    }
    gtk_widget_destroy(dialog);
}

/* Undo callback */
static void undo(GtkWidget *widget, gpointer data) {
    Paint *app = (Paint *)data;
    if (app->history_count > 0) {
        cairo_surface_destroy(app->surface);
        app->surface = app->history[--app->history_count];
        gtk_widget_queue_draw(app->drawing_area);
    }
}

/* Clear canvas callback */
static void clear_canvas(GtkWidget *widget, gpointer data) {
    Paint *app = (Paint *)data;
    clear_surface(app->surface);
    gtk_widget_queue_draw(app->drawing_area);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    Paint *app = g_malloc0(sizeof(Paint));
    app->tool = "brush";
    app->color_r = 0; app->color_g = 0; app->color_b = 0;
    app->history_count = 0;
    app->surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, 900, 600);
    clear_surface(app->surface);

    app->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app->window), "Advanced Paint");
    g_signal_connect(app->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(app->window), vbox);

    app->drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(app->drawing_area, 900, 600);
    gtk_box_pack_start(GTK_BOX(vbox), app->drawing_area, TRUE, TRUE, 0);

    g_signal_connect(app->drawing_area, "draw", G_CALLBACK(on_draw), app);
    g_signal_connect(app->drawing_area, "button-press-event", G_CALLBACK(on_button_press), app);
    g_signal_connect(app->drawing_area, "motion-notify-event", G_CALLBACK(on_motion_notify), app);
    g_signal_connect(app->drawing_area, "button-release-event", G_CALLBACK(on_button_release), app);
    gtk_widget_set_events(app->drawing_area, GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK | GDK_BUTTON_RELEASE_MASK);

    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    char *tools[] = {"brush", "line", "rect", "oval", "text", "eraser"};
    for (int i = 0; i < 6; i++) {
        GtkWidget *btn = gtk_button_new_with_label(tools[i]);
        struct { Paint *app; char *name; } *params = g_malloc(sizeof(*params));
        params->app = app; params->name = tools[i];
        g_signal_connect(btn, "clicked", G_CALLBACK(set_tool), params);
        gtk_box_pack_start(GTK_BOX(toolbar), btn, FALSE, FALSE, 0);
    }

    GtkWidget *btn_color = gtk_button_new_with_label("색");
    g_signal_connect(btn_color, "clicked", G_CALLBACK(pick_color), app);
    gtk_box_pack_start(GTK_BOX(toolbar), btn_color, FALSE, FALSE, 0);

    GtkWidget *btn_save = gtk_button_new_with_label("저장");
    g_signal_connect(btn_save, "clicked", G_CALLBACK(save_file), app);
    gtk_box_pack_start(GTK_BOX(toolbar), btn_save, FALSE, FALSE, 0);

    GtkWidget *btn_open = gtk_button_new_with_label("열기");
    g_signal_connect(btn_open, "clicked", G_CALLBACK(open_file), app);
    gtk_box_pack_start(GTK_BOX(toolbar), btn_open, FALSE, FALSE, 0);

    GtkWidget *btn_undo = gtk_button_new_with_label("Undo");
    g_signal_connect(btn_undo, "clicked", G_CALLBACK(undo), app);
    gtk_box_pack_start(GTK_BOX(toolbar), btn_undo, FALSE, FALSE, 0);

    GtkWidget *btn_clear = gtk_button_new_with_label("Clear");
    g_signal_connect(btn_clear, "clicked", G_CALLBACK(clear_canvas), app);
    gtk_box_pack_start(GTK_BOX(toolbar), btn_clear, FALSE, FALSE, 0);

    app->size_slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 20, 1);
    gtk_range_set_value(GTK_RANGE(app->size_slider), 5);
    gtk_widget_set_size_request(app->size_slider, 100, -1);
    gtk_box_pack_start(GTK_BOX(toolbar), app->size_slider, FALSE, FALSE, 0);

    gtk_widget_show_all(app->window);
    gtk_main();

    return 0;
}
