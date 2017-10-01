//
// Created by Jonathan Gescheit on 9/24/17.
//

// The Game Window - where the actual gameplay takes place.

#ifndef CHESS1_CHESSGAMEWINDOW_H
#define CHESS1_CHESSGAMEWINDOW_H
#include <SDL.h>
#include <SDL_video.h>
#include "ChessButton.h"
#include "ChessPiece.h"
#include "ChessRect.h"
#include "../GameFlowHelper.h"
#include "../GameState.h"
#include "../GameSettings.h"
#include "../consoleUI.h"
#include "../MiniMax.h"

/**
 * Represents an event in the game window
 */
typedef enum {
    CHESS_GAME_INVALID, CHESS_GAME_START, CHESS_GAME_BACK, CHESS_GAME_EXIT, CHESS_GAME_NONE, CHESS_GAME_MOVE_FAIL, CHESS_GAME_MOVE_SUCCESS,
    CHESS_GAME_STALEMATE, CHESS_GAME_MATE, CHESS_GAME_CHECK, CHESS_GAME_UNDO, CHESS_GAME_RESTART, CHESS_GAME_LOAD, CHESS_GAME_SAVE, CHESS_GAME_MAIN_MENU
} CHESS_GAME_EVENT;

/**
 * Represents the window itself
 */
typedef struct chess_game_window ChessGameWindow;
struct chess_game_window {
    SDL_Window* window;
    SDL_Renderer* windowRenderer;
    ChessButton** buttons;
    ChessPiece** pieces;
    int numOfButtons;
    int numOfPieces;
    GameSettings* settings;
    GameState* game;
    ChessRect **rects;
    int numOfRects;
};

/**
 * Create game window
 * @param settings
 * @param loadGame
 * @return window
 */
ChessGameWindow *createGameWindow(GameSettings *settings, GameState *loadGame);

/**
 * Destroy game window
 * @param src
 */
void destroyGameWindow(ChessGameWindow *src);

/**
 * Draw game window on screen
 * @param src
 */
void drawGameWindow(ChessGameWindow *src);

/**
 * Hide game window
 * @param src
 */
void hideGameWindow(ChessGameWindow* src);

/**
 * Show game window
 * @param src
 */
void showGameWindow(ChessGameWindow* src);

/**
 * Handle an event which occurs in game window
 * @param src
 * @param event
 * @return the relevant event
 */
CHESS_GAME_EVENT handleEventGameWindow(ChessGameWindow *src, SDL_Event *event);

/**
 * Draw the chess board on screen
 * @param renderer
 */
void drawChessBoard(SDL_Renderer *renderer);

/**
 * Draw game pieces
 * @param src
 */
void drawChessGamePieces(ChessGameWindow* src);

/**
 * Create gameplay piece
 * @param renderer
 * @param board
 * @param numOfPieces
 * @return created piece
 */
ChessPiece **createGameWindowChessPieces(SDL_Renderer *renderer, GameBoard *board, int numOfPieces);

/**
 * Create board rectangles (positions, used to follow the location of pieces)
 * @param renderer
 * @return created rectangle
 */
ChessRect **createGameWindowChessRects(SDL_Renderer *renderer);

/**
 * Reset gameplay pieces
 * @param src
 */
void resetGameWindowChessPieces(ChessGameWindow* src);

/**
 * Destroy game window
 * @param buttons
 * @param numOfButtons
 */
void destroyGameWindowButtons(ChessButton** buttons, int numOfButtons);

#endif //CHESS1_CHESSGAMEWINDOW_H
