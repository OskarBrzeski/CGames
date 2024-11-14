#import "menu.h"

#import "../pong/pong.h"
#import "raylib.h"

typedef enum { MENU = 0, PONG, SNAKE, TETRIS } GameScreen;

GameScreen current_game = MENU;

#define ITEMHEIGHT  80
#define ICONSIZE    12
#define ICONMARGIN  (ITEMHEIGHT - ICONSIZE) / 2
#define TEXTSIZE    30
#define TEXTOFFSETX ITEMHEIGHT
#define TEXTOFFSETY (ITEMHEIGHT - TEXTSIZE) / 2
#define GAMECOUNT   3

int select_position = 0;

void
run_menu(void)
{
    if (current_game == MENU)
    {
        handle_input();
        render_menu();
    } else
    {
        handle_ingame_input();
        switch (current_game)
        {
        case MENU: render_menu(); break;
        case PONG: run_pong(); break;
        default:   current_game = MENU; render_menu();
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
    } while (key != 0);
}

void
change_game(void)
{
    int shifted = select_position + 1;
    switch (shifted)
    {
    case PONG:   current_game = PONG; break;
    case SNAKE:  current_game = SNAKE; break;
    case TETRIS: current_game = TETRIS; break;
    }
}
