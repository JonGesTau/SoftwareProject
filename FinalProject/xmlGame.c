//
// Created by Dror on 2017-08-19.
//


#include "xmlGame.h"

bool xmlGameSaveGame(GameState* game, char* filename){
    // TODO: "validate filename as if it's user input"
    FILE * f = fopen(filename, "w"); // happily overwrite

    if(f == NULL) return false;

    fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(f, "<game>\n");
    fprintf(f, "\t<current_turn>%d</current_turn>\n",(game->gameBoard->whiteTurn?1:0));
    fprintf(f, "\t<game_mode>%d</game_mode>\n", game->mode);
    fprintf(f, "\t<difficulty>%d</difficulty>\n", game->difficulty);
    fprintf(f, "\t<user_color>%d</user_color>\n", (game->isPlayerWhite?1:0));
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

bool xmlGameNextRow(FILE *f, char *line, unsigned int *start_pos) {
    // advances pointers and buffers to the start of the next
    // non-empty line, and also skips leading whitespace
    (*start_pos) = 0;
    do{
        if(!fgets(line, XML_GAME_MAX_LINE_LENGTH, f)){
            return false;
        } // file over or something else
    }while(strlen(line) == 0);
    while(*start_pos < strlen(line) && isspace(line[*start_pos])){ (*start_pos) ++; }

    if(*start_pos >= strlen(line)){ return false; }// if the line is only whitespaces

    return true;
}

GameState* xmlGameLoadGame(char* filename){
    FILE* f = fopen(filename, "r");

    if(f == NULL){
        return NULL;
        // ERROR
    }
    char line[XML_GAME_MAX_LINE_LENGTH];
    unsigned int start_pos = 0;

    int current_turn = 0;
    char game_mode; // TODO: clean here
    char difficulty = 2;
    char user_color = 1; // player is white by default

    // stage <? .... ?>
    if(!xmlGameNextRow(f, line, &start_pos)){
        fclose(f);
        return NULL; // ERRORS
    }

    if((start_pos > sizeof(line) - 2) || line[start_pos] != '<' || line[start_pos+1]!='?'){
        fclose(f);
        return NULL; //first non-empty line must start "<?", can have leading whitespace
    }
    // stage <game>
    if(!xmlGameNextRow(f, line, &start_pos)){
        fclose(f);
        return NULL;
    }
    if(strncmp(line+start_pos, "<game", 5) != 0){
        fclose(f);
        return NULL;
    }

    // <current_turn>
    if(!xmlGameNextRow(f, line, &start_pos)){
        fclose(f);
        return NULL;
    }
    if(strncmp(line+start_pos, "<current_turn>", 14) != 0){
        fclose(f);
        return NULL;
    }

    current_turn = line[start_pos+14]-'0';

    // <game_mode>
    if(!xmlGameNextRow(f, line, &start_pos)){
        fclose(f);
        return NULL;
    }
    if(strncmp(line+start_pos, "<game_mode>", 11) != 0){
        fclose(f);
        return NULL;
    }
    game_mode = line[start_pos+11];
    if(game_mode != '1' && game_mode != '2'){
        fclose(f);
        return NULL;
    } // illegal game_mode
    game_mode -= '0';

    if(game_mode != 1 && game_mode != 2){
        fclose(f);
        return NULL; // ERROR: illegal game_mode
    }

    if(game_mode == 1){
        // <difficulty>
        if(!xmlGameNextRow(f, line, &start_pos)){
            fclose(f);
            return NULL;
        }
        if(strncmp(line+start_pos, "<difficulty>", 12) != 0){
            fclose(f);
            return NULL;
        }
        // 49 = '1', 50 = '2'
        difficulty = line[start_pos+12];
        if(difficulty < '1' || difficulty > '4'){
            fclose(f);
            return NULL;
            // illegal difficulty; assumes expert is not supported
        }
        difficulty -= '0';

        // <user_color>
        if(!xmlGameNextRow(f, line, &start_pos)){
            fclose(f);
            return NULL;
        }
        if(strncmp(line+start_pos, "<user_color>", 12) != 0){
            fclose(f);
            return NULL;
        }

        user_color = line[start_pos+12];
        if(user_color != '1' && user_color != '0'){
            fclose(f);
            return NULL;
            // illegal user_color
        }
        user_color -= '0';

        if(!xmlGameNextRow(f, line, &start_pos)) {
            fclose(f);
            return NULL;
            // now should be board
        }
        if(strncmp(line+start_pos, "<board>", 7) != 0){
            fclose(f);
            return NULL;
        }
    } else {
        do{
            if(!xmlGameNextRow(f, line, &start_pos)){
                fclose(f);
                return NULL;
            }
        }while((strncmp(line+start_pos, "<board>", 7) != 0));
    }

    // <rows>
    GameBoard* board = gameBoardCreate();
    board->whiteTurn = current_turn == 1;

    for(int row = 7; row > -1; row--){
        if(!xmlGameNextRow(f, line, &start_pos)){
            fclose(f);
            gameBoardDestroy(board);
            return NULL;
        }
        if(!xmlGameParseRow(board, (unsigned char)row, line+start_pos+7)){
            fclose(f);
            gameBoardDestroy(board);
            return NULL; // can unite into one if
        }
    }

 //  In "2 players" mode, the tags <difficulty> and <user_color> should not contain any value and
 // can also be discarded from the file. MODE ==2
 // the order is exactly the sam.e there will be no superfluous empty lines.

    //consoleUIPrintBoard(board);
    //gameBoardDestroy(board);

    GameState* state = GameStateCreate(difficulty, user_color == 1, game_mode);
    gameBoardDestroy(state->gameBoard); // pretty stupid actually
    state->gameBoard = board;

    fclose(f);
    return state;
}

bool xmlGameParseRow(GameBoard* game, unsigned char rowNumber, char* row){
    // parses a single row string into the GameBoard object

    if(strlen(row) < 8) return false;
    if(rowNumber > 7) return false;
    if(game == NULL) return false;

    char* pieces = "_mbnrqk";
    int piece = 0;
    bool isBlack = false;

    for(int x = 0; x<8; x++){
        char* found = strchr(pieces, (char)tolower(row[x]));
        if(found == NULL) return false;

        piece = (int) (found - pieces);
        isBlack = tolower(row[x]) != row[x];
        game -> board[rowNumber][x] = (signed char) (piece * (isBlack ? -1 : 1));
    }
    return true;
}




