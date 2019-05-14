/*Задача c-program-wc: Program a-la wc

Программа получает список файлов и должна вывести информацию о содержимом: число строк, слов и символов.

Строки: последовательность до перевода строки ('\n')
Слова: непустая последовательность непробельных символов (isspace)
Символы: суммарно все символы, включая переводы строк и т.д.
Если списка файлов нет, то работает со стандартным вводом.

Ошибки от открытия файла надо обрабатывать (perror) и переходить к следующему

Вывести построчно, через один пробел: три числа и имя файла, если с имена были заданы (для каждого файла, который успешно открылся) и просто три числа в строке, если работа идет со стандартным потоком.

Тесты и пример приведены для случая без файлов

Примеры

Входные данные

a b c
      
Результат работы

1 3 6
Входные данные

a b c[no new-line here, EOF after c]
      
Результат работы

0 3 5
*/

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
