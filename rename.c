#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

bool isFile(char* path);

int main(int argc, char* argv[]){

	if(argc != 4){
		fprintf(stderr,"Usage: %s /path/to/file file.name new.name\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	chdir(argv[1]);

	if(isFile(argv[2]) == false){
		fprintf(stderr,"Invalid file %s\n",argv[2]);
		exit(EXIT_FAILURE);
	}

	if(rename(argv[2], argv[3]) == 0){
		printf("%s has been renamed to %s.\n", argv[2], argv[3]);
	}
	else{
		fprintf(stderr, "Error renaming %s.\n", argv[2]);
	}
	

}


bool isFile(char* path){

	struct stat path_stat;
    	stat(path, &path_stat);
    	if(S_ISREG(path_stat.st_mode))
		return true;
	else
		return false;

}


