//
// Created by Jonathan Gescheit on 8/25/17.
//

// Parse user commands

#ifndef FINALPROJECT_CHESSPARSER_H
#define FINALPROJECT_CHESSPARSER_H

#include <stdbool.h>
#include <inttypes.h>
#include "Moves.h"
#include <memory.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>


//a type used to represent a command
typedef enum {
    GAME_MODE,
    DIFFICULTY,
    USER_COLOR,
    LOAD,
    DEFAULT,
    PRINT_SETTING,
    QUIT,
    START,
    MOVE,
    GET_MOVES,
    SAVE,
    UNDO,
    RESET,
    INVALID_LINE
} COMMAND;

//a new type that is used to encapsulate a parsed line
typedef struct command_t {
    COMMAND cmd;
    bool validArg; //is set to true if the line contains a valid argument,
    bool isIntArg;
    int numArgs;
    char* arg;
} Command;


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
Command parseLine(const char* str);

/**
 * Takes a string and returns the matching SP_COMMAND.
 * @param str
 * @return the command in type SP_COMMAND
 */
COMMAND getCommand(char* str);

/**
 * Parse a move given by the user
 * @param str
 * @return the parsed move struct
 */
Move* parseMove(char* str);

/**
 * Copy a char from a string from a specific index from src to dest
 * @param dest
 * @param src
 * @param index
 */
void copyCharByIndex(char* dest, char* src, int index);

#endif //FINALPROJECT_CHESSPARSER_H
