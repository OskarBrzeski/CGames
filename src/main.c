#include "main.h"

#include "menu/menu.h"
#include "raylib.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

int
main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Starting Example");
    SetTargetFPS(60);
    SetExitKey(KEY_F4);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        run_menu();
        handle_FPS_toggle();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

int FPS_target_index = 0;
void
handle_FPS_toggle(void)
{
    int FPS_targets[] = {60, 144};
    int FPS_target_length = sizeof(FPS_targets) / sizeof(FPS_targets[0]);
    int key;
    do {
        key = GetKeyPressed();
        if (key == KEY_SPACE)
        {
            FPS_target_index = (FPS_target_index + 1) % FPS_target_length;
            SetTargetFPS(FPS_targets[FPS_target_index]);
        }
    }
    while (key != 0);
}
