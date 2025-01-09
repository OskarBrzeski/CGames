#ifndef MENU_H
#define MENU_H

typedef enum { MENU, PONG, SNAKE, TETRIS, TOFE } GameScreen;

void run_menu(void);
void render_menu(void);
void handle_ingame_input(void);
void handle_input(void);
void change_game(void);

#endif
