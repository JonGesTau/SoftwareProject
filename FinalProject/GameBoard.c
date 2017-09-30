//
// Created by Dror on 2017-08-18.
//

#include <stdio.h>
#include "GameBoard.h"

bool gameBoardIsLegalMove(GameBoard *game, unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2){
    /* V make sure legal coordinates
     * V make sure src != dest
     * V make sure src is not empty
     * V make sure dest is empty or other color
     * V make sure piece moves correctly and that path isn't blocked
     * V make sure no self-check
     */
    if(!isLegalCoordinate(y1,x1) || !isLegalCoordinate(y2,x2)) return false;
    if(y1 == y2 && x1 == x2) return false;
    if(game->board[y1][x1] == CH_PIECE_EMPTY) return false;
    if(isWhite(game->board[y1][x1]) && isWhite(game->board[y2][x2])) return false;
    if(isBlack(game->board[y1][x1]) && isBlack(game->board[y2][x2])) return false;

    char pieceType = whichPiece(game->board[y1][x1]);
    bool isWhitePiece = isWhite(game->board[y1][x1]);

    switch(pieceType){
        case CH_PIECE_ROOK:
            if(!gameBoardIsLegalRookMove(game, y1, x1, y2, x2)) return false;
            break;
        case CH_PIECE_BISHOP:
            if(!gameBoardIsLegalBishopMove(game, y1, x1, y2, x2)) return false;
            break;
        case CH_PIECE_QUEEN:
            if(!gameBoardIsLegalRookMove(game, y1, x1, y2, x2) && !gameBoardIsLegalBishopMove(game, y1, x1, y2, x2))
                return false;
            break;
        case CH_PIECE_KING:
            if(abs(x1-x2) > 1 || abs(y1-y2) > 1) return false;
            break;
        case CH_PIECE_KNIGHT:
            if(!((abs(x1-x2) == 1 && abs(y1-y2) == 2) || (abs(x1-x2) == 2 && abs(y1-y2) == 1))) return false;
            break;
        case CH_PIECE_PAWN:
            if(abs(x1-x2) > 1 || abs(y1-y2) > 2 || abs(y1-y2) < 1) return false;
            // make sure dest is within 3*5 rectangle
            if(isWhitePiece && (y2<y1)) return false;
            if(!isWhitePiece && (y2>y1)) return false;
            /// making sure they're going the right way

            if(x1 != x2){ // capturing move
                if(abs(y1-y2) != 1) return false; // must move diagonally
                if(game -> board[y2][x2] == 0 || isWhite(game->board[y2][x2]) == isWhitePiece) return false;
                // making sure we are capturing someone from the other color
            } else if(abs(y1-y2) == 1){ // normal forward move
                if(game -> board[y2][x2] != 0) return false; // dest must be empty
            } else{ // two space move
                if(isWhitePiece && y1 != 1) return false;
                if(!isWhitePiece && y1 != 6) return false;
                // making sure pawn hasn't moved yet

                int y_mid = y1 + (y2>y1 ? 1 : -1);
                if(game -> board[y_mid][x1] != 0) return false;
                // making sure middle square is empty
            }
            break;
    }

    // making sure resulting board has no self-check
    GameBoard* after = gameBoardCopy(game);
    gameBoardPerformMove(after, y1, x1, y2, x2);
    if(gameBoardIsCheck(after, isWhite(game->board[y1][x1]))) return false;

    gameBoardDestroy(after);
    return true;
}

bool gameBoardIsLegalRookMove(GameBoard *game, unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2){
    if(x1 != x2 && y1 != y2) return false;

    if(x1 != x2){ // making sure horizontal movement not blocked
        int min_x = (x1<x2 ? x1 : x2);
        int max_x = (x1>x2 ? x1 : x2);
        for(int x_mid = min_x+1; x_mid < max_x; x_mid++){
            if(game -> board[y1][x_mid] != 0) return false;
        }
    }

    if(y1 != y2){
        int min_y = (y1<y2 ? y1 : y2);
        int max_y = (y1>y2 ? y1 : y2);
        for(int y_mid = min_y+1; y_mid < max_y; y_mid++){
            if(game -> board[y_mid][x1] != 0) return false;
        }
    }

    return true;
}

