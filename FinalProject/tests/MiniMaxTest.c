//
// Created by Dror on 2017-09-18.
//

#include "MiniMaxTest.h"


int MiniMaxTestScore(){
    GameBoard* board = gameBoardCreate();
    gameBoardSetup(board);

    printf("Before game: %d\n", miniMaxBoardScore(board));
    board->board[1][0] = CH_PIECE_EMPTY;
    printf("-pawn: %d\n", miniMaxBoardScore(board));
    board->board[6][7] = CH_PIECE_EMPTY;
    printf("0: %d\n", miniMaxBoardScore(board));
    board->board[7][3] = CH_PIECE_EMPTY;
    printf("+queen: %d\n", miniMaxBoardScore(board));
    board->board[0][2] = CH_PIECE_EMPTY;
    printf("+queen-bishop: %d\n", miniMaxBoardScore(board));
    board->board[7][1] = CH_PIECE_EMPTY;
    printf("+queen-bishop+knight: %d\n", miniMaxBoardScore(board));
    /*board->board[0][0] = CH_PIECE_EMPTY;
    printf("1: %d\n", miniMaxBoardScore(board));
    board->board[0][0] = CH_PIECE_EMPTY;
    printf("1: %d\n", miniMaxBoardScore(board));
*/
    gameBoardDestroy(board);
  return 1;
}