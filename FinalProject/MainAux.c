//
// Created by Jonathan Gescheit on 8/26/17.
//

#include "MainAux.h"
#include "GameFlowHelper.h"


const char* const PIECE_NAMES[] = {"pawn","bishop","knight","rook","queen","king"};

void startConsoleMode() {
    Command userCmd;
    GameSettings* settings = NULL;
    GameState* game = NULL;
    bool is_reset = true;
    // also never checked for memory errors - are we supposed to anyway?

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
            //arg = strtoumax(userCmd.arg, NULL, 10); // TODO: what does this mean? 10 ?
            game = xmlGameLoadGame(userCmd.arg);
            // TODO: Make sure no errors - should be here or in xml?
            if(game != NULL){
                GameSettingsDestroy(settings);
                settings = NULL;
                is_reset = startGame(game);
                game = NULL;
                if(!is_reset){
                    break;
                }
            } else {
                printf(STR_ERR_FILE);
            }
        } else if (userCmd.cmd == DEFAULT) {
            setDefaultSettings(settings); // TODO: This is never freed
        } else if (userCmd.cmd == PRINT_SETTING) {
            printSettings(settings);
        } else if (userCmd.cmd == QUIT) {
            printf(STR_EXITING);

            GameSettingsDestroy(settings);
            return;
            // Quit
            // free settings and command(does it need freeing?)
            // then break
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
    // also handle load
    GameSettingsDestroy(settings);
}

// returns true if restart command, false if quit
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
                MoveDestroy(userMove); // TODO: was this used?
                return false;
            }
            if (gameBoardIsMate(game->gameBoard, game->gameBoard->whiteTurn)) {
                printf("Checkmate! %s player wins the game\n", COLOR(!game->gameBoard->whiteTurn));
                GameStateDestroy(game);
                MoveDestroy(userMove); // TODO: was this used?
                return false;
            }

            if (gameBoardIsCheck(game->gameBoard, game->gameBoard->whiteTurn)) {
                printf("Check!");
            }
            continue; // make sure we check mate etc.
        }

        // on user move:
        consoleUIPrintBoard(game->gameBoard);

        // TODO: here we should check for mate and print accordingly
        // If no mate/check, ask for player turn.
        promptUserMove(game);
        userCmd = getUserCommand();

        if (userCmd.cmd == MOVE) {
            bool isMoveSuccessful = false;
            // loop until successful move
            userMove = parseMove(userCmd.arg);
            isMoveSuccessful = handleUserMove(game, userMove);
            if (isMoveSuccessful) {
                if(gameBoardIsStalemate(game->gameBoard)){
                    // TODO: actually thehre is waste because we check for mate twice
                    printf("The game is tied\n");
                    GameStateDestroy(game);
                    MoveDestroy(userMove); // TODO: was this used?
                    return false;
                }
                if (gameBoardIsMate(game->gameBoard, game->gameBoard->whiteTurn)) {
                    printf("Checkmate! %s player wins the game\n", COLOR(!game->gameBoard->whiteTurn));
                    GameStateDestroy(game);
                    MoveDestroy(userMove); // TODO: was this used?
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
                    // TODO: make sure hist gets destroyed
                    if(hist != NULL) {
                        printf("Undo move for player %s : <%c,%c> -> <%c,%c>\n",
                               (game->gameBoard->whiteTurn ? "black" : "white"),
                               (hist->move->y2 + '1'), (hist->move->x2 + 'A'), (hist->move->y1 + '1'),
                               (hist->move->x1 + 'A'));
                        GameStateUndoHistoryMove(game);
                        // TODO: what happens if player went first and then undos it all?
                    }
                }
            }
        } else if (userCmd.cmd == RESET) {
            printf(STR_RESTARTING);
            GameStateDestroy(game);
            MoveDestroy(userMove); // TODO: was this used?
            return true;
        } else if (userCmd.cmd == QUIT) {
            printf(STR_EXITING);
            GameStateDestroy(game);
            MoveDestroy(userMove); // TODO: was this used?
            return false;
        }
    }
}

int startGUIMode() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
        printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }
    ChessGuiManager* manager = ChessManagerCreate();
    if (manager == NULL ) {
        SDL_Quit();
        return 0;
    }
    SDL_Event event;
    while (1) {
        SDL_WaitEvent(&event);
        if (chessManagerHandleEvent(manager, &event) == CHESS_MANAGER_QUTT) {
            break;
        }
        chessManagerDraw(manager);
    }
    chessManagerDestroy(manager);
    SDL_Quit();
    return 0;
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

