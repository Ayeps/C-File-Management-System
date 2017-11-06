#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

bool isFile(char* path);

int main(int argc, char* argv[]){
	
	if(argc < 4 || argc > 5){
		fprintf(stderr,"Usage: %s /path/to/file file.name /where/to/copy(optional) nameOf.copy\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	chdir(argv[1]);
	if(isFile(argv[2]) == false){
		fprintf(stderr,"Invalid file %s\n",argv[2]);
		exit(EXIT_FAILURE);
	}

	char ch;
	FILE *f1, *f2;
	f1 = fopen(argv[2],"r");
	if(argc == 4){
		f2 = fopen(argv[3],"w");
	}
	else{
		chdir(argv[3]);
		f2 = fopen(argv[4],"w");
	}

	while(1){

		ch = fgetc(f1);
		if(ch == EOF)
			break;
		else
			putc(ch,f2);
	
	}
	
	printf("File copied Successfully\n");
	fclose(f1);
	fclose(f2);

}

bool isFile(char* path){

	struct stat path_stat;
    	stat(path, &path_stat);
    	if(S_ISREG(path_stat.st_mode))
		return true;
	else
		return false;

}

