#include "tofe.h"

#include "raylib.h"

#define ANIM_TIME 0.3

TofeGameState tofe = {};

void
tofe_new_game(void)
{
    tofe = (TofeGameState) {
        .animation = false,
        .anim_count = 0,
        .animations = {{0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0}},
        .time = 0.0,
        .score = 0,
        .tiles =
            {
                       {{.value = 0, .upgrade = false, .animate = false},
                 {.value = 0, .upgrade = false, .animate = false},
                 {.value = 0, .upgrade = false, .animate = false},
                 {.value = 0, .upgrade = false, .animate = false}},
                       {{.value = 0, .upgrade = false, .animate = false},
                 {.value = 0, .upgrade = false, .animate = false},
                 {.value = 0, .upgrade = false, .animate = false},
                 {.value = 0, .upgrade = false, .animate = false}},
                       {{.value = 0, .upgrade = false, .animate = false},
                 {.value = 0, .upgrade = false, .animate = false},
                 {.value = 0, .upgrade = false, .animate = false},
                 {.value = 0, .upgrade = false, .animate = false}},
                       {{.value = 0, .upgrade = false, .animate = false},
                 {.value = 0, .upgrade = false, .animate = false},
                 {.value = 0, .upgrade = false, .animate = false},
                 {.value = 0, .upgrade = false, .animate = false}},
                       },
    };
    tofe_spawn_tile();
    tofe_clear_anims();
}

void
tofe_run_game(void)
{
    if (!tofe_is_game_over())
    {
        if (!tofe.animation)
        {
            tofe_handle_input();
            tofe_upgrade_tiles();
        }
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
    tofe.tiles[pos_true / 4][pos_true % 4].animate = true;
}

void
tofe_move_up(void)
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 1; y < 4; y++)
        {
            if (tofe.tiles[y][x].value == 0) { continue; }

            int curr_y = y;
            while (curr_y > 0 && tofe.tiles[curr_y - 1][x].value == 0)
            {
                tofe.tiles[curr_y - 1][x].value = tofe.tiles[curr_y][x].value;
                tofe.tiles[curr_y][x].value = 0;
                --curr_y;
            }

            if (curr_y == 0 || tofe.tiles[curr_y - 1][x].upgrade)
            {
                tofe_append_anim(x, y, x, curr_y, tofe.tiles[curr_y][x].value);
                tofe.tiles[curr_y][x].animate = true;
            }
            else if (tofe.tiles[curr_y][x].value ==
                     tofe.tiles[curr_y - 1][x].value)
            {
                tofe.tiles[curr_y - 1][x].upgrade = true;
                tofe.tiles[curr_y][x].value = 0;
                tofe_append_anim(x, y, x, curr_y - 1,
                                 tofe.tiles[curr_y - 1][x].value);
                tofe.tiles[curr_y - 1][x].animate = true;
            }
            else
            {
                tofe_append_anim(x, y, x, curr_y, tofe.tiles[curr_y][x].value);
                tofe.tiles[curr_y][x].animate = true;
            }
        }
    }
    tofe.animation = true;
    tofe_spawn_tile();
}

void
tofe_move_down(void)
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 2; y >= 0; y--)
        {
            if (tofe.tiles[y][x].value == 0) { continue; }

            int curr_y = y;
            while (tofe.tiles[curr_y + 1][x].value == 0 && curr_y < 3)
            {
                tofe.tiles[curr_y + 1][x].value = tofe.tiles[curr_y][x].value;
                tofe.tiles[curr_y][x].value = 0;
                ++curr_y;
            }

            if (curr_y == 3 || tofe.tiles[curr_y + 1][x].upgrade)
            {
                tofe_append_anim(x, y, x, curr_y, tofe.tiles[curr_y][x].value);
                tofe.tiles[curr_y][x].animate = true;
            }

            else if (tofe.tiles[curr_y][x].value ==
                     tofe.tiles[curr_y + 1][x].value)
            {
                tofe.tiles[curr_y + 1][x].upgrade = true;
                tofe.tiles[curr_y][x].value = 0;
                tofe_append_anim(x, y, x, curr_y + 1,
                                 tofe.tiles[curr_y + 1][x].value);
                tofe.tiles[curr_y + 1][x].animate = true;
            }
            else
            {
                tofe_append_anim(x, y, x, curr_y, tofe.tiles[curr_y][x].value);
                tofe.tiles[curr_y][x].animate = true;
            }
        }
    }
    tofe.animation = true;
    tofe_spawn_tile();
}

