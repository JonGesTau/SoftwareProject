CC = gcc
OBJS = main.o GameBoard.o consoleUI.o GameState.o MiniMax.o Moves.o ChessParser.o MainAux.o GameSettings.o xmlGame.o ChessButton.o ChessGUICommon.o ChessGUIManager.o ChessMainWindow.o ChessSettingsWindow.o ChessGameWindow.o ChessPiece.o ChessRect.o GameFlowHelper.o ChessLoadWindow.o ChessSaveWindow.o
 
EXEC = chessprog
COMP_FLAG = -std=c99 -Wall -Wextra \
-Werror -pedantic-errors

#Local
SDL_COMP_FLAG = -I/usr/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

#Nova
#SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
#SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
main.o: main.c MainAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
MainAux.o: MainAux.c MainAux.h ChessParser.h GameSettings.h GameState.h consoleUI.h GameBoard.h Moves.h xmlGame.h MiniMax.h graphics/ChessGUIManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessParser.o: ChessParser.c ChessParser.h Moves.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
consoleUI.o: consoleUI.c consoleUI.h GameBoard.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameBoard.o: GameBoard.c GameBoard.h Moves.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameSettings.o: GameSettings.c GameSettings.h GameFlowHelper.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameState.o: GameState.c GameState.h GameBoard.h Moves.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
MiniMax.o: MiniMax.c MiniMax.h GameBoard.h Moves.h GameState.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Moves.o: Moves.c Moves.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
xmlGame.o: xmlGame.c xmlGame.h GameState.h consoleUI.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameFlowHelper.o: GameFlowHelper.c GameFlowHelper.h GameState.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessButton.o: graphics/ChessButton.c graphics/ChessButton.h graphics/ChessGUICommon.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessGameWindow.o: graphics/ChessGameWindow.c graphics/ChessGameWindow.h graphics/ChessButton.h GameSettings.h graphics/ChessRect.h graphics/ChessPiece.h MiniMax.h consoleUI.h GameFlowHelper.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessGUICommon.o: graphics/ChessGUICommon.c graphics/ChessGUICommon.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessGUIManager.o: graphics/ChessGUIManager.c graphics/ChessGUIManager.h graphics/ChessMainWindow.h graphics/ChessSettingsWindow.h graphics/ChessLoadWindow.h graphics/ChessSaveWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessMainWindow.o: graphics/ChessMainWindow.c graphics/ChessMainWindow.h graphics/ChessButton.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessSettingsWindow.o: graphics/ChessSettingsWindow.c graphics/ChessSettingsWindow.h graphics/ChessButton.h GameSettings.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessLoadWindow.o: graphics/ChessLoadWindow.c graphics/ChessLoadWindow.h graphics/ChessButton.h xmlGame.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessSaveWindow.o: graphics/ChessSaveWindow.c graphics/ChessSaveWindow.h graphics/ChessButton.h xmlGame.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessRect.o: graphics/ChessRect.c graphics/ChessRect.h graphics/ChessGUICommon.h graphics/ChessPiece.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
ChessPiece.o: graphics/ChessPiece.c graphics/ChessPiece.h graphics/ChessGUICommon.h GameBoard.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c graphics/$*.c
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)
