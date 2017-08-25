//
// Created by Dror on 2017-08-19.
//


#include "xmlGame.h"

bool xmlGameSaveGame(GameState* game, char* filename){
    // TODO: "file names can be either relative or absolute"
    // TODO: "validate filename as if it's user input"
    FILE * f = fopen(filename, "w"); // happily overwrite

    if(f == NULL) return false;

    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(f, "<game>\n");
    fprintf(f, "\t<current_turn>%d</current_turn>\n",42); // TODO
    fprintf(f, "\t<game_mode>%d</game_mode>\n", game->mode+1); // TODO make sure accuracy
    fprintf(f, "\t<difficulty>%d</difficulty>\n", game->difficulty);
    fprintf(f, "\t<user_color>%d</user_color>\n", game->isPlayerWhite); // TODO make sure bool is converted correctly
    fprintf(f, "\t<board>\n");

    for(int y = 7; y > -1; y--){
        fprintf(f, "\t\t<row_%d>", (y+1));
        for(int x = 0; x < 8; x++){
            fprintf(f, "%c", consolePieceChar(game->gameBoard->board[y][x]));
        }
        fprintf(f, "</row_%d>\n", (y+1));
    }

    fprintf(f, "\t</board>\n");
    fprintf(f, "</game>");

    fclose(f);

    return true;
}


GameState* xmlGameLoadGame(char* filename){
    //TODO: parse XML....
}

bool xmlGameParseRow(GameBoard* game, char rowNumber, char* row){
    // parses a single row string into the GameBoard object
    if(strlen(row) != 8) return false;
    if(rowNumber < 0 || rowNumber > 7) return false;
    if(game == NULL) return false;

    char* pieces = "_mbnrqk";
    int piece = 0;
    bool isBlack = false;

    for(int x = 0; x<8; x++){
        piece = strcspn(pieces, (char *)tolower(row[x]));
        if(piece >= strlen(pieces)) return false; // illegal char
        isBlack = row[x] < 0;
        game -> board[rowNumber][x] = (signed char) (piece * (isBlack ? -1 : 1));
    }
    return true;
}




