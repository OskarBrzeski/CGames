#include "snake.h"

#include "raylib.h"

#include <stdio.h>

SnakeGameState state;

void
snake_new_game(void)
{
    state = (SnakeGameState) {
        .snake_body = {{.x = 2, .y = 0, .dir = RIGHT},
                       {.x = 1, .y = 0, .dir = RIGHT},
                       {.x = 0, .y = 0, .dir = RIGHT}},
        .snake_length = 3,
        .fruit = {.x = 5, .y = 5},
        .direction = RIGHT,
        .desired = RIGHT,
        .time = 0.0,
        .game_over = PLAYING
    };
}

void
snake_run_game(void)
{
    float dt = GetFrameTime();
    state.time += dt * 1000;

    if (!state.game_over && state.time > MSPERTICK)
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

    snake_render_cell_head_anim(state.snake_body[0], WHITE);
    for (int i = 1; i < state.snake_length - 1; i++)
    {
        snake_render_cell(state.snake_body[i], WHITE);
    }
    snake_render_cell_tail_anim(state.snake_body[state.snake_length - 1],
                                WHITE);
    snake_render_cell(state.fruit, RED);

    if (state.game_over) { snake_render_game_over(); }
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
                      screen_height - 2 * margin, GRAY);
    }
    for (int i = 0; i <= ROWS; i++)
    {
        DrawRectangle(margin, margin + i * (cell_size + GRIDWIDTH),
                      screen_width - 2 * margin, GRIDWIDTH, GRAY);
    }
}

void
snake_render_cell(SnakeGridCell cell, Color color)
{
    int cell_size = snake_cell_size();
    int margin = snake_margin();

    Rectangle rect = {
        .x = margin + cell.x * cell_size + (cell.x + 1) * GRIDWIDTH,
        .y = margin + cell.y * cell_size + (cell.y + 1) * GRIDWIDTH,
        .width = cell_size,
        .height = cell_size,
    };

    switch (cell.dir)
    {
    case NONE: break;
    case UP:
        rect.y -= margin;
        rect.height = cell_size + margin;
        break;
    case RIGHT: rect.width = cell_size + margin; break;
    case DOWN:  rect.height = cell_size + margin; break;
    case LEFT:
        rect.x -= margin;
        rect.width = cell_size + margin;
        break;
    }

    DrawRectangleRec(rect, color);
}

void
snake_render_cell_head_anim(SnakeGridCell cell, Color color)
{
    int cell_size = snake_cell_size();
    int margin = snake_margin();

    Rectangle rect = {
        .x = margin + cell.x * cell_size + (cell.x + 1) * GRIDWIDTH,
        .y = margin + cell.y * cell_size + (cell.y + 1) * GRIDWIDTH,
        .width = cell_size,
        .height = cell_size,
    };

    float tick_progress = state.time / MSPERTICK;
    int extended = (cell_size + margin) * tick_progress;

    switch (cell.dir)
    {
    case NONE: break;
    case UP:
        rect.y = rect.y + cell_size - (cell_size + margin) * tick_progress;
        rect.height = extended;
        break;
    case RIGHT: rect.width = extended; break;
    case DOWN:  rect.height = extended; break;
    case LEFT:
        rect.x = rect.x + cell_size - (cell_size + margin) * tick_progress;
        rect.width = extended;
        break;
    }

    DrawRectangleRec(rect, color);
}

void
snake_render_cell_tail_anim(SnakeGridCell cell, Color color)
{
    int cell_size = snake_cell_size();
    int margin = snake_margin();

    Rectangle rect = {
        .x = margin + cell.x * cell_size + (cell.x + 1) * GRIDWIDTH,
        .y = margin + cell.y * cell_size + (cell.y + 1) * GRIDWIDTH,
        .width = cell_size,
        .height = cell_size,
    };

    float tick_progress = state.time / MSPERTICK;
    int extended = cell_size + margin - (cell_size + margin) * tick_progress;

    switch (cell.dir)
    {
    case NONE: break;
    case UP:
        rect.y -= margin;
        rect.height = extended;
        break;
    case RIGHT:
        rect.x += (cell_size + margin) * tick_progress;
        rect.width = extended;
        break;
    case DOWN:
        rect.y += (cell_size + margin) * tick_progress;
        rect.height = extended;
        break;
    case LEFT:
        rect.x -= margin;
        rect.width = extended;
        break;
    }

    DrawRectangleRec(rect, color);
}

