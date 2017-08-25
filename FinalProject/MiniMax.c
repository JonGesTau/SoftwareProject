//
// Created by Dror on 2017-08-19.
//

/*
 * perhaps remember past searches for expert ai? just to help with pruning?
 */

#include "MiniMax.h"

int miniMaxGetBestMove(GameBoard *game, char depth, char maxDepth, bool isMax, int parentBest) {
    GameBoard* temp;
    int score = 0;
    int choice = 0; // perhaps create a move struct?
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
    for(int y = 0; y<8; y++){
        for(int x = 0; x<8; x++){
            if(game -> board[y][x] == CH_PIECE_EMPTY) continue;
            if(game -> board[y][x] > 0 != isMax) continue; // making sure this piece is proper color

            char whichPiece = (char)whichPiece(game->board[y][x]);

            // TODO: we can/should have a more efficient move checking here
            int y2, x2;

            switch(whichPiece){
                case CH_PIECE_ROOK:
                    y2 = y+1;
                    x2 = x;
                    while(isLegalCoordinate(y2,x2)){
                        // see if possible
                        if(game->board[])
                        y2 ++;
                    }
            }
        }
    }
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


    if(depth == maxDepth) return choice; // this will have to change
    return bestScore;
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
