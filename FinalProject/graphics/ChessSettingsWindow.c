//
// Created by Jonathan Gescheit on 9/22/17.
//

#include "ChessSettingsWindow.h"

//Helper function to create buttons in the simple window;
ChessButton** createSettingsWindowChessButtons(SDL_Renderer *renderer, GameSettings *settings) {
    if (renderer == NULL ) {
        return NULL ;
    }

    const int numButtons = 10;

    ChessButton** buttons = malloc(numButtons * sizeof(ChessButton*));
    if (buttons == NULL ) {
        return NULL ;
    }

    SDL_Rect onePlayer = { .x = 250, .y = 50, .h = 100, .w = 250 };
    SDL_Rect twoPlayer = { .x = 550, .y = 50, .h = 100, .w = 250 };

    SDL_Rect noob = { .x = 250, .y = 200, .h = 100, .w = 250 };
    SDL_Rect easy = { .x = 550, .y = 200, .h = 100, .w = 250 };
    SDL_Rect moderate = { .x = 250, .y = 350, .h = 100, .w = 250 };
    SDL_Rect hard = { .x = 550, .y = 350, .h = 100, .w = 250 };

    SDL_Rect white = { .x = 250, .y = 500, .h = 100, .w = 250 };
    SDL_Rect black = { .x = 550, .y = 500, .h = 100, .w = 250 };

    SDL_Rect start = { .x = 200, .y = 650, .h = 100, .w = 250 };
    SDL_Rect back = { .x = 600, .y = 650, .h = 100, .w = 250 };

    buttons[0] = createChessButton(renderer, &onePlayer, "./assets/oneplayer_active.bmp", "./assets/oneplayer_inactive.bmp", CHESS_BUTTON_1PLAYER, false);
    buttons[1] = createChessButton(renderer, &twoPlayer, "./assets/twoplayer_active.bmp", "./assets/twoplayer_inactive.bmp", CHESS_BUTTON_2PLAYER, false);
    buttons[2] = createChessButton(renderer, &noob, "./assets/noob_active.bmp", "./assets/noob_inactive.bmp", CHESS_BUTTON_NOOB, false);
    buttons[3] = createChessButton(renderer, &easy, "./assets/easy_active.bmp", "./assets/easy_inactive.bmp", CHESS_BUTTON_EASY, false);
    buttons[4] = createChessButton(renderer, &moderate, "./assets/moderate_active.bmp", "./assets/moderate_inactive.bmp", CHESS_BUTTON_MODERATE, false);
    buttons[5] = createChessButton(renderer, &hard, "./assets/hard_active.bmp", "./assets/hard_inactive.bmp", CHESS_BUTTON_HARD, false);
    buttons[6] = createChessButton(renderer, &white, "./assets/white_active.bmp", "./assets/white_inactive.bmp", CHESS_BUTTON_WHITE, false);
    buttons[7] = createChessButton(renderer, &black, "./assets/black_active.bmp", "./assets/black_inactive.bmp", CHESS_BUTTON_BLACK, false);
    buttons[8] = createChessButton(renderer, &start, "./assets/start_active.bmp", "./assets/start_active.bmp", CHESS_BUTTON_START, true);
    buttons[9] = createChessButton(renderer, &back, "./assets/back_active.bmp", "./assets/back_active.bmp", CHESS_BUTTON_BACK, true);

    for (int i = 0; i < numButtons ; i++) {
        if (buttons[i] == NULL) {
            destroySettingsWindowButtons(buttons, numButtons);
            return NULL;
        }
    }

    if (settings->gameMode == 1) {
        buttons[0]->isActive = true;
    } else {
        buttons[1]->isActive = true;
    }

    if (settings->difficulty == 1) {
        buttons[2]->isActive = true;
    } else if (settings->difficulty == 2) {
        buttons[3]->isActive = true;
    } else if (settings->difficulty == 3) {
        buttons[4]->isActive = true;
    } else if (settings->difficulty == 4) {
        buttons[5]->isActive = true;
    }

    if (settings->userColor) {
        buttons[6]->isActive = true;
    } else {
        buttons[7]->isActive = true;
    }

    return buttons;
}
ChessSettingsWindow* createSettingsWindow() {
    ChessSettingsWindow* res = malloc(sizeof(ChessSettingsWindow));
    SDL_Window* window = SDL_CreateWindow("Tests", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    GameSettings* settings = GameSettingsCreate();
    ChessButton** buttons = createSettingsWindowChessButtons(renderer, settings);
    if (res == NULL || window == NULL || renderer == NULL || settings == NULL || buttons == NULL ) {
        free(res);
        free(buttons);
        GameSettingsDestroy(settings);
        //We first destroy the renderer
        SDL_DestroyRenderer(renderer); //NULL safe
        SDL_DestroyWindow(window); //NULL safe
        return NULL ;
    }
    res->buttons = buttons;
    res->numOfButtons = 10;
    res->numDifficulties = 4;
    res->numColors = 2;
    res->numModes = 2;
    res->window = window;
    res->windowRenderer = renderer;
    res->settings = settings;

    return res;
}
void destroySettingsWindow(ChessSettingsWindow *src) {
    if (src == NULL ) {
        return;
    }

    for (int i = 0; i < src->numOfButtons; i++) {
        destroyChessButton(src->buttons[i]);
    }
    free(src->buttons);
    GameSettingsDestroy(src->settings);
    SDL_DestroyRenderer(src->windowRenderer);
    SDL_DestroyWindow(src->window);

    free(src);
}
void drawSettingsWindow(ChessSettingsWindow *src) {
    if (src == NULL ) {
        return;
    }

    SDL_Rect difficultyTitle = { .x = 10, .y = 50, .h = 100, .w = 250};
    SDL_Rect modeTitle = { .x = 10, .y = 200, .h = 100, .w = 250};
    SDL_Rect colorTitle = { .x = 10, .y = 500, .h = 100, .w = 250};


    //Draw window
    SDL_SetRenderDrawColor(src->windowRenderer, 255, 255, 255, 255);
    SDL_RenderClear(src->windowRenderer);
    int i = 0;
    for (; i < src->numOfButtons; i++) {
        drawChessButton(src->buttons[i]);
    }

    drawTitle(src->windowRenderer, &difficultyTitle, "./assets/difficulty_title.bmp");
    drawTitle(src->windowRenderer, &modeTitle, "./assets/mode_title.bmp");
    drawTitle(src->windowRenderer, &colorTitle, "./assets/color_title.bmp");

    SDL_RenderPresent(src->windowRenderer);
}

CHESS_SETTINGS_EVENT handleEventSettingsWindow(ChessSettingsWindow *src, SDL_Event *event){
    if(src == NULL || event==NULL){
        return CHESS_SETTINGS_EXIT;
    }

    for(int i = 0;i<src->numOfButtons;i++){
        ChessButton* button = src->buttons[i];
        BUTTON_CLICK_EVENT clickEvent = handleChessButtonEvent(button, event);
        // TODO: Refactor handling functions
        switch (clickEvent) {
            case CHESS_CLICKED_1PLAYER:
                toggleModeButton(ONEPLAYER_NUMBER, src, src->buttons[i], MODE_SETTING_START_INDEX);
                break;
            case CHESS_CLICKED_2PLAYER:
                toggleModeButton(TWOPLAYER_NUMBER, src, src->buttons[i], MODE_SETTING_START_INDEX);
                break;
            case CHESS_CLICKED_NOOB:
                toggleDifficultyButton(NOOB_NUMBER, src, src->buttons[i], DIFFICULTY_SETTING_START_INDEX);
                break;
            case CHESS_CLICKED_EASY:
                toggleDifficultyButton(EASY_NUMBER, src, src->buttons[i], DIFFICULTY_SETTING_START_INDEX);

                break;
            case CHESS_CLICKED_MODERATE:
                toggleDifficultyButton(MODERATE_NUMBER, src, src->buttons[i], DIFFICULTY_SETTING_START_INDEX);
                break;
            case CHESS_CLICKED_HARD:
                toggleDifficultyButton(HARD_NUMBER, src, src->buttons[i], DIFFICULTY_SETTING_START_INDEX);
                break;
            case CHESS_CLICKED_WHITE:
                toggleColorButton(WHITE_NUMBER, src, src->buttons[i], COLOR_SETTING_START_INDEX);
                break;
            case CHESS_CLICKED_BLACK:
                toggleColorButton(BLACK_NUMBER, src, src->buttons[i], COLOR_SETTING_START_INDEX);
                break;
            case CHESS_CLICKED_START:
                return CHESS_SETTINGS_START;
                break;
            case CHESS_CLICKED_BACK:
                return CHESS_SETTINGS_BACK;
            case CHESS_CLICKED_NEW_GAME:break;
            case CHESS_CLICKED_LOAD:break;
            case CHESS_CLICKED_QUIT:break;
            case CHESS_CLICKED_NONE:break;
            case CHESS_CLICKED_RESTART:break;
            case CHESS_CLICKED_SAVE:break;
            case CHESS_CLICKED_MAIN_MENU:break;
            case CHESS_CLICKED_UNDO:break;
            case CHESS_CLICKED_SLOT_1:break;
            case CHESS_CLICKED_SLOT_2:break;
            case CHESS_CLICKED_SLOT_3:break;
            case CHESS_CLICKED_SLOT_4:break;
            case CHESS_CLICKED_SLOT_5:break;
        }
    }

    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE) return CHESS_SETTINGS_EXIT;

    return CHESS_SETTINGS_NONE;
}

