//
// Created by Jonathan Gescheit on 8/26/17.
//

#ifndef CHESS1_MAINAUX_H
#define CHESS1_MAINAUX_H

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <SDL.h>

#include "ChessParser.h"
#include "GameSettings.h"
#include "GameState.h"
#include "consoleUI.h"
#include "GameBoard.h"
#include "Moves.h"
#include "xmlGame.h"
#include "MiniMax.h"
#include "graphics/ChessGUIManager.h"
#include "GameFlowHelper.h"

#define EXPERT_LEVEL_SUPPORTED false





Command getUserCommand();
int arg;
GameState* game;

void startConsoleMode();
int startGUIMode();
bool startGame(GameState* game);
void promptUserMove(GameState* game);


#endif //CHESS1_MAINAUX_H
