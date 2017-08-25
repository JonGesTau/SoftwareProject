//
// Created by Dror on 2017-08-18.
//

#include "consoleUI.h"

void consoleUIPrintBoard(GameBoard* game){
    if(game == NULL) return; // error here

    for(int y = 7; y>-1; y--){
        printf("%d| ", (y+1));
        for(int x = 0; x<8; x++){
            printf("%c ", consolePieceChar(game->board[y][x]));
        }
        printf("|\n");
    }
    printf("  -----------------\n   A B C D E F G H\n");
}