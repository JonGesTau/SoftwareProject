//
// Created by Jonathan Gescheit on 8/26/17.
//

#ifndef CHESS1_MAINAUX_H
#define CHESS1_MAINAUX_H

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "ChessParser.h"
#include "GameSettings.h"
#include "GameState.h"
#include "consoleUI.h"
#include "GameBoard.h"
#include "Moves.h"
//#include "SDL.h"
#include "xmlGame.h"
#include "MiniMax.h"

#define EXPERT_LEVEL_SUPPORTED false

#define STR_SELECT_SETTINGS "Specify game setting or type 'start' to begin a game with the current setting:\n"
#define STR_EXITING "Exiting...\n"
#define STR_RESTARTING "Restarting...\n"
#define STR_ERR_UNDO_UNAVAILABLE "Undo command not available in 2 players mode\n"
#define STR_ERR_EMPTY_HISTORY "Empty history, move cannot be undone\n"
#define STR_ERR_CANT_SAVE "File cannot be created or modified\n"
#define STR_ERR_INVALID_POSITION "Invalid position on the board\n"
#define STR_ERR_WRONG_COLOR "The specified position does not contain your piece\n"
#define STR_ERR_ILLEGAL_MOVE "Illegal move\n"

Command getUserCommand();
int arg;
GameState* game;

void startConsoleMode();
void startGUIMode();
bool startGame(GameState* game);
void promptUserMove(GameState* game);
bool handleUserMove(GameState* game, Move* userMove);


#endif //CHESS1_MAINAUX_H
