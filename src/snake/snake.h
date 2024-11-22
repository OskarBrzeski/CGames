#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

#define GRIDWIDTH 4
#define ROWS     12
#define COLUMNS  16
#define MSPERTICK 300

typedef enum {
    UP,
    LEFT,
    DOWN,
    RIGHT,
} Direction;

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
} SnakeGameState;

void snake_new_game(void);
void snake_run_game(void);
void snake_render_game(void);
int snake_cell_size(void);
int snake_margin(void);
void snake_render_grid(void);
void snake_render_cell(GridCell cell, Color color);
void snake_update_pos(void);
void snake_handle_input(void);

#endif
