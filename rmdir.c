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
			
			printf("Directory already exists\n");	
		}
		else
		{
			rmdir(argv[1], 0777);
			printf("Directory successfully created !\n");
		}
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
