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

    printf("Please enter the difficulty level between [1-7]:\n");
    gets(userInput);

    if (spParserIsInt(userInput)) {
        level = strtoumax(userInput, NULL, 10);
        if (level < 1 || level > 7) printf("error");
    }

    game = spFiarGameCreate(HISTORY_SIZE);
    spFiarGamePrintBoard(game);

    while (winner == '\0') {
        printf("Please make the next move:\n");
        gets(userInput);
        command = spParserPraseLine(userInput);

        spFiarGameSetMove(game, command.arg - 1);

        winner = spFiarCheckWinner(game);

        if (winner == '\0') {
            int computerMove = spMinimaxSuggestMove(game, level);
            spFiarGameSetMove(game, computerMove);
        }

        spFiarGamePrintBoard(game);

        winner = spFiarCheckWinner(game);
    }

    printf("%c", winner);



    return 0;
}