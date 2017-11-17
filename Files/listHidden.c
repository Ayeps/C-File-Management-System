#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>

unsigned int fsize(char *name);
bool isFile(char* path);
void listHiddenFiles(const char* path);
void listHiddenFilesWithSizes(const char* path);

int main(int argc,char* argv[]){

	if(argc < 2 || argc > 3){
		fprintf(stderr,"Usage: %s /path/to/directory -s(optional with sizes)\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else if(argc == 2)
		listHiddenFiles(argv[1]);
	else if(argc == 3 && strcmp(argv[2],"-s") == 0)
		listHiddenFilesWithSizes(argv[1]);
	else{
		fprintf(stderr,"Unknown flag %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

}

unsigned int fsize(char *name){

	struct stat sb;
	if(stat(name,&sb) != 0 || !S_ISREG(sb.st_mode)){}
	else
		return sb.st_size;

}

bool isFile(char* path){

	struct stat sb;
    	stat(path, &sb);
    	if(S_ISREG(sb.st_mode))
		return true;
	else
		return false;

}

void listHiddenFiles(const char* path){

	DIR *d;
  	struct dirent *dir;
  	d = opendir(path);
	chdir(path);
  	if (d){
    		while ((dir = readdir(d)) != NULL){
			if(dir->d_name[0] == '.' && strcmp(dir->d_name,".") != 0 && strcmp(dir->d_name,"..") != 0 && isFile(dir->d_name)==true){
				printf("%s\n",dir->d_name);
			}    		
		}

   	closedir(d);
  	}		

}

void listHiddenFilesWithSizes(const char* path){

	DIR *d;
  	struct dirent *dir;
  	d = opendir(path);
	int fileSize;
	chdir(path);
  	if (d){
    		while ((dir = readdir(d)) != NULL){
			if(dir->d_name[0] == '.' && strcmp(dir->d_name,".") != 0 && strcmp(dir->d_name,"..") != 0 && isFile(dir->d_name)==true){
				fileSize = fsize(dir->d_name);
      				printf("%s file is %u bytes length.\n", dir->d_name,fileSize);
			}    		
		}

   	closedir(d);
  	}		

}
