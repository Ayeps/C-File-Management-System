#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>


bool isFile(const char* path);

int main(int argc, char* argv[]){

	if(argc != 3){
		fprintf(stderr,"Usage: %s /path/to/file file.name\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	chdir(argv[1]);
	if(isFile(argv[2]) == false){
		fprintf(stderr,"Invalid file %s\n",argv[2]);
		exit(EXIT_FAILURE);
	}

	if (remove(argv[2]) == 0){
		printf("%s removed successfully\n",argv[2]);
		exit(EXIT_SUCCESS);
	}
	else{
		printf("Failure removig %s\n",argv[2]);
		exit(EXIT_FAILURE);
	}

}

bool isFile(const char* path){
	
	struct stat st;
	stat(path,&st);
	if(S_ISREG(st.st_mode))
		return true;
	else
		return false;

}
