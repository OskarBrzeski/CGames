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
void render_game(int window_width, int window_height);
void move_opponent(float dt);
Rectangle player_paddle_to_rec();
Rectangle opponent_paddle_to_rec(int window_width);
void handle_user_input(int window_height, float dt);
void update_ball_pos(int window_width, int window_height, float dt);
void ball_hit_player();
void ball_hit_opponent(int window_width);

#endif