void hideSettingsWindow(ChessSettingsWindow* src) {
    SDL_HideWindow(src->window);
}

void showSettingsWindow(ChessSettingsWindow* src) {
    SDL_ShowWindow(src->window);
}

void destroySettingsWindowButtons(ChessButton** buttons, int numOfButtons) {
    for (int i = 0; i < numOfButtons; i++) {
        destroyChessButton(buttons[i]);
    }

    free(buttons);
}

void toggleDifficultyButton(int selectedDifficulty, ChessSettingsWindow* src, ChessButton* button, int startIndex) {
    if (src->settings->difficulty != selectedDifficulty) {
        setDifficulty(src->settings, selectedDifficulty);

        for (int j = startIndex;j < (startIndex + src->numDifficulties); j++) {
            if (src->buttons[j]->isActive) toggleChessButton(src->buttons[j]);
        }
        toggleChessButton(button);
    }
}

void toggleColorButton(int selectedColor, ChessSettingsWindow* src, ChessButton* button, int startIndex) {
    if (src->settings->userColor != selectedColor) {
        setUserColor(src->settings, selectedColor);

        for (int j = startIndex;j < (startIndex + src->numColors); j++) {
            if (src->buttons[j]->isActive) toggleChessButton(src->buttons[j]);
        }
        toggleChessButton(button);
    }
}

void toggleModeButton(int selectedMode, ChessSettingsWindow* src, ChessButton* button, int startIndex) {
    if (src->settings->gameMode != selectedMode) {
        setGameMode(src->settings, selectedMode);

        for (int j = startIndex;j < (startIndex + src->numModes); j++) {
            if (src->buttons[j]->isActive) toggleChessButton(src->buttons[j]);
        }
        toggleChessButton(button);
    }
}

void drawTitle(SDL_Renderer* renderer, SDL_Rect* location, const char* image) {
    SDL_Surface* loadingSurface = SDL_LoadBMP(image);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);

    if (loadingSurface == NULL || texture == NULL) {
        SDL_FreeSurface(loadingSurface); //It is safe to pass NULL
        SDL_DestroyTexture(texture); //It is safe to pass NULL
    }

    SDL_FreeSurface(loadingSurface);
    SDL_RenderCopy(renderer, texture, NULL, location);
}