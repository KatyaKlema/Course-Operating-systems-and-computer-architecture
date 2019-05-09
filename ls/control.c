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

void print(struct stat F, char *fileName, char* currentDirName){
    char *userName = malloc(100000000 * sizeof(char));
    int userUID;
    struct passwd *p = getpwuid(F.st_uid);
    if(p == NULL){
        userUID = F.st_uid;
    }
    else{
        strcpy(userName, p->pw_name);
    }
    struct group *g = getgrgid(F.st_gid);
    int groupGID;
    char *groupName = malloc(100000000 * sizeof(char));
    
    
    if(g == NULL){
        groupGID = F.st_gid;
    }
    else{
        strcpy(groupName, g->gr_name);
    }
    
    char array[11] = "----------";
    fill(array, F);
    printf("%s %d ", array, F.st_nlink);
    if (p != NULL && g != NULL) {
        printf("%s %s ", userName, groupName);
    }
    else if (p == NULL && g != NULL) {
        printf("%d %s ", userUID, groupName);
    }
    else if (p != NULL && g == NULL) {
        printf("%s %d ", userName, groupGID);
    }
    else /*if(groupGID != -10 && userUID != -10)*/{
        printf("%d %d ",userUID, groupGID);
    }
    
    printf("%lld %s", F.st_size, fileName);
    /*if (S_ISLNK(F.st_mode)) {
     char* link = malloc(100000000 * sizeof(char));
     if (readlink(currentDirName, link, 99999999) != -1) {
     printf(" -> %s", link);
     } else {
     exit(0);
     }
     }
     printf("\n");
     */
    free(userName);
    free(groupName);
    
    
}

int countF(DIR *dir, char **arrayOfFiles){
    int count = 0;
    struct dirent *d;
    while((d = readdir(dir)) != NULL){
        arrayOfFiles[count] = malloc((strlen(d->d_name) + 1) * sizeof(char));
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
    
    int countOfFiles = countF(dir, arrayOfFiles);
    
    char **arrayOfDirectories = malloc(100000 * sizeof(char*));
    int countOfDirectories = 0;
    printf("%s:\n", directoryName);
    qsort(arrayOfFiles, countOfFiles, sizeof(char*), comp);
    for (int i = 0; i < countOfFiles; i++) {
        char *currentDirName = malloc((10000) * sizeof(char));
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
            print(file, arrayOfFiles[i], currentDirName);
            if (S_ISLNK(file.st_mode)) {
                char* link = malloc(100000000 * sizeof(char));
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
        print(f, argv[1], argv[1]);
        
        if (S_ISLNK(f.st_mode)) {
            char* link = malloc(100000000* sizeof(char));
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


