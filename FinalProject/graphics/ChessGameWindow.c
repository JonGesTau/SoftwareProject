//
// Created by Jonathan Gescheit on 9/24/17.
//

#include "ChessGameWindow.h"

//Helper function to create buttons in the simple window;
ChessButton **createGameWindowChessButtons(SDL_Renderer *renderer, int gameMode) {
    if (renderer == NULL ) {
        return NULL ;
    }

    const int numOfButtons = 6;

    ChessButton** buttons = malloc(numOfButtons * sizeof(ChessButton*));
    if (buttons == NULL ) {
        return NULL ;
    }

    SDL_Rect restart = { .x = 20, .y = 10, .h = 100, .w = 250 };
    SDL_Rect save = { .x = 20, .y = 120, .h = 100, .w = 250 };
    SDL_Rect load = { .x = 20, .y = 230, .h = 100, .w = 250 };
    SDL_Rect undo = { .x = 20, .y = 340, .h = 100, .w = 250 };
    SDL_Rect mainmenu = { .x = 20, .y = 450, .h = 100, .w = 250 };
    SDL_Rect quit = { .x = 20, .y = 560, .h = 100, .w = 250 };


    buttons[0] = createChessButton(renderer, &restart, "./assets/restart_active.bmp", "./assets/restart_active.bmp", CHESS_BUTTON_RESTART, true);
    buttons[1] = createChessButton(renderer, &save, "./assets/save_active.bmp", "./assets/save_active.bmp", CHESS_BUTTON_SAVE, true);
    buttons[2] = createChessButton(renderer, &load, "./assets/load.bmp", "./assets/load.bmp", CHESS_BUTTON_LOAD, true);
    buttons[3] = createChessButton(renderer, &undo, "./assets/undo_active.bmp", "./assets/undo_inactive.bmp", CHESS_BUTTON_UNDO, false);
    buttons[4] = createChessButton(renderer, &mainmenu, "./assets/mainmenu_active.bmp", "./assets/mainmenu_active.bmp", CHESS_BUTTON_MAIN_MENU, true);
    buttons[5] = createChessButton(renderer, &quit, "./assets/quit.bmp", "./assets/quit.bmp", CHESS_BUTTON_QUIT, true);


    for (int i = 0; i < numOfButtons ; i++) {
        if (buttons[i] == NULL) {
            destroyGameWindowButtons(buttons, numOfButtons);
            return NULL;
        }
    }

    if (gameMode == 1) buttons[3]->isActive = true;

    return buttons;
}

