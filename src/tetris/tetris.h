#ifndef TETRIS_H
#define TETRIS_H

#include "raylib.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    I,
    O,
    T,
    S,
    Z,
    L,
    J,
} TetrisPieceType;

typedef enum {
    THREE,
    FOUR,
} TetrisSize;

typedef struct {
    int8_t x;
    int8_t y;
} TetrisTile;

typedef struct {
    int8_t rotation;
    TetrisTile position;
    TetrisTile tiles[4][4];
} TetrisPiece;

typedef struct {
    int16_t lines_cleared;
    int8_t current_index;
    TetrisPiece current_piece;
    TetrisPieceType grid[20][10];
    TetrisPieceType next_pieces[14];
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

TetrisPiece tetris_piece(TetrisPieceType type);

void tetris_render_game(void);

void tetris_render_grid(void);
void tetris_render_grid_rows(TetrisGridStuff* grid);
void tetris_render_grid_columns(TetrisGridStuff* grid);
void tetris_render_pieces(TetrisGridStuff* grid, TetrisPieceType type);
Color tetris_colour(TetrisPieceType type);
void tetris_render_text(TetrisGridStuff* grid);

void tetris_handle_input(void);
#endif
