/*
Задача ls-lR: Program a-la ls -lR

Реализуйте упрощённый аналог команды ls -lR.

Программе в качестве первого аргумента передаётся имя директории.

Необходимо рекурсивно вывести содержимое директории в виде (в отсортированном по имени) :

имя директории:

АТТРИБУТЫ КОЛ_ВО_ССЫЛОК ВЛАДЕЛЕЦ ГРУППА РАЗМЕР ИМЯ
после вывода всех объектов, если есть вложенные директории, то повторить: пустая строка, содержимое в том же рекурсивном формате очередной директории

Если в качестве аргумента указано имя файла, то вывести информацию только об этом единственном файле (одна строка).

Для символических ссылок выведите ещё и имена файлов, на которые они ссылаются.

Суперправа показывать не надо (если не знаете, что это, то и не покажете).

В случае ошибки - вывести текст ошибки на стандартный поток ошибок и завершить работу с кодом 1.

Отсутствие пользователя/группы ошибкой не является, в этом случае вывести номер (uid/gid)

по ссылкам идти не нужно

Примеры

Входные данные

/boot
Результат работы

/boot:
-rw-r--r-- 1 root root  3474420 System.map-4.12.14-lp150.12.22-default
-rw-r--r-- 1 root root      512 backup_mbr
lrwxrwxrwx 1 root root        1 boot -> .
-rw-r--r-- 1 root root     1725 boot.readme
-rw-r--r-- 1 root root   196482 config-4.12.14-lp150.12.22-default
drwxr-xr-x 2 root root     4096 grub2
lrwxrwxrwx 1 root root       34 initrd -> initrd-4.12.14-lp150.12.22-default
-rw------- 1 root root 11847632 initrd-4.12.14-lp150.12.22-default
-rw-r--r-- 1 root root   182704 memtest.bin
-rw-r--r-- 1 root root   422912 message
-rw-r--r-- 1 root root  1124964 symtypes-4.12.14-lp150.12.22-default.gz
-rw-r--r-- 1 root root   388747 symvers-4.12.14-lp150.12.22-default.gz
-rw-r--r-- 1 root root      484 sysctl.conf-4.12.14-lp150.12.22-default
-rw-r--r-- 1 root root  8028448 vmlinux-4.12.14-lp150.12.22-default.gz
lrwxrwxrwx 1 root root       35 vmlinuz -> vmlinuz-4.12.14-lp150.12.22-default
-rw-r--r-- 1 root root  7057520 vmlinuz-4.12.14-lp150.12.22-default

/boot/grub2:
-r--r--r-- 1 root root    9971 grub.cfg
-rw-r--r-- 1 root root    1024 grubenv
-rw-r--r-- 1 root root 2397557 unicode.pf2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>


int comp (const void *i, const void *j) {
    return strcmp(*(const char**)i, *(const char**)j);
}

void fill(char *array, struct stat fStat){
    if(S_ISDIR(fStat.st_mode))
        array[0] = 'd';
    else if(S_ISBLK(fStat.st_mode))
        array[0] = 'b';
    else if(S_ISLNK(fStat.st_mode))
        array[0] = 'l';
    else if(S_ISCHR(fStat.st_mode))
        array[0] = 'c';
    else if(S_ISFIFO(fStat.st_mode))
        array[0] = 'p';
    
    
    if (fStat.st_mode & S_IRUSR)
        array[1] = 'r';
    if (fStat.st_mode & S_IWUSR)
        array[2] = 'w';
    if (fStat.st_mode & S_IXUSR)
        array[3] = 'x';
    if (fStat.st_mode & S_IRGRP)
        array[4] = 'r';
    if (fStat.st_mode & S_IWGRP)
        array[5] = 'w';
    if (fStat.st_mode & S_IXGRP)
        array[6] = 'x';
    if (fStat.st_mode & S_IROTH)
        array[7] = 'r';
    if (fStat.st_mode & S_IWOTH)
        array[8] = 'w';
    if(fStat.st_mode & S_IXOTH)
        array[9] = 'x';
}

void print(struct stat F, char *fileName){
    
    struct passwd *p = getpwuid(F.st_uid);
    
    struct group *g = getgrgid(F.st_gid);
    
    
    char array[11] = "----------";
    fill(array, F);
    printf("%s %d ", array, F.st_nlink);
    if (p != NULL && g != NULL) {
        printf("%s %s ", p->pw_name, g->gr_name);
    }
    else if (p == NULL && g != NULL) {
        printf("%d %s ", F.st_uid, g->gr_name);
    }
    else if (p != NULL && g == NULL) {
        printf("%s %d ", p->pw_name, F.st_gid);
    }
    else{
        printf("%d %d ",F.st_uid, F.st_gid);
    }
    
    printf("%d %s", F.st_size, fileName);
    
}

int countF(DIR *dir, char **arrayOfFiles){
    int count = 0;
    struct dirent *d;
    while((d = readdir(dir)) != NULL){
        arrayOfFiles[count] = malloc((strlen(d->d_name) + 1) * sizeof(char));
        if(arrayOfFiles[count] == NULL){
            perror("Malloc Error");
            exit(0);
        }
        strcpy(arrayOfFiles[count], d->d_name);
        ++count;
    }
    
    return count;
}

void recursion(char *directoryName){
    DIR* dir = opendir(directoryName);
    if(dir == NULL){
        perror("Error");
        closedir(dir);
        exit(0);
    }
    char **arrayOfFiles = malloc(100000 * sizeof(char*));
    if(arrayOfFiles == NULL){
        perror("Malloc Error");
        exit(0);
    }
    int countOfFiles = countF(dir, arrayOfFiles);
    
    char **arrayOfDirectories = malloc(100000 * sizeof(char*));
    if(arrayOfDirectories == NULL){
        perror("Malloc Error");
        exit(0);
    }
    int countOfDirectories = 0;
    printf("%s:\n", directoryName);
    qsort(arrayOfFiles, countOfFiles, sizeof(char*), comp);
    for (int i = 0; i < countOfFiles; i++) {
        char *currentDirName = malloc((10000) * sizeof(char));
        if(currentDirName == NULL){
            perror("Malloc Error");
            exit(0);
        }
        strcpy(currentDirName, directoryName);
        if (currentDirName[strlen(currentDirName) - 1] != '/') {
            strcat(currentDirName, "/");
        }
        strcat(currentDirName, arrayOfFiles[i]);
        if (!(strlen(arrayOfFiles[i]) == 1 && arrayOfFiles[i][0] == '.') &&
            !(strlen(arrayOfFiles[i]) == 2 && arrayOfFiles[i][0] == '.' && arrayOfFiles[i][1] == '.')){
            struct stat file;
            if (lstat(currentDirName, &file) != 0) {
                perror("");
                exit(1);
            }
            if (S_ISDIR(file.st_mode)) {
                arrayOfDirectories[countOfDirectories++] = currentDirName;
            }
            print(file, arrayOfFiles[i]);
            if (S_ISLNK(file.st_mode)) {
                char* link = malloc(100000000 * sizeof(char));
                if(link == NULL){
                    perror("Malloc Error");
                    exit(0);
                }
                if (readlink(currentDirName, link, 99999999) != -1) {
                    printf(" -> %s", link);
                } else {
                    exit(0);
                }
            }
            printf("\n");
            
        }
    }
    printf("\n");
    for (int i = 0; i < countOfDirectories; i++) {
        recursion(arrayOfDirectories[i]);
    }
    for (int i = 0; i < 100000; ++i) {
        free(arrayOfFiles[i]);
        free(arrayOfDirectories[i]);
    }
    closedir(dir);
    
}
int main(int argc, char **argv) {
    struct stat f;
    if(lstat(argv[1], &f) != 0){
        perror("Error");
        exit(0);
    }
    if(!S_ISDIR(f.st_mode)){
        print(f, argv[1]);
        
        if (S_ISLNK(f.st_mode)) {
            char* link = malloc(100000000 * sizeof(char));
            if(link == NULL){
                perror("Malloc Error");
                exit(0);
            }
            if (readlink(argv[1], link, 99999999) == -1) {
                exit(1);
            } else {
                printf(" -> %s", link);
            }
        }
        printf("\n");
    }
    else{
        recursion(argv[1]);
    }
    
    return 0;
}