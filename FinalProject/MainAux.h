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
#define STR_ERR_FILE "Error: File doesn't exist or cannot be opened\n"
#define STR_EXITING "Exiting...\n"
#define STR_RESTARTING "Restarting...\n"
#define STR_ERR_UNDO_UNAVAILABLE "Undo command not available in 2 players mode\n"
#define STR_ERR_EMPTY_HISTORY "Empty history, move cannot be undone\n"
#define STR_ERR_CANT_SAVE "File cannot be created or modified\n"
#define STR_ERR_INVALID_POSITION "Invalid position on the board\n"
#define STR_ERR_WRONG_COLOR "The specified position does not contain your piece\n"
#define STR_ERR_ILLEGAL_MOVE "Illegal move\n"

#define COLOR(p) (p?"White":"Black")

/**
 * Parses the user's command.
 * @return A Command object containing the user's command.
 */
Command getUserCommand();
int arg;
GameState* game;

/**
 * Enters console mode. Starts with setup mode and moves to game mode using startGame.
 */
void startConsoleMode();

/**
 * Starts GUI mode.
 */
void startGUIMode();

/**
 * Handles game mode in the console.
 * @param game
 * @return true if exited via Reset, false if via Quit.
 */
bool startGame(GameState* game);

/**
 * Prints a prompt for the player to enter their commad during game mode.
 * @param game
 */
void promptUserMove(GameState* game);

/**
 * Performs a move for the human player. Makes sure the coordinates are correct and that the move is legal
 * and does not result in self-check. Calls GameStatePerformMove.
 * @param game
 * @param userMove - the move to be played.
 * @return true if the move was legal and performed successfully.
 */
bool handleUserMove(GameState* game, Move* userMove);


#endif //CHESS1_MAINAUX_H
