#include "SPMainAux.h"

int getLevel() {
    char userInput[1024];
    int level = 0;

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

SPCommand getNextMove() {
    printf("Please make the next move:\n");
    gets(userInput);
    command = spParserPraseLine(userInput);

    return command;
}

int getSuggestedMove() {
    int suggestedMove = spMinimaxSuggestMove(game, level);
    printf("Suggested move: drop a disc to column %d\n", suggestedMove + 1);

    return suggestedMove;
}

void undo(char player) {
    undoState = spFiarGameUndoPrevMove(game);
    if (undoState == SP_FIAR_GAME_INVALID_ARGUMENT || undoState == SP_FIAR_GAME_NO_HISTORY) {
        printf("Error: cannot undo previous move!\n");
    } else {
        isUndo = true;
        if (player == SP_FIAR_GAME_PLAYER_1_SYMBOL) printf("Remove disc: remove user’s disc at column %d\n",userMove + 1);
        else printf("Remove disc: remove computer’s disc at column %d\n", computerMove + 1);
    }
}

char addDisc() {
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

    return winner;
}

int quit() {
    printf("Exiting...\n");
    spFiarGameDestroy(game);
    exit(0);
}

void invalidCommand() {
    printf("Error: invalid command\n");
}

void endGame() {
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
        restart();
    } else if (command.cmd == SP_QUIT) {
        quit();
    } else if (command.cmd == SP_UNDO_MOVE) {
        resetWinner();
        undo(SP_FIAR_GAME_PLAYER_1_SYMBOL);
        spFiarGamePrintBoard(game);
    } else if (command.cmd == SP_INVALID_LINE) {
        invalidCommand();
    }
}

void restart() {
    spFiarGameDestroy(game);
    resetWinner();
    isUndo = false;
    isRestart = true;
}

void resetWinner() {
    winner = '\0';
}