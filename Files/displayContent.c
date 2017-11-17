#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>

bool isFile(char* path);

int main(int argc, char* argv[]){
	
	if (argc!=2){
		fprintf(stderr,"Usage: %s /path/to/file \n",argv[0]);
		exit(EXIT_FAILURE);
	}

	if(isFile(argv[1])==false){
		fprintf(stderr,"Invalid file %s. \n",argv[1]);
		exit(EXIT_FAILURE);
	}

	FILE *fptr = fopen(argv[1],"r");
	char ch;	

	while(1){

		ch = fgetc(fptr);
		if(ch == EOF)
			break;
		else
			printf("%c",ch);
	
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
