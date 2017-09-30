//
// Created by Jonathan Gescheit on 9/24/17.
//

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

typedef enum {
    CHESS_GAME_INVALID, CHESS_GAME_START, CHESS_GAME_BACK, CHESS_GAME_EXIT, CHESS_GAME_NONE, CHESS_GAME_MOVE_FAIL, CHESS_GAME_MOVE_SUCCESS,
    CHESS_GAME_STALEMATE, CHESS_GAME_MATE, CHESS_GAME_CHECK, CHESS_GAME_UNDO, CHESS_GAME_RESTART, CHESS_GAME_LOAD, CHESS_GAME_SAVE, CHESS_GAME_MAIN_MENU
} CHESS_GAME_EVENT;

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

ChessGameWindow *createGameWindow(GameSettings *settings);
void destroyGameWindow(ChessGameWindow *src);
void drawGameWindow(ChessGameWindow *src);
void hideGameWindow(ChessGameWindow* src);
void showGameWindow(ChessGameWindow* src);
CHESS_GAME_EVENT handleEventGameWindow(ChessGameWindow *src, SDL_Event *event);
void drawChessBoard(SDL_Renderer *renderer);
void drawChessGamePieces(ChessGameWindow* src);
ChessPiece **createGameWindowChessPieces(SDL_Renderer *renderer, GameBoard *board, int numOfPieces);
ChessRect **createGameWindowChessRects(SDL_Renderer *renderer);
void resetGameWindowChessPieces(ChessGameWindow* src);
void destroyGameWindowButtons(ChessButton** buttons, int numOfButtons);

#endif //CHESS1_CHESSGAMEWINDOW_H
