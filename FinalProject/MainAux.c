//
// Created by Jonathan Gescheit on 8/26/17.
//

#include "MainAux.h"

const char* const PIECE_NAMES[] = {"pawn","bishop","knight","rook","queen","king"};

void startConsoleMode() {
    Command userCmd;
    GameSettings* settings = NULL;
    GameState* game = NULL;
    bool is_reset = true;

    do {
        if(is_reset){
            printf(STR_SELECT_SETTINGS);
            is_reset = false;
        }

        if(settings == NULL){
            settings = GameSettingsCreate();
        }

        userCmd = getUserCommand(); // Get the user's command.

        // Settings state
        if (userCmd.cmd == GAME_MODE) {
            arg = strtoumax(userCmd.arg, NULL, 10);
            setGameMode(settings, arg);
        } else if (userCmd.cmd == DIFFICULTY) {
            arg = strtoumax(userCmd.arg, NULL, 10);
            setDifficulty(settings, arg);
        } else if (userCmd.cmd == USER_COLOR) {
            arg = strtoumax(userCmd.arg, NULL, 10);
            setUserColor(settings, arg);
        } else if (userCmd.cmd == LOAD) {
            game = xmlGameLoadGame(userCmd.arg);
            if(game != NULL){
                GameSettingsDestroy(settings);
                settings = NULL;
                //is_reset = startGame(game);
                //game = NULL;
                //if(!is_reset){
                //    break;
                //}
            } else {
                printf(STR_ERR_FILE);
            }
        } else if (userCmd.cmd == DEFAULT) {
            setDefaultSettings(settings);
        } else if (userCmd.cmd == PRINT_SETTING) {
            printSettings(settings);
        } else if (userCmd.cmd == QUIT) {
            printf(STR_EXITING);

            GameSettingsDestroy(settings);
            return;
        } else if (userCmd.cmd == START){
            if(game == NULL){
                game = GameStateCreate(settings->difficulty, settings->userColor==1, settings->gameMode);
            }

            GameSettingsDestroy(settings);
            settings = NULL;
            is_reset = startGame(game);
            game = NULL;
            if(!is_reset){
                break;
            }
        }
    } while (userCmd.cmd != QUIT);

    GameSettingsDestroy(settings);
}

