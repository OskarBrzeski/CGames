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
                  {{.value = 0, .upgrade = false},
             {.value = 0, .upgrade = false},
             {.value = 0, .upgrade = false},
             {.value = 0, .upgrade = false}},
                  {{.value = 0, .upgrade = false},
             {.value = 0, .upgrade = false},
             {.value = 0, .upgrade = false},
             {.value = 0, .upgrade = false}},
                  {{.value = 0, .upgrade = false},
             {.value = 0, .upgrade = false},
             {.value = 0, .upgrade = false},
             {.value = 0, .upgrade = false}},
                  {{.value = 0, .upgrade = false},
             {.value = 0, .upgrade = false},
             {.value = 0, .upgrade = false},
             {.value = 0, .upgrade = false}},
                  }
    };
    tofe_spawn_tile();
}

void
tofe_run_game(void)
{
    if (!tofe_is_game_over())
    {
        tofe_handle_input();
        tofe_upgrade_tiles();
    }
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
            if (tofe.tiles[y][x].value == 0)
            {
                indexes[empty_count] = y * 4 + x;
                ++empty_count;
            }
        }
    }

    int pos_rel = GetRandomValue(0, empty_count - 1);
    int pos_true = indexes[pos_rel];

    int16_t value = GetRandomValue(1, 8) == 8 ? 4 : 2;
    tofe.tiles[pos_true / 4][pos_true % 4].value = value;
}

void
tofe_move_up(void)
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 1; y < 4; y++)
        {
            int cy = y;
            while (tofe.tiles[cy - 1][x].value == 0 && cy > 0)
            {
                tofe.tiles[cy - 1][x].value = tofe.tiles[cy][x].value;
                tofe.tiles[cy][x].value = 0;
                --cy;
            }

            if (tofe.tiles[cy - 1][x].upgrade) { continue; }

            if (tofe.tiles[cy][x].value == tofe.tiles[cy - 1][x].value)
            {
                tofe.tiles[cy - 1][x].upgrade = true;
                tofe.tiles[cy][x].value = 0;
            }
        }
    }
    tofe_spawn_tile();
}

void
tofe_move_down(void)
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 2; y >= 0; y--)
        {
            int cy = y;
            while (tofe.tiles[cy + 1][x].value == 0 && cy < 3)
            {
                tofe.tiles[cy + 1][x].value = tofe.tiles[cy][x].value;
                tofe.tiles[cy][x].value = 0;
                ++cy;
            }

            if (tofe.tiles[cy + 1][x].upgrade) { continue; }

            if (tofe.tiles[cy][x].value == tofe.tiles[cy + 1][x].value)
            {
                tofe.tiles[cy + 1][x].upgrade = true;
                tofe.tiles[cy][x].value = 0;
            }
        }
    }
    tofe_spawn_tile();
}

void
tofe_move_left(void)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 1; x < 4; x++)
        {
            int cx = x;
            while (tofe.tiles[y][cx - 1].value == 0 && cx > 0)
            {
                tofe.tiles[y][cx - 1].value = tofe.tiles[y][cx].value;
                tofe.tiles[y][cx].value = 0;
                --cx;
            }

            if (tofe.tiles[y][cx - 1].upgrade) { continue; }

            if (tofe.tiles[y][cx].value == tofe.tiles[y][cx - 1].value)
            {
                tofe.tiles[y][cx - 1].upgrade = true;
                tofe.tiles[y][cx].value = 0;
            }
        }
    }
    tofe_spawn_tile();
}

void
tofe_move_right(void)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 2; x >= 0; x--)
        {
            int cx = x;
            while (tofe.tiles[y][cx + 1].value == 0 && cx < 3)
            {
                tofe.tiles[y][cx + 1].value = tofe.tiles[y][cx].value;
                tofe.tiles[y][cx].value = 0;
                ++cx;
            }

            if (tofe.tiles[y][cx + 1].upgrade) { continue; }

            if (tofe.tiles[y][cx].value == tofe.tiles[y][cx + 1].value)
            {
                tofe.tiles[y][cx + 1].upgrade = true;
                tofe.tiles[y][cx].value = 0;
            }
        }
    }
    tofe_spawn_tile();
}

