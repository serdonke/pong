#include <raylib.h>
#include <raymath.h> 
#include <stdio.h>

void stateSwitch();

typedef struct Paddle
{
    Rectangle entity;
    Color color;
    int score;
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
#define BALL_OFFSET 600

int GAMESTATE = 0;
// 0 -> menu
// 1 -> play
// 2 -> paus
// 3 -> over

int main(void)
{
    int monitor;
    int height = 720;
    int width  = 1280;

    Image icon = LoadImage("./res/icon.png");

    InitWindow(width, height, "Pong");
    SetWindowIcon(icon);
    
    InitAudioDevice();
    Sound impact  = LoadSound("./res/paddle_hit.wav");
    Sound wallHit = LoadSound("./res/wall_hit.wav");
    Sound score   = LoadSound("./res/score.wav");

    Paddle playerPaddle, AIPaddle;
    playerPaddle.color = AIPaddle.color = RAYWHITE;
    playerPaddle.score = AIPaddle.score = 0;
    playerPaddle.entity.height = AIPaddle.entity.height = PADDLE_HEIGHT;
    playerPaddle.entity.width  = AIPaddle.entity.width  = PADDLE_WIDTH;
    playerPaddle.entity.x = 20;
    playerPaddle.entity.y = GetRenderHeight() / 2.0;
    AIPaddle.entity.x = GetRenderWidth() - 40;
    AIPaddle.entity.y = GetRenderHeight() / 2.0;

    Ball ball;
    ball.position.x = GetRenderWidth() / 2.0;
    ball.position.y = GetRenderHeight() / 2.0;
    ball.radius = BALL_RADIUS;
    ball.color  = RAYWHITE;
    int direction = GetRandomValue(-1, 1);
    float offset  = GetRandomValue(-BALL_OFFSET, BALL_OFFSET);

    //Score keeping
    char *strplayerScore = MemAlloc(1024);
    char *strAIScore = MemAlloc(1024);
    strplayerScore[0] = '0';
    strAIScore[0] = '0';

    monitor = GetCurrentMonitor();
    printf("Monitor: %d\nHeight: %d\nWidth: %d\n",monitor, GetRenderHeight(), GetRenderWidth());
    printf("%s\n", GetWorkingDirectory());

    SetTargetFPS(GetMonitorRefreshRate(monitor));
    while (!WindowShouldClose())
    {
        stateSwitch();
        switch (GAMESTATE)
        {
            case 0:
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
            break;

            case 1: // Play State
                if(IsKeyDown(KEY_S) && playerPaddle.entity.y < GetRenderHeight() - PADDLE_HEIGHT)
                {
                    playerPaddle.entity.y += PADDLE_SPEED * GetFrameTime();
                }
                else if(IsKeyDown(KEY_W) && playerPaddle.entity.y > 0)
                {
                    playerPaddle.entity.y -= PADDLE_SPEED * GetFrameTime();
                }
                // //AIPAddle Test
                // if(IsKeyDown(KEY_DOWN) && AIPaddle.entity.y < GetRenderHeight() - PADDLE_HEIGHT)
                // {
                //     AIPaddle.entity.y += PADDLE_SPEED * GetFrameTime();
                // }
                // else if(IsKeyDown(KEY_UP) && AIPaddle.entity.y > 0)
                // {
                //     AIPaddle.entity.y -= PADDLE_SPEED * GetFrameTime();
                // }
                //AI Paddle
                if(direction == 1)
                {
                    if (AIPaddle.entity.y > GetRenderHeight() / 2.0 - PADDLE_HEIGHT / 2.0)
                    {
                        AIPaddle.entity.y -= (PADDLE_SPEED * GetFrameTime());
                    }
                    else 
                    {
                        AIPaddle.entity.y += (PADDLE_SPEED * GetFrameTime());    
                    }
                }
                else if (ball.position.x > GetRenderWidth() / 2.0)
                {
                    if (AIPaddle.entity.y != ball.position.y)
                    {
                        if (AIPaddle.entity.y > ball.position.y)
                        {
                            AIPaddle.entity.y -= PADDLE_SPEED * GetFrameTime();
                        }
                        else
                        {
                            if(AIPaddle.entity.y < GetRenderHeight() - PADDLE_HEIGHT)
                                AIPaddle.entity.y += PADDLE_SPEED * GetFrameTime();
                        }
                    }
                }

                //Ball Movement
                ball.position.x += (BALL_SPEED * (direction ? -1 : 1)) * GetFrameTime();
                ball.position.y += offset * GetFrameTime();

                if(ball.position.y <= 0 + ball.radius || ball.position.y >= GetRenderHeight() - ball.radius)
                {    
                    offset *= -1;
                    PlaySound(wallHit);            
                }
                //Ball-player Interaction
                if(CheckCollisionCircleRec(ball.position, ball.radius, ((ball.position.x <= width / 2.0) ? playerPaddle.entity : AIPaddle.entity)))
                {
                    direction = ball.position.x <= width / 2.0 ? 0 : 1;
                    offset = GetRandomValue(-BALL_OFFSET, BALL_OFFSET);
                    PlaySound(impact);
                }
                //Track balls and scores
                if(ball.position.x <= 0)
                {
                    ball.position.x = GetRenderWidth() / 2.0;
                    ball.position.y = GetRenderHeight() / 2.0;
                    direction = GetRandomValue(-1, 1);
                    offset = GetRandomValue(-BALL_OFFSET, BALL_OFFSET);
                    PlaySound(score);
                    playerPaddle.score += 1;
                    sprintf(strplayerScore, "%d", playerPaddle.score);
                }
                if(ball.position.x >= GetRenderWidth())
                {
                    ball.position.x = GetRenderWidth() / 2.0;
                    ball.position.y = GetRenderHeight() / 2.0;
                    direction = GetRandomValue(-1, 1);
                    offset = GetRandomValue(-BALL_OFFSET, BALL_OFFSET);
                    PlaySound(score);
                    AIPaddle.score += 1;
                    sprintf(strAIScore, "%d", AIPaddle.score);
                }
            break;
        }


        BeginDrawing();
            switch (GAMESTATE)
            {
                case 0:
                break;

                case 1:
                    DrawCircleV(ball.position, ball.radius, ball.color);
                break;
            }
            DrawText(strplayerScore, GetRenderWidth() / 2 - 200, GetRenderHeight() / 2 - 200, 30, RAYWHITE);
            ClearBackground(BLACK);
            DrawText(strAIScore, GetRenderWidth() / 2 + 200, GetRenderHeight() / 2 - 200, 30, RAYWHITE);
            DrawRectangleRec(playerPaddle.entity, playerPaddle.color);
            DrawRectangleRec(AIPaddle.entity, AIPaddle.color);
        EndDrawing();
    }
    
    UnloadImage(icon);
    MemFree(strplayerScore);
    MemFree(strAIScore);
    CloseAudioDevice();
    CloseWindow();
}

void stateSwitch()
{
    if (IsKeyPressed(KEY_ENTER))
    { 
        GAMESTATE = (GAMESTATE) ? 0 : 1;
    }
}