ChessPiece **createGameWindowChessPieces(SDL_Renderer *renderer, GameBoard *board, int numOfPieces) {
    if (renderer == NULL ) {
        return NULL ;
    }

    ChessPiece** pieces = malloc(numOfPieces * sizeof(ChessPiece*));
    if (pieces == NULL ) {
        return NULL ;
    }

    SDL_Rect rect, darea;
    SDL_Rect *rectp;
    char piece;

    /* Get the Size of drawing surface */
    SDL_RenderGetViewport(renderer, &darea);
    darea.w = 0.7 * darea.w;
    darea.h = 0.7 * darea.h;
    int i = 0;

    for (int y = 7; y > -1; y--) {
        for (int x = 0; x < 8; x++) {
            piece = consolePieceChar(board->board[y][x]);
            ChessPiece *piecep;

            rect.w = darea.w / 8;
            rect.h = darea.h / 8;
            rect.x = x * rect.w + darea.w * 0.4;
            rect.y = (7-y) * rect.h + darea.w * 0.15;
            rectp = &rect;

            switch (piece) {
                case 'M':
                    piecep = createChessPiece(renderer, rectp, CHESS_PIECE_PAWN, CHESS_PIECE_COLOR_BLACK, x, y);
                    break;
                case 'B':
                    piecep = createChessPiece(renderer, rectp, CHESS_PIECE_BISHOP, CHESS_PIECE_COLOR_BLACK, x, y);
                    break;
                case 'R':
                    piecep = createChessPiece(renderer, rectp, CHESS_PIECE_ROOK, CHESS_PIECE_COLOR_BLACK, x, y);
                    break;
                case 'N':
                    piecep = createChessPiece(renderer, rectp, CHESS_PIECE_KNIGHT, CHESS_PIECE_COLOR_BLACK, x, y);
                    break;
                case 'Q':
                    piecep = createChessPiece(renderer, rectp, CHESS_PIECE_QUEEN, CHESS_PIECE_COLOR_BLACK, x, y);
                    break;
                case 'K':
                    piecep = createChessPiece(renderer, rectp, CHESS_PIECE_KING, CHESS_PIECE_COLOR_BLACK, x, y);
                    break;
                case 'm':
                    piecep = createChessPiece(renderer, rectp, CHESS_PIECE_PAWN, CHESS_PIECE_COLOR_WHITE, x, y);
                    break;
                case 'b':
                    piecep = createChessPiece(renderer, rectp, CHESS_PIECE_BISHOP, CHESS_PIECE_COLOR_WHITE, x, y);
                    break;
                case 'r':
                    piecep = createChessPiece(renderer, rectp, CHESS_PIECE_ROOK, CHESS_PIECE_COLOR_WHITE, x, y);
                    break;
                case 'n':
                    piecep = createChessPiece(renderer, rectp, CHESS_PIECE_KNIGHT, CHESS_PIECE_COLOR_WHITE, x, y);
                    break;
                case 'q':
                    piecep = createChessPiece(renderer, rectp, CHESS_PIECE_QUEEN, CHESS_PIECE_COLOR_WHITE, x, y);
                    break;
                case 'k':
                    piecep = createChessPiece(renderer, rectp, CHESS_PIECE_KING, CHESS_PIECE_COLOR_WHITE, x, y);
                    break;
                default:
                    piecep = NULL;
                    break;
            }

            if (piecep != NULL) {
                pieces[i] = piecep;
                i++;
            }
        }
    }


    return pieces;
}

void resetGameWindowChessPieces(ChessGameWindow* src) {
    for(int i = 0; i < src->numOfPieces; i++) {
        destroyChessPiece(src->pieces[i]);
    }
}

ChessRect **createGameWindowChessRects(SDL_Renderer *renderer) {
    if (renderer == NULL ) {
        return NULL ;
    }
    ChessRect** rects = malloc(64 * sizeof(ChessRect*));
    if (rects == NULL ) {
        return NULL ;
    }

    SDL_Rect rect, darea;

    /* Get the Size of drawing surface */
    SDL_RenderGetViewport(renderer, &darea);
    darea.w = 0.7 * darea.w;
    darea.h = 0.7 * darea.h;
    int i = 0;

    for (int y = 7; y > -1; y--) {
        for (int x = 0; x < 8; x++) {
            rect.w = darea.w / 8;
            rect.h = darea.h / 8;
            rect.x = x * rect.w + darea.w * 0.4;
            rect.y = y * rect.h + darea.w * 0.15;

            if (y % 2 == 0) {
                if (x % 2 == 0) {
                    rects[i] = createChessRect(renderer, &rect, CHESS_RECT_COLOR_GREY, x, 7 - y);
                } else {
                    rects[i] = createChessRect(renderer, &rect, CHESS_RECT_COLOR_WHITE, x, 7 - y);
                }
            } else {
                if (x % 2 != 0) {
                    rects[i] = createChessRect(renderer, &rect, CHESS_RECT_COLOR_GREY, x, 7 - y);
                } else {
                    rects[i] = createChessRect(renderer, &rect, CHESS_RECT_COLOR_WHITE, x, 7 - y);
                }
            }

            i++;

        }
    }

    return rects;
}

