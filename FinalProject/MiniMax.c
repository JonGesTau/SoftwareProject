//
// Created by Dror on 2017-08-19.
//

/*
 * perhaps remember past searches for expert ai? just to help with pruning?
 */

#include "MiniMax.h"
#include "GameState.h"

ScoredMove* miniMaxGetBestMove(GameBoard *game, char depth, char maxDepth, bool isMax, int parentBest) {
    //GameBoard* temp;
    int score = 0;
    //int choice = 0; // perhaps create a move struct?
    Move* bestMove = MoveCreate(9,9,9,9); // illegal move until a legal one is found
    int bestScore = isMax ? INT_MIN : INT_MAX;
    //return 0;
    // TODO: be sure to deal with the situation of no moves!
    /*
     * if this is a maximum node, therefore parent is minimum node (make sure parent exists!)
     * we know the current best score for our parent, they will choose the smallest one.
     * suppose we now find a branch with a higher score than that,
     * since we are a maximum node, we will def. choose something at least as high
     * which means we will be ignored by the parent, so we can stop.
     *
     * if(parent exists && this is maximum node)
     *   if(current bestscore > parent current bestscore)
     *     return current bestscore and stop scanning.
     *
     * if(parent exists && this is minimum node)
     *   if(current bestscore < parent current bestscore)
     *     return current bestscore and stop scanning.
     *
     *
     */
    // move finding logic
    // it might be better to first store all possible moves and then loop?
    // in that case we might want to use linked list.
    MoveList* moves = gameBoardAllMoves(game, isMax);
    //MovesTestPrintMoves(moves);
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
    Move* move;

    while(lmove != NULL){
        //printf("|");
        move = lmove->move;

        // do stuff
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

    /*
     * for each possible move: // try to be efficient with the checks; if moving with the rook
     *   if legal move: // gives self-check, then moving it anywhere will
     *     temp = GameBoardCopy(game);
     *     GameBoardApply(move)
     *     if depth == 1:
     *       score = miniMaxBoardScore(temp)
     *     else:
     *       score = miniMaxGetBestMove(temp, depth-1, maxDepth, !isMax)
     *
     *     if (score > bestScore && isMax) || (score < bestScore && !isMax):
     *       bestScore = score;
     *       choice = move;
     *
     *     if(depth != maxDepth){ // there is parent
     *       if(isMax && bestScore > parentBest) return bestScore;
     *       if(!isMax && bestScore < parentBest) return bestScore;
     *
     *     gameBoardDestroy(temp);
     */

    if(bestMove -> y1 == 9){
        printf("no possible moves\n");
        bestScore = 0; // tie
        // TODO: no move found
        if(gameBoardIsCheck(game, game->whiteTurn)){
            bestScore = game->whiteTurn ? INT_MIN : INT_MAX;
        }
    }

    //printf("%d ", bestScore);
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

/*
int spMiniMaxNodeEvaluate(SPFiarGame* board, unsigned int depth, unsigned int maxDepth, bool sign){
    // sign is True -> return max score (find best move for 1st player)
    SPFiarGame* tempBoard;
    int choice = 0;
    int score = 0;
    int bestScore = sign ? INT_MIN : INT_MAX;

    for(int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
        //printf("\ncolumn %d:",(i+1));
        if(!spFiarGameIsValidMove(board, i)){
            //printf(" invalid move!\n");
            continue;
        }else{
            tempBoard = spFiarGameCopy(board);
            spFiarGameSetMove(tempBoard, i);

            if(depth == 1){
                // find direct score
                score = spMiniMaxNodeScore(tempBoard);
            }else{
                // go deeper
                score = spMiniMaxNodeEvaluate(tempBoard, depth-1, maxDepth, !sign);
            }

            if((sign && score > bestScore) || (!sign && score < bestScore)){
                bestScore = score;
                choice = i;
            }

            spFiarGameDestroy(tempBoard);
        }
    }

    if(depth == maxDepth)
        return choice;
    return bestScore;
}*/


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
