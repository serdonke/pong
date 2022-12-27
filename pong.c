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
#define PADDLE_SPEED  500

int main(void)
{
    int monitor;
    int height  = 720;
    int width   = 1280;

    InitWindow(width, height, "Pong");

    Paddle playerPaddle, AIPaddle;
    playerPaddle.color = AIPaddle.color = RAYWHITE;
    playerPaddle.entity.height = AIPaddle.entity.height = PADDLE_HEIGHT;
    playerPaddle.entity.width  = AIPaddle.entity.width  = PADDLE_WIDTH;
    playerPaddle.entity.x = 20;
    playerPaddle.entity.y = height / 2;
    AIPaddle.entity.x = GetRenderWidth() - 40;
    AIPaddle.entity.y = 500;

    monitor = GetCurrentMonitor();
    printf("Monitor: %d\nHeight: %d\n Width: %d\n",monitor, GetRenderHeight(), GetRenderWidth());
    SetTargetFPS(GetMonitorRefreshRate(monitor));

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_S) && playerPaddle.entity.y < GetRenderHeight() - PADDLE_HEIGHT)
        {
            playerPaddle.entity.y += PADDLE_SPEED * GetFrameTime();
        }
        else if(IsKeyDown(KEY_W) && playerPaddle.entity.y > 0)
        {
            playerPaddle.entity.y -= PADDLE_SPEED * GetFrameTime();
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleRec(playerPaddle.entity, playerPaddle.color);
            DrawRectangleRec(AIPaddle.entity, AIPaddle.color);
        EndDrawing();
    }
    
    CloseWindow();
}