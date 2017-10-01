//
// Created by Jonathan Gescheit on 9/22/17.
//

// Common functions used in the GUI

#ifndef CHESS1_CHESSGUICOMMON_H
#define CHESS1_CHESSGUICOMMON_H

#include <SDL.h>
#include <SDL_video.h>

/**
 * Copy an SDL rectangle
 * @param src
 * @return SDL rectangle
 */
SDL_Rect* spCopyRect(SDL_Rect* src);

#endif //CHESS1_CHESSGUICOMMON_H
