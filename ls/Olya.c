#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>

int compare (const void *first, const void *second) {
	return strcmp(*(const char**)first, *(const char**)second);
}

void attributes(int file, char* string) {
        if (S_ISDIR(file)) {
		string[0] = 'd';	
	}
	else if (S_ISCHR(file)) {
		string[0] = 'c';	
	}
	else if (S_ISBLK(file)) {
		string[0] = 'b';	
	}
	else if (S_ISFIFO(file)) {
		string[0] = 'p';	
	}
	else if (S_ISLNK(file)) {
		string[0] = 'l';	
	}
	else {
		string[0] = '-';	
	}
	if (file & S_IRUSR) {
		string[1] = 'r';	
	}
	else {
		string[1] = '-';	
	}
	if (file & S_IWUSR) {
		string[2] = 'w';	
	}
	else {
		string[2] = '-';	
	}
	if (file & S_IXUSR) {
		string[3] = 'x';	
	}
	else {
		string[3] = '-';	
	}
	if (file & S_IRGRP) {
		string[4] = 'r';	
	}
	else {
		string[4] = '-';	
	}
	if (file & S_IWGRP) {
		string[5] = 'w';	
	}
	else {
		string[5] = '-';	
	}
	if (file & S_IXGRP) {
		string[6] = 'x';	
	}
	else {
		string[6] = '-';	
	}
	if (file & S_IROTH) {
		string[7] = 'r';	
	}
	else {
		string[7] = '-';	
	}
	if (file & S_IWOTH) {
		string[8] = 'w';	
	}
	else {
		string[8] = '-';	
	}
	if (file & S_IXOTH) {
		string[9] = 'x';	
	}
	else {
		string[9] = '-';	
	} 
}

void printFileInfo(struct stat file, char* filename, char* path) {
	char* user = malloc(100000000 * sizeof(char));
	int usr_uid = -2;
	struct passwd* pswd = getpwuid(file.st_uid);
	if (pswd == NULL) {
		usr_uid = file.st_uid;
	}
	else {
		strcpy(user, pswd->pw_name);
	}
	char* group = malloc(100000000 * sizeof(char));
	int grp_gid = -2;
	struct group* grp = getgrgid(file.st_gid);
	if (grp == NULL) {
		grp_gid = file.st_gid;	
	}
	else {
		strcpy(group, grp->gr_name);
	}
	char attr[11];
	attributes(file.st_mode, attr);
	if (grp_gid == -2 && usr_uid == -2)
		printf("%s %ld %s %s %ld %s", attr, file.st_nlink, user, group, file.st_size, filename);
	else if (grp_gid == -2 && usr_uid != -2)
		printf("%s %ld %d %s %ld %s", attr, file.st_nlink, usr_uid, group, file.st_size, filename);
	else if (grp_gid != -2 && usr_uid == -2)
		printf("%s %ld %s %d %ld %s", attr, file.st_nlink, user, grp_gid, file.st_size, filename);
	else if (grp_gid != -2 && usr_uid != -2)
		printf("%s %ld %d %d %ld %s", attr, file.st_nlink, usr_uid, grp_gid, file.st_size, filename);
	if (S_ISLNK(file.st_mode)) {
		char* linkinfo = malloc(100000000 * sizeof(char));
		if (readlink(path, linkinfo, 99999999) != -1) {
			printf(" -> %s", linkinfo);
		}
		else {
			perror("");
			exit(1);		
		}			
	}
	printf("\n");
	free(user);
	free(group);
}

void ls_lR(char *dirname) {
	printf("%s:\n", dirname);
	char **files = malloc(100000 * sizeof(char*));
	char **dirs = malloc(100000 * sizeof(char*));
	DIR* dir = opendir(dirname);
	if (dir != NULL) {
		struct dirent *dp;
		int files_cnt = 0;
		while ((dp = readdir(dir)) != NULL) {
			files[files_cnt] = malloc((strlen(dp->d_name) + 1) * sizeof(char));
			strcpy(files[files_cnt], dp->d_name);
			files_cnt++;	
		}
		int dirs_cnt = 0;
		qsort(files, files_cnt, sizeof(char*), compare);
		for (int i = 0; i < files_cnt; i++) {
			char *next_dir = malloc((strlen(dirname) + strlen(files[i]) + 2) * sizeof(char));
			strcpy(next_dir, dirname);
			if (next_dir[strlen(next_dir) - 1] != '/') {
				strcat(next_dir, "/");
			}
			strcat(next_dir, files[i]);	
			struct stat file;
			if (lstat(next_dir, &file) != 0) {
				perror("");
				exit(1);
			}
			if (strcmp(files[i], ".") != 0 && strcmp(files[i], "..") != 0) {		
				if (S_ISDIR(file.st_mode)) {
					dirs[dirs_cnt] = next_dir;
					dirs_cnt++;			
				}
				printFileInfo(file, files[i], next_dir);
			}
		}
		printf("\n");
		for (int i = 0; i < dirs_cnt; i++) {
			ls_lR(dirs[i]);	
		}
		for (int i = 0; i < 100000; ++i) {
			free(files[i]);	
			free(dirs[i]);	
		}
		closedir(dir);
	}
	else {
		perror("");
		exit(1);
	}
}

int main(int argc, char **argv) {
	struct stat file;
	if (lstat(argv[1], &file) != 0) {
		perror("");
		return 1;
	}
	if (!S_ISDIR(file.st_mode)) {
		printFileInfo(file, argv[1], argv[1]);
	}
	else {
		ls_lR(argv[1]);
	}
	return 0;
}
