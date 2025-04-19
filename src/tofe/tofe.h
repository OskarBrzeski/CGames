#ifndef TOFE_H
#define TOFE_H

#include "../utils/utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "raylib.h"

typedef struct {
    int x;
    int y;
} TofeCoords;

typedef struct {
    int32_t value;
    bool upgrade;
    bool animate;
} TofeTile;

typedef struct {
    int8_t startx;
    int8_t starty;
    int8_t endx;
    int8_t endy;
    int32_t value;
} TofeAnimation;

typedef struct {
    bool animation;
    int8_t anim_count;
    TofeAnimation animations[16];
    float time;
    int32_t score;
    TofeTile tiles[4][4];
} TofeGameState;

void tofe_new_game(void);
void tofe_run_game(void);

void tofe_spawn_tile(void);
void tofe_move_up(void);
void tofe_move_down(void);
void tofe_move_left(void);
void tofe_move_right(void);
void tofe_append_anim(int8_t sx, int8_t sy, int8_t ex, int8_t ey, int32_t v);
void tofe_clear_anims(void);
void tofe_upgrade_tiles(void);
bool tofe_is_game_over(void);

void tofe_render_game(void);
void tofe_render_grid(Grid* grid);
void tofe_render_grid_rows(Grid* grid);
void tofe_render_grid_columns(Grid* grid);
void tofe_render_tiles(Grid* grid);
void tofe_render_tile(Grid* grid, TofeCoords coords, int32_t value);
TofeCoords tofe_tile_coords(Grid* grid, int8_t x, int8_t y);
void tofe_render_text(Grid* grid, TofeCoords coords, char* text);
TofeCoords tofe_text_coords(Grid* grid, int8_t x, int8_t y, int32_t text_width);
void tofe_render_anim(Grid* grid, TofeAnimation* anim);
Color tofe_tile_colour(int32_t value);
void tofe_render_game_over(void);

void tofe_handle_input(void);

#endif
