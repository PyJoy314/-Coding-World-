#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 260

#define WIDTH 900
#define HEIGHT 600
#define MAX_HISTORY 10

// 툴 종류 정의
typedef enum { BRUSH, LINE, TOOL_RECT, OVAL, ERASER } Tool;

// Undo(되돌리기)를 위한 히스토리 구조체
typedef struct {
    Image images[MAX_HISTORY];
    int count;
} History;

// 간단한 파일 경로 입력 방식 (대화상자 없이도 빌드 가능)
char* OpenFileDialog() {
    static char filename[MAX_PATH] = {0};
    printf("Enter image path to open: ");
    if (fgets(filename, sizeof(filename), stdin)) {
        filename[strcspn(filename, "\r\n")] = '\0';
        return filename;
    }
    return NULL;
}

char* SaveFileDialog() {
    static char filename[MAX_PATH] = {0};
    printf("Enter image path to save: ");
    if (fgets(filename, sizeof(filename), stdin)) {
        filename[strcspn(filename, "\r\n")] = '\0';
        if (filename[0] == '\0') strcpy(filename, "output.png");
        return filename;
    }
    return NULL;
}

int main(void) {
    // 1. 윈도우 및 캔버스 초기화 (하단 툴바 공간 포함해 높이 660)
    InitWindow(WIDTH, 660, "Advanced Paint in C");
    SetTargetFPS(60);

    // 내부 그림 저장용 레이블 이미지 및 텍스처
    Image canvasImage = GenImageColor(WIDTH, HEIGHT, WHITE);
    Texture2D canvasTexture = LoadTextureFromImage(canvasImage);

    // 상태 변수들
    Tool currentTool = BRUSH;
    Color currentColor = BLACK;
    int brushSize = 5;
    Vector2 startPos = { 0 };
    bool isDrawing = false;

    // Undo 히스토리 초기화
    History history = { 0 };

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        // 2. 마우스 그리기 이벤트 처리 (캔버스 영역 안에서만)
        if (mousePos.y < HEIGHT) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                isDrawing = true;
                startPos = mousePos;

                // Undo 히스토리에 현재 상태 저장
                if (history.count < MAX_HISTORY) {
                    history.images[history.count] = ImageCopy(canvasImage);
                    history.count++;
                } else {
                    UnloadImage(history.images[0]);
                    for (int i = 1; i < MAX_HISTORY; i++) history.images[i-1] = history.images[i];
                    history.images[MAX_HISTORY-1] = ImageCopy(canvasImage);
                }
            }

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && isDrawing) {
                if (currentTool == BRUSH) {
                    ImageDrawLine(&canvasImage, startPos.x, startPos.y, mousePos.x, mousePos.y, currentColor);
                    startPos = mousePos;
                } else if (currentTool == ERASER) {
                    ImageDrawLine(&canvasImage, startPos.x, startPos.y, mousePos.x, mousePos.y, WHITE);
                    startPos = mousePos;
                }
                UpdateTexture(canvasTexture, canvasImage.data);
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && isDrawing) {
                if (currentTool == LINE) {
                    ImageDrawLine(&canvasImage, startPos.x, startPos.y, mousePos.x, mousePos.y, currentColor);
                } else if (currentTool == TOOL_RECT) {
                    ImageDrawRectangleLines(&canvasImage, (Rectangle) {
                        startPos.x, startPos.y, mousePos.x - startPos.x, mousePos.y - startPos.y
                    }, brushSize, currentColor);
                } else if (currentTool == OVAL) {
                    int radiusX = abs(mousePos.x - startPos.x) / 2;
                    int radiusY = abs(mousePos.y - startPos.y) / 2;
                    ImageDrawCircle(&canvasImage, startPos.x + (mousePos.x - startPos.x)/2, startPos.y + (mousePos.y - startPos.y)/2, radiusX, currentColor);
                }
                UpdateTexture(canvasTexture, canvasImage.data);
                isDrawing = false;
            }
        }

        // 3. 툴바 버튼 클릭 이벤트 처리
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mousePos.y >= HEIGHT) {
            int x = mousePos.x;
            if (x > 10 && x < 70) currentTool = BRUSH;
            else if (x > 80 && x < 140) currentTool = LINE;
            else if (x > 150 && x < 210) currentTool = TOOL_RECT;
            else if (x > 220 && x < 280) currentTool = OVAL;
            else if (x > 290 && x < 350) currentTool = ERASER;
            // 색상 변경 (단순 구현을 위해 기본 빨간색으로 토글)
            else if (x > 360 && x < 420) currentColor = (currentColor.r == 0) ? RED : BLACK;
            // Clear 기능
            else if (x > 430 && x < 490) {
                ImageClearBackground(&canvasImage, WHITE);
                UpdateTexture(canvasTexture, canvasImage.data);
            }
            // Undo 기능
            else if (x > 500 && x < 560 && history.count > 0) {
                history.count--;
                UnloadImage(canvasImage);
                canvasImage = ImageCopy(history.images[history.count]);
                UpdateTexture(canvasTexture, canvasImage.data);
                UnloadImage(history.images[history.count]);
            }
            // 열기 기능
            else if (x > 570 && x < 630) {
                char* path = OpenFileDialog();
                if (path) {
                    UnloadImage(canvasImage);
                    canvasImage = LoadImage(path);
                    ImageResize(&canvasImage, WIDTH, HEIGHT); // 900x600 강제 리사이즈 유지
                    UpdateTexture(canvasTexture, canvasImage.data);
                }
            }
            // 저장 기능
            else if (x > 640 && x < 700) {
                char* path = SaveFileDialog();
                if (path) ExportImage(canvasImage, path);
            }
        }

        // 4. 화면 그리기 (렌더링)
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // 캔버스 그리기
        DrawTexture(canvasTexture, 0, 0, WHITE);

        // 하단 툴바 UI 그리기
        DrawRectangle(0, HEIGHT, WIDTH, 60, LIGHTGRAY);
        DrawText("Brush", 20, HEIGHT + 20, 16, (currentTool == BRUSH) ? BLUE : DARKGRAY);
        DrawText("Line", 90, HEIGHT + 20, 16, (currentTool == LINE) ? BLUE : DARKGRAY);
        DrawText("Rect", 160, HEIGHT + 20, 16, (currentTool == TOOL_RECT) ? BLUE : DARKGRAY);
        DrawText("Oval", 230, HEIGHT + 20, 16, (currentTool == OVAL) ? BLUE : DARKGRAY);
        DrawText("Eraser", 300, HEIGHT + 20, 16, (currentTool == ERASER) ? BLUE : DARKGRAY);
        DrawText("Color", 370, HEIGHT + 20, 16, currentColor);
        DrawText("Clear", 440, HEIGHT + 20, 16, DARKGRAY);
        DrawText("Undo", 510, HEIGHT + 20, 16, DARKGRAY);
        DrawText("Open", 580, HEIGHT + 20, 16, DARKGRAY);
        DrawText("Save", 650, HEIGHT + 20, 16, DARKGRAY);

        EndDrawing();
    }

    // 메모리 해제
    UnloadImage(canvasImage);
    UnloadTexture(canvasTexture);
    for (int i = 0; i < history.count; i++) UnloadImage(history.images[i]);
    CloseWindow();

    return 0;
}