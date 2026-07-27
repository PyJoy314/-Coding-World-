#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ===== Settings (100% Same as Python Version) =====
#define CELL_SIZE 1
#define WIDTH 834
#define HEIGHT 634
#define DELAY 83
const char* RLE_FILE = "Empire_Dithered_327x537 Minecraft Bedrock image (1) (1).rle";

// ===== Global Variables =====
int grid[HEIGHT][WIDTH];
int next_grid[HEIGHT][WIDTH];
GtkWidget *drawing_area;

// ===== RLE Loader =====
gboolean load_rle(const char *path, int offset_x, int offset_y) {
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("❌ Error: RLE file not found.\n");
        return FALSE;
    }

    // Initialize Grid
    memset(grid, 0, sizeof(grid));

    char line[1024];
    char data[65536] = ""; // Temporary buffer for RLE data string

    while (fgets(line, sizeof(line), f)) {
        // Trim and skip comments/headers
        char *trimmed = line;
        while (isspace((unsigned char)*trimmed)) trimmed++;
        if (trimmed[0] == '\0' || trimmed[0] == '#' || trimmed[0] == 'x') {
            continue;
        }
        strcat(data, trimmed);
    }
    fclose(f);

    int x = offset_x;
    int y = offset_y;
    char count_str[32] = "";
    int c_idx = 0;

    for (int i = 0; data[i] != '\0'; i++) {
        char ch = data[i];

        if (isdigit((unsigned char)ch)) {
            count_str[c_idx++] = ch;
            count_str[c_idx] = '\0';
            continue;
        }

        int n = (c_idx > 0) ? atoi(count_str) : 1;
        c_idx = 0; // Reset count index

        if (ch == 'o') {
            for (int k = 0; k < n; k++) {
                if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                    grid[y][x] = 1;
                }
                x++;
            }
        } else if (ch == 'b') {
            x += n;
        } else if (ch == '$') {
            y += n;
            x = offset_x;
        } else if (ch == '!') {
            break;
        }
    }

    printf("✅ Success: RLE file loaded.\n");
    return TRUE;
}

// ===== Random Initialization (Triggered by Spacebar) =====
void random_init() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = (rand() % 2);
        }
    }
}

// ===== Life Game Rules (Next Generation) =====
void next_generation() {
    memset(next_grid, 0, sizeof(next_grid));

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int neighbors = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dx == 0 && dy == 0) continue;
                    int ny = y + dy;
                    int nx = x + dx;
                    if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                        neighbors += grid[ny][nx];
                    }
                }
            }

            if (grid[y][x] == 1 && (neighbors == 2 || neighbors == 3)) {
                next_grid[y][x] = 1;
            } else if (grid[y][x] == 0 && neighbors == 3) {
                next_grid[y][x] = 1;
            }
        }
    }
    memcpy(grid, next_grid, sizeof(grid));
}

// ===== GTK Cairo Drawing =====
static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    // Background: Black (bg="black")
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);

    // Cells: Gold / Emperor Color (#ffcc00 -> R:1.0, G:0.8, B:0.0)
    cairo_set_source_rgb(cr, 1.0, 0.8, 0.0);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x]) {
                cairo_rectangle(cr, x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
                cairo_fill(cr);
            }
        }
    }
    return FALSE;
}

// ===== Timer Update Loop =====
static gboolean update(gpointer data) {
    next_generation();
    gtk_widget_queue_draw(drawing_area);
    return TRUE; // Keeps the loop running
}

// ===== Mouse Click Event (Toggle Cell State) =====
static gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    if (event->button == GDK_BUTTON_PRIMARY) {
        int x = (int)(event->x / CELL_SIZE);
        int y = (int)(event->y / CELL_SIZE);
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            grid[y][x] ^= 1;
            gtk_widget_queue_draw(drawing_area);
        }
    }
    return TRUE;
}

// ===== Key Press Event Mapping (c, space, r) =====
static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (strcmp(gdk_keyval_name(event->keyval), "c") == 0) {
        // Press 'c' to clear grid
        memset(grid, 0, sizeof(grid));
        gtk_widget_queue_draw(drawing_area);
        printf("🧹 Grid cleared successfully.\n");
    } 
    else if (strcmp(gdk_keyval_name(event->keyval), "space") == 0) {
        // Press 'Space' to randomize grid
        random_init();
        gtk_widget_queue_draw(drawing_area);
        printf("🎲 Random cells generated successfully.\n");
    } 
    else if (strcmp(gdk_keyval_name(event->keyval), "r") == 0) {
        // Press 'r' to reload RLE
        load_rle(RLE_FILE, 0, 0);
        gtk_widget_queue_draw(drawing_area);
    }
    return TRUE;
}

int main(int argc, char *argv[]) {
    // Set random seed
    srand(g_get_monotonic_time());

    gtk_init(&argc, &argv);

    // If RLE loading fails, start with a random grid
    if (!load_rle(RLE_FILE, 0, 0)) {
        random_init();
    }

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Conway's Game of Life — Multiverse Empire (C Version)");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE);
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    // Connect signals (drawing, mouse, and keyboard)
    g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw), NULL);
    g_signal_connect(window, "button-press-event", G_CALLBACK(on_button_press), NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    // Enable window events
    gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK | GDK_KEY_PRESS_MASK);

    // Start real-time simulation loop (Interval: DELAY milliseconds)
    g_timeout_add(DELAY, update, NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}