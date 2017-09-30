//
// Created by Dror on 2017-08-19.
//

/*
 * While GameBoard only holds a board position,
 * this also holds other game settings such as history, difficulty, game mode etc.
 */


#ifndef CHESS1_GAMESTATE_H
#define CHESS1_GAMESTATE_H

#define MAX_UNDO 3

#include "GameBoard.h"
#include "Moves.h"

// contains everything about a game, including board, game settings and history
/**
 * This data structure represents an ongoing game, and contains both the settings and the board state.
 */
typedef struct chess_gamestate{
    GameBoard* gameBoard;
    char difficulty; // 1 to 4
    char mode; // 1 or 2 human players
    bool isPlayerWhite;
    HistoryMove* history[MAX_UNDO*2]; // each undo also undoes opponent
} GameState;

/**
 * Allocates a GameState object given the parameters.
 * @param difficulty
 * @param isPlayerWhite
 * @param mode
 * @return a pointer to the allocated object.
 */
GameState* GameStateCreate(char difficulty, bool isPlayerWhite, char mode);

/**
 * Frees from memory the given GameState object and all other associated memory (gameBoard, history).
 * @param game - the object to be freed.
 */
void GameStateDestroy(GameState* game);

/**
 * Applies a move to a GameState object. Saves it in the appropriate slot in the history[] array,
 * and uses gameBoardPerformMove to apply it to the board.
 * @param game - the GameState on which the move is performed.
 * @param y1 - origin y coord.
 * @param x1 - origin x coord.
 * @param y2 - dest y coord.
 * @param x2 - dest x coord.
 * @return true if the move was performed successfully.
 */
bool GameStatePerformMove(GameState* game, unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2);

/**
 * Returns the most recent move saved in the history array.
 * @param game
 * @return A pointer to the most recent move.
 */
HistoryMove* GameStateGetLastMove(GameState* game);

/**
 * Undoes the last move from the history array, given it is not empty.
 * @param game
 */
void GameStateUndoHistoryMove(GameState* game);


#endif //CHESS1_GAMESTATE_H
