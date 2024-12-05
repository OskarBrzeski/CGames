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
        .hold = 0,
        .next_pieces = {.head = 0, .tail = 0, .values = {}},
    };

    tetris_piece_batch();
    tetris_next_piece();
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
tetris_run_game(void)
{
    tetris_piece_batch();
    tetris_handle_input();
    tetris_clear_line();
    tetris_render_game();
}

void
tetris_place_piece(void)
{
    while (tetris_valid_position()) { ++tetris.current_piece.position.y; }
    --tetris.current_piece.position.y;

    TetrisTile* tiles =
        tetris.current_piece.tiles[tetris.current_piece.rotation];

    for (int i = 0; i < 4; i++)
    {
        int x = tetris.current_piece.position.x + tiles[i].x;
        int y = tetris.current_piece.position.y + tiles[i].y;
        tetris.grid[y][x] = tetris.current_piece.type;
    }

    tetris_next_piece();
}

bool
tetris_valid_position(void)
{
    int curr_x = tetris.current_piece.position.x;
    int curr_y = tetris.current_piece.position.y;
    int rotation = tetris.current_piece.rotation;

    for (int i = 0; i < 4; i++)
    {
        int x = curr_x + tetris.current_piece.tiles[rotation][i].x;
        int y = curr_y + tetris.current_piece.tiles[rotation][i].y;

        if (x < 0 || x >= 10) return false;
        if (y >= 20) return false;
        if (y < 0) continue;
        if (tetris.grid[y][x] != 0) return false;
    }
    return true;
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
tetris_clear_line(void)
{
    for (int y = 0; y < 20; y++)
    {
        int count = 0;
        for (int x = 0; x < 10; x++)
        {
            if (tetris.grid[y][x] > 0) ++count;
        }
        if (count == 10) { tetris_shift_lines(y); }
    }
}

void
tetris_shift_lines(int8_t line)
{
    for (int y = line; y > 0; y--)
    {
        for (int x = 0; x < 10; x++)
        {
            tetris.grid[y][x] = tetris.grid[y - 1][x];
        }
    }

    for (int x = 0; x < 10; x++) { tetris.grid[0][x] = 0; }
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
    tetris_render_tiles(&grid);
    tetris_render_hold(&grid);
    tetris_render_next(&grid);
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

void
tetris_render_tiles(TetrisGridStuff* grid)
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int x = grid->margin_x + grid->grid_border * (j + 1) +
                    grid->cell_size * j;
            int y = grid->margin_y + grid->grid_border * (i + 1) +
                    grid->cell_size * i;
            DrawRectangle(x, y, grid->cell_size, grid->cell_size,
                          tetris_colour(tetris.grid[i][j]));
        }
    }
}

void
tetris_render_hold(TetrisGridStuff* grid)
{
    int16_t cell_size = grid->cell_size * 3 / 5;
    int16_t x = grid->margin_x + 11 * (grid->grid_border + grid->cell_size) + 8;
    int16_t y = grid->margin_y;
    Rectangle rect = {
        .x = x, .y = y, .width = cell_size * 5, .height = cell_size * 5};

    DrawRectangleLinesEx(rect, grid->grid_border, WHITE);

    if (tetris.hold == 0) return;

    TetrisPiece piece = tetris_piece(tetris.hold);

    tetris_render_small_piece(x, y, cell_size, piece.tiles[0], piece.type);
}

void
tetris_render_small_piece(int16_t x, int16_t y, int16_t cell_size,
                          TetrisTile tiles[4], TetrisPieceType type)
{
    for (int i = 0; i < 4; i++)
    {
        DrawRectangle(x + (cell_size * tiles[i].x) + cell_size / 2,
                      y + (cell_size * tiles[i].y) + cell_size / 2, cell_size,
                      cell_size, tetris_colour(type));
    }
}

void
tetris_render_next(TetrisGridStuff* grid)
{
}

Color
tetris_colour(TetrisPieceType type)
{
    switch (type)
    {
    case I: return SKYBLUE;
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
        case KEY_Z:
            tetris.current_piece.rotation =
                ((tetris.current_piece.rotation - 1) % 4 + 4) % 4;
            if (!tetris_valid_position())
            {
                tetris.current_piece.rotation =
                    (tetris.current_piece.rotation + 1) % 4;
            }
            break;
        case KEY_X:
            tetris.current_piece.rotation =
                (tetris.current_piece.rotation + 1) % 4;
            if (!tetris_valid_position())
            {
                tetris.current_piece.rotation =
                    ((tetris.current_piece.rotation - 1) % 4 + 4) % 4;
            }
            break;
        case KEY_C:
            if (tetris.hold == 0)
            {
                tetris.hold = tetris.current_piece.type;
                tetris_next_piece();
            }
            else
            {
                TetrisPieceType temp = tetris.hold;
                tetris.hold = tetris.current_piece.type;
                tetris.current_piece = tetris_piece(temp);
            }
        case KEY_LEFT:
            --tetris.current_piece.position.x;
            if (!tetris_valid_position()) ++tetris.current_piece.position.x;
            break;
        case KEY_RIGHT:
            ++tetris.current_piece.position.x;
            if (!tetris_valid_position()) --tetris.current_piece.position.x;
            break;
        case KEY_DOWN:
            ++tetris.current_piece.position.y;
            if (!tetris_valid_position()) --tetris.current_piece.position.y;
            break;
        case KEY_UP: tetris_place_piece(); break;
        }
    }
    while (key != 0);
}
