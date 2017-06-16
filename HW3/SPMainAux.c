#include "SPMainAux.h"

int getLevel() {
    char userInput[1024];
    int level = 0;

    printf("Please enter the difficulty level between [1-7]:\n");
    gets(userInput);

    if (spParserIsInt(userInput)) {
        level = strtoumax(userInput, NULL, 10);
        if (level < 1 || level > 7) {
            printf("Error: invalid level (should be between 1 to 7\n");
            getLevel();
        }
    }

    return level;
}