void
tofe_upgrade_tiles(void)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (tofe.tiles[y][x].upgrade)
            {
                tofe.tiles[y][x].value *= 2;
                tofe.tiles[y][x].upgrade = false;
                tofe.score += tofe.tiles[y][x].value;
            }
        }
    }
}

bool
tofe_is_game_over(void)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (tofe.tiles[y][x].value == 0) { return false; }

            if (y != 3 && tofe.tiles[y][x].value == tofe.tiles[y + 1][x].value)
            {
                return false;
            }

            if (x != 3 && tofe.tiles[y][x].value == tofe.tiles[y][x + 1].value)
            {
                return false;
            }
        }
    }
    return true;
}

void
tofe_render_game(void)
{
    Grid grid = create_grid(4, 4, 4);

    tofe_render_grid(&grid);
    tofe_render_tiles(&grid);

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
            if (tofe.tiles[y][x].value == 0) { continue; }

            Color colour = tofe_tile_colour(tofe.tiles[y][x].value);
            int rx = grid->margin.x + grid->thickness * (x + 1) +
                     grid->cell_size * x;
            int ry = grid->margin.y + grid->thickness * (y + 1) +
                     grid->cell_size * y;
            DrawRectangle(rx, ry, grid->cell_size, grid->cell_size, colour);

            char text[10];
            snprintf(text, 10, "%d", tofe.tiles[y][x].value);
            int text_length = MeasureText(text, 40);

            int xx = grid->margin.x + (grid->thickness + grid->cell_size) * x +
                     grid->thickness + grid->cell_size / 2 - text_length / 2;
            int yy = grid->margin.y + (grid->thickness + grid->cell_size) * y +
                     grid->thickness + grid->cell_size / 2 - 20;
            DrawText(text, xx, yy, 40, WHITE);
        }
    }
}

Color
tofe_tile_colour(int32_t value)
{
    switch (value)
    {
        /*
         * Colors generated via colordesigner.io/gradient-generator
         * {244, 78, 78} -> {197, 31, 219} 13 steps in HSL mode (longer)
         */
    case 2 << 0:  return (Color) {244, 79, 79, 255}; break;
    case 2 << 1:  return (Color) {243, 143, 74, 225}; break;
    case 2 << 2:  return (Color) {241, 209, 70, 255}; break;
    case 2 << 3:  return (Color) {201, 240, 65, 255}; break;
    case 2 << 4:  return (Color) {56, 236, 63, 255}; break;
    case 2 << 5:  return (Color) {52, 235, 133, 255}; break;
    case 2 << 6:  return (Color) {48, 233, 205, 255}; break;
    case 2 << 7:  return (Color) {43, 183, 231, 255}; break;
    case 2 << 8:  return (Color) {39, 103, 229, 255}; break;
    case 2 << 9:  return (Color) {48, 35, 227, 255}; break;
    case 2 << 10: return (Color) {123, 31, 225, 255}; break;
    case 2 << 11: return (Color) {197, 31, 219, 255}; break;
    default:      return BLACK; break;
    }
}

void
tofe_render_game_over(void)
{
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    DrawRectangle(0, 0, width, height, (Color) {0, 0, 0, 200});

    int text_width = MeasureText("Game Over", 48);
    DrawText("Game Over", (width - text_width) / 2, (height - 48) / 2, 48,
             WHITE);

    char score[24];
    snprintf(score, 24, "Score: %d", tofe.score);
    int score_width = MeasureText(score, 30);
    DrawText(score, (width - score_width) / 2, (height + 110) / 2, 30, WHITE);
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
