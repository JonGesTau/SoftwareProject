//
// Created by Jonathan Gescheit on 9/27/17.
//

#include "ChessPiece.h"
//You need a create function:
ChessPiece *
createChessPiece(SDL_Renderer *windowRender, SDL_Rect *location, PieceType type, PieceColor color, int x, int y) {
    if (windowRender == NULL || location == NULL) {
        return NULL ;
    }
    //Allocate data
    ChessPiece* res = (ChessPiece*) malloc(sizeof(ChessPiece));
    const char* activeImage = getPieceImg(type, color);
    SDL_Surface* loadingSurface = SDL_LoadBMP(activeImage);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(windowRender, loadingSurface);
    if (res == NULL || loadingSurface == NULL || texture == NULL) {
        free(res);
        SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
        SDL_DestroyTexture(texture); //It is safe to pass NULL
        return NULL ;
    }
    SDL_FreeSurface(loadingSurface); //Surface is not actually needed after texture is created
    res->texture = texture;
    res->location = spCopyRect(location);
    res->previousLocation = spCopyRect(location);
    res->windowRenderer = windowRender;
    res->type = type;
    res->color = color;
    res->isDragged = false;
    res->x = x;
    res->y = y;
    return res;
}

//You need this function in order to destroy all data Associate with a button:
void destroyChessPiece(ChessPiece* src) {
    if (src == NULL ) {
        return;
    }
    free(src->location);
    SDL_DestroyTexture(src->texture);
    free(src);
}

PIECE_CLICK_EVENT handleChessPieceEvent(ChessPiece *src, SDL_Event *event) {
    if (src == NULL || event == NULL ) {
        return PIECE_CLICKED_NONE; //Better to return an error value
    }

    if (src->type != CHESS_PIECE_EMPTY) {
        if (event->type == SDL_MOUSEBUTTONDOWN) {
            SDL_Point point;
            point.x = event->button.x;
            point.y = event->button.y;
            if (SDL_PointInRect(&point, src->location)) {
                src->isDragged = true;
                src->previousLocation = spCopyRect(src->location);
                return CHESS_DRAG_PIECE;
            }
        }

        if (event->type == SDL_MOUSEBUTTONUP) {
            if (src->isDragged) {
                src->isDragged = false;
                return CHESS_DROP_PIECE;
            }
        }

        if (event->type == SDL_MOUSEMOTION) {
            if (src->isDragged) {
                src->location->x = event->motion.x - src->location->w / 2;
                src->location->y = event->motion.y - src->location->h / 2;
                return CHESS_MOTION_PIECE;
            }
        }
    }

    return PIECE_CLICKED_NONE;

}

void drawChessPiece(ChessPiece* src) {
    if (src == NULL ) {
        return;
    }

    SDL_RenderCopy(src->windowRenderer, src->texture, NULL, src->location);
}

char* getPieceImg(PieceType type, PieceColor color) {
    if (type == CHESS_PIECE_EMPTY) return whiteRookImg;
    if (color == CHESS_PIECE_COLOR_WHITE) {
        // TODO: return null img sort of thing
        switch (type) {
            case CHESS_PIECE_ROOK:
                return whiteRookImg;
            case CHESS_PIECE_KING:
                return whiteKingImg;
            case CHESS_PIECE_QUEEN:
                return whiteQueenImg;
            case CHESS_PIECE_BISHOP:
                return whiteBishopImg;
            case CHESS_PIECE_KNIGHT:
                return whiteKnightImg;
            case CHESS_PIECE_PAWN:
                return whitePawnImg;
            case CHESS_PIECE_EMPTY:
                return whiteRookImg;
        }
    } else {
        switch (type) {
            case CHESS_PIECE_ROOK:
                return blackRookImg;
            case CHESS_PIECE_KING:
                return blackKingImg;
            case CHESS_PIECE_QUEEN:
                return blackQueenImg;
            case CHESS_PIECE_BISHOP:
                return blackBishopImg;
            case CHESS_PIECE_KNIGHT:
                return blackKnightImg;
            case CHESS_PIECE_PAWN:
                return blackPawnImg;
            case CHESS_PIECE_EMPTY:
                return blackRookImg;
        }
    }

    return whiteRookImg;
}