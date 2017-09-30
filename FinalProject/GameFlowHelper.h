//
// Created by jonathangescheit on 9/30/17.
//

#ifndef CHESS1_GAMEFLOWHELPER_H
#define CHESS1_GAMEFLOWHELPER_H

#include <printf.h>
#include <stdbool.h>
#include "GameState.h"

#define STR_ERR_INVALID_POSITION "Invalid position on the board\n"
#define STR_ERR_WRONG_COLOR "The specified position does not contain your piece\n"
#define STR_ERR_ILLEGAL_MOVE "Illegal move\n"
#define COLOR(p) (p?"White":"Black")


bool handleUserMove(GameState* game, Move* userMove);

#endif //CHESS1_GAMEFLOWHELPER_H
