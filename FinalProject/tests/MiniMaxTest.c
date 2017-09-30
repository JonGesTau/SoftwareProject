//
// Created by Dror on 2017-09-18.
//

#include "MiniMaxTest.h"
#include "MovesTest.h"

int MiniMaxTestDepth1(){
    GameBoard* board = gameBoardCreate();
    ScoredMove* best;
    //
    board->board[1][3] = CH_PIECE_ROOK;
    board->board[6][3] = -CH_PIECE_QUEEN;

    consoleUIPrintBoard(board);
    best = miniMaxGetBestMove(board, 1, 1, true, 0);
    printf("Best move for B is: (%d, %d) -> (%d, %d)\n", best->move->y1,best->move->x1,best->move->y2,best->move->x2);
    best = miniMaxGetBestMove(board, 1, 1, false, 0);
    printf("Best move for B is: (%d, %d) -> (%d, %d)\n", best->move->y1,best->move->x1,best->move->y2,best->move->x2);

    //
    board->board[1][6] = -CH_PIECE_ROOK;
    board->board[6][3] = -CH_PIECE_BISHOP;

    consoleUIPrintBoard(board);
    best = miniMaxGetBestMove(board, 1, 1, true, 0);
    printf("Best move for B is: (%d, %d) -> (%d, %d)\n", best->move->y1,best->move->x1,best->move->y2,best->move->x2);
    best = miniMaxGetBestMove(board, 1, 1, false, 0);
    printf("Best move for B is: (%d, %d) -> (%d, %d)\n", best->move->y1,best->move->x1,best->move->y2,best->move->x2);

    //
    board->board[5][1] = CH_PIECE_QUEEN;
    board->board[6][3] = -CH_PIECE_KNIGHT;

    consoleUIPrintBoard(board);
    best = miniMaxGetBestMove(board, 1, 1, true, 0);
    printf("Best move for B is: (%d, %d) -> (%d, %d)\n", best->move->y1,best->move->x1,best->move->y2,best->move->x2);
    best = miniMaxGetBestMove(board, 1, 1, false, 0);
    printf("Best move for B is: (%d, %d) -> (%d, %d)\n", best->move->y1,best->move->x1,best->move->y2,best->move->x2);

    gameBoardDestroy(board);
    ScoredMoveDestroy(best);
}

int MiniMaxTestDeep(){
    GameBoard* board = gameBoardCreate();
    ScoredMove* best;
    //
    board->board[1][3] = CH_PIECE_ROOK;
    board->board[2][3] = -CH_PIECE_BISHOP;
    board->board[1][6] = -CH_PIECE_PAWN;
    board->board[0][7] = CH_PIECE_ROOK; // (0,6)<->(0,7) and see what happens
    board->board[6][6] = -CH_PIECE_PAWN; // need this to avoid tie when capturing bishop

    consoleUIPrintBoard(board);
    best = miniMaxGetBestMove(board, 1, 1, true, 0);
    printf("Best move for W (1) is: (%d, %d) -> (%d, %d)\n", best->move->y1,best->move->x1,best->move->y2,best->move->x2);
    best = miniMaxGetBestMove(board, 2, 2, true, 0);
    printf("Best move for W (2) is: (%d, %d) -> (%d, %d)\n", best->move->y1,best->move->x1,best->move->y2,best->move->x2);

    //MoveList* moves = gameBoardAllMoves(board, true);
    //MovesTestPrintMoves(moves);

    gameBoardDestroy(board);
    ScoredMoveDestroy(best);
}

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

int StrangeMateTest(){
    GameBoard* game = gameBoardCreate();
    game->board[7][4] = CH_PIECE_KING;
    game->board[6][7] = -CH_PIECE_ROOK;
    game->board[5][0] = -CH_PIECE_ROOK;
    game->board[4][4] = -CH_PIECE_KNIGHT;
    game->board[0][5] = -CH_PIECE_KING;
    game->whiteTurn = false;

    consoleUIPrintBoard(game);
    ScoredMove* smv = miniMaxGetBestMove(game, 3, 3, false, 0);
    Move* mv = smv->move;
    printf("<%d,%d> -> <%d,%d>\n", mv->y1, mv->x1, mv->y2, mv->x2);
}