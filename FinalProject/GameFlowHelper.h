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
#define STR_SELECT_SETTINGS "Specify game setting or type 'start' to begin a game with the current setting:\n"
#define STR_ERR_FILE "Error: File doesn't exist or cannot be opened\n"
#define STR_EXITING "Exiting...\n"
#define STR_RESTARTING "Restarting...\n"
#define STR_ERR_UNDO_UNAVAILABLE "Undo command not available in 2 players mode\n"
#define STR_ERR_EMPTY_HISTORY "Empty history, move cannot be undone\n"
#define STR_ERR_CANT_SAVE "File cannot be created or modified\n"
#define COLOR(p) (p?"White":"Black")

bool handleUserMove(GameState* game, Move* userMove);

#endif //CHESS1_GAMEFLOWHELPER_H
