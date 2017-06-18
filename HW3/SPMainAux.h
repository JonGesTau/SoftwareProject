#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

#include <stdio.h>
#include <inttypes.h>
#include "SPFIARGame.h"
#include "SPFIARParser.h"
#include "SPMiniMax.h"

int HISTORY_SIZE;
int level;
int userMove;
int numUndos;
int computerMove;
char winner;
char userInput[1024];
bool isRestart;
bool isUndo;
bool undoSuccess;
bool dontShowPrompt;
SPCommand command;
SP_FIAR_GAME_MESSAGE undoState;
SPFiarGame* game;

/**
 * Get the game's level
 * @return the level
 */
int getLevel();

/**
 * Suggest a move to the user
 * @return the suggested move
 */
int getSuggestedMove();

/**
 * Get the user's next move
 * @param noPrompt show prompt or not
 * @return the command the user entered
 */
SPCommand getNextMove(bool noPrompt);

/**
 * Quit the game
 */
void quit();

/**
 * Undo the last move
 * @param player which player's move is being undone
 */
void undo(char player);

/**
 * Add a disc to the board
 * @return the winner of the game (if null then there's a tie)
 */
char addDisc();

/**
 * Handle invalid command
 */
void invalidCommand();

/**
 * End the game
 */
void endGame();

/**
 * Restart the game
 */
void restart();

/**
 * Reset the winner variable value
 */
void resetWinner();

/**
 * Reset the numUndos variable
 */
void resetNumUndos();

/**
 * Get input from user
 */
void getUserInput();

#endif
