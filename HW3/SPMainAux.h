#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

#include <stdio.h>
#include <inttypes.h>
#include "SPFIARGame.h"
#include "SPFIARParser.h"
#include "SPMiniMax.h"

//put auxiliary functions and constants used by the main function here.
int HISTORY_SIZE;
char winner;
char userInput[1024];
int level;
int userMove;
int computerMove;
bool isRestart;
bool isUndo;
SPCommand command;
SP_FIAR_GAME_MESSAGE undoState;
SPFiarGame* game;

int getLevel();
SPCommand getNextMove();
int getSuggestedMove();
void undo(char player);
char addDisc();
int quit();
void invalidCommand();
void endGame();
void restart();
void resetWinner();

#endif
