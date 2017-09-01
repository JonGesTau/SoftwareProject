cmake_minimum_required(VERSION 3.8)
project(Chess1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c GameBoard.c GameBoard.h consoleUI.c consoleUI.h GameState.c GameState.h MiniMax.c MiniMax.h Moves.c Moves.h ChessParser.c ChessParser.h MainAux.c MainAux.h GameSettings.c GameSettings.h)
add_executable(Chess1 ${SOURCE_FILES})