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
#define STR_ERR_UNDO_UNAVAILABLE "Undo command not available in 2 players mode\n" // TODO: in the PDF this is spelt avaialbe
#define STR_ERR_EMPTY_HISTORY "Empty history, move cannot be undone\n"

Command getUserCommand();
int arg;
GameState* game;

void startConsoleMode();
void startGUIMode();
void startGame(GameState* game);
void promptUserMove(GameState* game);
bool handleUserMove(GameState* game, Move* userMove);


#endif //CHESS1_MAINAUX_H