bool gameBoardIsLegalBishopMove(GameBoard *game, unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2){
    if(abs(x1 - x2) != abs(y1-y2)) return false;
    // does not make sure destination doesn't have friendly piece or is a legal coordinate

    int diff_y = (y2 > y1 ? 1 : -1);
    int diff_x = (x2 > x1 ? 1 : -1);

    for(int c = 1; c<7; c++){
        if(y1 + c*diff_y == y2) break;
        if(game->board[y1 + c*diff_y][x1 + c*diff_x] != CH_PIECE_EMPTY) return false;
    }

    return true;
}

GameBoard* gameBoardCreate(){
    GameBoard* game = malloc(sizeof(GameBoard));
    if(game == NULL){
        //ERROR
        printf("ERROR");
        return NULL;
    }

    for(int y = 0; y<8; y++){
        for(int x = 0; x<8; x++){
            game->board[y][x] = CH_PIECE_EMPTY;
        }
    }
    game->whiteTurn = true;
    return game;
}

void gameBoardSetup(GameBoard *game){
    for(int y = 0; y<8; y++){
        for(int x = 0; x<8; x++){
            game -> board[y][x] = CH_PIECE_EMPTY;
        }
    }

    game -> whiteTurn = true;

    for(int x = 0; x<8; x++){
        game -> board[6][x] = -1*CH_PIECE_PAWN; // top side
        game -> board[1][x] = CH_PIECE_PAWN;
    }

    game -> board[7][0] = game -> board[7][7] = -1*CH_PIECE_ROOK;
    game -> board[7][1] = game -> board[7][6] = -1*CH_PIECE_KNIGHT;
    game -> board[7][2] = game -> board[7][5] = -1*CH_PIECE_BISHOP;

    game -> board[0][0] = game -> board[0][7] = CH_PIECE_ROOK;
    game -> board[0][1] = game -> board[0][6] = CH_PIECE_KNIGHT;
    game -> board[0][2] = game -> board[0][5] = CH_PIECE_BISHOP;

    game -> board[0][3] = CH_PIECE_QUEEN;
    game -> board[0][4] = CH_PIECE_KING;
    game -> board[7][3] = -CH_PIECE_QUEEN;
    game -> board[7][4] = -CH_PIECE_KING;
}

GameBoard* gameBoardCopy(GameBoard* src){
    if(src == NULL)
        return NULL;
    GameBoard* game2 = malloc(sizeof(GameBoard));
    if(game2 == NULL)
        return NULL;

    game2 -> whiteTurn = src->whiteTurn;

    for(int y = 0; y<8; y++){
        for(int x = 0; x<8; x++){
            game2 -> board[y][x] = src -> board[y][x];
        }
    }
    return game2;
}

void gameBoardDestroy(GameBoard* src){
    free(src);
}

bool gameBoardPerformMove(GameBoard* game, unsigned char y1, unsigned char x1, unsigned char y2, unsigned char x2){
    if(game == NULL) return false;
    game->board[y2][x2] = game->board[y1][x1];
    game->board[y1][x1] = CH_PIECE_EMPTY;
    game->whiteTurn = !game->whiteTurn;
    return true;
}

// TODO: remember to destory history move after using, possibly in the calling function
bool gameBoardUndoMove(GameBoard* game, HistoryMove* hist){
    Move* mv = hist->move;
    game->board[mv->y1][mv->x1] = game->board[mv->y2][mv->x2];
    game->board[mv->y2][mv->x2] = hist->original;
    game->whiteTurn = !game->whiteTurn;
    return true;
}

