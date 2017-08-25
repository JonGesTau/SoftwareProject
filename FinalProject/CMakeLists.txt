cmake_minimum_required(VERSION 3.8)
project(Chess1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c GameBoard.c GameBoard.h consoleUI.c consoleUI.h xmlGame.c xmlGame.h GameState.c GameState.h MiniMax.c MiniMax.h)
add_executable(Chess1 ${SOURCE_FILES})