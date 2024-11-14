#ifndef PONG_H
#define PONG_H

#include "raylib.h"

typedef struct {
    float player_pos;
    float opponent_pos;
    Vector2 ball_pos;
    Vector2 ball_vel;
    int player_score;
    int opponent_score;
} GameState;

void run_pong(void);

void
render_game(int window_width, int window_height);

void
move_opponent(float dt);

Rectangle
player_paddle_to_rec(void);

Rectangle
opponent_paddle_to_rec(int window_width);

void
handle_user_input(int window_height, float dt);

void
update_ball_pos(int window_width, int window_height, float dt);

void
ball_hit_player(void);

void
ball_hit_opponent(int window_width);

#endif
