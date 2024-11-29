#include "tetris.h"

#include "raylib.h"

#include <stdbool.h>
#include <stdint.h>

TetrisState tetris = {};

void
tetris_new_game(void)
{
    tetris = (TetrisState) {
        .lines_cleared = 0,
        .current_index = 0,
        .current_piece = tetris_piece(T),
        .grid = {},
        .next_pieces = {},
    };
}

void
tetris_run_game(void)
{
    tetris_handle_input();
    tetris_render_game();
}

TetrisPiece
tetris_piece(TetrisPieceType type)
{
    switch (type)
    {
    case I:
        return (TetrisPiece) {
            .position = {.x = 3, .y = -2},
            .tiles = {
                         {{.x = 0, .y = 1},
                 {.x = 1, .y = 1},
                 {.x = 2, .y = 1},
                 {.x = 3, .y = 1}},
                         {{.x = 2, .y = 0},
                 {.x = 2, .y = 1},
                 {.x = 2, .y = 2},
                 {.x = 2, .y = 3}},
                         {{.x = 0, .y = 2},
                 {.x = 1, .y = 2},
                 {.x = 2, .y = 2},
                 {.x = 3, .y = 2}},
                         {{.x = 1, .y = 0},
                 {.x = 1, .y = 1},
                 {.x = 1, .y = 2},
                 {.x = 1, .y = 3}},
                         }
        };
    case O:
        return (TetrisPiece) {
            .position = {.x = 3, .y = -3},
            .tiles = {
                         {{.x = 1, .y = 1},
                 {.x = 1, .y = 2},
                 {.x = 2, .y = 1},
                 {.x = 2, .y = 2}},
                         {{.x = 1, .y = 1},
                 {.x = 1, .y = 2},
                 {.x = 2, .y = 1},
                 {.x = 2, .y = 2}},
                         {{.x = 1, .y = 1},
                 {.x = 1, .y = 2},
                 {.x = 2, .y = 1},
                 {.x = 2, .y = 2}},
                         {{.x = 1, .y = 1},
                 {.x = 1, .y = 2},
                 {.x = 2, .y = 1},
                 {.x = 2, .y = 2}},
                         }
        };
    case T:
        return (TetrisPiece) {
            .position = {.x = 3, .y = -2},
            .tiles = {
                         {{.x = 1, .y = 0},
                 {.x = 0, .y = 1},
                 {.x = 1, .y = 1},
                 {.x = 2, .y = 1}},
                         {{.x = 1, .y = 0},
                 {.x = 1, .y = 1},
                 {.x = 2, .y = 1},
                 {.x = 1, .y = 2}},
                         {{.x = 0, .y = 1},
                 {.x = 1, .y = 1},
                 {.x = 2, .y = 1},
                 {.x = 1, .y = 2}},
                         {{.x = 1, .y = 0},
                 {.x = 0, .y = 1},
                 {.x = 1, .y = 1},
                 {.x = 1, .y = 2}},
                         }
        };
    case S:
        return (TetrisPiece) {
            .position = {.x = 3, .y = -2},
            .tiles = {
                         {{.x = 1, .y = 0},
                 {.x = 2, .y = 0},
                 {.x = 0, .y = 1},
                 {.x = 1, .y = 1}},
                         {{.x = 1, .y = 0},
                 {.x = 1, .y = 1},
                 {.x = 2, .y = 1},
                 {.x = 2, .y = 2}},
                         {{.x = 1, .y = 1},
                 {.x = 2, .y = 1},
                 {.x = 0, .y = 2},
                 {.x = 1, .y = 2}},
                         {{.x = 0, .y = 0},
                 {.x = 0, .y = 1},
                 {.x = 1, .y = 1},
                 {.x = 1, .y = 2}},
                         }
        };
    case Z:
        return (TetrisPiece) {
            .position = {.x = 3, .y = -2},
            .tiles = {
                         {{.x = 0, .y = 0},
                 {.x = 1, .y = 0},
                 {.x = 1, .y = 1},
                 {.x = 2, .y = 1}},
                         {{.x = 2, .y = 0},
                 {.x = 1, .y = 1},
                 {.x = 2, .y = 1},
                 {.x = 1, .y = 2}},
                         {{.x = 0, .y = 1},
                 {.x = 1, .y = 1},
                 {.x = 1, .y = 2},
                 {.x = 2, .y = 2}},
                         {{.x = 1, .y = 0},
                 {.x = 0, .y = 1},
                 {.x = 1, .y = 1},
                 {.x = 0, .y = 2}},
                         }
        };
    case L:
        return (TetrisPiece) {
            .position = {.x = 3, .y = -2},
            .tiles = {
                         {{.x = 2, .y = 0},
                 {.x = 0, .y = 1},
                 {.x = 1, .y = 1},
                 {.x = 1, .y = 2}},
                         {{.x = 1, .y = 0},
                 {.x = 1, .y = 1},
                 {.x = 1, .y = 2},
                 {.x = 2, .y = 2}},
                         {{.x = 0, .y = 1},
                 {.x = 1, .y = 1},
                 {.x = 2, .y = 1},
                 {.x = 0, .y = 2}},
                         {{.x = 0, .y = 0},
                 {.x = 1, .y = 0},
                 {.x = 1, .y = 1},
                 {.x = 1, .y = 2}},
                         }
        };
    case J:
        return (TetrisPiece) {
            .position = {.x = 3, .y = -2},
            .tiles = {
                         {{.x = 0, .y = 0},
                 {.x = 0, .y = 1},
                 {.x = 1, .y = 1},
                 {.x = 2, .y = 1}},
                         {{.x = 1, .y = 0},
                 {.x = 2, .y = 0},
                 {.x = 1, .y = 1},
                 {.x = 1, .y = 2}},
                         {{.x = 0, .y = 1},
                 {.x = 1, .y = 1},
                 {.x = 2, .y = 1},
                 {.x = 2, .y = 2}},
                         {{.x = 1, .y = 0},
                 {.x = 1, .y = 1},
                 {.x = 0, .y = 2},
                 {.x = 1, .y = 2}},
                         }
        };
    }
}

