//
// Created by Jonathan Gescheit on 9/24/17.
//

#ifndef CHESS1_CHESSGAMEWINDOW_H
#define CHESS1_CHESSGAMEWINDOW_H
#include <SDL.h>
#include <SDL_video.h>
#include "ChessButton.h"
#include "../GameSettings.h"
#include "../GameState.h"
#include "../consoleUI.h"
#include "ChessPiece.h"

typedef enum {
    CHESS_GAME_START, CHESS_GAME_BACK, CHESS_GAME_EXIT
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
};

ChessGameWindow* createGameWindow();
void destroyGameWindow(ChessGameWindow *src);
void drawGameWindow(ChessGameWindow *src);
void hideGameWindow(ChessGameWindow* src);
void showGameWindow(ChessGameWindow* src);
CHESS_GAME_EVENT handleEventGameWindow(ChessGameWindow *src, SDL_Event *event);
void drawChessBoard(SDL_Renderer *renderer, ChessGameWindow *src);
void drawPieces(ChessGameWindow* src, SDL_Renderer* renderer);

#endif //CHESS1_CHESSGAMEWINDOW_H
