#include <stdio.h>
#include<stdlib.h>
#include<ctype.h>


int main(int argc, int **argv) {
    int countOfStrings = 0;
    int countOfWords = 0;
    int countOfSymbols = 0;

    int length = 0;
    int currentSymbol;
    int currentString = 0;
    int currentWord = 0;
    int currentCharacter = 0;
    if(argc == 1){
        while((currentSymbol = getchar()) != EOF) {
            ++currentCharacter;
            if(isspace(currentSymbol) && length != 0)
                ++currentWord;
            if(currentSymbol == '\n')
                ++currentString;
            if(!isspace(currentSymbol))
                ++length;
            else
                length = 0;
        }
        if(length > 0)
            ++currentWord;
        printf("%d %d %d\n", currentString, currentWord, currentCharacter);
    }
    else {
        for (int i = 1; i < argc; ++i) {
            FILE *file = fopen(argv[i], "r");
            if(file == NULL){
                perror("");
                continue;
            }
            while ((currentSymbol = fgetc(file)) != EOF) {
                ++currentCharacter;
                if (isspace(currentSymbol) && length != 0)
                    ++currentWord;
                if (currentSymbol == '\n')
                    ++currentString;
                if (!isspace(currentSymbol))
                    ++length;
                else
                    length = 0;
            }

            if (length > 0)
                ++currentWord;

            printf("%d %d %d %s\n", currentString, currentWord, currentCharacter, argv[i]);
            countOfStrings += currentString;
            countOfWords += currentWord;
            countOfSymbols += currentCharacter;
        }

    }
    return 0;
}
