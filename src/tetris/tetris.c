#include "tetris.h"

#include "raylib.h"

#include <stdbool.h>
#include <stdint.h>

TetrisState tetris = {};

void
tetris_queue_append(TetrisQueue* queue, TetrisPieceType type)
{
    queue->values[queue->head] = type;
    queue->head = (queue->head + 1) % 14;
}

TetrisPieceType
tetris_queue_pop(TetrisQueue* queue)
{
    TetrisPieceType value = tetris_queue_peek(queue, 0);
    queue->tail = (queue->tail + 1) % 14;
    return value;
}

TetrisPieceType
tetris_queue_peek(TetrisQueue* queue, int8_t offset)
{
    return queue->values[(queue->tail + offset) % 14];
}

int8_t
tetris_queue_length(TetrisQueue* queue)
{
    return ((queue->head - queue->tail) % 14 + 14) % 14;
}

void
tetris_new_game(void)
{
    tetris = (TetrisState) {
        .lines_cleared = 0,
        .current_index = 0,
        .time = 0.0,
        .current_piece = {},
        .grid = {},
        .next_pieces = {.head = 0, .tail = 0, .values = {}},
    };

    tetris_piece_batch();
    tetris_next_piece();
}

void
tetris_run_game(void)
{
    tetris_piece_batch();
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
            .rotation = 0,
            .type = I,
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
            .rotation = 0,
            .type = O,
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
            .rotation = 0,
            .type = T,
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
            .rotation = 0,
            .type = S,
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
            .rotation = 0,
            .type = Z,
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
            .rotation = 0,
            .type = L,
            .position = {.x = 3, .y = -2},
            .tiles = {
                         {{.x = 2, .y = 0},
                 {.x = 0, .y = 1},
                 {.x = 1, .y = 1},
                 {.x = 2, .y = 1}},
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
            .rotation = 0,
            .type = J,
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
tetris_piece_batch(void)
{
    if (tetris_queue_length(&(tetris.next_pieces)) < 8)
    {
        TetrisPieceType values[7] = {I, O, T, S, Z, L, J};
        int last_index = 6;
        for (int i = 0; i < 7; i++)
        {
            int num = GetRandomValue(0, last_index);
            tetris_queue_append(&(tetris.next_pieces), values[num]);

            for (int j = num; j < last_index; j++)
            {
                values[j] = values[j + 1];
            }
            --last_index;
        }
    }
}

void
tetris_next_piece(void)
{
    TetrisPieceType type = tetris_queue_pop(&(tetris.next_pieces));
    tetris.current_piece = tetris_piece(type);
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
    tetris_render_pieces(&grid);
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
tetris_render_pieces(TetrisGridStuff* grid)
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
                      tetris_colour(tetris.current_piece.type));
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
        case KEY_ENTER: tetris_next_piece(); break;
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
        case KEY_DOWN:  ++tetris.current_piece.position.y; break;
        }
    }
    while (key != 0);
}
