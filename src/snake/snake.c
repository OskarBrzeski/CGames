#include "snake.h"

#include "raylib.h"

SnakeGameState state = {};

void
snake_new_game(void)
{
    state = (SnakeGameState) {
        .snake_body = {{.x = 0, .y = 0}, {.x = 1, .y = 0}, {.x = 2, .y = 0}},
        .snake_length = 3,
        .fruit = {.x = 5, .y = 5},
        .direction = RIGHT,
        .desired = RIGHT,
        .time = 0.0
    };
}

void
snake_run_game(void)
{
    float dt = GetFrameTime();
    state.time += dt * 1000;

    if (state.time > MSPERTICK)
    {
        state.direction = state.desired;
        snake_update_pos();
        state.time -= MSPERTICK;
    }

    snake_handle_input();
    snake_render_game();
}

void
snake_render_game(void)
{
    snake_render_grid();
    for (int i = 0; i < state.snake_length; i++)
    {
        snake_render_cell(state.snake_body[i], WHITE);
    }
    snake_render_cell(state.fruit, RED);
}

int
snake_cell_size(void)
{
    int screen_width = GetScreenWidth();

    return (screen_width - GRIDWIDTH * (COLUMNS + 1)) / COLUMNS;
}

int
snake_margin(void)
{
    int cell_size = snake_cell_size();
    int screen_width = GetScreenWidth();

    return (screen_width - cell_size * COLUMNS - GRIDWIDTH * (COLUMNS + 1)) / 2;
}

void
snake_render_grid(void)
{
    int cell_size = snake_cell_size();
    int margin = snake_margin();
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    for (int i = 0; i <= COLUMNS; i++)
    {
        DrawRectangle(margin + i * (cell_size + GRIDWIDTH), margin, GRIDWIDTH,
                      screen_height - 2 * margin, GREEN);
    }
    for (int i = 0; i <= ROWS; i++)
    {
        DrawRectangle(margin, margin + i * (cell_size + GRIDWIDTH),
                      screen_width - 2 * margin, GRIDWIDTH, GREEN);
    }
}

void
snake_render_cell(GridCell cell, Color color)
{
    int cell_size = snake_cell_size();
    int margin = snake_margin();

    DrawRectangle(margin + cell.x * cell_size + (cell.x + 1) * GRIDWIDTH,
                  margin + cell.y * cell_size + (cell.y + 1) * GRIDWIDTH,
                  cell_size, cell_size, color);
}

void
snake_update_pos(void)
{
    GridCell head = state.snake_body[state.snake_length - 1];

    for (int i = 0; i < state.snake_length - 1; i++)
    {
        state.snake_body[i] = state.snake_body[i + 1];
    }

    switch (state.direction)
    {
    case UP:
        state.snake_body[state.snake_length - 1] =
            (GridCell) {.x = head.x, .y = head.y - 1};
        break;
    case LEFT:
        state.snake_body[state.snake_length - 1] =
            (GridCell) {.x = head.x - 1, .y = head.y};
        break;
    case DOWN:
        state.snake_body[state.snake_length - 1] =
            (GridCell) {.x = head.x, .y = head.y + 1};
        break;
    case RIGHT:
        state.snake_body[state.snake_length - 1] =
            (GridCell) {.x = head.x + 1, .y = head.y};
        break;
    }
}

void
snake_handle_input(void)
{
    int key;
    do {
        key = GetKeyPressed();

        switch (key)
        {
        case KEY_UP:
            if (state.direction != DOWN) state.desired = UP;
            break;
        case KEY_LEFT:
            if (state.direction != RIGHT) state.desired = LEFT;
            break;
        case KEY_DOWN:
            if (state.direction != UP) state.desired = DOWN;
            break;
        case KEY_RIGHT:
            if (state.direction != LEFT) state.desired = RIGHT;
            break;
        }
    } while (key != 0);
}
