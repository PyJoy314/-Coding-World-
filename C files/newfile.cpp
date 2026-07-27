#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <string>

// Constants for UI / System Architecture
const int WINDOW_WIDTH = 950;
const int WINDOW_HEIGHT = 750;
const int CANVAS_WIDTH = 900;
const int CANVAS_HEIGHT = 600;
const int CANVAS_X = 10;
const int CANVAS_Y = 100; // Left padding for Toolbar zone

#define TOOL_BRUSH  1
#define TOOL_LINE   2
#define TOOL_RECT   3
#define TOOL_OVAL   4
#define TOOL_TEXT   5
#define TOOL_ERASER 6

// Global Variables
int currentTool = TOOL_BRUSH;
SDL_Color currentColor = {0, 0, 0, 255}; // Default: Black
int g_penSize = 5;
int startX, startY;
bool isDrawing = false;

// Structures for Undo System Data
struct LineData {
    int x1, y1, x2, y2;
    SDL_Color color;
    int size;
    int toolType; // BRUSH, LINE, RECT, OVAL, ERASER
};

std::vector<LineData> drawingHistory;

// Simple Button Box Component for Linux/Android UI
struct Button {
    SDL_Rect rect;
    std::string label;
    int id;
};
std::vector<Button> buttons;

void InitButtons() {
    std::string tools[] = {"brush", "line", "rect", "oval", "text", "eraser", "Color", "Undo", "Clear"};
    int x = 10;
    for (int i = 0; i < 9; ++i) {
        buttons.push_back({{x, 10, 80, 40}, tools[i], 101 + i});
        x += 85;
    }
}

// Function to render an open ellipse/oval circle
void DrawOval(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) {
    int rx = abs(x2 - x1) / 2;
    int ry = abs(y2 - y1) / 2;
    int cx = (x1 + x2) / 2;
    int cy = (y1 + y2) / 2;

    for (int w = 0; w < rx * 2; w++) {
        for (int h = 0; h < ry * 2; h++) {
            int dx = w - rx;
            int dy = h - ry;
            if ((dx * dx * ry * ry + dy * dy * rx * rx) <= (rx * rx * ry * ry) &&
                (dx * dx * ry * ry + dy * dy * rx * rx) >= ((rx - 2) * (rx - 2) * ry * ry)) {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Initialization Engine Failed!" << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Advanced Paint (Cxxdroid Port)",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    InitButtons();
    bool quit = false;
    SDL_Event event;

    // Main Engine Loop
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            // Mouse & Touch Input Handler
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mx = event.button.x;
                int my = event.button.y;

                // Check Button click event
                for (auto& btn : buttons) {
                    if (mx >= btn.rect.x && mx <= btn.rect.x + btn.rect.w &&
                        my >= btn.rect.y && my <= btn.rect.y + btn.rect.h) {
                        
                        if (btn.id >= 101 && btn.id <= 106) currentTool = btn.id - 100;
                        else if (btn.id == 107) { // Color Change Cycle
                            if (currentColor.r == 0 && currentColor.g == 0) currentColor = {255, 0, 0, 255}; // Red
                            else if (currentColor.r == 255) currentColor = {0, 0, 255, 255}; // Blue
                            else currentColor = {0, 0, 0, 255}; // Black
                        }
                        else if (btn.id == 108) { // Undo Code Block
                            if (!drawingHistory.empty()) drawingHistory.pop_back();
                        }
                        else if (btn.id == 109) { // Clear Canvas Area
                            drawingHistory.clear();
                        }
                    }
                }

                // Canvas Area Click Detect
                if (mx >= CANVAS_X && mx < CANVAS_X + CANVAS_WIDTH && my >= CANVAS_Y && my < CANVAS_Y + CANVAS_HEIGHT) {
                    startX = mx;
                    startY = my;
                    isDrawing = true;
                }
            }
            else if (event.type == SDL_MOUSEMOTION && isDrawing) {
                int mx = event.motion.x;
                int my = event.motion.y;

                if (currentTool == TOOL_BRUSH || currentTool == TOOL_ERASER) {
                    SDL_Color col = (currentTool == TOOL_ERASER) ? SDL_Color{255, 255, 255, 255} : currentColor;
                    drawingHistory.push_back({startX, startY, mx, my, col, g_penSize, currentTool});
                    startX = mx;
                    startY = my;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP && isDrawing) {
                int mx = event.button.x;
                int my = event.button.y;

                if (currentTool == TOOL_LINE || currentTool == TOOL_RECT || currentTool == TOOL_OVAL) {
                    drawingHistory.push_back({startX, startY, mx, my, currentColor, g_penSize, currentTool});
                }
                isDrawing = false;
            }
        }

        // --- Render Target Engine ---
        SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255); // Background gray
        SDL_RenderClear(renderer);

        // Draw Canvas Frame
        SDL_Rect canvasRect = {CANVAS_X, CANVAS_Y, CANVAS_WIDTH, CANVAS_HEIGHT};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Canvas White
        SDL_RenderFillRect(renderer, &canvasRect);

        // Draw UI Elements (Buttons)
        for (auto& btn : buttons) {
            SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
            SDL_RenderFillRect(renderer, &btn.rect);
        }

        // Draw Drawing Database Vector Stack (Undo Engine Sync)
        for (const auto& item : drawingHistory) {
            SDL_SetRenderDrawColor(renderer, item.color.r, item.color.g, item.color.b, item.color.a);
            
            if (item.toolType == TOOL_BRUSH || item.toolType == TOOL_LINE || item.toolType == TOOL_ERASER) {
                SDL_RenderDrawLine(renderer, item.x1, item.y1, item.x2, item.y2);
            }
            else if (item.toolType == TOOL_RECT) {
                SDL_Rect r = {item.x1, item.y1, item.x2 - item.x1, item.y2 - item.y1};
                SDL_RenderDrawRect(renderer, &r);
            }
            else if (item.toolType == TOOL_OVAL) {
                DrawOval(renderer, item.x1, item.y1, item.x2, item.y2);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 Frame Rate Controller
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}