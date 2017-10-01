//
// Created by Jonathan Gescheit on 9/22/17.
//

// The button used in the GUI

#ifndef CHESS1_CHESSBUTTON_H
#define CHESS1_CHESSBUTTON_H

#include <stdbool.h>
#include <SDL.h>
#include <SDL_video.h>
#include "ChessGUICommon.h"

/**
 * A type used to represent the button's type
 */
typedef enum {
    CHESS_BUTTON_NEW_GAME, CHESS_BUTTON_LOAD, CHESS_BUTTON_QUIT,
    CHESS_BUTTON_1PLAYER, CHESS_BUTTON_2PLAYER,
    CHESS_BUTTON_NOOB, CHESS_BUTTON_EASY, CHESS_BUTTON_MODERATE, CHESS_BUTTON_HARD,
    CHESS_BUTTON_WHITE, CHESS_BUTTON_BLACK,
    CHESS_BUTTON_BACK, CHESS_BUTTON_START,
    CHESS_BUTTON_RESTART, CHESS_BUTTON_SAVE, CHESS_BUTTON_MAIN_MENU, CHESS_BUTTON_UNDO,
    CHESS_BUTTON_SLOT_1, CHESS_BUTTON_SLOT_2, CHESS_BUTTON_SLOT_3, CHESS_BUTTON_SLOT_4, CHESS_BUTTON_SLOT_5
} ButtonType;

/**
 * A type used to represent the button was clicked
 */
typedef enum {
    CHESS_CLICKED_NEW_GAME, CHESS_CLICKED_LOAD, CHESS_CLICKED_QUIT, CHESS_CLICKED_NONE,
    CHESS_CLICKED_1PLAYER, CHESS_CLICKED_2PLAYER,
    CHESS_CLICKED_NOOB, CHESS_CLICKED_EASY, CHESS_CLICKED_MODERATE, CHESS_CLICKED_HARD,
    CHESS_CLICKED_WHITE, CHESS_CLICKED_BLACK,
    CHESS_CLICKED_BACK, CHESS_CLICKED_START,
    CHESS_CLICKED_RESTART, CHESS_CLICKED_SAVE, CHESS_CLICKED_MAIN_MENU, CHESS_CLICKED_UNDO,
    CHESS_CLICKED_SLOT_1, CHESS_CLICKED_SLOT_2, CHESS_CLICKED_SLOT_3, CHESS_CLICKED_SLOT_4, CHESS_CLICKED_SLOT_5
} BUTTON_CLICK_EVENT;

/**
 * A type used to represent the button
 */
typedef struct chess_button{
    SDL_Texture* activeTexture;
    SDL_Texture* inactiveTexture;
    SDL_Renderer* windowRenderer;
    SDL_Rect* location;
    bool isActive;
    ButtonType type;
} ChessButton;

/**
 * Create button
 * @param windowRender
 * @param location
 * @param activeImage
 * @param inactiveImage
 * @param type
 * @param isActive
 * @return the button
 */
ChessButton* createChessButton(SDL_Renderer* windowRender, SDL_Rect* location, const char* activeImage, const char* inactiveImage, ButtonType type, bool isActive);

/**
 * Destroy button
 */
void destroyChessButton(ChessButton*);

/**
 * Handle a button event
 * @param src
 * @param event
 * @return which click event occured
 */
BUTTON_CLICK_EVENT handleChessButtonEvent(ChessButton *src, SDL_Event *event);

/**
 * Draw button on screen
 * @param src
 */
void drawChessButton(ChessButton* src);

/**
 * Toggle button
 * @param src
 */
void toggleChessButton(ChessButton* src);

#endif //CHESS1_CHESSBUTTON_H
