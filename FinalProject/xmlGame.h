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
#include "consoleUI.h" // TODO: not ideal but we need it for consolePieceChar

bool xmlGameSaveGame(GameState* game, char* filename);
GameState* xmlGameLoadGame(char* filename);

bool xmlGameParseRow(GameBoard* game, char rowNumber, char* row);

#endif //CHESS1_XMLGAME_H