void
snake_render_game_over()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                  (Color) {0, 0, 0, 150});

    if (state.game_over == WIN)
    {
        DrawText("Congratulations, you win!", 100, 100, 30, WHITE);
    }
    else
    {
        char length[4];
        snprintf(length, 4, "%d", state.snake_length);
        DrawText(length, 100, 100, 30, WHITE);
    }

    DrawText("Press Enter to Try Again", 100, 200, 30, WHITE);
}

void
snake_update_pos(void)
{
    SnakeGridCell head = state.snake_body[0];
    SnakeGridCell tail = state.snake_body[state.snake_length - 1];

    for (int i = state.snake_length - 1; i > 0; i--)
    {
        state.snake_body[i] = state.snake_body[i - 1];
    }

    switch (state.direction)
    {
    case NONE: break;
    case UP:
        state.snake_body[0] =
            (SnakeGridCell) {.x = head.x, .y = head.y - 1, .dir = UP};
        state.snake_body[1].dir = UP;
        break;
    case LEFT:
        state.snake_body[0] =
            (SnakeGridCell) {.x = head.x - 1, .y = head.y, .dir = LEFT};
        state.snake_body[1].dir = LEFT;
        break;
    case DOWN:
        state.snake_body[0] =
            (SnakeGridCell) {.x = head.x, .y = head.y + 1, .dir = DOWN};
        state.snake_body[1].dir = DOWN;
        break;
    case RIGHT:
        state.snake_body[0] =
            (SnakeGridCell) {.x = head.x + 1, .y = head.y, .dir = RIGHT};
        state.snake_body[1].dir = RIGHT;
        break;
    }

    state.game_over = snake_is_game_over();

    if (snake_cell_equal(state.snake_body[0], state.fruit))
    {
        state.snake_body[state.snake_length++] = tail;

        if (state.snake_length == ROWS * COLUMNS)
        {
            state.game_over = WIN;
            return;
        }

        snake_new_fruit();
    }
}

void
snake_handle_input(void)
{
    int key;
    do
    {
        key = GetKeyPressed();

        if (state.game_over)
        {
            if (key == KEY_ENTER) { snake_new_game(); }
        }
        else
        {
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
        }
    }
    while (key != 0);
}

int
snake_cell_equal(SnakeGridCell c1, SnakeGridCell c2)
{
    return c1.x == c2.x && c1.y == c2.y;
}

void
snake_new_fruit(void)
{
    int position = GetRandomValue(0, ROWS * COLUMNS - state.snake_length);

    int area[ROWS * COLUMNS] = {0};
    snake_grid_arr(area);

    for (int i = 0, empty = 0; i < ROWS * COLUMNS; i++)
    {
        if (area[i] == 0) ++empty;

        if (empty == position)
        {
            state.fruit = (SnakeGridCell) {.x = i % COLUMNS, .y = i / COLUMNS};
            break;
        }
    }
}

void
snake_grid_arr(int* grid)
{
    for (int i = 0; i < state.snake_length; i++)
    {
        int pos = state.snake_body[i].x + COLUMNS * state.snake_body[i].y;
        grid[pos] = 1;
    }
}

SnakePlayStatus
snake_is_game_over(void)
{
    SnakeGridCell head = state.snake_body[0];

    if (head.x < 0 || head.x >= COLUMNS || head.y < 0 || head.y >= ROWS)
    {
        return LOSE;
    }

    for (int i = 1; i < state.snake_length; i++)
    {
        if (snake_cell_equal(head, state.snake_body[i])) { return LOSE; }
    }

    return PLAYING;
}