bool startGame(GameState* game) {
    Command userCmd;
    Move* userMove = NULL;

    while (true) {
        if(game->mode == 1 && (game->gameBoard->whiteTurn != game->isPlayerWhite)){
            // if player vs AI and it's not the human's turn
            Move* compMove = miniMaxGetComputerMove(game);
            printf("Computer: move %s at <%c,%c> to <%c,%c>\n",
                   PIECE_NAMES[(whichPiece(game->gameBoard->board[compMove->y1][compMove->x1]))-1],
                   (compMove->y1+'1'), (compMove->x1+'A'), (compMove->y2+'1'), (compMove->x2+'A'));

            GameStatePerformMove(game, compMove->y1, compMove->x1, compMove->y2, compMove->x2);
            MoveDestroy(compMove);

            if(gameBoardIsStalemate(game->gameBoard)){
                printf("The game is tied\n");
                GameStateDestroy(game);
                MoveDestroy(userMove);
                return false;
            }
            if (gameBoardIsMate(game->gameBoard, game->gameBoard->whiteTurn)) {
                printf("Checkmate! %s player wins the game\n", COLOR(!game->gameBoard->whiteTurn));
                GameStateDestroy(game);
                MoveDestroy(userMove);
                return false;
            }

            if (gameBoardIsCheck(game->gameBoard, game->gameBoard->whiteTurn)) {
                printf("Check!");
            }
            continue;
        }

        // on user move:
        consoleUIPrintBoard(game->gameBoard);

        promptUserMove(game);
        userCmd = getUserCommand();

        if (userCmd.cmd == MOVE) {
            bool isMoveSuccessful = false;
            // loop until successful move
            userMove = parseMove(userCmd.arg);
            isMoveSuccessful = handleUserMove(game, userMove);
            if (isMoveSuccessful) {
                if(gameBoardIsStalemate(game->gameBoard)){
                    printf("The game is tied\n");
                    GameStateDestroy(game);
                    MoveDestroy(userMove);
                    return false;
                }
                if (gameBoardIsMate(game->gameBoard, game->gameBoard->whiteTurn)) {
                    printf("Checkmate! %s player wins the game\n", COLOR(!game->gameBoard->whiteTurn));
                    GameStateDestroy(game);
                    MoveDestroy(userMove);
                    return false;
                }

                if (gameBoardIsCheck(game->gameBoard, game->gameBoard->whiteTurn)) {
                    printf("Check: %s King is threatened!\n", COLOR(game->gameBoard->whiteTurn));
                }
            }
        } else if (userCmd.cmd == SAVE) {
            if(!xmlGameSaveGame(game, userCmd.arg))
                printf(STR_ERR_CANT_SAVE);
        } else if (userCmd.cmd == UNDO) {
            if(game->mode == 2){ // illegal
                printf(STR_ERR_UNDO_UNAVAILABLE);
            } else {
                HistoryMove* hist = GameStateGetLastMove(game);
                if(hist == NULL) {
                    printf(STR_ERR_EMPTY_HISTORY);
                } else {
                    printf("Undo move for player %s : <%c,%c> -> <%c,%c>\n",
                           (game->gameBoard->whiteTurn ? "black" : "white"),
                           (hist->move->y2 + '1'), (hist->move->x2 + 'A'), (hist->move->y1 + '1'),
                           (hist->move->x1 + 'A'));
                    GameStateUndoHistoryMove(game);
                    hist = GameStateGetLastMove(game);

                    if(hist != NULL) {
                        printf("Undo move for player %s : <%c,%c> -> <%c,%c>\n",
                               (game->gameBoard->whiteTurn ? "black" : "white"),
                               (hist->move->y2 + '1'), (hist->move->x2 + 'A'), (hist->move->y1 + '1'),
                               (hist->move->x1 + 'A'));
                        GameStateUndoHistoryMove(game);
                    }
                }
            }
        } else if (userCmd.cmd == RESET) {
            printf(STR_RESTARTING);
            GameStateDestroy(game);
            MoveDestroy(userMove);
            return true;
        } else if (userCmd.cmd == QUIT) {
            printf(STR_EXITING);
            GameStateDestroy(game);
            MoveDestroy(userMove);
            return false;
        }
    }
}

void startGUIMode() {
    // Do nothing for now
}

Command getUserCommand() {
    char userInput[1024];
    Command userCommand;

    fgets(userInput, 1024, stdin);
    char *pos;

    // remove line break character
    if ((pos=strchr(userInput, '\n')) != NULL)
        *pos = '\0';

    userCommand = parseLine(userInput);

    return userCommand;
}

void promptUserMove(GameState* game) {
    char* color = game->gameBoard->whiteTurn ? "White" : "Black";
    printf("%s player - enter your move:\n", color);
}

bool handleUserMove(GameState* game, Move* userMove) {
    if(!isLegalCoordinate(userMove->y1, userMove->x1) || !isLegalCoordinate(userMove->y2, userMove->x2)){
        printf(STR_ERR_INVALID_POSITION);
        return false;
    }

    if(game->gameBoard->board[userMove->y1][userMove->x1] == CH_PIECE_EMPTY ||
            isWhite(game->gameBoard->board[userMove->y1][userMove->x1]) != game->gameBoard->whiteTurn){
        printf(STR_ERR_WRONG_COLOR);
        return false;
    }

    if (!gameBoardIsLegalMove(game->gameBoard, userMove->y1, userMove->x1, userMove->y2, userMove->x2)){
        printf(STR_ERR_ILLEGAL_MOVE);
        return false;
    }

    return GameStatePerformMove(game, userMove->y1, userMove->x1, userMove->y2, userMove->x2);
}
