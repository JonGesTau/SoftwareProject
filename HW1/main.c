// gcc src.c -o output.exe

#include <stdio.h>
#include <string.h>

int main(){
    int baseA;
    int baseB;
    unsigned long value = 0;
    enum { MAX_INPUT_SIZE = 256 };
    char input[MAX_INPUT_SIZE];
    char output[MAX_INPUT_SIZE];

    ///// base a
    printf("Please enter the number's base:\n");
    scanf("%d", &baseA);

    if(baseA < 2 || baseA > 16){
        printf("Invalid input base\n");
        return -1;
    }

    ///// base b
    printf("Please enter the desired base:\n");
    scanf("%d", &baseB);

    if(baseB < 2 || baseB > 16){
        printf("Invalid desired base\n");
        return -1;
    }

    ////// get input
    printf("Please enter a number in base %d:\n", baseA);
    scanf("%s", *&input);

    for(unsigned int i = 0; i < strlen(input); i++){
        // 97 a 65 A 0 is 48
        int digit = (int) input[i];

        if(digit > 47 && digit < 58){
            if(digit - 47 > baseA){
                printf("Invalid number!\n");
                return -1;
            }
            continue;
        }

        if(digit > 96 && digit < 103){ // switch to upper case
            input[i] = (char) (input[i] - 32);
            digit -= 32;
        }

        if(digit > 64 && digit < 71){
            if(digit - 54 > baseA){
                printf("Invalid number!\n");
                return -1;
            }
            continue;
        }

        printf("Invalid number!\n");
        return -1;
    }

    ////// convert to long
    int power = 1;

    for(int i = strlen(input)-1; i > -1; i--){
        int digit = 0;

        if((int)input[i] > 47 && (int)input[i] < 58)
            digit = (int)input[i] - 48;
        else
            digit = (int)input[i] - 55;

        value += power * digit;
        power *= baseA;
    }

    ///// convert to new base
    int index = 0;
    while(value > 0){
        char digit = value % baseB;
        value -= digit;
        value /= baseB;
        output[index] = digit < 10 ? (char)(48+digit) : (char)(55+digit);
        index ++;
    }

    index -= 1;

    //// print output string in reverse
    printf("The result is : ");
    for(; index >= 0; index --){
        printf("%c", output[index]);
    }
    printf("\n");

    return 0;
}
