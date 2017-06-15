#include <stdio.h>
#include <inttypes.h>
#include "SPFIARGame.h"
#include "SPFIARParser.h"
#include "SPMiniMax.h"

int main() {
    const int HISTORY_SIZE = 20;
    char userInput[1024];
    int level;
    char winner = '\0';
    SPCommand command;
    SPFiarGame* game;

    level = getLevel();

    game = spFiarGameCreate(HISTORY_SIZE);
    spFiarGamePrintBoard(game);

    while (winner == '\0') {
        printf("Please make the next move:\n");
        gets(userInput);
        command = spParserPraseLine(userInput);

        if (command.cmd == SP_SUGGEST_MOVE) {
            int suggestedMove = spMinimaxSuggestMove(game, level);
            printf("Suggested move: drop a disc to column %d\n", suggestedMove);
        } else if (command.cmd == SP_UNDO_MOVE) {
            spFiarGameUndoPrevMove(game);
            continue;
        } else if (command.cmd == SP_ADD_DISC && command.validArg) {
            if (command.arg < 1 || command.arg > 7) {
                printf("Error: column number must be in range 1-7\n");
                continue;
            }

            if (!spFiarGameIsValidMove(game, command.arg - 1)) {
                printf("Error: column %d is full\n", command.arg);
                continue;
            }

            spFiarGameSetMove(game, command.arg - 1);

            winner = spFiarCheckWinner(game);

            if (winner == '\0') {
                int computerMove = spMinimaxSuggestMove(game, level);
                spFiarGameSetMove(game, computerMove);
            }

            spFiarGamePrintBoard(game);

            winner = spFiarCheckWinner(game);
        } else if (command.cmd == SP_RESTART) {
            printf("restart");
        } else if (command.cmd == SP_QUIT) {
            printf("quit");
        } else if (command.cmd == SP_INVALID_LINE) {
            printf("invalid command");
        }
    }

    printf("%c", winner);



    return 0;
}

int getLevel() {
    char userInput[1024];
    int level;

    printf("Please enter the difficulty level between [1-7]:\n");
    gets(userInput);

    if (spParserIsInt(userInput)) {
        level = strtoumax(userInput, NULL, 10);
        if (level < 1 || level > 7) {
            printf("Error: invalid level (should be between 1 to 7\n");
            getLevel();
        }
    }

    return level;
}
