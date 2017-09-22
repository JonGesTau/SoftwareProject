//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSWINDOW_H
#define CHESS1_CHESSWINDOW_H

#include <SDL.h>
#include <SDL_video.h>
#include "../MainAux.h"

typedef struct chess_window ChessWindow;
struct chess_window {
    void* data;
    void (*drawWindow)(ChessWindow* );
    int (*handleEventWindow)(ChessWindow* , SDL_Event* );
    void (*destroyWindow)(ChessWindow* );
    // Add exit and hide
};

//NULL safe FUNCTION
void destroyWindow(ChessWindow* src);


#endif //CHESS1_CHESSWINDOW_H