void
tofe_move_left(void)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 1; x < 4; x++)
        {
            if (tofe.tiles[y][x].value == 0) { continue; }

            int curr_x = x;
            while (curr_x > 0 && tofe.tiles[y][curr_x - 1].value == 0)
            {
                tofe.tiles[y][curr_x - 1].value = tofe.tiles[y][curr_x].value;
                tofe.tiles[y][curr_x].value = 0;
                --curr_x;
            }

            if (curr_x == 0 || tofe.tiles[y][curr_x - 1].upgrade)
            {

                tofe_append_anim(x, y, curr_x, y, tofe.tiles[y][curr_x].value);
                tofe.tiles[y][curr_x].animate = true;
            }
            else if (tofe.tiles[y][curr_x].value ==
                     tofe.tiles[y][curr_x - 1].value)
            {
                tofe.tiles[y][curr_x - 1].upgrade = true;
                tofe.tiles[y][curr_x].value = 0;
                tofe_append_anim(x, y, curr_x - 1, y,
                                 tofe.tiles[y][curr_x - 1].value);
                tofe.tiles[y][curr_x - 1].animate = true;
            }
            else
            {
                tofe_append_anim(x, y, curr_x, y, tofe.tiles[y][curr_x].value);
                tofe.tiles[y][curr_x].animate = true;
            }
        }
    }
    tofe.animation = true;
    tofe_spawn_tile();
}

void
tofe_move_right(void)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 2; x >= 0; x--)
        {
            if (tofe.tiles[y][x].value == 0) { continue; }

            int curr_x = x;
            while (curr_x < 3 && tofe.tiles[y][curr_x + 1].value == 0)
            {
                tofe.tiles[y][curr_x + 1].value = tofe.tiles[y][curr_x].value;
                tofe.tiles[y][curr_x].value = 0;
                ++curr_x;
            }

            if (curr_x == 3 || tofe.tiles[y][curr_x + 1].upgrade)
            {
                tofe_append_anim(x, y, curr_x, y, tofe.tiles[y][curr_x].value);
                tofe.tiles[y][curr_x].animate = true;
            }
            else if (tofe.tiles[y][curr_x].value ==
                     tofe.tiles[y][curr_x + 1].value)
            {
                tofe.tiles[y][curr_x + 1].upgrade = true;
                tofe.tiles[y][curr_x].value = 0;
                tofe_append_anim(x, y, curr_x + 1, y,
                                 tofe.tiles[y][curr_x + 1].value);
                tofe.tiles[y][curr_x + 1].animate = true;
            }
            else
            {
                tofe_append_anim(x, y, curr_x, y, tofe.tiles[y][curr_x].value);
                tofe.tiles[y][curr_x].animate = true;
            }
        }
    }
    tofe.animation = true;
    tofe_spawn_tile();
}

void
tofe_append_anim(int8_t sx, int8_t sy, int8_t ex, int8_t ey, int32_t v)
{
    TofeAnimation* anim = &tofe.animations[tofe.anim_count];
    anim->startx = sx;
    anim->starty = sy;
    anim->endx = ex;
    anim->endy = ey;
    anim->value = v;
    ++tofe.anim_count;
}

