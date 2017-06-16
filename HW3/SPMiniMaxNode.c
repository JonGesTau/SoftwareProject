#include "SPMiniMaxNode.h"


//Put all decleartions and constants here


int spMiniMaxNodeEvaluate(SPFiarGame* board, unsigned int depth, unsigned int maxDepth, bool sign){
	// sign is True -> return max score (find best move for 1st player)
	SPFiarGame* boards[SP_FIAR_GAME_N_COLUMNS];
	int choice = 0;
	int score = 0;
	int bestScore = sign ? INT_MIN : INT_MAX;
	
	for(int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
		if(!spFiarGameIsValidMove(board, i)){
			boards[i] = NULL;
		}else{
			boards[i] = spFiarGameCopy(board);
			spFiarGameSetMove(boards[i], i);
			
			if(depth == maxDepth){
				// find direct score
				score = spMiniMaxNodeScore(boards[i]);
			}else{
				// go deeper
				score = spMiniMaxNodeEvaluate(board, depth-1, maxDepth, !sign);
			}
			
			if((sign && score > bestScore) || (!sign && score < bestScore)){
				bestScore = score;
				choice = i;
			}
			
			spFiarGameDestroy(boards[i]);
		}
	}
	
	if(depth == 1)
		return choice;
	return score;
}



int spMiniMaxNodeScore(SPFiarGame* board){
	const int SPAN = SP_FIAR_GAME_SPAN;
	const int COLS = SP_FIAR_GAME_N_COLUMNS;
	const int ROWS = SP_FIAR_GAME_N_ROWS;
//	const char PLAYER1 = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	const int weights[SP_FIAR_GAME_SPAN-1] = {1, 2, 5}; // TODO #define
	
	int scores[SP_FIAR_GAME_SPAN][2] = {{0}}; // [][0] for negative (plyr2), [][1] for positive
	// init scores to zeros
	
	int val = 0;
	
	// note that brd = board->gameBoard
	for(int col = 0; col < COLS; col++){
		for(int row = 0; row < ROWS; row++){
			if(row <= ROWS - SPAN){ // check up the row
				val = SP_MINI_MAX_NODE_PLAYER_VAL(brd[row][col]);
				val += SP_MINI_MAX_NODE_PLAYER_VAL(brd[row+1][col]);
				val += SP_MINI_MAX_NODE_PLAYER_VAL(brd[row+2][col]);
				val += SP_MINI_MAX_NODE_PLAYER_VAL(brd[row+3][col]);
				if(val != 0){
					scores[abs(val) - 1][val < 0 ? 0 : 1] ++;
				}
			}
			if(col <= COLS - SPAN){ // check rightways
				val = SP_MINI_MAX_NODE_PLAYER_VAL(brd[row][col]);
				val += SP_MINI_MAX_NODE_PLAYER_VAL(brd[row][col+1]);
				val += SP_MINI_MAX_NODE_PLAYER_VAL(brd[row][col+2]);
				val += SP_MINI_MAX_NODE_PLAYER_VAL(brd[row][col+3]);
				if(val != 0){
					scores[abs(val) - 1][val < 0 ? 0 : 1] ++;
				}
				
				if(row <= ROWS - SPAN){ // check right-up
					val = SP_MINI_MAX_NODE_PLAYER_VAL(brd[row][col]);
					val += SP_MINI_MAX_NODE_PLAYER_VAL(brd[row+1][col+1]);
					val += SP_MINI_MAX_NODE_PLAYER_VAL(brd[row+2][col+2]);
					val += SP_MINI_MAX_NODE_PLAYER_VAL(brd[row+3][col+3]);
					if(val != 0){
						scores[abs(val) - 1][val < 0 ? 0 : 1] ++;
					}
				}
				if(row >= SPAN - 1){ // check right-down
					val = SP_MINI_MAX_NODE_PLAYER_VAL(brd[row][col]);
					val += SP_MINI_MAX_NODE_PLAYER_VAL(brd[row-1][col+1]);
					val += SP_MINI_MAX_NODE_PLAYER_VAL(brd[row-2][col+2]);
					val += SP_MINI_MAX_NODE_PLAYER_VAL(brd[row-3][col+3]);
					if(val != 0){
						scores[abs(val) - 1][val < 0 ? 0 : 1] ++;
					}
				}
			}
		}
	}
	
	if(scores[SPAN-1][0] > 0)
		return INT_MIN;
	if(scores[SPAN-1][1] > 0)
		return INT_MAX;
	
	int score = 0;
	for(int i = 0; i<SPAN-1; i++){
		score += (scores[i][1] - scores[i][0]) * weights[i];
	}
	return score;
}

/*void scoreTest(){
	SPFiarGame* res = spFiarGameCreate(10);
	
	int moves[14] = {6,1,3,2,3,3,2,1,1,1,2,4,5,1};
	
	for(int i = 0; i<14; i++){
		spFiarGameSetMove(res, moves[i]);
	}
	
	spFiarGamePrintBoard(res);
	printf("score: %d \n", spMiniMaxNodeScore(res));
	spFiarGameDestroy(res);
}

int main(){
	scoreTest();
	return 0;
}*/
