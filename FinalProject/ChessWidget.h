//
// Created by Jonathan Gescheit on 9/22/17.
//

#ifndef CHESS1_CHESSWIDGET_H
#define CHESS1_CHESSWIDGET_H

#include <SDL.h>
#include <SDL_video.h>
typedef struct widget ChessWidget;
struct widget {
    void (*drawWidget)(ChessWidget*);
    void (*handleEvent)(ChessWidget*, SDL_Event*);
    void (*destroyWidget)(ChessWidget*);
    void* data;
};

//This function would be usefull for NULL safe desetroy
void destroyWidget(ChessWidget* src);

#endif //CHESS1_CHESSWIDGET_H
