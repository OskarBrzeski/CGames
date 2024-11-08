#include "pong.h"

#include "raylib.h"

#define PLAYER_HEIGHT 60
#define PLAYER_WIDTH  10
#define BALL_RAIDUS   8.0

typedef struct {
    int player_pos;
    int opponent_pos;
    Vector2 ball_pos;
    Vector2 ball_vel;
} Objects;

Objects global = {
    0, 0, {50, 50},
      { 0,  0}
};

void
render_game(int window_width, int window_height)
{
    DrawRectangle(10, global.player_pos, PLAYER_WIDTH, PLAYER_HEIGHT, WHITE);
    DrawRectangle(window_width - PLAYER_WIDTH - 10, global.opponent_pos,
                  PLAYER_WIDTH, PLAYER_HEIGHT, WHITE);
    DrawCircle(global.ball_pos.x, global.ball_pos.y, BALL_RAIDUS, WHITE);
}
