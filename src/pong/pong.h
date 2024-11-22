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
} PongGameState;

void pong_new_game(void);
void pong_run_game();
void pong_render_game(int window_width, int window_height);
void pong_move_opponent(float dt);
Rectangle pong_player_paddle_to_rec();
Rectangle pong_opponent_paddle_to_rec(int window_width);
void pong_handle_user_input(int window_height, float dt);
void pong_update_ball_pos(int window_width, int window_height, float dt);
void pong_ball_hit_player();
void pong_ball_hit_opponent(int window_width);

#endif
