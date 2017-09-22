//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSQUITBUTTON_H
#define CHESS1_CHESSQUITBUTTON_H

#include "ChessWidget.h" //A button is a widget also

typedef struct chess_quit_button ChessQuitButton;
struct chess_quit_button{
    SDL_Texture* buttonTexture;
    SDL_Renderer* windowRenderer;
    SDL_Rect* location;
};

//You need a create function:
ChessWidget* createChessQuitButton(SDL_Renderer* windowRender, SDL_Rect* location,
                                   const char* image);

//You need this function in order to destroy all data Associate with a button:
void destroyChessQuitButton(ChessWidget*);

void handleChessQuitButtonEvenet(ChessWidget* src, SDL_Event* event);

void drawChessQuitButton(ChessWidget* src);

#endif //CHESS1_CHESSQUITBUTTON_H
