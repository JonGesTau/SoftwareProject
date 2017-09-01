//
// Created by Jonathan Gescheit on 8/26/17.
//

#include "MainAux.h"

void startConsoleMode() {
    Command userCmd;
    GameSettings* settings = getDefaultSettings();

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
            settings = getDefaultSettings();
        } else if (userCmd.cmd == PRINT_SETTING) {
            printSettings(settings);
        } else if (userCmd.cmd == QUIT) {
            // Quit
        }
    } while (userCmd.cmd != START);

    // Start game
    startGame(settings);
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

void startGame(GameSettings* settings) {
    Command userCmd;
    Move* userMove;

    game = GameStateCreate(settings->difficulty, settings->userColor, settings->gameMode);
    consoleUIPrintBoard(game->gameBoard);
    promptUserMove();
    userCmd = getUserCommand();
    userMove = parseMove(userCmd.arg);
    gameBoardPerformMove(game, userMove->y1, userMove->x1, userMove->y2, userMove->x2);
    consoleUIPrintBoard(game->gameBoard);
}

void promptUserMove() {
    char* color = game->gameBoard->whiteTurn ? "White" : "Black";
    printf("%s player - enter your move:\n", color);
}
