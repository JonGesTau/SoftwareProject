//
// Created by jonathangescheit on 9/30/17.
//


#include "GameFlowHelper.h"

bool handleUserMove(struct chess_gamestate * game, struct move * userMove) {
    if(!isLegalCoordinate(userMove->y1, userMove->x1) || !isLegalCoordinate(userMove->y2, userMove->x2)){
        printf(STR_ERR_INVALID_POSITION);
        return false;
    }

    if(game->gameBoard->board[userMove->y1][userMove->x1] == CH_PIECE_EMPTY ||
            isWhite(game->gameBoard->board[userMove->y1][userMove->x1]) != game->gameBoard->whiteTurn){
        printf(STR_ERR_WRONG_COLOR);
        return false;
    }

    if (!gameBoardIsLegalMove(game->gameBoard, userMove->y1, userMove->x1, userMove->y2, userMove->x2)){
        printf(STR_ERR_ILLEGAL_MOVE);
        return false;
    }

    return GameStatePerformMove(game, userMove->y1, userMove->x1, userMove->y2, userMove->x2);
}