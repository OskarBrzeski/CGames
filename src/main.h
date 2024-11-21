#ifndef MAIN_H
#define MAIN_H

#include "pong/pong.h"

typedef union {
    PongGameState game;
} GameState;

void handle_FPS_toggle(void);

#endif
