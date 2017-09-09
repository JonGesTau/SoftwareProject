//
// Created by Jonathan Gescheit on 8/26/17.
//

#ifndef CHESS1_MAINAUX_H
#define CHESS1_MAINAUX_H

#include <printf.h>
#include <memory.h>
#include <stdlib.h>

#include "ChessParser.h"
#include "GameSettings.h"
#include "GameState.h"
#include "consoleUI.h"
#include "GameBoard.h"
#include "Moves.h"
#include "SDL.h"

Command getUserCommand();
int arg;
GameState* game;

void startConsoleMode();
void startGUIMode();
void startGame(GameSettings* settings);
void promptUserMove();


#endif //CHESS1_MAINAUX_H
