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