void
tetris_render_game(void)
{
    tetris_render_grid();
}

void
tetris_render_grid(void)
{
    TetrisGridStuff grid = {};

    grid.window_width = GetScreenWidth();
    grid.window_height = GetScreenHeight();
    grid.grid_border = 2;
    grid.cell_size = (grid.window_height - 21 * grid.grid_border) / 20;
    grid.margin_x =
        (grid.window_width - 11 * grid.grid_border - 10 * grid.cell_size) / 2;
    grid.margin_y =
        (grid.window_height - 21 * grid.grid_border - 20 * grid.cell_size) / 2;

    tetris_render_grid_rows(&grid);
    tetris_render_grid_columns(&grid);
    tetris_render_pieces(&grid, T);
}

void
tetris_render_grid_rows(TetrisGridStuff* grid)
{
    int16_t width = 11 * grid->grid_border + 10 * grid->cell_size;
    for (int i = 0; i < 21; i++)
    {
        int16_t y =
            grid->margin_y + i * grid->grid_border + i * grid->cell_size;
        DrawRectangle(grid->margin_x, y, width, grid->grid_border, WHITE);
    }
}

void
tetris_render_grid_columns(TetrisGridStuff* grid)
{
    int16_t height = 21 * grid->grid_border + 20 * grid->cell_size;
    for (int i = 0; i < 11; i++)
    {
        int16_t x =
            grid->margin_x + i * grid->grid_border + i * grid->cell_size;
        DrawRectangle(x, grid->margin_y, grid->grid_border, height, WHITE);
    }
}

void
tetris_render_pieces(TetrisGridStuff* grid, TetrisPieceType type)
{
    TetrisPiece* piece = &tetris.current_piece;

    for (int i = 0; i < 4; i++)
    {
        int offset = grid->cell_size + grid->grid_border;
        int x =
            grid->margin_x + grid->grid_border +
            offset * (piece->position.x + piece->tiles[piece->rotation][i].x);
        int y =
            grid->margin_y + grid->grid_border +
            offset * (piece->position.y + piece->tiles[piece->rotation][i].y);

        DrawRectangle(x, y, grid->cell_size, grid->cell_size,
                      tetris_colour(type));
    }
}

Color
tetris_colour(TetrisPieceType type)
{
    switch (type)
    {
    case I: return BLUE;
    case O: return YELLOW;
    case T: return PURPLE;
    case S: return GREEN;
    case Z: return RED;
    case L: return ORANGE;
    case J: return DARKBLUE;
    }
}

void
tetris_render_text(TetrisGridStuff* grid)
{
}

void
tetris_handle_input(void)
{
    int key;
    do {
        key = GetKeyPressed();

        switch (key)
        {
        case KEY_X:
            tetris.current_piece.rotation =
                (tetris.current_piece.rotation + 1) % 4;
            break;
        case KEY_Z:
            tetris.current_piece.rotation =
                ((tetris.current_piece.rotation - 1) % 4 + 4) % 4;
            break;
        case KEY_LEFT:  --tetris.current_piece.position.x; break;
        case KEY_RIGHT: ++tetris.current_piece.position.x; break;
        case KEY_DOWN:  ++tetris.current_piece.position.y;
        }
    }
    while (key != 0);
}
