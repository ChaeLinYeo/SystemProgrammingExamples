#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void access_perm(char *perm, mode_t mode){
	int i;
	char permchar[] = "rwx";

	memset(perm, '-', 10);
	perm[10] = '\0';

	if(S_ISDIR(mode)) perm[0] = 'd';
	else if(S_ISCHR(mode)) perm[0] = 'c';
	else if(S_ISBLK(mode)) perm[0] = 'b';
	else if(S_ISFIFO(mode)) perm[0] = 'p';
	else if(S_ISLNK(mode)) perm[0] = 'l';

	for(i=0; i<9; i++){
		if((mode << i)&0x100){
			perm[i+1] = permchar[i%3];
		}
	}

	if(mode & S_ISUID) perm[3] = 's';
	if(mode & S_ISGID) perm[6] = 's';
	if(mode & S_ISVTX) perm[9] = 't';
}

int main(int argc, char *argv[]){
	DIR *dp;
	struct stat statbuf;
	struct dirent *dent;
	char perm[11];
	char pathname[1024];

	if(argc < 2){
		fprintf(stderr, "no directory name is provided");
		exit(1);
	}

	if(access(argv[1], F_OK) == -1){
		perror("access error");
		exit(1);
	}

	if(stat(argv[1], &statbuf) < 0){
		perror("stat error");
		exit(1);
	}

	if(!S_ISDIR(statbuf.st_mode)){
		fprintf(stderr, "%s is not directory\n", argv[1]);
		exit(1);
	}

	if((dp = opendir(argv[1])) == NULL){
		perror("opendir error");
		exit(1);
	}

	printf("List of Directory(%s):\n", argv[1]);
	while((dent = readdir(dp)) != NULL){
		sprintf(pathname, "%s/%s", argv[1], dent->d_name);
		if(stat(pathname, &statbuf) < 0){
			perror("stat error");
			exit(1);
		}

		access_perm(perm, statbuf.st_mode);
		printf("%s %8ld %s\n", perm, statbuf.st_size, dent->d_name);
	}

	closedir(dp);
	exit(0);
}

			
