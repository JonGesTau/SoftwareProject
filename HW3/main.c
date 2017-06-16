#include "SPMainAux.h"

int main() {
    const int HISTORY_SIZE = 20;
    char winner = '\0';

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
            undoState = spFiarGameUndoPrevMove(game);
            if (undoState == SP_FIAR_GAME_INVALID_ARGUMENT || undoState == SP_FIAR_GAME_NO_HISTORY) {
                printf("Error: cannot undo previous move!\n");
            } else {
                spFiarGameUndoPrevMove(game);
                printf("Remove disc: remove computer’s disc at column %d\n", computerMove + 1);
                spFiarGameUndoPrevMove(game);
                printf("Remove disc: remove user’s disc at column %d\n",userMove + 1);
                spFiarGamePrintBoard(game);
            }

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

            userMove = command.arg - 1;
            spFiarGameSetMove(game, userMove);

            winner = spFiarCheckWinner(game);

            if (winner == '\0') {
                computerMove = spMinimaxSuggestMove(game, level);
                spFiarGameSetMove(game, computerMove);
                printf("Computer move: add disc to column %d\n", computerMove + 1);
            }

            spFiarGamePrintBoard(game);

            winner = spFiarCheckWinner(game);
        } else if (command.cmd == SP_RESTART) {
            printf("restart");
        } else if (command.cmd == SP_QUIT) {
            printf("Exiting...\n");
            spFiarGameDestroy(game);
            return 0;
        } else if (command.cmd == SP_INVALID_LINE) {
            printf("Error: invalid command\n");
        }
    }

    if (winner == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
        printf("Game over: you win\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    } else if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
        printf("Game over: computer wins\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    } else {
        printf("Game over: it’s a tie\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    }

    gets(userInput);
    command = spParserPraseLine(userInput);

    if (command.cmd == SP_RESTART) {
        printf("Game restarted!\n");

    } else if (command.cmd == SP_QUIT) {
        printf("Exiting...\n");
        spFiarGameDestroy(game);
        return 0;
    } else if (command.cmd == SP_INVALID_LINE) {
        printf("Error: invalid command\n");
    }


    return 0;
}



