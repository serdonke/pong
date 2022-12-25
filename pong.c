#include <raylib.h>
#include <raymath.h> 
#include <stdio.h>

typedef struct Paddle
{
    Rectangle entity;
    Color color;
} Paddle;

#define PADDLE_HEIGHT 140
#define PADDLE_WIDTH  18

int main(void)
{
    int monitor = GetCurrentMonitor();
    int height  = GetMonitorHeight(monitor);
    int width   = GetMonitorWidth(monitor);


    Paddle playerPaddle, AIPaddle;
    playerPaddle.color = AIPaddle.color = RAYWHITE;
    playerPaddle.entity.height = AIPaddle.entity.height = PADDLE_HEIGHT;
    playerPaddle.entity.width  = AIPaddle.entity.width  = PADDLE_WIDTH;
    playerPaddle.entity.x = width + 20;
    playerPaddle.entity.y = 500;
    AIPaddle.entity.x = GetRenderWidth() - 50;
    AIPaddle.entity.y = 500;

    InitWindow(width, height, "Pong");
    printf("Monitor: %d\nHeight: %d\n Width: %d\n",monitor, GetRenderHeight(), GetRenderWidth());

    SetTargetFPS(GetMonitorRefreshRate(monitor));

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_DOWN))
        {
            playerPaddle.entity.y += 300 * GetFrameTime();
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleRec(playerPaddle.entity, playerPaddle.color);
            DrawRectangleRec(AIPaddle.entity, AIPaddle.color);
        EndDrawing();
    }
    
    CloseWindow();
}