bool gameBoardIsThreatened(GameBoard *game, unsigned char y1, unsigned char x1){
    //if(y1 == -1 || x1 == -1) return false;
    if(game->board[y1][x1] == CH_PIECE_EMPTY) return false; // also ERROR

    bool isWhite = isWhite(game->board[y1][x1]);

    int temp_y;
    int temp_x;
    signed char enemy = (signed char) (isWhite ? -1 : 1);

    // ----------------------- check for rooks/queens on 4 directions:
    temp_y = y1;
    temp_x = x1 + 1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_ROOK || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_x ++;
    }

    temp_y = y1;
    temp_x = x1 - 1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_ROOK || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_x --;
    }

    temp_y = y1 + 1;
    temp_x = x1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_ROOK || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_y ++;
    }

    temp_y = y1 - 1;
    temp_x = x1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_ROOK || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_y --;
    }

    // -------------- check for bishops/queens in 4 directions
    temp_y = y1 + 1;
    temp_x = x1 + 1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_BISHOP || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_y ++;
        temp_x ++;
    }

    temp_y = y1 + 1;
    temp_x = x1 - 1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_BISHOP || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_y ++;
        temp_x --;
    }

    temp_y = y1 - 1;
    temp_x = x1 + 1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_BISHOP || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_y --;
        temp_x ++;
    }

    temp_y = y1 - 1;
    temp_x = x1 - 1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_BISHOP || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_y --;
        temp_x --;
    }

    // ---------------------- check for knights
    if(isLegalCoordinate(y1+2, x1+1) && game->board[y1+2][x1+1] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(y1+2, x1-1) && game->board[y1+2][x1-1] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(y1-2, x1+1) && game->board[y1-2][x1+1] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(y1-2, x1-1) && game->board[y1-2][x1-1] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(y1+1, x1+2) && game->board[y1+1][x1+2] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(y1+1, x1-2) && game->board[y1+1][x1-2] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(y1-1, x1+2) && game->board[y1-1][x1+2] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(y1-1, x1-2) && game->board[y1-1][x1-2] == enemy*CH_PIECE_KNIGHT) return true;

    // ----------------- check for threatening pawns
    if((isWhite && y1 < 6) || (!isWhite && y1 > 1)) { // first make sure king isn't past pawn row
        if(x1 > 0 && game->board[y1+(isWhite?1:-1)][x1-1] == enemy*CH_PIECE_PAWN) return true;
        if(x1 < 7 && game->board[y1+(isWhite?1:-1)][x1+1] == enemy*CH_PIECE_PAWN) return true;
    }

    // ------------------- check for close king
    if(isLegalCoordinate(y1+1, x1) && game->board[y1+1][x1] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(y1-1, x1) && game->board[y1-1][x1] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(y1, x1+1) && game->board[y1][x1+1] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(y1, x1-1) && game->board[y1][x1-1] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(y1+1, x1+1) && game->board[y1+1][x1+1] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(y1+1, x1-1) && game->board[y1+1][x1-1] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(y1-1, x1+1) && game->board[y1-1][x1+1] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(y1-1, x1-1) && game->board[y1-1][x1-1] == enemy*CH_PIECE_KING) return true;

    return false;
}

bool gameBoardIsCheck(GameBoard *game, bool isWhite){
    int king_y = -1;
    int king_x = -1;

    for(int y = 0; y<8; y++){
        for(int x = 0; x<8; x++){
            if(game->board[y][x] == (isWhite?1:-1)*CH_PIECE_KING){
                king_y = y;
                king_x = x;
                break;
            }
        }
    }

    if(king_y == -1) return false;

    return gameBoardIsThreatened(game, king_y, king_x);
}

