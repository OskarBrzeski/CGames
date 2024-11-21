#include "pong.h"

#include "raylib.h"
#include "raymath.h"

#include <stdio.h>

#define PADDLE_HEIGHT 60
#define PADDLE_WIDTH  10
#define PADDLE_MARGIN 20
#define PADDLE_SPEED  270
#define BALL_RAIDUS   8
#define BALL_SPEED    360

PongGameState global = {};

void
pong_new_game(void)
{
    global = (PongGameState) {
        .player_pos = 0,
        .opponent_pos = 0,
        .ball_pos = {        .x = 50,         .y = 50},
        .ball_vel = {.x = BALL_SPEED, .y = BALL_SPEED},
        .player_score = 0,
        .opponent_score = 0
    };
}

void
pong_run_game()
{
    int window_width = GetRenderWidth();
    int window_height = GetRenderHeight();
    float dt = GetFrameTime();

    handle_user_input(window_height, dt);
    move_opponent(dt);
    update_ball_pos(window_width, window_height, dt);

    render_game(window_width, window_height);
}

void
render_game(int window_width, int window_height)
{
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

void
move_opponent(float dt)
{
    if (global.ball_pos.y < global.opponent_pos + PADDLE_HEIGHT / 2.0)
    {
        global.opponent_pos -= PADDLE_SPEED * dt;
    } else
    {
        global.opponent_pos += PADDLE_SPEED * dt;
    }
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
    global.ball_pos =
        Vector2Add(global.ball_pos, Vector2Scale(global.ball_vel, dt));

    int hit_walls = global.ball_pos.y < BALL_RAIDUS ||
                    global.ball_pos.y > window_height - BALL_RAIDUS;
    if (hit_walls) { global.ball_vel.y = -global.ball_vel.y; }

    ball_hit_player();
    ball_hit_opponent(window_width);

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

void
ball_hit_player()
{
    Rectangle player = player_paddle_to_rec();
    if (CheckCollisionCircleRec(global.ball_pos, BALL_RAIDUS, player))
    {
        global.ball_vel.x = -global.ball_vel.x;
        if (global.ball_pos.y < global.player_pos - BALL_RAIDUS * 2.0 / 3.0 ||
            global.ball_pos.y >
                global.player_pos + PADDLE_HEIGHT + BALL_RAIDUS * 2.0 / 3.0)
        {
            global.ball_vel.y = -global.ball_vel.y;
        }
    }
}

void
ball_hit_opponent(int window_width)
{
    Rectangle opponent = opponent_paddle_to_rec(window_width);
    if (CheckCollisionCircleRec(global.ball_pos, BALL_RAIDUS, opponent))
    {
        global.ball_vel.x = -global.ball_vel.x;
        if (global.ball_pos.y < global.opponent_pos - BALL_RAIDUS * 2 / 3 ||
            global.ball_pos.y >
                global.opponent_pos + PADDLE_HEIGHT + BALL_RAIDUS * 2 / 3)
        {
            global.ball_vel.y = -global.ball_vel.y;
        }
    }
}
