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
    G,
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
    bool game_over;
    int16_t lines_cleared;
    int32_t score;
    int8_t current_index;
    float time;
    TetrisPiece current_piece;
    TetrisPieceType hold;
    TetrisQueue next_pieces;
    TetrisPieceType grid[20][10];
} TetrisState;

void tetris_piece_batch(void);
void tetris_next_piece(void);
void tetris_new_game(void);
TetrisPiece tetris_piece(TetrisPieceType type);

void tetris_run_game(void);

void tetris_place_piece(void);
bool tetris_valid_position(TetrisPiece* piece);
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
void tetris_render_piece(TetrisGridStuff* grid, TetrisPiece* piece);
void tetris_render_tiles(TetrisGridStuff* grid);
void tetris_render_ghost(TetrisGridStuff* grid);
void tetris_render_hold(TetrisGridStuff* grid);
void tetris_render_next(TetrisGridStuff* grid);
void tetris_render_small_piece(int16_t x, int16_t y, int16_t cell_size, TetrisTile tiles[4], TetrisPieceType type);
Color tetris_colour(TetrisPieceType type);
void tetris_render_text(TetrisGridStuff* grid);
void tetris_render_cleared(TetrisGridStuff* grid);
void tetris_render_score(TetrisGridStuff* grid);
void tetris_render_game_over(void);

void tetris_handle_input(void);
#endif
