#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdlib.h>

bool isFile(char* path);

int main(int argc, char *argv[]){
	
	if(argc == 2){

		if(isFile(argv[1]) == true)
			printf("It is file.\n");
		else
			printf("It is not file.\n");

	}
	else{
		
		fprintf(stderr,"Usage: %s /path/to/file\n",argv[0]);
		exit(EXIT_FAILURE);

	}

}

bool isFile(char* path){

	struct stat sb;
    	stat(path, &sb);
    	if(S_ISREG(sb.st_mode))
		return true;
	else
		return false;

}
