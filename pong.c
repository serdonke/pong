#include <raylib.h>
#include <raymath.h> 
#include <stdio.h>

typedef struct Paddle
{
    Rectangle entity;
    Color color;
} Paddle;

typedef struct Ball
{
    Vector2 position;
    float radius;
    Color color;
} Ball;

#define PADDLE_HEIGHT 140
#define PADDLE_WIDTH  18
#define PADDLE_SPEED  800

#define BALL_RADIUS 5
#define BALL_SPEED  600
#define BALL_OFFSET 400

int main(void)
{
    int monitor;
    int height = 720;
    int width  = 1280;

    InitWindow(width, height, "Pong");

    Paddle playerPaddle, AIPaddle;
    playerPaddle.color = AIPaddle.color = RAYWHITE;
    playerPaddle.entity.height = AIPaddle.entity.height = PADDLE_HEIGHT;
    playerPaddle.entity.width  = AIPaddle.entity.width  = PADDLE_WIDTH;
    playerPaddle.entity.x = 20;
    playerPaddle.entity.y = GetRenderHeight() / 2;
    AIPaddle.entity.x = GetRenderWidth() - 40;
    AIPaddle.entity.y = GetRenderHeight() / 2;

    Ball ball;
    ball.position.x = GetRenderWidth() / 2;
    ball.position.y = GetRenderHeight() / 2;
    ball.radius = BALL_RADIUS;
    ball.color  = RAYWHITE;
    int direction = GetRandomValue(-1, 1);
    float offset  = GetRandomValue(-BALL_OFFSET, BALL_OFFSET);

    monitor = GetCurrentMonitor();
    printf("Monitor: %d\nHeight: %d\nWidth: %d\n",monitor, GetRenderHeight(), GetRenderWidth());

    SetTargetFPS(GetMonitorRefreshRate(monitor));

    while (!WindowShouldClose())
    {
        if(IsKeyDown(KEY_S) && playerPaddle.entity.y < GetRenderHeight() - PADDLE_HEIGHT)
        {
            playerPaddle.entity.y += PADDLE_SPEED * GetFrameTime();
        }
        else if(IsKeyDown(KEY_W) && playerPaddle.entity.y > 0)
        {
            playerPaddle.entity.y -= PADDLE_SPEED * GetFrameTime();
        }
        //AIPAddle Test
        if(IsKeyDown(KEY_DOWN) && AIPaddle.entity.y < GetRenderHeight() - PADDLE_HEIGHT)
        {
            AIPaddle.entity.y += PADDLE_SPEED * GetFrameTime();
        }
        else if(IsKeyDown(KEY_UP) && AIPaddle.entity.y > 0)
        {
            AIPaddle.entity.y -= PADDLE_SPEED * GetFrameTime();
        }


        //Ball Movement
        ball.position.x += (BALL_SPEED * (direction ? -1 : 1)) * GetFrameTime();
        ball.position.y += offset * GetFrameTime();
//        if(ball.position.x <= 0) { direction = 0; }
//        else if(ball.position.x >= GetRenderWidth()) { direction = -1; }
        //Ball environment behaviour
        if(ball.position.x <= 0 || ball.position.x >= GetRenderWidth())
        {
            ball.position.x = GetRenderWidth() / 2;
            ball.position.y = GetRenderHeight() / 2;
            direction = GetRandomValue(-1, 1);
            offset = GetRandomValue(-BALL_OFFSET, BALL_OFFSET);            
        }
        if(ball.position.y <= 0 + ball.radius || ball.position.y >= GetRenderHeight() - ball.radius)
        {    
            offset *= -1;
        }
        //Ball-player Interaction
        if(CheckCollisionCircleRec(ball.position, ball.radius, ((ball.position.x <= width / 2) ? playerPaddle.entity : AIPaddle.entity)))
        {
            direction = ball.position.x <= width / 2 ? 0 : 1;
            offset = GetRandomValue(-600, 600);
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleRec(playerPaddle.entity, playerPaddle.color);
            DrawRectangleRec(AIPaddle.entity, AIPaddle.color);
            DrawCircleV(ball.position, ball.radius, ball.color);
        EndDrawing();
    }
    
    CloseWindow();
}