//
// Created by Dror on 2017-08-19.
//

#include "MiniMax.h"

ScoredMove* miniMaxGetBestMove(GameBoard *game, char depth, char maxDepth, bool isMax, int parentBest) {
    int score = 0;
    Move* bestMove = MoveCreate(9,9,9,9); // illegal move until a legal one is found
    int bestScore = isMax ? INT_MIN : INT_MAX;
    MoveList* moves = gameBoardAllMoves(game, isMax);
    GameBoard* temp;

    LinkedMove* lmove = MovePop(moves);
    if(lmove == NULL){
        bestScore = 0;
        if(gameBoardIsCheck(game, isMax)){
            bestScore = isMax ? INT_MIN : INT_MAX;
        }
        MoveDestroy(bestMove);
        ScoredMove* smove = ScoredMoveCreate(9, 9, 9, 9, bestScore);
        return smove;
    }
    Move* move = NULL;

    while(lmove != NULL){
        move = lmove->move;

        temp = gameBoardCopy(game);
        gameBoardPerformMove(temp, move->y1, move->x1, move->y2, move->x2);
        if(!gameBoardIsCheck(temp, isMax)){ // making sure no self-check
            if(depth == 1){
                score = miniMaxBoardScore(temp);
            } else {
                ScoredMove* result = miniMaxGetBestMove(temp, depth-1, maxDepth, !isMax, bestScore);
                score = result->score;
                ScoredMoveDestroy(result);
            }

            if(((score > bestScore) && isMax) || ((score < bestScore) && !isMax)){
                bestScore = score;
                bestMove -> y1 = move -> y1;
                bestMove -> x1 = move -> x1;
                bestMove -> y2 = move -> y2;
                bestMove -> x2 = move -> x2;
            }

            if(depth != maxDepth){ // there is a parent, pruning here
                if((isMax && (bestScore >= parentBest)) || (!isMax && (bestScore <= parentBest))){
                    ScoredMove* smove = ScoredMoveCreate(bestMove->y1, bestMove->x1,
                                                         bestMove->y2, bestMove->x2, bestScore);
                    MoveDestroy(bestMove);
                    gameBoardDestroy(temp);
                    LinkedMoveDestroy(lmove);
                    MoveListDestroy(moves);
                    return smove;
                }
            }

        }
        gameBoardDestroy(temp);

        LinkedMoveDestroy(lmove);
        lmove = MovePop(moves);
    }
    MoveListDestroy(moves);

    if(bestMove -> y1 == 9){
        bestScore = 0; // tie
        if(gameBoardIsCheck(game, game->whiteTurn)){
            bestScore = game->whiteTurn ? INT_MIN : INT_MAX;
        }
    }

    ScoredMove* smove = ScoredMoveCreate(bestMove->y1, bestMove->x1, bestMove->y2, bestMove->x2, bestScore);
    MoveDestroy(bestMove);
    return smove;
}

Move* miniMaxGetComputerMove(GameState* game){
    ScoredMove* compScoredMove = miniMaxGetBestMove(game->gameBoard, game->difficulty, game->difficulty,
                                                    game->gameBoard->whiteTurn, 0);
    Move* compMove = MoveCreate(compScoredMove->move->y1, compScoredMove->move->x1, compScoredMove->move->y2, compScoredMove->move->x2);
    ScoredMoveDestroy(compScoredMove);
    return compMove;
}

int miniMaxBoardScore(GameBoard *game){
    if(game == NULL) return 0;

    int score = 0;

    for(int y = 0; y<8; y++){
        for(int x = 0; x<8; x++){
            score += chPieceScore(game->board[y][x]);
        }
    }
    return score;
}
