#include "SPMainAux.h"

int getLevel() {
    int level = 0;

    while (level < 1 || level > 7) {
        printf("Please enter the difficulty level between [1-7]:\n");
        getUserInput();

        command = spParserPraseLine(userInput);

        if (command.cmd == SP_RESTART) {
            restart();
        } else if (command.cmd == SP_QUIT) {
            quit();
        } else if (command.cmd == SP_INVALID_LINE) {
            if (spParserIsInt(userInput)) {
                level = strtoumax(userInput, NULL, 10);
                if (level < 1 || level > 7) {
                    printf("Error: invalid level (should be between 1 to 7)\n");
                }
            } else {
                printf("Error: invalid level (should be between 1 to 7)\n");
            }
        }
    }

    return level;
}

SPCommand getNextMove(bool noPrompt) {
    if (!noPrompt) printf("Please make the next move:\n");
    getUserInput();
    command = spParserPraseLine(userInput);

    // If there's an invalid command don't show prompt for command
    dontShowPrompt = command.cmd == SP_INVALID_LINE;

    return command;
}

int getSuggestedMove() {
    int suggestedMove = spMinimaxSuggestMove(game, level);
    printf("Suggested move: drop a disc to column %d\n", suggestedMove + 1);
    dontShowPrompt = true;

    return suggestedMove;
}

void undo(char player) {
    undoState = (numUndos == HISTORY_SIZE) ? SP_FIAR_GAME_NO_HISTORY : spFiarGameUndoPrevMove(game);
    if (undoState == SP_FIAR_GAME_INVALID_ARGUMENT || undoState == SP_FIAR_GAME_NO_HISTORY) {
        printf("Error: cannot undo previous move!\n");
        undoSuccess = false;
        dontShowPrompt = true;
    } else {
        isUndo = true;
        numUndos++;
        if (player == SP_FIAR_GAME_PLAYER_1_SYMBOL) printf("Remove disc: remove user\'s disc at column %d\n",userMove + 1);
        else printf("Remove disc: remove computer\'s disc at column %d\n", computerMove + 1);
        undoSuccess = true;
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

void quit() {
    printf("Exiting...\n");
    if (!spArrayListIsEmpty(game->gameHistory)) spFiarGameDestroy(game);
    exit(0);
}

void invalidCommand() {
    printf("Error: invalid command\n");
    dontShowPrompt = true;
}

void endGame() {
    if (winner == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
        printf("Game over: you win\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    } else if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
        printf("Game over: computer wins\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    } else {
        printf("Game over: it’s a tie\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
    }

    do {
        getUserInput();
        command = spParserPraseLine(userInput);

        if (command.cmd == SP_RESTART) {
            restart();
        } else if (command.cmd == SP_QUIT) {
            quit();
        } else if (command.cmd == SP_UNDO_MOVE) {
            resetWinner();
            undo(SP_FIAR_GAME_PLAYER_1_SYMBOL);
            spFiarGamePrintBoard(game);
            if (!undoSuccess) endGame();
        } else {
            command.cmd = SP_INVALID_LINE;
            invalidCommand();
        }
    } while (command.cmd == SP_INVALID_LINE);
}

void restart() {
    if (!spArrayListIsEmpty(game->gameHistory)) spFiarGameDestroy(game);
    resetWinner();
    resetNumUndos();
    isUndo = false;
    isRestart = true;
    dontShowPrompt = false;
    printf("Game restarted!\n");
}

void resetWinner() {
    winner = '\0';
}

void resetNumUndos() {
    numUndos = 0;
}

void getUserInput() {
    fgets(userInput, 1024, stdin);
    char *pos;

    // remove line break character
    if ((pos=strchr(userInput, '\n')) != NULL)
        *pos = '\0';
}
