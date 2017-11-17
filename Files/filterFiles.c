#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>

bool isFile(char* path);
void listFilteredFiles(const char* path,char ext[5]);
void listFilteredFilesWithSizes(const char* path,char ext[5]);
unsigned int fsize(char* name);

int main(int argc, char* argv[]){

	if(argc < 3 || argc > 4){
		fprintf(stderr,"Usage: %s /path/to/directory keyword -s(optional with sizes)\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else if(argc == 3)
		listFilteredFiles(argv[1],argv[2]);
	else if(argc == 4 && strcmp(argv[3],"-s") == 0)
		listFilteredFilesWithSizes(argv[1],argv[2]);
	else{
		fprintf(stderr,"Unknown flag %s\n", argv[3]);
		exit(EXIT_FAILURE);
	}
	
}

void listFilteredFiles(const char* path, char ext[5]){

	DIR *d;
  	struct dirent *dir;
  	d = opendir(path);
	chdir(path);
  	if (d){
    		while ((dir = readdir(d)) != NULL){
			if(strstr(dir->d_name,ext) != 0)
				printf("%s\n",dir->d_name);	
		}

   	closedir(d);
  	}		

}

void listFilteredFilesWithSizes(const char* path, char ext[5]){

	DIR *d;
  	struct dirent *dir;
  	d = opendir(path);
	int fileSize;
	chdir(path);
  	if (d){
    		while ((dir = readdir(d)) != NULL){
			if(strstr(dir->d_name,ext) != 0){
				fileSize = fsize(dir->d_name);
      				printf("%s file is %u bytes length.\n", dir->d_name,fileSize);
			}    		
		}

   	closedir(d);
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

unsigned int fsize(char *name){

	struct stat sb;
	if(stat(name,&sb) != 0 || !S_ISREG(sb.st_mode)){}
	else
		return sb.st_size;

}
