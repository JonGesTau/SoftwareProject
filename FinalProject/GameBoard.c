//
// Created by Dror on 2017-08-18.
//

#include "GameBoard.h"

// TODO: said in forum that white pieces are always at the bottom!
bool gameBoardIsLegalMove(GameBoard *game, char y1, char x1, char y2, char x2){
    /*
     * ? make sure legal board?
     * V make sure legal coordinates
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
            if(isWhitePiece && (game->whiteOnBottom != y2>y1)) return false;
            if(!isWhitePiece && (game->whiteOnBottom != y2<y1)) return false;
            /// making sure they're going the right way

            if(x1 != x2){ // capturing move
                if(abs(y1-y2) != 1) return false; // must move diagonally
                if(game -> board[y2][x2] == 0 || isWhite(game->board[y2][x2]) == isWhitePiece) return false;
                // making sure we are capturing someone from the other color
            } else if(abs(y1-y2) == 1){ // normal forward move
                if(game -> board[y2][x2] != 0) return false; // dest must be empty
            } else{ // two space move
                if(isWhitePiece && y1 != (game->whiteOnBottom?1:6)) return false;
                if(!isWhitePiece && y1 != (game->whiteOnBottom?6:1)) return false;
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

    return true;
}

bool gameBoardIsLegalRookMove(GameBoard *game, char y1, char x1, char y2, char x2){
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

bool gameBoardIsLegalBishopMove(GameBoard *game, char y1, char x1, char y2, char x2){
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

void gameBoardSetup(GameBoard *game, bool whiteOnBottom){
    for(int y = 0; y<8; y++){
        for(int x = 0; x<8; x++){
            game -> board[y][x] = 0;
        }
    }

    game -> whiteTurn = true;
    game ->whiteOnBottom = whiteOnBottom;
    signed char sign = (signed char) (whiteOnBottom ? 1 : -1);

    for(int x = 0; x<8; x++){
        game -> board[6][x] = (signed char)( -1*sign*CH_PIECE_PAWN); // top side
        game -> board[1][x] = sign*CH_PIECE_PAWN;
    }

    game -> board[7][0] = game -> board[7][7] = -1*sign*CH_PIECE_ROOK;
    game -> board[7][1] = game -> board[7][6] = -1*sign*CH_PIECE_KNIGHT;
    game -> board[7][2] = game -> board[7][5] = -1*sign*CH_PIECE_BISHOP;

    game -> board[0][0] = game -> board[0][7] = sign*CH_PIECE_ROOK;
    game -> board[0][1] = game -> board[0][6] = sign*CH_PIECE_KNIGHT;
    game -> board[0][2] = game -> board[0][5] = sign*CH_PIECE_BISHOP;

    // when w on bottom, queens are on the left
    if(whiteOnBottom){
        game -> board[0][3] = CH_PIECE_QUEEN;
        game -> board[0][4] = CH_PIECE_KING;
        game -> board[7][3] = -CH_PIECE_QUEEN;
        game -> board[7][4] = -CH_PIECE_KING;
    } else {
        game -> board[0][3] = -CH_PIECE_KING;
        game -> board[0][4] = -CH_PIECE_QUEEN;
        game -> board[7][3] = CH_PIECE_KING;
        game -> board[7][4] = CH_PIECE_QUEEN;
    }
}

GameBoard* gameBoardCopy(GameBoard* src){
    if(src == NULL)
        return NULL;
    GameBoard* game2 = malloc(sizeof(GameBoard));
    if(game2 == NULL)
        return NULL;

    game2 -> whiteTurn = src->whiteTurn;
    game2 -> whiteOnBottom = src->whiteOnBottom;

    for(int y = 0; y<8; y++){
        for(int x = 0; x<8; x++){
            game2 -> board[y][x] = src -> board[y][x];
        }
    }
    return game2;
}

void gameBoardDestroy(GameBoard* src){
    if(src == NULL)
        return;
    free(src);
}

bool gameBoardPerformMove(GameBoard* game, char y1, char x1, char y2, char x2){
    if(game == NULL) return false;
    game->board[y2][x2] = game->board[y1][x1];
    game->board[y1][x1] = CH_PIECE_EMPTY;
    return true;
}

bool gameBoardIsCheck(GameBoard *game, bool isWhite){
    // we do this stupidly: we first locate the appropriate king
    // then we go on all four sides until blocked, seeing if threatened by rook or queen
    // similarly for bishop or queen; knight; pawn; king
    // TODO: consider would it be better to keep the location of the kings for time tradeoff

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

    if(king_y == -1) return false; // TODO: big error, but shouldn't happen; atleast print to console

    int temp_y = king_y;
    int temp_x = king_x;
    signed char enemy = (signed char) (isWhite ? -1 : 1);

    // ----------------------- check for rooks/queens on 4 directions:
    temp_y = king_y;
    temp_x = king_x + 1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_ROOK || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_x ++;
    }

    temp_y = king_y;
    temp_x = king_x - 1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_ROOK || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_x --;
    }

    temp_y = king_y + 1;
    temp_x = king_x;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_ROOK || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_y ++;
    }

    temp_y = king_y - 1;
    temp_x = king_x;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_ROOK || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_y --;
    }

    // -------------- check for bishops/queens in 4 directions
    temp_y = king_y + 1;
    temp_x = king_x + 1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_BISHOP || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_y ++;
        temp_x ++;
    }

    temp_y = king_y + 1;
    temp_x = king_x - 1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_BISHOP || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_y ++;
        temp_x --;
    }

    temp_y = king_y - 1;
    temp_x = king_x + 1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_BISHOP || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_y --;
        temp_x ++;
    }

    temp_y = king_y - 1;
    temp_x = king_x - 1;
    while(isLegalCoordinate(temp_y,temp_x)){
        if(game->board[temp_y][temp_x] == enemy*CH_PIECE_BISHOP || game->board[temp_y][temp_x] == enemy*CH_PIECE_QUEEN)
            return true; // in check
        if(game->board[temp_y][temp_x] != 0) break; // path is blocked
        temp_y --;
        temp_x --;
    }

    // ---------------------- check for knights
    if(isLegalCoordinate(king_y+2, king_x+1) && game->board[king_y+2][king_x+1] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(king_y+2, king_x-1) && game->board[king_y+2][king_x-1] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(king_y-2, king_x+1) && game->board[king_y-2][king_x+1] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(king_y-2, king_x-1) && game->board[king_y-2][king_x-1] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(king_y+1, king_x+2) && game->board[king_y+1][king_x+2] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(king_y+1, king_x-2) && game->board[king_y+1][king_x-2] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(king_y-1, king_x+2) && game->board[king_y-1][king_x+2] == enemy*CH_PIECE_KNIGHT) return true;
    if(isLegalCoordinate(king_y-1, king_x-2) && game->board[king_y-1][king_x-2] == enemy*CH_PIECE_KNIGHT) return true;

    // ----------------- check for threatening pawns
    if(isWhite && king_y < 6 || !isWhite && king_y > 1) { // first make sure king isn't past pawn row
        if(king_x > 0 && game->board[king_y+(isWhite?1:-1)][king_x-1] == enemy*CH_PIECE_PAWN) return true;
        if(king_x < 7 && game->board[king_y+(isWhite?1:-1)][king_x+1] == enemy*CH_PIECE_PAWN) return true;
    }

    // ------------------- check for close king
    if(isLegalCoordinate(king_y+1, king_x) && game->board[king_y+1][king_x] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(king_y-1, king_x) && game->board[king_y-1][king_x] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(king_y, king_x+1) && game->board[king_y][king_x+1] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(king_y, king_x-1) && game->board[king_y][king_x-1] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(king_y+1, king_x+1) && game->board[king_y+1][king_x+1] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(king_y+1, king_x-1) && game->board[king_y+1][king_x-1] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(king_y-1, king_x+1) && game->board[king_y-1][king_x+1] == enemy*CH_PIECE_KING) return true;
    if(isLegalCoordinate(king_y-1, king_x-1) && game->board[king_y-1][king_x-1] == enemy*CH_PIECE_KING) return true;

    return false;
}

bool gameBoardIsMate(GameBoard *game, bool isWhite){
    // TODO
    return true;
}
