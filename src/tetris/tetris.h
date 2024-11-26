#ifndef TETRIS_H
#define TETRIS_H

#include "raylib.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int8_t x;
    int8_t y;
} TetrisTile;

typedef enum {
    OnTile,
    BetweenTiles,
} TetrisCentreType;

typedef struct {
    int8_t rotation;
    TetrisCentreType centre_type;
    TetrisTile centre;
    TetrisTile tiles[4];
} TetrisPiece;

typedef struct {
    int16_t lines_cleared;
    bool grid[20][10];
    TetrisPiece next_pieces[14];
} TetrisState;

typedef struct {
    int16_t window_width;
    int16_t window_height;
    int16_t grid_border;
    int16_t cell_size;
    int16_t margin_x;
    int16_t margin_y;
} TetrisGridStuff;

void tetris_new_game(void);
void tetris_run_game(void);

void tetris_render_game(void);

void tetris_render_grid(void);
void tetris_render_grid_rows(TetrisGridStuff* grid);
void tetris_render_grid_columns(TetrisGridStuff* grid);

void tetris_render_pieces(void);
void tetris_render_text(void);

#endif
