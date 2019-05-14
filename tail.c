/*
Задача c-program-tail: Program a-la system tail

Программа получает список файлов и должна вывести последние 10 строк (или сколько может) из каждого файла. Последняя строка может быть во вводе без '\n', свои символы перевода строк не добавлять, дополнительные файлы не использовать.

Если списка файлов нет, то работает со стандартным вводом.

Ошибки от открытия файла надо обрабатывать (perror) и переходить к следующему

Если работает с файлами, то перед выводом каждого (успешного или нет) пишет: ==> имя-файла <==

Тесты и пример приведены для случая без файлов.

Примеры

Входные данные

a
b
c
d
e
f
g
h
1
2
3
4
5
z
y
x
      
Результат работы

g
h
1
2
3
4
5
z
y
x

*/

#include <stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <stdlib.h>
void tail(FILE* file, char *ans[11]){
    char *ch;
    int countWords = 0;
    int i;
    for(i = 0; i <= 10; ++i){
        ans[i] = (char*)malloc(100000000);
    }
    while((ch = fgets(ans[countWords], 100000000, file)) != NULL){
        countWords++;
        countWords %= 11;
        free(ans[countWords]);
        ans[countWords] = (char*)malloc(100000000);
        if(ans[countWords] == NULL){
            perror("");
            exit(0);
        }
    }
    int k = countWords;
    int count = 0;
    while(count <= 10){
        printf("%s", ans[k]);
        k++;
        k %= 11;
        ++count;
    }
}
int main(int argc, char *argv[]){
    char *ans[11];
    int i;
    if(argc == 1){
        tail(stdin, ans);
        int k;
        for(k = 0; k < 11; ++k){
            free(ans[k]);
        }
    }
    else{
        for(i = 1; i < argc; ++i){
            FILE *file = fopen(argv[i], "r");
            printf("==>%s<==\n", argv[i]);
            if(file == NULL){
                perror("");
                continue;
            }
            tail(file, ans);
            fclose(file);
        }
    }
}