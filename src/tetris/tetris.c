#include "tetris.h"

#include "raylib.h"

#include <stdbool.h>
#include <stdint.h>

TetrisState tetris = {};

void
tetris_new_game(void)
{
    tetris = (TetrisState) {
        .grid = (bool) {},
        .next_pieces = (TetrisPiece) {},
    };
}

void
tetris_run_game(void)
{
    tetris_render_game();
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
tetris_render_pieces(void)
{
}

void
tetris_render_text(void)
{
}
