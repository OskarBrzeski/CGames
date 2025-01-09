#include "tofe.h"

#include "../utils/utils.h"
#include "raylib.h"

#include <stdbool.h>
#include <stdio.h>

TofeGameState tofe = {};

void
tofe_new_game(void)
{
    tofe = (TofeGameState) {
        .score = 0,
        .tiles = {
                  {0, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0},
                  }
    };
    tofe_spawn_tile();
}

void
tofe_run_game(void)
{
    if (!tofe_is_game_over()) { tofe_handle_input(); }
    tofe_render_game();
}

void
tofe_spawn_tile(void)
{
    int empty_count = 0;
    int indexes[16] = {};
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (tofe.tiles[y][x] == 0)
            {
                indexes[empty_count] = y * 4 + x;
                ++empty_count;
            }
        }
    }

    int pos_rel = GetRandomValue(0, empty_count - 1);
    int pos_true = indexes[pos_rel];

    int16_t value = GetRandomValue(1, 8) == 8 ? 4 : 2;
    tofe.tiles[pos_true / 4][pos_true % 4] = value;
}

void
tofe_move_up(void)
{
    tofe_spawn_tile();
}

void
tofe_move_down(void)
{
}

void
tofe_move_left(void)
{
}

void
tofe_move_right(void)
{
}

bool
tofe_is_game_over(void)
{
    return false;
}

void
tofe_render_game(void)
{
    Grid grid = create_grid(4, 4, 4);

    tofe_render_grid(&grid);
    tofe_render_tiles(&grid);
    tofe_render_score(&grid);

    if (tofe_is_game_over()) { tofe_render_game_over(); }
}

void
tofe_render_grid(Grid* grid)
{
    tofe_render_grid_rows(grid);
    tofe_render_grid_columns(grid);
}

void
tofe_render_grid_rows(Grid* grid)
{
    for (int i = 0; i < 5; i++)
    {
        Rectangle row = {.x = grid->margin.x,
                         .y = grid->margin.y +
                              (grid->cell_size + grid->thickness) * i,
                         .width = grid->thickness * 5 + grid->cell_size * 4,
                         .height = grid->thickness};
        DrawRectangleRec(row, WHITE);
    }
}

void
tofe_render_grid_columns(Grid* grid)
{
    for (int i = 0; i < 5; i++)
    {
        Rectangle column = {
            .x = grid->margin.x + (grid->cell_size + grid->thickness) * i,
            .y = grid->margin.y,
            .width = grid->thickness,
            .height = grid->thickness * 5 + grid->cell_size * 4};
        DrawRectangleRec(column, WHITE);
    }
}

void
tofe_render_tiles(Grid* grid)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (tofe.tiles[y][x] == 0) { continue; }

            char text[10];
            snprintf(text, 10, "%d", tofe.tiles[y][x]);
            int text_length = MeasureText(text, 40);

            int xx = grid->margin.x + (grid->thickness + grid->cell_size) * x +
                     grid->thickness + grid->cell_size / 2 - text_length / 2;
            int yy = grid->margin.y + (grid->thickness + grid->cell_size) * y +
                     grid->thickness + grid->cell_size / 2 - 20;
            DrawText(text, xx, yy, 40, WHITE);
        }
    }
}

void
tofe_render_score(Grid* grid)
{
}

void
tofe_render_game_over(void)
{
}

void
tofe_handle_input(void)
{
    int key;
    do {
        key = GetKeyPressed();

        switch (key)
        {
        case KEY_UP:    tofe_move_up(); break;
        case KEY_DOWN:  tofe_move_down(); break;
        case KEY_LEFT:  tofe_move_left(); break;
        case KEY_RIGHT: tofe_move_right(); break;
        }
    }
    while (key > 0);
}
