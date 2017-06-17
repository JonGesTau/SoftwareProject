#include "SPFIARGame.h"

/**
 * SPFIARGame Summary:
 *
 * A container that represents a classic connect-4 game, a two players 6 by 7
 * board game (rows X columns). The container supports the following functions.
 *
 * spFiarGameCreate           - Creates a new game board
 * spFiarGameCopy             - Copies a game board
 * spFiarGameDestroy          - Frees all memory resources associated with a game
 * spFiarGameSetMove          - Sets a move on a game board
 * spFiarGameIsValidMove      - Checks if a move is valid
 * spFiarGameUndoPrevMove     - Undoes previous move made by the last player
 * spFiarGamePrintBoard       - Prints the current board
 * spFiarGameGetCurrentPlayer - Returns the current player
 *
 */


/**
 * Creates a new game with a specified history size. The history size is a
 * parameter which specifies the number of previous moves to store. If the number
 * of moves played so far exceeds this parameter, then first moves stored will
 * be discarded in order for new moves to be stored.
 *
 * @historySize - The total number of moves to undo,
 *                a player can undo at most historySizeMoves turns.
 * @return
 * NULL if either a memory allocation failure occurs or historySize <= 0.
 * Otherwise, a new game instant is returned.
 */
SPFiarGame* spFiarGameCreate(int historySize){
	if(historySize <= 0)
		return NULL;
	SPFiarGame* game = malloc(sizeof(SPFiarGame));
	if(game == 0)
		return NULL;
	game->gameHistory = spArrayListCreate(historySize);
	// you said historySize = # moves player can undo
	// but player can only do half that!
	if(game->gameHistory == 0){
		free(game);
		return NULL;
	}
	
	for(int i = 0; i<SP_FIAR_GAME_N_COLUMNS; i++){
		game -> tops[i] = 0;
		for(int j = 0; j<SP_FIAR_GAME_N_ROWS; j++){
			game->gameBoard[j][i] = SP_FIAR_GAME_EMPTY_ENTRY;
		}
	}
	game->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	
	return game;
}

/**
 *	Creates a copy of a given game.
 *	The new copy has the same status as the src game.
 *
 *	@param src - the source game which will be copied
 *	@return
 *	NULL if either src is NULL or a memory allocation failure occurred.
 *	Otherwise, an new copy of the source game is returned.
 *
 */
SPFiarGame* spFiarGameCopy(SPFiarGame* src){
	if(src == NULL)
		return NULL;
	SPFiarGame* game2 = malloc(sizeof(SPFiarGame));
	if(game2 == NULL)
		return NULL;
	
	game2 -> gameHistory = spArrayListCopy(src->gameHistory);
	if(game2 -> gameHistory == NULL){
		free(game2);
		return NULL;
	}
	
	game2 -> currentPlayer = src -> currentPlayer;
	
	for(int i = 0; i<SP_FIAR_GAME_N_COLUMNS; i++){
		game2 -> tops[i] = src -> tops[i];
		for(int j = 0; j<SP_FIAR_GAME_N_ROWS; j++){
			game2 -> gameBoard[j][i] = src -> gameBoard[j][i];
		}
	}
	
	return game2;
}

/**
 * Frees all memory allocation associated with a given game. If src==NULL
 * the function does nothing.
 *
 * @param src - the source game
 */
void spFiarGameDestroy(SPFiarGame* src){
	if(src == NULL)
		return;
	spArrayListDestroy(src -> gameHistory);
	free(src);
}

/**
 * Sets the next move in a given game by specifying column index. The
 * columns are 0-based and in the range [0,SP_FIAR_GAME_N_COLUMNS -1].
 *
 * @param src - The target game
 * @param col - The target column, the columns are 0-based
 * @return
 * SP_FIAR_GAME_INVALID_ARGUMENT - if src is NULL or col is out-of-range
 * SP_FIAR_GAME_INVALID_MOVE - if the given column is full.
 */
SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col){
	if(src == NULL || col >= SP_FIAR_GAME_N_COLUMNS)
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	if(!spFiarGameIsValidMove(src, col))
		return SP_FIAR_GAME_INVALID_MOVE;
	
	src -> gameBoard[src->tops[col]][col] = src->currentPlayer;
	src -> tops[col] ++;
	if(src -> currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL)
		src -> currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
	else
		src -> currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	
	if(spArrayListAddLast(src -> gameHistory, col) == SP_ARRAY_LIST_FULL){
		// TODO: possible unhandled exception
		spArrayListRemoveFirst(src -> gameHistory);
		spArrayListAddLast(src -> gameHistory, col);
	}
	
	return SP_FIAR_GAME_SUCCESS; // TODO: documentation didn't say this
}

/**
 * Checks if a disk can be put in the specified column.
 *
 * @param src - The source game
 * @param col - The specified column
 * @return
 * true  - if the a disc can be put in the target column
 * false - otherwise.
 */
bool spFiarGameIsValidMove(SPFiarGame* src, int col){
	if(src -> tops[col] >= SP_FIAR_GAME_N_ROWS)
		return false;
	return true;
}

/**
 * Removes a disc that was put in the previous move and changes the current
 * player's turn. If the user invoked this command more than historySize times
 * in a row then an error occurs.
 *
 * @param src - The source game
 * @return
 * SP_FIAR_GAME_INVALID_ARGUMENT - if src == NULL
 * SP_FIAR_GAME_NO_HISTORY       - if the user invoked this function more then
 *                                 historySize in a row.
 * SP_FIAR_GAME_SUCCESS          - on success. The last disc that was put on the
 *                                 board is removed and the current player is changed
 */
SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src){
	if(src == NULL || src -> gameHistory == NULL)
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	if(spArrayListIsEmpty(src -> gameHistory))
		return SP_FIAR_GAME_NO_HISTORY;
	
	int col = spArrayListGetLast(src->gameHistory);
	spArrayListRemoveLast(src->gameHistory); //TODO: unhandled exception
	src->tops[col] --;
	src->gameBoard[src->tops[col]][col] = SP_FIAR_GAME_EMPTY_ENTRY;
	// the above is required because of printing and for win checks
	
	if(src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL)
		src->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
	else
		src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	// strictly speaking this is not necessary since undos come 2 at a time
	
	return SP_FIAR_GAME_SUCCESS;
}

/**
 * On success, the function prints the board game. If an error occurs, then the
 * function does nothing. The characters 'X' and 'O' are used to represent
 * the discs of player 1 and player 2, respectively.
 *
 * @param src - the target game
 * @return
 * SP_FIAR_GAME_INVALID_ARGUMENT - if src==NULL
 * SP_FIAR_GAME_SUCCESS - otherwise
 *
 */
SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src){
	if(src == NULL)
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	
	for(int row = SP_FIAR_GAME_N_ROWS - 1; row >= 0; row--){
		printf("|");
		for(int col = 0; col < SP_FIAR_GAME_N_COLUMNS; col++){
			printf(" %c", src->gameBoard[row][col]);
		}
		printf(" |\n");
	}
	
	for(int i = 0; i < 2*SP_FIAR_GAME_N_COLUMNS + 3; i++){
		printf("-");
	}
	
	printf("\n ");
	for(int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
		printf(" %d", (i+1));
	}

    printf("  ");
	printf("\n");
	
	return SP_FIAR_GAME_SUCCESS;
}

/**
 * Returns the current player of the specified game.
 * @param src - the source game
 * @return
 * SP_FIAR_GAME_PLAYER_1_SYMBOL - if it's player one's turn
 * SP_FIAR_GAME_PLAYER_2_SYMBOL - if it's player two's turn
 * SP_FIAR_GAME_EMPTY_ENTRY     - otherwise
 */
char spFiarGameGetCurrentPlayer(SPFiarGame* src){
	// TODO: did not check src == NULL
	return src -> currentPlayer;
}

/**
* Checks if there's a winner in the specified game status. The function returns either
* SP_FIAR_GAME_PLAYER_1_SYMBOL or SP_FIAR_GAME_PLAYER_2_SYMBOL in case there's a winner, where
* the value returned is the symbol of the winner. If the game is over and there's a tie
* then the value SP_FIAR_GAME_TIE_SYMBOL is returned. in any other case the null characters
* is returned.
* @param src - the source game
* @return
* SP_FIAR_GAME_PLAYER_1_SYMBOL - if player 1 won
* SP_FIAR_GAME_PLAYER_2_SYMBOL - if player 2 won
* SP_FIAR_GAME_TIE_SYMBOL - If the game is over and there's a tie
* null character - otherwise
*/
char spFiarCheckWinner(SPFiarGame* src){ // TODO: test this
	const int SPAN = SP_FIAR_GAME_SPAN;
	const int COLS = SP_FIAR_GAME_N_COLUMNS;
	const int ROWS = SP_FIAR_GAME_N_ROWS;
	// here its enough only to check for the last player that moved
	// because for the other player, we already checked last turn
	char player = SP_FIAR_GAME_PLAYER_1_SYMBOL; // which player to check
	if(src -> currentPlayer == player)
		player = SP_FIAR_GAME_PLAYER_2_SYMBOL;
	
	bool isFull = true; // set to false upon meeting empty entry
	
	
	for(int col = 0; col < COLS; col++){
		for(int row = 0; row < ROWS; row++){
			if(src -> gameBoard[row][col] == SP_FIAR_GAME_EMPTY_ENTRY){
				isFull = false;
				break;
			}
			if(src -> gameBoard[row][col] != player){
				continue;
			}
			
			if(row <= ROWS - SPAN){
				// check up the row
				if(src -> gameBoard[row+1][col] == player
				  && src -> gameBoard[row+2][col] == player
				  && src -> gameBoard[row+3][col] == player)
					return player;
				
			}
			if(col <= COLS - SPAN){
				// check rightways
				if(src -> gameBoard[row][col+1] == player
				  && src -> gameBoard[row][col+2] == player
				  && src -> gameBoard[row][col+3] == player)
					return player;
				
				if(row <= ROWS - SPAN){
					// check right-up
					if(src -> gameBoard[row+1][col+1] == player
					  && src -> gameBoard[row+2][col+2] == player
					  && src -> gameBoard[row+3][col+3] == player)
						return player;
				}
				if(row >= SPAN - 1){
					// check right-down
					if(src -> gameBoard[row-1][col+1] == player
					  && src -> gameBoard[row-2][col+2] == player
					  && src -> gameBoard[row-3][col+3] == player)
						return player;
				}
			}
		}
	}
	
	if(isFull)
		return SP_FIAR_GAME_TIE_SYMBOL;
	return '\0';
}
