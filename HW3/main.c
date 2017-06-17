#include "SPMainAux.h"

int main() {
    HISTORY_SIZE = 20;
    numUndos = 0;
    winner = '\0';
    isRestart = false;

    do {
        if (!isUndo) {
            isRestart = false;
            level = getLevel();
            game = spFiarGameCreate(HISTORY_SIZE);
            spFiarGamePrintBoard(game);
        }

        while (winner == '\0') {
            getNextMove();

            if (command.cmd == SP_SUGGEST_MOVE) {
                getSuggestedMove();
            } else if (command.cmd == SP_UNDO_MOVE) {
                bool undoSuccess = undo(SP_FIAR_GAME_PLAYER_2_SYMBOL);
                if (undoSuccess) undo(SP_FIAR_GAME_PLAYER_1_SYMBOL);
                spFiarGamePrintBoard(game);
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

                winner = addDisc();
            } else if (command.cmd == SP_RESTART) {
                restart();
                break;
            } else if (command.cmd == SP_QUIT) {
                quit();
            } else if (command.cmd == SP_INVALID_LINE) {
                invalidCommand();
            }
        }

        if (!isRestart) endGame();
    } while (isRestart || isUndo);
}



