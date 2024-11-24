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

    pong_handle_user_input(window_height, dt);
    pong_move_opponent(dt);
    pong_update_ball_pos(window_width, window_height, dt);

    pong_render_game(window_width, window_height);
}

void
pong_render_game(int window_width, int window_height)
{
    DrawRectangleRec(pong_left_paddle_rec(), WHITE);
    DrawRectangleRec(pong_right_paddle_rec(window_width), WHITE);
    DrawCircle(global.ball_pos.x, global.ball_pos.y, BALL_RAIDUS, WHITE);

    pong_render_text(window_width, window_height);
}

void
pong_render_text(int window_width, int window_height)
{
    char p_score[16], o_score[16];
    snprintf(p_score, 16, "%d", global.player_score);
    snprintf(o_score, 16, "%d", global.opponent_score);

    int offset = MeasureText(o_score, 18);
    DrawText(p_score, 50, window_height - 25, 18, WHITE);
    DrawText(o_score, window_width - 50 - offset, window_height - 25, 18,
             WHITE);

    DrawFPS(5, 5);
}

void
pong_move_opponent(float dt)
{
    if (global.ball_pos.y < global.opponent_pos + PADDLE_HEIGHT / 2.0)
    {
        global.opponent_pos -= PADDLE_SPEED * dt;
    }
    else { global.opponent_pos += PADDLE_SPEED * dt; }
}

Rectangle
pong_left_paddle_rec()
{
    return (Rectangle) {.x = PADDLE_MARGIN,
                        .y = global.player_pos,
                        .width = PADDLE_WIDTH,
                        .height = PADDLE_HEIGHT};
}

Rectangle
pong_right_paddle_rec(int window_width)
{
    return (Rectangle) {.x = window_width - PADDLE_WIDTH - PADDLE_MARGIN,
                        .y = global.opponent_pos,
                        .width = PADDLE_WIDTH,
                        .height = PADDLE_HEIGHT};
}

void
pong_handle_user_input(int window_height, float dt)
{
    if (IsKeyDown(KEY_DOWN))
    {
        global.player_pos += PADDLE_SPEED * dt;
        if (global.player_pos > window_height - PADDLE_HEIGHT)
        {
            global.player_pos = window_height - PADDLE_HEIGHT;
        }
    }
    else if (IsKeyDown(KEY_UP))
    {
        global.player_pos -= PADDLE_SPEED * dt;
        if (global.player_pos < 0) { global.player_pos = 0; }
    }
}

void
pong_update_ball_pos(int window_width, int window_height, float dt)
{
    global.ball_pos =
        Vector2Add(global.ball_pos, Vector2Scale(global.ball_vel, dt));

    if (global.ball_pos.y < BALL_RAIDUS)
    {
        global.ball_vel.y = -global.ball_vel.y;

        float ball_too_far = global.ball_pos.y - BALL_RAIDUS;
        global.ball_pos.y = global.ball_pos.y - 2 * ball_too_far;
    }

    if (global.ball_pos.y > window_height - BALL_RAIDUS)
    {
        global.ball_vel.y = -global.ball_vel.y;

        float ball_too_far = global.ball_pos.y + BALL_RAIDUS - window_height;
        global.ball_pos.y = global.ball_pos.y - 2 * ball_too_far;
    }

    pong_ball_hit_left();
    pong_ball_hit_right(window_width);

    if (global.ball_pos.x < 0)
    {
        global.opponent_score++;
        global.ball_pos.x = 50;
        global.ball_vel.x = -global.ball_vel.x;
    }
    else if (global.ball_pos.x > window_width)
    {
        global.player_score++;
        global.ball_pos.x = window_width - 50;
        global.ball_vel.x = -global.ball_vel.x;
    }
}

void
pong_ball_hit_left()
{
    Rectangle player = pong_left_paddle_rec();
    if (CheckCollisionCircleRec(global.ball_pos, BALL_RAIDUS, player))
    {
        global.ball_vel.x = -global.ball_vel.x;

        // hit top of paddle
        if (global.ball_vel.y > 0 &&
            global.ball_pos.x + global.ball_pos.y <
                global.player_pos + PADDLE_WIDTH + PADDLE_MARGIN)
        {
            global.ball_vel.y = -global.ball_vel.y;

            float delta_verti =
                global.ball_pos.y + BALL_RAIDUS - global.player_pos;
            global.ball_pos.y = global.ball_pos.y - 2 * delta_verti;
        }
        // hit bottom of paddle
        else if (global.ball_vel.y < 0 &&
                 global.ball_pos.y - global.ball_pos.x >
                     global.player_pos + PADDLE_HEIGHT - PADDLE_WIDTH -
                         PADDLE_MARGIN)
        {
            global.ball_vel.y = -global.ball_vel.y;

            float delta_verti = global.player_pos + PADDLE_HEIGHT -
                                (global.ball_pos.y - BALL_RAIDUS);
            global.ball_pos.y = global.ball_pos.y + 2 * delta_verti;
        }
        // hit side of paddle
        else
        {
            float delta_horiz = PADDLE_MARGIN + PADDLE_WIDTH -
                                (global.ball_pos.x - BALL_RAIDUS);
            global.ball_pos.x = global.ball_pos.x + 2 * delta_horiz;
        }
    }
}

void
pong_ball_hit_right(int window_width)
{
    Rectangle opponent = pong_right_paddle_rec(window_width);
    if (CheckCollisionCircleRec(global.ball_pos, BALL_RAIDUS, opponent))
    {
        global.ball_vel.x = -global.ball_vel.x;

        // hit top of paddle
        if (global.ball_vel.y > 0 &&
            global.ball_pos.y - global.ball_pos.x <
                global.opponent_pos -
                    (window_width - PADDLE_MARGIN - PADDLE_WIDTH))
        {
            global.ball_vel.y = -global.ball_vel.y;

            float delta_verti =
                global.ball_pos.y + BALL_RAIDUS - global.opponent_pos;
            global.ball_pos.y = global.ball_pos.y - 2 * delta_verti;
        }
        // hit bottom of paddle
        else if (global.ball_vel.y < 0 &&
                 global.ball_pos.y + global.ball_pos.x >
                     global.opponent_pos + PADDLE_HEIGHT +
                         (window_width - PADDLE_MARGIN - PADDLE_WIDTH))
        {
            global.ball_vel.y = -global.ball_vel.y;

            float delta_verti = global.opponent_pos + PADDLE_HEIGHT -
                                (global.ball_pos.y - BALL_RAIDUS);
            global.ball_pos.y = global.ball_pos.y + 2 * delta_verti;
        }
        // hit side of paddle
        else
        {
            float delta_horiz = global.ball_pos.x + BALL_RAIDUS -
                                (window_width - PADDLE_MARGIN - PADDLE_WIDTH);
            global.ball_pos.x = global.ball_pos.x - 2 * delta_horiz;
        }
    }
}
