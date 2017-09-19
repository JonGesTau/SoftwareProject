cmake_minimum_required(VERSION 3.8)
project(Chess1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c GameBoard.c GameBoard.h consoleUI.c consoleUI.h GameState.c GameState.h MiniMax.c MiniMax.h Moves.c Moves.h ChessParser.c ChessParser.h MainAux.c MainAux.h GameSettings.c GameSettings.h xmlGame.c xmlGame.h tests/MovesTest.c tests/MovesTest.h tests/MiniMaxTest.c tests/MiniMaxTest.h tests/GameBoardTest.c tests/GameBoardTest.h)
add_executable(Chess1 ${SOURCE_FILES})

#cmake_minimum_required(VERSION 2.8)
#project(Chess1)
#
## includes cmake/FindSDL2.cmake
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
#
#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIR})
#target_link_libraries(Chess1 ${SDL2_LIBRARY})