ChessGameWindow *createGameWindow(GameSettings *settings) {
    if (settings == NULL) return NULL;

    const int numOfButtons = 6;
    const int numOfRects = 64;
    const int numOfPieces = 32;

    ChessGameWindow* res = malloc(sizeof(ChessGameWindow));
    SDL_Window* window = SDL_CreateWindow("Tests", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    GameState* game = GameStateCreate(settings->difficulty, settings->userColor, settings->gameMode);
    ChessRect** rects = createGameWindowChessRects(renderer);
    ChessPiece** pieces = createGameWindowChessPieces(renderer, game->gameBoard, numOfPieces);
    ChessButton** buttons = createGameWindowChessButtons(renderer, settings->gameMode);

    if (res == NULL || window == NULL || renderer == NULL || game == NULL || rects == NULL || pieces == NULL || buttons == NULL ) {
        free(res);
        free(buttons);
        free(rects);
        free(pieces);
        GameStateDestroy(game);
        GameSettingsDestroy(settings);
        //We first destroy the renderer
        SDL_DestroyRenderer(renderer); //NULL safe
        SDL_DestroyWindow(window); //NULL safe
        return NULL ;
    }

    res->buttons = buttons;
    res->rects = rects;
    res->pieces = pieces;
    res->numOfButtons = numOfButtons;
    res->numOfRects = numOfRects;
    res->numOfPieces = numOfPieces;
    res->window = window;
    res->windowRenderer = renderer;
    res->settings = settings;
    res->game = game;

    return res;
}

void destroyGameWindow(ChessGameWindow *src) {
    if (src == NULL ) {
        return;
    }

    for (int i = 0; i < src->numOfButtons; i++) {
        destroyChessButton(src->buttons[i]);
    }

    for (int i = 0; i < src->numOfRects; i++) {
        destroyChessRect(src->rects[i]);
    }

    for (int i = 0; i < src->numOfPieces; i++) {
        destroyChessPiece(src->pieces[i]);
    }

    free(src->buttons);
    free(src->pieces);
    free(src->rects);
    GameStateDestroy(src->game);
    SDL_DestroyRenderer(src->windowRenderer);
    SDL_DestroyWindow(src->window);

    free(src);
}
void drawGameWindow(ChessGameWindow *src) {
    if (src == NULL ) {
        return;
    }

    //Draw window
    SDL_SetRenderDrawColor(src->windowRenderer, 255, 255, 255, 255);
    SDL_RenderClear(src->windowRenderer);

    drawChessBoard(src->windowRenderer);
    for (int i = 0; i < src->numOfPieces; i++) {
        drawChessPiece(src->pieces[i]);
    }


    for (int i = 0; i < src->numOfButtons; i++) {
        drawChessButton(src->buttons[i]);
    }

    SDL_RenderPresent(src->windowRenderer);
}

CHESS_GAME_EVENT handleEventGameWindow(ChessGameWindow *src, SDL_Event *event){
    if(src == NULL || event==NULL){
        return CHESS_GAME_EXIT;
    }
    ChessPiece* droppedPiece = NULL;
    ChessRect* droppedRect = NULL;

    for (int i = 0; i < src->numOfPieces; i++) {
        PIECE_CLICK_EVENT clickEvent =  handleChessPieceEvent(src->pieces[i], event);

        switch(clickEvent) {
            case CHESS_DROP_PIECE:
                droppedPiece = src->pieces[i];
                break;
            case CHESS_DRAG_PIECE:
                break;
            case PIECE_CLICKED_NONE:break;
            case CHESS_MOTION_PIECE:break;
        }
    }

    for (int i = 0; i < src->numOfRects; i++) {
        RECT_CLICK_EVENT clickEvent =  handleChessRectEvent(src->rects[i], event);

        switch(clickEvent) {
            case CHESS_DROP_RECT:
                droppedRect = src->rects[i];
                break;
            case RECT_CLICKED_NONE:break;
        }
    }


    if (droppedPiece != NULL && droppedRect != NULL) {
        SDL_Rect rect;
        if (SDL_IntersectRect(droppedPiece->location, droppedRect->location, &rect)) {
            Move* userMove = MoveCreate(droppedPiece->y, droppedPiece->x, droppedRect->y, droppedRect->x);
            bool isMoveSuccessful = handleUserMove(src->game, userMove);

            if (isMoveSuccessful) {

//                droppedPiece->location = spCopyRect(droppedRect->location);
//                droppedPiece->previousLocation = spCopyRect(droppedRect->location);

                if(gameBoardIsStalemate(src->game->gameBoard)){
                    // TODO: actually thehre is waste because we check for mate twice
                    MoveDestroy(userMove); // TODO: was this used?
                    return CHESS_GAME_STALEMATE;
                }
                if (gameBoardIsMate(src->game->gameBoard, src->game->gameBoard->whiteTurn)) {
                    MoveDestroy(userMove); // TODO: was this used?
                    return CHESS_GAME_MATE;
                }

                if (gameBoardIsCheck(src->game->gameBoard, src->game->gameBoard->whiteTurn)) {
                    return CHESS_GAME_CHECK;
                }

                return CHESS_GAME_MOVE_SUCCESS;
            } else {
                return CHESS_GAME_MOVE_FAIL;
            }
        }
    } else if (droppedPiece != NULL && droppedRect == NULL) {
        droppedPiece->location = spCopyRect(droppedPiece->previousLocation);
    }

    for(int i = 0 ;i<src->numOfButtons;i++){
        BUTTON_CLICK_EVENT clickEvent = handleChessButtonEvent(src->buttons[i], event);
        switch (clickEvent) {
            case CHESS_CLICKED_RESTART:
                return CHESS_GAME_RESTART;
            case CHESS_CLICKED_SAVE:
                return CHESS_GAME_SAVE;
            case CHESS_CLICKED_LOAD:
                return CHESS_GAME_LOAD;
            case CHESS_CLICKED_UNDO:
                return CHESS_GAME_UNDO;
            case CHESS_CLICKED_MAIN_MENU:
                return CHESS_GAME_MAIN_MENU;
            case CHESS_CLICKED_QUIT:
                return CHESS_GAME_EXIT;
            case CHESS_CLICKED_NEW_GAME:break;
            case CHESS_CLICKED_NONE:break;
            case CHESS_CLICKED_1PLAYER:break;
            case CHESS_CLICKED_2PLAYER:break;
            case CHESS_CLICKED_NOOB:break;
            case CHESS_CLICKED_EASY:break;
            case CHESS_CLICKED_MODERATE:break;
            case CHESS_CLICKED_HARD:break;
            case CHESS_CLICKED_WHITE:break;
            case CHESS_CLICKED_BLACK:break;
            case CHESS_CLICKED_BACK:break;
            case CHESS_CLICKED_START:break;
        }
    }

    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE) return CHESS_GAME_EXIT;

    return CHESS_GAME_NONE;
}

