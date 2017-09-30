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
#include "../GameFlowHelper.h"
#include "../consoleUI.h"

typedef enum {
    CHESS_GAME_START, CHESS_GAME_BACK, CHESS_GAME_EXIT, CHESS_GAME_NONE, CHESS_GAME_MOVE_FAIL, CHESS_GAME_MOVE_SUCCESS, CHESS_GAME_STALEMATE, CHESS_GAME_MATE, CHESS_GAME_CHECK
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

ChessGameWindow* createGameWindow();
void destroyGameWindow(ChessGameWindow *src);
void drawGameWindow(ChessGameWindow *src);
void hideGameWindow(ChessGameWindow* src);
void showGameWindow(ChessGameWindow* src);
CHESS_GAME_EVENT handleEventGameWindow(ChessGameWindow *src, SDL_Event *event);
void drawChessBoard(SDL_Renderer *renderer, ChessGameWindow *src);
void drawPieces(ChessGameWindow* src, SDL_Renderer* renderer);
ChessPiece **createGameWindowChessPieces(SDL_Renderer *renderer, GameBoard *board, int numOfPieces);
ChessRect** createGameWindowChessRects(SDL_Renderer *renderer, GameBoard* board);
void resetGameWindowChessPieces(ChessGameWindow* src);

#endif //CHESS1_CHESSGAMEWINDOW_H
