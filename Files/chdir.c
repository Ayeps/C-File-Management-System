#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

bool isDirectory(char* path);

int main(int argc, char* argv[])
{
	if (argc == 2){
		if(isDirectory(argv[1]) == true)
		{
			chdir("argv[1]");
			printf("Directory changed successfully , Current Directory %s\n",argv[1]);	
		}
		else
			printf("%s is not a valid directory path\n",argv[1]);
	}
	else
	{
		fprintf(stderr,"Usage: %s /path/to/directory\n",argv[0]);
		exit(EXIT_FAILURE);
	}
    return 0;
}

bool isDirectory(char* path){

	struct stat statbuf;
   	if (stat(path, &statbuf) != 0)
   		return false;
   	return S_ISDIR(statbuf.st_mode);

}
