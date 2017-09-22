//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessWindow.h"

#include <stdlib.h>

void destroyWindow(ChessWindow* src){
    if(!src){
        return;
    }
    src->destroyWindow(src);
}
