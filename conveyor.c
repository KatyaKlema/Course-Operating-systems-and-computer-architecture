/*
Задача conveyor: Program microshell

Программе в качестве аргументов передаются имена программ, которые надо запустить и свзяать между собой через каналы (pipe). Т.е. если программу запустили с параметрами p1 p2 p3 p4, то работа должна быть эквивалента запуску в оболочке (shell) последовательности p1 | p2 | p3 | p4:

процессы запускаются параллельно
вывод первого подается на вход второго, выход второго — на вход третьего и т.д.
Можно использовать dup2, pipe, fork и любой из exec'ов. Нельзя использовать: system (как и любой другой способ переложить на shell), popen.

exec может быть неуспешен, надо проверять
если не следить за дескрипторами канала, то их может быть слишком много.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void print(char *str,  int index, int **fd, int n){
    int prev, current;
    if(index == 0){
        prev = fd[index][1];
        current = 0;
    }
    else if(index == n){
        prev = 1;
        current = fd[index - 1][0];
    }
    else{
        prev = fd[index][1];
        current = fd[index - 1][0];
    }
    if(dup2(prev, 1) == -1){
        perror("Error");
        exit(0);
    }
    
    if(dup2(current, 0) == -1){
        perror("Error");
        exit(0);
    }
    for(int i = 0; i < n; ++i){
        if (fd[i][1] != prev) {
            close(fd[i][1]);
        }
        if (fd[i][0] != current) {
            close(fd[i][0]);
        }
    }
    if(execlp(str, str, NULL) == -1){
        perror("Error");
        exit(1);
    }
    perror("Launch Error");
    exit(0);
}
int main(int argc, char **argv) {
    pid_t pid;
    if (argc < 3) {
        if ((pid = fork()) == 0) {
            execlp(argv[1], argv[1], NULL);
            perror("Error");
            exit(1);
        }
        else if (pid == -1) {
            perror("");
            return 1;
        }
        wait(NULL);
        return 0;
    }
    else{
    int **fd = (int **) malloc(sizeof(int *) * argc);
    for(int i = 0; i < argc; ++i){
        fd[i] = (int *)malloc(2 * sizeof(int));
    }
    
    if(pipe(fd[0]) == -1){
        perror("Error");
        exit(0);
    }
    
    if((pid = fork()) == 0){
        print(argv[1], 0, fd, argc - 2);
    }
    else if(pid == -1){
        perror("Error");
        exit(0);
    }
    for(int i = 1; i < argc - 2; ++i){
        if(pipe(fd[i]) == -1){
            perror("Error");
            exit(0);
        }
        
        if((pid = fork()) == 0){
            print(argv[i + 1], i, fd, argc - 2);
        }
        else if(pid == -1){
            perror("Error");
            exit(0);
        }
    }
    
    if((pid = fork()) == 0)
    print(argv[argc - 1], argc - 2, fd, argc - 2);
    else if(pid == -1){
        perror("Error");
        exit(0);
    }
    for(int i = 0; i < argc; ++i){
        close(fd[i][0]);
        close(fd[i][1]);
    }
    for(int i = 0; i < argc; ++i){
        wait(NULL);
    }
    
    for(int i = 0; i < argc; ++i){
        free(fd[i]);
    }
    free(fd);
    return 0;
    }
}