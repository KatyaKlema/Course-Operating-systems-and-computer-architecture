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
