#ifndef TETRIS_H
#define TETRIS_H

#include "raylib.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    I = 1,
    O,
    T,
    S,
    Z,
    L,
    J,
} TetrisPieceType;

typedef struct {
    int8_t head;
    int8_t tail;
    TetrisPieceType values[14];
} TetrisQueue;

void tetris_queue_append(TetrisQueue* queue, TetrisPieceType type);
TetrisPieceType tetris_queue_pop(TetrisQueue* queue);
TetrisPieceType tetris_queue_peek(TetrisQueue* queue, int8_t offset);
int8_t tetris_queue_length(TetrisQueue* queue);

typedef struct {
    int8_t x;
    int8_t y;
} TetrisTile;

typedef struct {
    int8_t rotation;
    TetrisPieceType type;
    TetrisTile position;
    TetrisTile tiles[4][4];
} TetrisPiece;

typedef struct {
    int16_t lines_cleared;
    int8_t current_index;
    float time;
    TetrisPiece current_piece;
    TetrisQueue next_pieces;
    TetrisPieceType grid[20][10];
} TetrisState;

void tetris_piece_batch(void);
void tetris_next_piece(void);
void tetris_new_game(void);
TetrisPiece tetris_piece(TetrisPieceType type);

void tetris_run_game(void);

void tetris_place_piece(void);
bool tetris_valid_position(void);
void tetris_clear_line(void);
void tetris_shift_lines(int8_t line);

typedef struct {
    int16_t window_width;
    int16_t window_height;
    int16_t grid_border;
    int16_t cell_size;
    int16_t margin_x;
    int16_t margin_y;
} TetrisGridStuff;

void tetris_render_game(void);
void tetris_render_grid(void);
void tetris_render_grid_rows(TetrisGridStuff* grid);
void tetris_render_grid_columns(TetrisGridStuff* grid);
void tetris_render_pieces(TetrisGridStuff* grid);
void tetris_render_tiles(TetrisGridStuff* grid);
Color tetris_colour(TetrisPieceType type);
void tetris_render_text(TetrisGridStuff* grid);

void tetris_handle_input(void);
#endif
