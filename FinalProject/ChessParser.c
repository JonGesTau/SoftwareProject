#include <memory.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include "ChessParser.h"
#include "Moves.h"

bool isInt(const char* str) {
    // If str is a negative number, remove '-'
    if (str[0] == '-') str++;

    for (unsigned int i = 0; i < strlen(str) ; ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

/**
 * Parses a specified line. If the line is a command which has an integer
 * argument then the argument is parsed and is saved in the field arg and the
 * field validArg is set to true. In any other case then 'validArg' is set to
 * false and the value 'arg' is undefined
 *
 * @return
 * A parsed line such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   validArg - is set to true if the command is add_disc and the integer argument
 *              is valid
 *   arg      - the integer argument in case validArg is set to true
 */
Command parseLine(const char* str) {
    char strCopy[1024];
    strcpy(strCopy, str);
    Command command;

    const char delimiter[8] = " \t\r\n";
    char* token = strtok(strCopy, delimiter);

    // Init command
    command.cmd = getCommand(token);
    command.validArg = false;

    switch(command.cmd) {
        case DEFAULT:
        case PRINT_SETTING:
        case QUIT:
        case START:
        case UNDO:
        case RESET:
            command.numArgs = 0;
            break;
        case GAME_MODE:
        case DIFFICULTY:
        case USER_COLOR:
        case SAVE:
        case LOAD:
        case GET_MOVES:
            command.numArgs = 1;
            break;
        case MOVE:
            command.numArgs = 3;
            break;
    }

    // Get next token
    token = strtok(NULL, delimiter);

    if (command.numArgs > 0) {
        char arg[50] = {'\0'};
        char buffer[50] = {'\0'};

        while (token != NULL) {
            strcpy(buffer, token);
            strcat(arg, buffer);
            strcat(arg, " ");
            token = strtok(NULL, delimiter);
        }
        
        command.arg = arg;
        command.validArg = false;
    }


    return command;
}

/**
 * Takes a string and returns the matching COMMAND.
 * @param str
 * @return the command in type COMMAND
 */
COMMAND getCommand(char* str) {
    if (str == '\0') return INVALID_LINE;

    if (strcmp(str, "game_mode") == 0) return GAME_MODE;
    else if (strcmp(str, "difficulty") == 0) return DIFFICULTY;
    else if (strcmp(str, "user_color") == 0) return USER_COLOR;
    else if (strcmp(str, "load") == 0) return LOAD;
    else if (strcmp(str, "default") == 0) return DEFAULT;
    else if (strcmp(str, "print_setting") == 0) return PRINT_SETTING;
    else if (strcmp(str, "quit") == 0) return QUIT;
    else if (strcmp(str, "start") == 0) return START;
    else if (strcmp(str, "move") == 0) return MOVE;
    else if (strcmp(str, "get_moves") == 0) return GET_MOVES;
    else if (strcmp(str, "save") == 0) return SAVE;
    else if (strcmp(str, "undo") == 0) return UNDO;
    else if (strcmp(str, "reset") == 0) return RESET;
    else return INVALID_LINE;
}

Move* parseMove(char* str) {
    Move* move;
    char strCopy[128];
    char y1[2];
    char y2[2];
    char x1[2];
    char x2[2];

    strcpy(strCopy, str);
    copyCharByIndex(&x1, strCopy, 3);
    copyCharByIndex(&y1, strCopy, 1);
    copyCharByIndex(&x2, strCopy, 12);
    copyCharByIndex(&y2, strCopy, 10);
    

    move->x1 = (char) (*x1 - '0' - 17);
    move->x2 = (char) (*x2 - '0' - 17);
    move->y1 = (char) (*y1 - '0' - 1);
    move->y2 = (char) (*y2 - '0' - 1);

    return move;
}

void copyCharByIndex(char* dest, char* src, int index) {
    strncpy(dest, src+index, 1);
    dest[1] = '\0';
}
