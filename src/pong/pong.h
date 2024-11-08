#ifndef PONG_H
#define PONG_H

#include "raylib.h"

void
render_game();

Rectangle
player_paddle_to_rec();

Rectangle
opponent_paddle_to_rec(int window_width);

void
handle_user_input(int window_height, float dt);

void
update_ball_pos(int window_width, int window_height, float dt);

void
handle_FPS_toggle();

#endif