bool gameBoardIsMate(GameBoard *game, bool isWhite){
    // 1. make sure king is in check
    // 2. find all possible moves
    // 3. play each on a temporary board
    // 4. make sure it also results in check
    if(!gameBoardIsCheck(game, isWhite))
        return false; // must be check

    MoveList* moves = gameBoardAllMoves(game, isWhite);

    LinkedMove* lmove = MovePop(moves);
    if(lmove == NULL) return true; // no possible moves

    GameBoard* temp = gameBoardCopy(game);
    Move* move;

    while(lmove != NULL){
        move = lmove->move;
        gameBoardPerformMove(temp, move->y1, move->x1, move->y2, move->x2);
        if(!gameBoardIsCheck(temp, isWhite))
            return false;
        gameBoardDestroy(temp);
        temp = gameBoardCopy(game);

        LinkedMoveDestroy(lmove);
        lmove = MovePop(moves);
    }


    return true;
}


// returns true if the game is a stalemate given whose turn it is to play
// will return true IFF not in check and no moves to play
bool gameBoardIsStalemate(GameBoard* game){
    if(gameBoardIsCheck(game, game->whiteTurn)) return false;
    MoveList* moves = gameBoardAllMoves(game, game->whiteTurn);
    bool ret = isMoveListEmpty(moves);
    MoveListDestroy(moves);
    return ret;
}

MoveList* gameBoardAllMoves(GameBoard* game, bool isWhite){
    MoveList* moveList = MoveListCreate();
    int piece;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if(game->board[y][x] == CH_PIECE_EMPTY || (isWhite(game->board[y][x]) != isWhite)){
                continue;
            }

            piece = whichPiece(game->board[y][x]);

            if(piece == CH_PIECE_PAWN){
                gameBoardMovesPawn(game, moveList, y, x);
            } else if(piece == CH_PIECE_BISHOP){
                gameBoardMovesBishop(game, moveList, y, x);
            } else if(piece == CH_PIECE_KNIGHT){
                gameBoardMovesKnight(game, moveList, y, x);
            } else if(piece == CH_PIECE_ROOK){
                gameBoardMovesRook(game, moveList, y, x);
            } else if(piece == CH_PIECE_QUEEN){
                gameBoardMovesBishop(game, moveList, y, x);
                gameBoardMovesRook(game, moveList, y, x);
            } else if(piece == CH_PIECE_KING){
                gameBoardMovesKing(game, moveList, y, x);
            }
        }
    }
    // screen all moves with check

    MoveList* filtered = MoveListCreate();

    LinkedMove* lmove = MovePop(moveList);
    if(lmove == NULL) return NULL;
    Move* move;

    while(lmove != NULL){
        move = lmove->move;
        GameBoard* test = gameBoardCopy(game);
        gameBoardPerformMove(test, move->y1, move->x1, move->y2, move->x2);
        if(!gameBoardIsCheck(test, game->whiteTurn)){
            MovePush(filtered, move->y1, move->x1, move->y2, move->x2);
        }
        LinkedMoveDestroy(lmove);
        lmove = MovePop(moveList);
    }

    MoveListDestroy(moveList);

    return filtered;
}

// given a board, move list and coords of a pawn, pushes to move list all possible moves for that pawn
void gameBoardMovesPawn(GameBoard* game, MoveList* moves, unsigned char y, unsigned char x){
    bool isWhite = isWhite(game->board[y][x]);
    int sign = sign(game->board[y][x]);

    if(isLegalCoordinate(y+sign, x-1) && !isEmpty(game->board[y+sign][x-1]) &&
            sign(game->board[y+sign][x-1]) != sign){ // capture left
        MovePush(moves, y, x, (char)(y+sign), x-1);
    }

    if(isLegalCoordinate(y+sign, x+1) && !isEmpty(game->board[y+sign][x+1]) &&
            sign(game->board[y+sign][x+1]) != sign){ // capture right
        MovePush(moves, y, x, (char)(y+sign), x+1);
    }

    if(isLegalCoordinate(y+sign,x) && isEmpty(game->board[y+sign][x])){
        MovePush(moves, y, x, (char)(y+sign), x); // one step forward
    } else {
        return; // no need to check 2 steps forward
    }

    if(y == (isWhite?1:6) && isEmpty(game->board[y+2*sign][x])){
        MovePush(moves, y, x, (char)(y+2*sign), x); // two steps forward
    }
}

