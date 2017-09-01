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

Command getUserCommand();
int arg;

void startConsoleMode();
void startGUIMode();



#endif //CHESS1_MAINAUX_H
