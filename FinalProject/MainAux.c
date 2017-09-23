//
// Created by Jonathan Gescheit on 8/26/17.
//

#include "MainAux.h"
#include "graphics/ChessGUIManager.h"

void startConsoleMode() {
    Command userCmd;
    GameSettings* settings = getDefaultSettings(); // TODO: this is never freed.
    // also never checked for memory errors - are we supposed to anyway?

    promptSelectSetting(); // Prompt user to enter settings or start the game.

    do {
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
            // Load game
        } else if (userCmd.cmd == DEFAULT) {
            settings = getDefaultSettings(); // TODO: This is never freed
        } else if (userCmd.cmd == PRINT_SETTING) {
            printSettings(settings);
        } else if (userCmd.cmd == QUIT) {
            // Quit
        }
    } while (userCmd.cmd != START);

    // Start game
    startGame(settings);
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

void startGame(GameSettings* settings) {
    Command userCmd;
    Move* userMove;
    bool isLegalMove = false;

    game = GameStateCreate(settings->difficulty, settings->userColor, settings->gameMode);
    char* color = game->gameBoard->whiteTurn ? "White" : "Black";

    int winner = '\0';

    while (winner == '\0') {
        consoleUIPrintBoard(game->gameBoard);
        promptUserMove();
        userCmd = getUserCommand();

        if (userCmd.cmd == MOVE) {
            bool isMoveSuccessful = false;
            userMove = parseMove(userCmd.arg);
            isMoveSuccessful = handleUserMove(game->gameBoard, userMove);
            if (isMoveSuccessful) {
                if (gameBoardIsMate(game->gameBoard, game->gameBoard->whiteTurn)) {
                    printf("Checkmate! %s player wins the game\n", color);
                    winner = game->isPlayerWhite;
                } else {
                    if (gameBoardIsCheck(game->gameBoard, game->gameBoard->whiteTurn)) printf("Check: %s King is threatend!\n", color);
                    game->gameBoard->whiteTurn = !game->gameBoard->whiteTurn;
                }
            }
        } else if (userCmd.cmd == SAVE) {
            xmlGameSaveGame(game, userCmd.arg);
        } else if (userCmd.cmd == LOAD) {
            xmlGameLoadGame(userCmd.arg);
        }
    }
}

void promptUserMove() {
    char* color = game->gameBoard->whiteTurn ? "White" : "Black";
    printf("%s player - enter your move:\n", color);
}

bool handleUserMove(GameBoard* gameBoard, Move* userMove) {
    bool isLegalMove;
    isLegalMove = gameBoardIsLegalMove(gameBoard, userMove->y1, userMove->x1, userMove->y2, userMove->x2);

    if (isLegalMove) {
        gameBoardPerformMove(game->gameBoard, userMove->y1, userMove->x1, userMove->y2, userMove->x2);
        return true;
    } else {
        // TODO: Handle all kinds of errors here
        printf("Illegal move\n");
        return false;
    }
}
