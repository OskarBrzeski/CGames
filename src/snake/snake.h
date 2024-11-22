#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

#define GRIDWIDTH 4
#define ROWS     12
#define COLUMNS  16
#define MSPERTICK 200

typedef enum {
    UP,
    LEFT,
    DOWN,
    RIGHT,
} Direction;

typedef enum {
    PLAYING,
    LOSE,
    WIN,
} PlayStatus;

typedef struct {
    int x;
    int y;
} GridCell;

typedef struct {
    GridCell snake_body[ROWS * COLUMNS];
    int snake_length;
    GridCell fruit;
    Direction direction;
    Direction desired;
    float time;
    PlayStatus game_over;
} SnakeGameState;

void snake_new_game(void);
void snake_run_game(void);
void snake_render_game(void);
int snake_cell_size(void);
int snake_margin(void);
void snake_render_grid(void);
void snake_render_cell(GridCell cell, Color color);
void snake_render_game_over(void);
void snake_update_pos(void);
void snake_handle_input(void);
int snake_cell_equal(GridCell c1, GridCell c2);
void snake_new_fruit(void);
void snake_grid_arr(int* grid);
PlayStatus snake_is_game_over(void);

#endif