void hideGameWindow(ChessGameWindow* src) {
    SDL_HideWindow(src->window);
}

void showGameWindow(ChessGameWindow* src) {
    SDL_ShowWindow(src->window);
}

void drawChessBoard(SDL_Renderer *renderer) {
    SDL_Rect rect, darea;

    /* Get the Size of drawing surface */
    SDL_RenderGetViewport(renderer, &darea);
    darea.w = 0.7 * darea.w;
    darea.h = 0.7 * darea.h;

    for (int y = 7; y > -1; y--) {
        for (int x = 0; x < 8; x++) {
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0xFF);

            rect.w = darea.w / 8;
            rect.h = darea.h / 8;
            rect.x = x * rect.w + darea.w * 0.4;
            rect.y = y * rect.h + darea.w * 0.15;

            if (y % 2 == 0) {
                if (x % 2 == 0) {
                    SDL_RenderFillRect(renderer, &rect);
                }
            } else {
                if (x % 2 != 0) {
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }
    }
}

void drawChessGamePieces(ChessGameWindow* src) {
    resetGameWindowChessPieces(src);
    int numOfPieces = 0;

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            char piece = src->game->gameBoard->board[y][x];
            if (piece != CH_PIECE_EMPTY) numOfPieces++;
        }
    }
    src->pieces = createGameWindowChessPieces(src->windowRenderer, src->game->gameBoard, numOfPieces);
    src->numOfPieces = numOfPieces;
    for (int i = 0; i < src->numOfPieces; i++) {
        if (src->pieces[i] != NULL) drawChessPiece(src->pieces[i]);
    }
}

void destroyGameWindowButtons(ChessButton** buttons, int numOfButtons) {
    for (int i = 0; i < numOfButtons; i++) {
        destroyChessButton(buttons[i]);
    }

    free(buttons);
}