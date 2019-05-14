/*
 Задача network-chat: Program chat
 
 Программа получает в качестве параметра номер порта. Ждет подключений клиентов (nc, сообщение не больше 1024). Клиенты могут подключаться и отключаться в любой момент.
 
 Требуется реализовать чат между клиентами: сообщение одного попадает ко всем (в порядке поступления).
 

 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    int d  = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    int c;
    ssize_t s, r;
    char * buffer = malloc(1024 * sizeof(char));
    char * read = malloc(1024 * sizeof(char));
    if(read == NULL){
        perror("malloc Error");
        exit(0);
    }
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atol(argv[1]));
    if(bind(d, (struct sockaddr *)&servaddr, sizeof(servaddr))<0){
        perror("bind");
        exit(1);
    }
    if(listen(d, 10) < 0){
        perror("listen");
        exit(1);
    }
    int size = 1023;
    c = accept(d, (struct sockaddr*)NULL, (int*)NULL);
    while(true){
        s = recv(c, buffer, size, 0);
        scanf("%s", read);
        buffer[s] = '\0';
        if(strcmp(buffer, "quit")){
            printf("%s", buffer);
        }
        else
            break;
        
        
        if (strcmp(read, "quit")) {
            strcat(read, "\n");
            send(c, read, size, 0);
            read = realloc(read, 1024 * sizeof(char));
            if(read == NULL){
                perror("realloc Error");
                exit(0);
            }
        }
        else
            break;
    }
    close(c);
    free(buffer);
    return 0;
}
