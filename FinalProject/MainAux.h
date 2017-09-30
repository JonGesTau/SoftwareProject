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
int startGUIMode();

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



#endif //CHESS1_MAINAUX_H