void gameBoardMovesKnight(GameBoard* game, MoveList* moves, unsigned char y, unsigned char x){
    bool isWhite = isWhite(game->board[y][x]);
    int sign = (isWhite ? 1 : -1);

    if(isLegalCoordinate(y+2, x+1) && sign(game->board[y+2][x+1]) != sign){
        MovePush(moves, y, x, y+2, x+1);
    }

    if(isLegalCoordinate(y+2, x-1) && sign(game->board[y+2][x-1]) != sign){
        MovePush(moves, y, x, y+2, x-1);
    }

    if(isLegalCoordinate(y-2, x+1) && sign(game->board[y-2][x+1]) != sign){
        MovePush(moves, y, x, y-2, x+1);
    }

    if(isLegalCoordinate(y-2, x-1) && sign(game->board[y-2][x-1]) != sign){
        MovePush(moves, y, x, y-2, x-1);
    }

    //
    if(isLegalCoordinate(y+1, x+2) && sign(game->board[y+1][x+2]) != sign){
        MovePush(moves, y, x, y+1, x+2);
    }

    if(isLegalCoordinate(y+1, x-2) && sign(game->board[y+1][x-2]) != sign){
        MovePush(moves, y, x, y+1, x-2);
    }

    if(isLegalCoordinate(y-1, x+2) && sign(game->board[y-1][x+2]) != sign){
        MovePush(moves, y, x, y-1, x+2);
    }

    if(isLegalCoordinate(y-1, x-2) && sign(game->board[y-1][x-2]) != sign){
        MovePush(moves, y, x, y-1, x-2);
    }
}


// adds to list possible moves for king at (y,x)
void gameBoardMovesKing(GameBoard* game, MoveList* moves, unsigned char y, unsigned char x){
    bool isWhite = isWhite(game->board[y][x]);
    int sign = (isWhite ? 1 : -1);

    if(isLegalCoordinate(y+1, x) && sign(game->board[y+1][x]) != sign){
        MovePush(moves, y, x, y+1, x);
    }
    if(isLegalCoordinate(y-1, x) && sign(game->board[y-1][x]) != sign){
        MovePush(moves, y, x, y-1, x);
    }
    if(isLegalCoordinate(y, x+1) && sign(game->board[y][x+1]) != sign){
        MovePush(moves, y, x, y, x+1);
    }
    if(isLegalCoordinate(y, x-1) && sign(game->board[y][x-1]) != sign){
        MovePush(moves, y, x, y, x-1);
    }
    // diagonals
    if(isLegalCoordinate(y+1, x+1) && sign(game->board[y+1][x+1]) != sign){
        MovePush(moves, y, x, y+1, x+1);
    }
    if(isLegalCoordinate(y+1, x-1) && sign(game->board[y+1][x-1]) != sign){
        MovePush(moves, y, x, y+1, x-1);
    }
    if(isLegalCoordinate(y-1, x+1) && sign(game->board[y-1][x+1]) != sign){
        MovePush(moves, y, x, y-1, x+1);
    }
    if(isLegalCoordinate(y-1, x-1) && sign(game->board[y-1][x-1]) != sign){
        MovePush(moves, y, x, y-1, x-1);
    }
}


