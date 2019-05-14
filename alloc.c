/*Задача alloc

Программе на стандартный поток ввода подается некий текст, который надо разобрать на слова (лексемы), отсортировать, вывести отсортированный список слов, при выводе каждое слово помещать в двойные кавычки (").

Слова отделяются друг от друга непустой последовательностью пробельных символов (смотри isspace()). Для сортировки можно использовать функции strcmp и qsort

Модификации:

Базовый вариант: 1-5. Требуется проверят ошибки памяти, т.е. гарантироваться корректная работа в любых условиях.

Разделяющие лексемы (+0.5 за каждую, 3 за все). Сами по себе являются отдельным словом, всегда берется максимально возможной длины.

;

&

&&

|

||

Пример: a&b — три слова.

Кавычки (как двойные, так и одинарные) (+2). Несут особую функцию: внутри них (до парной) все символы являются частью слова. Кавычка не входит в слово и не является границей слова. Отсутствие парной кавычки — ошибка (должно обрабатываться).
Пример: aaa"'"bb (aaa, двойная кавычка, одиночная, двойная, bb) — это одно слово aaa'bb

Примеры

Входные данные

aaa    xb
cd
      
Результат работы

"aaa"
"cd"
"xb"
*/

#include <stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

int cmp(const void *p1, const void *p2);

int main() {
    char **ans = NULL, *buffer = NULL;
    int ch, currentSize = 0, size = 0;
    buffer = malloc(1);
    if (buffer == NULL) {
        perror("");
        exit(0);
    }
    while ((ch = getchar()) != EOF) {
        if (isspace(ch)) {
            if (currentSize != 0) {
                ans = realloc(ans, (size + 1) * sizeof(char*));
                if (ans == NULL) {
                    perror("");
                    exit(0);
                } else {
                    buffer = realloc(buffer, (currentSize + 1) * sizeof(char));
                    buffer[currentSize] = '\0';
                    ans[size++] = buffer;
                    buffer = malloc(1);
                    if (buffer == NULL) {
                        perror("");
                        exit(0);
                    }
                    currentSize = 0;
                }
            }
        }
        else {
            buffer = realloc(buffer, currentSize + 1);
            if (buffer == NULL) {
                perror("");
                exit(0);
            } else {
                buffer[currentSize++] = ch;
            }
        }
    }
    if (currentSize != 0) {
        ans = realloc(ans, (size + 1) * sizeof(char*));
        if (ans == NULL) {
            perror("");
            exit(0);
        }
        else {
            buffer[currentSize] = '\0';
            ans[size++] = buffer;
        }
    } else {
        free(buffer);
    }
    
    qsort(ans, size, sizeof(char*), cmp);
    int i;
    for (i = 0; i < size; ++i) {
        printf("\"%s\"\n", ans[i]);
        free(ans[i]);
    }
    return 0;
}

int cmp(const void *p1, const void *p2) {
    return strcmp(* (char * const *) p1, * (char * const *) p2);
}
