/*
Задача sieve: Поиск простых чисел

Программе в качестве ARG1 передается число нитей, которые надо запустить. Также может быть ARGV2 — предел поиска. Если предела нет, то бесконечность (ULLONG_MAX)

Требуется породить дополнительное число нитей/тяжелых процессов и с помощью них найти простые числа в промежутке 1…ARGV2. Эффективность работы можно смотреть с помощью программы time

Новые нити только считают, выводит всё основная нить, по одному числу в строке.

Варианты:

Базовый вариант: используя чисто счетный перебор: каждая нить перебирает свой интервал: 3.5
как предыдущий, но через fork() и mmap/shm_open: 4.5
как базовый, но интервалы делятся на кусочки по 100, нить обрабатывает только один, учёт обработанных не ведется: 6
как предыдущий, но через fork() и mmap/shm_open: 7.5
как базовый, но интервалы делятся на кусочки по 100, нить обрабатывает только один, ведется учёт (карта) обработанных (mutex): 8.5
как предыдущий, но через fork() и mmap/shm_open: 10.5
Примеры

Входные данные

./prog 2 100
      
Результат работы

2
3
5
7
11
13
17
19
23
29
31
37
41
43
47
53
59
61
67
71
73
79
83
89
97
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include<math.h>
#define MAX 2e6
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


struct threadInfo {
    int start;
    int finish;
    int val;
    int *num;
};

void check(struct threadInfo *info) {
    int current = info->start;
    while(current < info->finish){
        info->num[current] = 1;
        current += info->val;
    }
    pthread_exit(NULL);
}


void fill(int *num, int max_value){
    for(int i = 0; i < 2; ++i){
        num[i] = 1;
    }

    for(int i = 2; i < max_value; ++i){
        num[i] = 0;
    }
}

void modify(int *num, struct threadInfo *info, int maxValue, int numberOfThreads, pthread_t *threads, int i){
    int thread = max(1, (((maxValue) / i) + numberOfThreads - 1) / numberOfThreads);
    int j = 0;
    do{
        info[j].start = i * (1 + j * thread);
        info[j].finish = min(maxValue + 1, i * (1 + (j + 1) * thread));
        info[j].num = num;
        info[j].val = i;

        if (pthread_create(&threads[j], NULL, check, &info[j]) != 0) {
            perror("Error)");
            exit(0);
        }
        ++j;

    }while(j < numberOfThreads && info[j - 1].finish != (maxValue + 1));

    --j;

    while (j >= 0) {
        if (pthread_join(threads[j], NULL) != 0) {
            perror("");
            exit(0);
        }
        --j;
    }
}

int isPrime(int a, int *num){
    return 1 - num[a];
}
void operation(int numberOfThreads, int maxValue) {
    pthread_t threads[numberOfThreads];
    struct threadInfo info[numberOfThreads];

    int num[maxValue];
    fill(num, maxValue);
    for (int i = 2; i <= maxValue; ++i) {
        if (isPrime(i, num)) {
            printf("%d\n", i);
            modify(num, info, maxValue, numberOfThreads, threads, i);
        }
    }
}

int main(int argc, char **argv) {
    if(argc == 2) {
        operation(atoi(argv[1]), MAX);
    }
    else{
        operation(atoi(argv[1]), atoi(argv[2]));
    }
}