// adds to list possible moves for rook at (y,x)
void gameBoardMovesRook(GameBoard* game, MoveList* moves, unsigned char y, unsigned char x){
    bool isWhite = isWhite(game->board[y][x]);
    int sign = (isWhite ? 1 : -1);

    unsigned char tempY = y + 1;
    unsigned char tempX = x;

    while(isLegalCoordinate(tempY, tempX)){ // move up
        if(isEmpty(game->board[tempY][tempX])){
            MovePush(moves, y, x, tempY, tempX);
            tempY ++; // as long as it's empty, keep adding moves
            continue;
        }

        // if there is my/enemy piece, stop loop
        if(sign(game->board[tempY][tempX]) != sign){
            MovePush(moves, y, x, tempY, tempX);
        }

        break;
    }

    tempY = y - 1;
    tempX = x;

    while(isLegalCoordinate(tempY, tempX)){ // move down
        if(isEmpty(game->board[tempY][tempX])){
            MovePush(moves, y, x, tempY, tempX);
            tempY --; // as long as it's empty, keep adding moves
            continue;
        }

        // if there is my/enemy piece, stop loop
        if(sign(game->board[tempY][tempX]) != sign){
            MovePush(moves, y, x, tempY, tempX);
        }

        break;
    }

    tempY = y;
    tempX = x + 1;

    while(isLegalCoordinate(tempY, tempX)){ // move right
        if(isEmpty(game->board[tempY][tempX])){
            MovePush(moves, y, x, tempY, tempX);
            tempX ++; // as long as it's empty, keep adding moves
            continue;
        }

        // if there is my/enemy piece, stop loop
        if(sign(game->board[tempY][tempX]) != sign){
            MovePush(moves, y, x, tempY, tempX);
        }

        break;
    }


    tempY = y;
    tempX = x - 1;

    while(isLegalCoordinate(tempY, tempX)){ // move right
        if(isEmpty(game->board[tempY][tempX])){
            MovePush(moves, y, x, tempY, tempX);
            tempX --; // as long as it's empty, keep adding moves
            continue;
        }

        // if there is my/enemy piece, stop loop
        if(sign(game->board[tempY][tempX]) != sign){
            MovePush(moves, y, x, tempY, tempX);
        }

        break;
    }
}


// adds to list possible moves for bishop at (y,x)
void gameBoardMovesBishop(GameBoard* game, MoveList* moves, unsigned char y, unsigned char x){
    bool isWhite = isWhite(game->board[y][x]);
    int sign = (isWhite ? 1 : -1);

    unsigned char tempY = y + 1;
    unsigned char tempX = x + 1;

    while(isLegalCoordinate(tempY, tempX)){ // move up-right
        if(isEmpty(game->board[tempY][tempX])){
            MovePush(moves, y, x, tempY, tempX);
            tempY ++;
            tempX ++;
            continue;
        }

        if(sign(game->board[tempY][tempX]) != sign){
            MovePush(moves, y, x, tempY, tempX);
        }

        break;
    }


    tempY = y + 1;
    tempX = x - 1;

    while(isLegalCoordinate(tempY, tempX)){ // move up-right
        if(isEmpty(game->board[tempY][tempX])){
            MovePush(moves, y, x, tempY, tempX);
            tempY ++;
            tempX --;
            continue;
        }

        if(sign(game->board[tempY][tempX]) != sign){
            MovePush(moves, y, x, tempY, tempX);
        }

        break;
    }

    tempY = y - 1;
    tempX = x + 1;

    while(isLegalCoordinate(tempY, tempX)){ // move up-right
        if(isEmpty(game->board[tempY][tempX])){
            MovePush(moves, y, x, tempY, tempX);
            tempY --;
            tempX ++;
            continue;
        }

        if(sign(game->board[tempY][tempX]) != sign){
            MovePush(moves, y, x, tempY, tempX);
        }

        break;
    }

    tempY = y - 1;
    tempX = x - 1;

    while(isLegalCoordinate(tempY, tempX)){ // move up-right
        if(isEmpty(game->board[tempY][tempX])){
            MovePush(moves, y, x, tempY, tempX);
            tempY --;
            tempX --;
            continue;
        }

        if(sign(game->board[tempY][tempX]) != sign){
            MovePush(moves, y, x, tempY, tempX);
        }

        break;
    }
}