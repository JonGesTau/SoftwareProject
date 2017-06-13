#include <ctype.h>
#include <printf.h>
#include <memory.h>
#include <inttypes.h>
#include "SPFIARParser.h"

/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool spParserIsInt(const char* str) {
    // If str is a negative number, remove '-'
    if (str[0] == '-') str++;

    for (int i = 0; i <strlen(str) ; ++i) {
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
SPCommand spParserPraseLine(const char* str) {
    char strCopy[1024];
    strcpy(strCopy, str);
    SPCommand command;

    const char delimiter[8] = " \t\r\n";
    char* token = strtok(strCopy, delimiter);

    // Init command
    command.cmd = spGetCommand(token);
    command.validArg = false;

    // Get next token
    token = strtok(NULL, delimiter);

    if (command.cmd == SP_ADD_DISC && spParserIsInt(token)) {
        command.arg = strtoumax(token, NULL, 10);
        command.validArg = true;
    }

    return command;
}

/**
 * Takes a string and returns the matching SP_COMMAND.
 * @param str
 * @return the command in type SP_COMMAND
 */
SP_COMMAND spGetCommand(char* str) {
    if (strcmp(str, "undo_move") == 0) return SP_UNDO_MOVE;
    else if (strcmp(str, "add_disc") == 0) return SP_ADD_DISC;
    else if (strcmp(str, "suggest_move") == 0) return SP_SUGGEST_MOVE;
    else if (strcmp(str, "quit") == 0) return SP_QUIT;
    else if (strcmp(str, "restart") == 0) return SP_RESTART;
    else return SP_INVALID_LINE;
}