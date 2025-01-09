#include "menu.h"

#include "../pong/pong.h"
#include "../snake/snake.h"
#include "../tetris/tetris.h"
#include "../tofe/tofe.h"
#include "raylib.h"

#define ITEMHEIGHT  80
#define ICONSIZE    12
#define ICONMARGIN  (ITEMHEIGHT - ICONSIZE) / 2
#define TEXTSIZE    30
#define TEXTOFFSETX ITEMHEIGHT
#define TEXTOFFSETY (ITEMHEIGHT - TEXTSIZE) / 2
#define GAMECOUNT   4

int select_position = 0;
GameScreen current_game = MENU;

void
run_menu(void)
{
    if (current_game == MENU)
    {
        handle_input();
        render_menu();
    }
    else
    {
        handle_ingame_input();
        switch (current_game)
        {
        case PONG:   pong_run_game(); break;
        case SNAKE:  snake_run_game(); break;
        case TETRIS: tetris_run_game(); break;
        case TOFE:   tofe_run_game(); break;
        default:     current_game = MENU; render_menu();
        }
    }
}

void
render_menu(void)
{
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    Vector2 icon_centre = {ITEMHEIGHT / 2.0,
                           ITEMHEIGHT * (select_position + 0.5)};
    DrawPoly(icon_centre, 3, ICONSIZE, 0, WHITE);

    DrawText("Pong", TEXTOFFSETX, TEXTOFFSETY, TEXTSIZE, WHITE);
    DrawText("Snake", TEXTOFFSETX, ITEMHEIGHT + TEXTOFFSETY, TEXTSIZE, WHITE);
    DrawText("Tetris", TEXTOFFSETX, ITEMHEIGHT * 2 + TEXTOFFSETY, TEXTSIZE,
             WHITE);
    DrawText("2048", TEXTOFFSETX, ITEMHEIGHT * 3 + TEXTOFFSETY, TEXTSIZE,
             WHITE);
}

void
handle_ingame_input(void)
{
    if (IsKeyDown(KEY_ESCAPE)) { current_game = MENU; }
}

void
handle_input(void)
{
    int key;
    do {
        key = GetKeyPressed();

        switch (key)
        {
        case KEY_UP:
            select_position = (select_position + GAMECOUNT - 1) % GAMECOUNT;
            break;
        case KEY_DOWN:
            select_position = (select_position + 1) % GAMECOUNT;
            break;
        case KEY_ENTER: change_game(); break;
        }
    }
    while (key != 0);
}

void
change_game(void)
{
    int shifted = select_position + 1;
    switch (shifted)
    {
    case PONG:
        current_game = PONG;
        pong_new_game();
        break;
    case SNAKE:
        current_game = SNAKE;
        snake_new_game();
        break;
    case TETRIS:
        current_game = TETRIS;
        tetris_new_game();
        break;
    case TOFE:
        current_game = TOFE;
        tofe_new_game();
        break;
    }
}
