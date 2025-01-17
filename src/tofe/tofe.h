#ifndef TOFE_H
#define TOFE_H

#include "../utils/utils.h"
#include <stdbool.h>
#include <stdint.h>
#include "raylib.h"

typedef struct {
    int32_t value;
    bool upgrade;
} TofeTile;

typedef struct {
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
void tofe_upgrade_tiles(void);
bool tofe_is_game_over(void);

void tofe_render_game(void);
void tofe_render_grid(Grid* grid);
void tofe_render_grid_rows(Grid* grid);
void tofe_render_grid_columns(Grid* grid);
void tofe_render_tiles(Grid* grid);
Color tofe_tile_colour(int32_t value);
void tofe_render_game_over(void);

void tofe_handle_input(void);

#endif
