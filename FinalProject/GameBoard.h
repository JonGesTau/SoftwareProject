//
// Created by Dror on 2017-08-18.
//

#ifndef CHESS1_GAMEBOARD_H
#define CHESS1_GAMEBOARD_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "Moves.h"

#define CH_PIECE_EMPTY 0
#define CH_PIECE_PAWN 1
#define CH_PIECE_BISHOP 2
#define CH_PIECE_KNIGHT 3
#define CH_PIECE_ROOK 4
#define CH_PIECE_QUEEN 5
#define CH_PIECE_KING 6

#define whichPiece(p) ((unsigned char)(abs(p)))
#define isWhite(p) ((p) > 0)
#define isBlack(p) ((p) < 0)
#define isEmpty(p) ((p) == CH_PIECE_EMPTY)
#define sign(p) ((p)>0 ? 1 : ((p)==0 ? 0 : -1))
#define chPieceScore(p) (((int[]){0,1,3,3,5,9,100})[whichPiece(p)])*(isBlack(p)?-1:1)
#define isLegalCoordinate(y, x) ((((unsigned char)(y))<8) && (((unsigned char)(x))<8))

/**
 * This data structure represents the game board.
 * It contains signed char board[y][x], representing the board state,
 * and bool whiteTurn which is true IFF it's white turn to play.
 */
typedef struct chess_gameboard{
    signed char board[8][8];
    bool whiteTurn;
} GameBoard;

/**
 * Creates a clean GameBoard object.
 * @return Pointer to an allocated GameBoard, with white to play and empty board.
 */
GameBoard* gameBoardCreate();

/**
 * Allocates a new GameBoard and copies an existing board into it.
 * @param src - the original board to be copied.
 * @return a pointer to a newly allocated GameBoard with exactly the same data as src.
 */
GameBoard* gameBoardCopy(GameBoard* src);

/**
 * Frees memory for a GameBoard.
 * @param src - the GameBoard to free.
 */
void gameBoardDestroy(GameBoard* src);

/**
 * Clears the board and sets up pieces for a fresh game.
 * @param game - the GameBoard to be set up.
 */
void gameBoardSetup(GameBoard *game);


/**
 * Checks whether a given move <y1,x1> -> <y2,x2> is legal on a given board.
 * Makes sure the coordinates are legal and contain a piece, that the piece is moved
 * according to the rules, and that the play does not result in self-check.
 * @param game - the board on which we test legality
 * @param y1 - origin y coordinate
 * @param x1 - origin x coordinate
 * @param y2 - dest y coordinate
 * @param x2 - dest x coordinate
 * @return true if the move is legal.
 */
bool gameBoardIsLegalMove(GameBoard *game, unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2);

/**
 * Subprocedure for gameBoardIsLegalMove, checks whether <y1,x1> -> <y2,x2> is a legal move for a rook.
 * @param game - the board on which we test legality
 * @param y1 - origin y coordinate
 * @param x1 - origin x coordinate
 * @param y2 - dest y coordinate
 * @param x2 - dest x coordinate
 * @return true if the move is legal.
 */
bool gameBoardIsLegalRookMove(GameBoard *game, unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2);

/**
 * Subprocedure for gameBoardIsLegalMove, checks whether <y1,x1> -> <y2,x2> is a legal move for a bishop.
 * @param game - the board on which we test legality
 * @param y1 - origin y coordinate
 * @param x1 - origin x coordinate
 * @param y2 - dest y coordinate
 * @param x2 - dest x coordinate
 * @return true if the move is legal.
 */
bool gameBoardIsLegalBishopMove(GameBoard *game, unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2);

/**
 * Applies the move <y1,x1> -> <y2,x2> to a given board and switches whiteTurn value.
 * This is called only from GameStatePerformMove.
 * @param game - the board.
 * @param y1 - origin y coordinate
 * @param x1 - origin x coordinate
 * @param y2 - dest y coordinate
 * @param x2 - dest x coordinate
 * @return true if the move was performed successfully.
 */
bool gameBoardPerformMove(GameBoard* game, unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2);

/**
 * Undoes a move on the board, given a HistoryMove*. Called only from GameStateUndoMove.
 * Moves the piece to the original spot and replaces any missing pieces.
 * Switches whiteTurn value.
 * @param game - the board.
 * @param hist - the data of the move to be undoed.
 * @return true if successful.
 */
bool gameBoardUndoMove(GameBoard* game, HistoryMove* hist);

/**
 * Checks whether the piece at <y1,x1> is threatened by any other piece.
 * @param game - the board
 * @param y1 - y coord
 * @param x1 - x coord
 * @return true if the piece at <y1,x1> can be captured on the next turn, self-check notwithstanding.
 */
bool gameBoardIsThreatened(GameBoard *game, unsigned char y1, unsigned char x1);

/**
 * Checks whether one of the players is in check. Finds the king and applies gameBoardIsThreatened to it.
 * @param game - the board
 * @param isWhite - the side for which we check for check.
 * @return true IFF the king of that player is in check.
 */
bool gameBoardIsCheck(GameBoard *game, bool isWhite);

/**
 * Checks whether a given player is in mate. Makes sure that they are in check using gameBoardIsCheck,
 * and that any possible moves also result in check.
 * @param game - the board.
 * @param isWhite - the player for which we check.
 * @return true IFF the player is in check.
 */
bool gameBoardIsMate(GameBoard *game, bool isWhite);

/**
 * Checks for a stalemate, the next player to play is given by game->whiteTurn.
 * @param game - the board.
 * @return true IFF the current player has no legal moves but is not in check.
 */
bool gameBoardIsStalemate(GameBoard *game);


/**
 * Generates a MoveList* containing all legal moves for one of the players, by scanning the board
 * and Pushing all possible moves, using the functions gameBoardMovesXXX.
 * @param game - the board.
 * @param isWhite - the player for which we check.
 * @return pointer to the MoveList containing the moves.
 */
MoveList* gameBoardAllMoves(GameBoard* game, bool isWhite);

/**
 * Pushes to the MoveList all possible moves for a pawn at <y,x>.
 * @param game - the board.
 * @param moves - the move list into which we push.
 * @param y - y coord.
 * @param x - x coord.
 */
void gameBoardMovesPawn(GameBoard* game, MoveList* moves, unsigned char y, unsigned char x);

/**
 * Pushes to the MoveList all possible moves for a bishop at <y,x>.
 * @param game - the board.
 * @param moves - the move list into which we push.
 * @param y - y coord.
 * @param x - x coord.
 */
void gameBoardMovesBishop(GameBoard* game, MoveList* moves, unsigned char y, unsigned char x);

/**
 * Pushes to the MoveList all possible moves for a knight at <y,x>.
 * @param game - the board.
 * @param moves - the move list into which we push.
 * @param y - y coord.
 * @param x - x coord.
 */
void gameBoardMovesKnight(GameBoard* game, MoveList* moves, unsigned char y, unsigned char x);

/**
 * Pushes to the MoveList all possible moves for a rook at <y,x>.
 * @param game - the board.
 * @param moves - the move list into which we push.
 * @param y - y coord.
 * @param x - x coord.
 */
void gameBoardMovesRook(GameBoard* game, MoveList* moves, unsigned char y, unsigned char x);

/**
 * Pushes to the MoveList all possible moves for a king at <y,x>.
 * @param game - the board.
 * @param moves - the move list into which we push.
 * @param y - y coord.
 * @param x - x coord.
 */
void gameBoardMovesKing(GameBoard* game, MoveList* moves, unsigned char y, unsigned char x);

#endif //CHESS1_GAMEBOARD_H
