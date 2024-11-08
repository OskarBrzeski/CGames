#include "pong/pong.h"
#include "raylib.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

int
main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Starting Example");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        render_game(WINDOW_WIDTH, WINDOW_HEIGHT);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
