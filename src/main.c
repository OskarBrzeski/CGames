// #include "../include/raylib/include/raylib.h"
#include "raylib.h"

int
main()
{
    InitWindow(800, 600, "Starting Example");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
        DrawText("Works as intended", 10, 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
