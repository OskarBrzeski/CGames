#include "pong.h"

#include "raylib.h"

#include <stdio.h>

#define PADDLE_HEIGHT 60
#define PADDLE_WIDTH  10
#define PADDLE_MARGIN 20
#define PADDLE_SPEED  400
#define BALL_RAIDUS   8

typedef struct {
    float player_pos;
    float opponent_pos;
    Vector2 ball_pos;
    Vector2 ball_vel;
    int player_score;
    int opponent_score;
} GameState;

GameState global = {
    .player_pos = 0,
    .opponent_pos = 0,
    .ball_pos = { .x = 50,  .y = 50},
    .ball_vel = {.x = 220, .y = 220},
    .player_score = 0,
    .opponent_score = 0
};

void
render_game()
{
    int window_width = GetRenderWidth();
    int window_height = GetRenderHeight();

    float dt = GetFrameTime();

    handle_user_input(window_height, dt);
    update_ball_pos(window_width, window_height, dt);
    handle_FPS_toggle();

    DrawRectangleRec(player_paddle_to_rec(), WHITE);
    DrawRectangleRec(opponent_paddle_to_rec(window_width), WHITE);
    DrawCircle(global.ball_pos.x, global.ball_pos.y, BALL_RAIDUS, WHITE);
    DrawFPS(5, 5);

    char p_score[16], o_score[16];
    snprintf(p_score, 16, "%d", global.player_score);
    snprintf(o_score, 16, "%d", global.opponent_score);
    int offset = MeasureText(o_score, 18);
    DrawText(p_score, 50, window_height - 25, 18, WHITE);
    DrawText(o_score, window_width - 50 - offset, window_height - 25, 18,
             WHITE);
}

Rectangle
player_paddle_to_rec()
{
    return (Rectangle) {.x = PADDLE_MARGIN,
                        .y = global.player_pos,
                        .width = PADDLE_WIDTH,
                        .height = PADDLE_HEIGHT};
}

Rectangle
opponent_paddle_to_rec(int window_width)
{
    return (Rectangle) {.x = window_width - PADDLE_WIDTH - PADDLE_MARGIN,
                        .y = global.opponent_pos,
                        .width = PADDLE_WIDTH,
                        .height = PADDLE_HEIGHT};
}

void
handle_user_input(int window_height, float dt)
{

    if (IsKeyDown(KEY_DOWN))
    {
        global.player_pos += PADDLE_SPEED * dt;
        if (global.player_pos > window_height - PADDLE_HEIGHT)
        {
            global.player_pos = window_height - PADDLE_HEIGHT;
        }
    } else if (IsKeyDown(KEY_UP))
    {
        global.player_pos -= PADDLE_SPEED * dt;
        if (global.player_pos < 0) { global.player_pos = 0; }
    }
}

void
update_ball_pos(int window_width, int window_height, float dt)
{
    global.ball_pos.x += global.ball_vel.x * dt;
    global.ball_pos.y += global.ball_vel.y * dt;

    if (global.ball_pos.y < BALL_RAIDUS)
    {
        global.ball_vel.y = -global.ball_vel.y;
    } else if (global.ball_pos.y > window_height - BALL_RAIDUS)
    {
        global.ball_vel.y = -global.ball_vel.y;
    }

    if (CheckCollisionCircleRec(global.ball_pos, BALL_RAIDUS,
                                player_paddle_to_rec()))
    {
        global.ball_vel.x = -global.ball_vel.x;
        if (global.ball_pos.y < global.player_pos ||
            global.ball_pos.y > global.player_pos + PADDLE_HEIGHT)
        {
            global.ball_vel.y = -global.ball_vel.y;
        }
    } else if (CheckCollisionCircleRec(global.ball_pos, BALL_RAIDUS,
                                       opponent_paddle_to_rec(window_width)))
    {
        global.ball_vel.x = -global.ball_vel.x;
        if (global.ball_pos.y < global.player_pos ||
            global.ball_pos.y > global.player_pos + PADDLE_HEIGHT)
        {
            global.ball_vel.y = -global.ball_vel.y;
        }
    }

    if (global.ball_pos.x < 0)
    {
        global.opponent_score++;
        global.ball_pos.x = 50;
        global.ball_vel.x = -global.ball_vel.x;
    } else if (global.ball_pos.x > window_width)
    {
        global.player_score++;
        global.ball_pos.x = window_width - 50;
        global.ball_vel.x = -global.ball_vel.x;
    }
}

int FPS_target_index = 0;
void
handle_FPS_toggle()
{
    int FPS_targets[] = {24, 30, 48, 60, 90, 120, 144, 240};
    int FPS_target_length = sizeof(FPS_targets) / sizeof(FPS_targets[0]);
    int key;
    do {
        key = GetKeyPressed();
        if (key == KEY_SPACE)
        {
            FPS_target_index = (FPS_target_index + 1) % FPS_target_length;
            SetTargetFPS(FPS_targets[FPS_target_index]);
        }
    } while (key != 0);
}
