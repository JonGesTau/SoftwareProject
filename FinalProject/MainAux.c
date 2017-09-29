//
// Created by Jonathan Gescheit on 8/26/17.
//

#include "MainAux.h"


const char* const PIECE_NAMES[] = {"pawn","bishop","knight","rook","queen","king"};

void startConsoleMode() {
    Command userCmd;
    GameSettings* settings = GameSettingsCreate();
    GameState* game = NULL;
    // also never checked for memory errors - are we supposed to anyway?

    printf(STR_SELECT_SETTINGS);

    do {
        userCmd = getUserCommand(); // Get the user's command.
        // TODO: all tested! but for user argument for load
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
            game = xmlGameLoadGame("loadtest.xml");
            // TODO: Make sure no errors - should be here or in xml?
            if(game != NULL){
                break;
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
        }
    } while (userCmd.cmd != START);
    // also handle load
    if(userCmd.cmd == QUIT){
        GameSettingsDestroy(settings);
        return;
    }
    // Start game

    if(game == NULL){
        game = GameStateCreate(settings->difficulty, settings->userColor==1, settings->gameMode);
    }

    GameSettingsDestroy(settings);
    startGame(game);
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

void startGame(GameState* game) {
    Command userCmd;
    Move* userMove;
    bool isLegalMove = false;
    char* color = game->gameBoard->whiteTurn ? "White" : "Black"; // TODO: update this each move
    int winner = '\0';
    // in mode 1 - 1 player mode, we have to take care of computer move and also notice the color of player
    while (winner == '\0') {
        // TODO: test move
        // take care of what happens when the player makes a bad command so nothing actually changed.
        // do we reprint board? it seems board is not reprinted but the request for move is.
        if(game->mode == 1 && (game->gameBoard->whiteTurn != game->isPlayerWhite)){
            // if player vs AI and it's not the human's turn
            Move* compMove = miniMaxGetComputerMove(game);
            // TODO: macro/function to covert coords to correct form
            printf("Computer: move %s at <%d,%d> to <%d,%d>\n",
                   PIECE_NAMES[(whichPiece(game->gameBoard->board[compMove->y1][compMove->x1]))-1],
                   compMove->y1, compMove->x1, compMove->y2, compMove->x2);

            //TODO: this is actually wrong, should switch x and y, convert y to char and add 1 to x

            GameStatePerformMove(game, compMove->y1, compMove->x1, compMove->y2, compMove->x2);
            MoveDestroy(compMove);
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
                if (gameBoardIsMate(game->gameBoard, game->gameBoard->whiteTurn)) {
                    printf("Checkmate! %s player wins the game\n", color);
                    winner = game->isPlayerWhite;
                } else if (gameBoardIsCheck(game->gameBoard, game->gameBoard->whiteTurn)) {
                    printf("Check: %s King is threatend!\n", color);
                }
                // need to handel stalemate
            }
        } else if (userCmd.cmd == SAVE) {
            xmlGameSaveGame(game, userCmd.arg);
        } else if (userCmd.cmd == LOAD) {
            xmlGameLoadGame(userCmd.arg);
        } else if (userCmd.cmd == UNDO) {
            if(game->mode == 2){ // illegal
                printf(STR_ERR_UNDO_UNAVAILABLE);
            } else {
                HistoryMove* hist = GameStateGetLastMove(game);
                if(hist == NULL)
                    printf(STR_ERR_EMPTY_HISTORY);

                printf("Undo move for player XXX : <x,y> -> <w,z>\n");
                GameStateUndoHistoryMove(game, hist);
                hist = GameStateGetLastMove(game);
                // make sure hist != NULL!
                printf("Undo move for player XXX : <x,y> -> <w,z>\n");
                GameStateUndoHistoryMove(game, hist);

                // TODO: what happens if player went first and then undos it all?
                // then only one undo is possible
            }
        } else if (userCmd.cmd == RESET) {
            // TODO
        } else if (userCmd.cmd == QUIT) {
            printf(STR_EXITING);
            GameStateDestroy(game);
            MoveDestroy(userMove); // TODO: was this used?
            return;
            // TODO
        }
    }
}

void promptUserMove(GameState* game) {
    char* color = game->gameBoard->whiteTurn ? "White" : "Black";
    printf("%s player - enter your move:\n", color);
}

bool handleUserMove(GameState* game, Move* userMove) {
    //TODO:change argument to GameState* and use GameStatePerformMove instead, which also tests for legality

    bool isLegalMove;
    isLegalMove = gameBoardIsLegalMove(game->gameBoard, userMove->y1, userMove->x1, userMove->y2, userMove->x2);

    if (isLegalMove) {
        GameStatePerformMove(game, userMove->y1, userMove->x1, userMove->y2, userMove->x2);
        //TODO: gescheit, change the function so that we use GameStatePerformMove instead!
        return true;
    } else {
        // TODO: Handle all kinds of errors here
        printf("Illegal move\n");
        return false;
    }
}
