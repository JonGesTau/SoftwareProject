//
// Created by Dror on 2017-08-19.
//

#ifndef CHESS1_XMLGAME_H
#define CHESS1_XMLGAME_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "GameState.h"
#include "consoleUI.h"

#define XML_GAME_MAX_LINE_LENGTH 256

/**
 * Saves a GameState into a file.
 * @param game - the GameState object to save.
 * @param filename - the destination filename.
 * @return true if saved successfully.
 */
bool xmlGameSaveGame(GameState* game, char* filename);

/**
 * advances pointers and buffers to the start of the next
 * non-empty line, and also skips leading whitespace. Used by xmlGameLoadGame.
 * @param f - the file to read
 * @param line - string into which we copy the next line.
 * @param start_pos - the cursor for xmlGameLoadGame.
 * @return true if no errors occured.
 */
bool xmlGameNextRow(FILE* f, char* line, unsigned int* start_pos);

/**
 * Loads a GameState from a file.
 * @param filename - the file to load.
 * @return the gamestate read from the file.
 */
GameState* xmlGameLoadGame(char* filename);

/**
 * Parses a row from a text file into a gameboard object.
 * @param game - the gameBoard into which we save the row.
 * @param rowNumber - the number of the row (0-7).
 * @param row - the text to parse.
 * @return true if no errors.
 */
bool xmlGameParseRow(GameBoard* game, unsigned char rowNumber, char* row);

#endif //CHESS1_XMLGAME_H
