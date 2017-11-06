#include "isDirectory.h"

int main(int argc, char* argv[]){

	if (argc == 2){

		if(isDirectory(argv[1]) == true)
			printf("It is directory\n");
		else
			printf("It is not directory\n");

	}
	else{

		fprintf(stderr,"Usage: %s /path/to/directory\n",argv[0]);
		exit(EXIT_FAILURE);

	}

}

bool isDirectory(char* path){

	struct stat statbuf;
   	if (stat(path, &statbuf) != 0)
   		return false;
   	return S_ISDIR(statbuf.st_mode);

}
