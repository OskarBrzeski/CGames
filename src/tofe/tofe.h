#ifndef TOEF_H
#define TOFE_H

#include "../utils/utils.h"
#include <stdbool.h>
#include <stdint.h>
#include "raylib.h"

typedef struct {
    int16_t tiles[4][4];
    int32_t score;
} TofeGameState;

void tofe_new_game(void);
void tofe_run_game(void);

void tofe_spawn_tile(void);
void tofe_move_up(void);
void tofe_move_down(void);
void tofe_move_left(void);
void tofe_move_right(void);
bool tofe_is_game_over(void);

void tofe_render_game(void);
void tofe_render_grid(Grid* grid);
void tofe_render_grid_rows(Grid* grid);
void tofe_render_grid_columns(Grid* grid);
void tofe_render_tiles(Grid* grid);
void tofe_render_score(Grid* grid);
void tofe_render_game_over(void);

void tofe_handle_input(void);
#endif