void
tofe_clear_anims(void)
{
    for (int i = 0; i < tofe.anim_count; i++)
    {
        TofeAnimation* anim = &tofe.animations[i];
        anim->startx = 0;
        anim->starty = 0;
        anim->endx = 0;
        anim->endy = 0;
        anim->value = 0;
    }
    tofe.anim_count = 0;

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++) { tofe.tiles[y][x].animate = false; }
    }
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

    if (tofe.animation)
    {
        float dt = GetFrameTime();
        tofe.time += dt;

        if (tofe.time > ANIM_TIME)
        {
            tofe_clear_anims();
            tofe.animation = false;
            tofe.time = 0;
            tofe_render_tiles(&grid);
        }
        else
        {
            for (int i = 0; i < tofe.anim_count; i++)
            {
                tofe_render_anim(&grid, &tofe.animations[i]);
            }
        }
    }

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
            if (tofe.tiles[y][x].animate) { continue; }
            if (tofe.tiles[y][x].value == 0) { continue; }

            int32_t value = tofe.tiles[y][x].value;
            TofeCoords coords = tofe_tile_coords(grid, x, y);
            tofe_render_tile(grid, coords, value);

            char text[10];
            snprintf(text, 10, "%d", tofe.tiles[y][x].value);
            int text_width = MeasureText(text, 40);

            TofeCoords tcoords = tofe_text_coords(grid, x, y, text_width);
            tofe_render_text(grid, tcoords, text);
        }
    }
}

void
tofe_render_tile(Grid* grid, TofeCoords coords, int32_t value)
{
    DrawRectangle(coords.x, coords.y, grid->cell_size, grid->cell_size,
                  tofe_tile_colour(value));
}

TofeCoords
tofe_tile_coords(Grid* grid, int8_t x, int8_t y)
{
    int pixel_x = grid->margin.x + grid->thickness +
                  x * (grid->thickness + grid->cell_size);
    int pixel_y = grid->margin.y + grid->thickness +
                  y * (grid->thickness + grid->cell_size);

    return (TofeCoords) {.x = pixel_x, .y = pixel_y};
}

void
tofe_render_text(Grid* grid, TofeCoords coords, char* text)
{
    DrawText(text, coords.x, coords.y, 40, WHITE);
}

TofeCoords
tofe_text_coords(Grid* grid, int8_t x, int8_t y, int32_t text_width)
{
    int text_x = grid->margin.x + grid->thickness +
                 x * (grid->thickness + grid->cell_size) + grid->cell_size / 2 -
                 text_width / 2;
    int text_y = grid->margin.y + grid->thickness +
                 y * (grid->thickness + grid->cell_size) + grid->cell_size / 2 -
                 20;
    return (TofeCoords) {.x = text_x, .y = text_y};
}

void
tofe_render_anim(Grid* grid, TofeAnimation* anim)
{
    for (int i = 0; i < tofe.anim_count; i++)
    {
        TofeAnimation anim = tofe.animations[i];

        TofeCoords start = tofe_tile_coords(grid, anim.startx, anim.starty);
        TofeCoords end = tofe_tile_coords(grid, anim.endx, anim.endy);
        float interp_x = (end.x - start.x) * tofe.time / ANIM_TIME + start.x;
        float interp_y = (end.y - start.y) * tofe.time / ANIM_TIME + start.y;
        TofeCoords final = {.x = interp_x, .y = interp_y};
        tofe_render_tile(grid, final, anim.value);

        char text[10];
        snprintf(text, 10, "%d", anim.value);
        int text_width = MeasureText(text, 40);

        TofeCoords tstart =
            tofe_text_coords(grid, anim.startx, anim.starty, text_width);
        TofeCoords tend =
            tofe_text_coords(grid, anim.endx, anim.endy, text_width);
        float tinterp_x =
            (tend.x - tstart.x) * tofe.time / ANIM_TIME + tstart.x;
        float tinterp_y =
            (tend.y - tstart.y) * tofe.time / ANIM_TIME + tstart.y;
        TofeCoords tfinal = {.x = tinterp_x, .y = tinterp_y};
        tofe_render_text(grid, tfinal, text);
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
