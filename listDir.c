#include "listDir.h"

static unsigned int total = 0;

int main(int argc, char* argv[]){

	if(argc < 2 || argc > 3){
		fprintf(stderr,"Usage: %s /path/to/directory -s(optional with sizes)\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else if(argc == 2)
		listDirs(argv[1]);
	else if(argc == 3 && strcmp(argv[2],"-s") == 0)
		listDirsWithSizes(argv[1]);
	else{
		fprintf(stderr,"Unknown flag %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}	

}

bool isDirectory(char* path){

	struct stat statbuf;
   	if (stat(path, &statbuf) != 0)
   		return false;
   	return S_ISDIR(statbuf.st_mode);

}

void listDirs(const char* path){

	DIR *d;
  	struct dirent *dir;
  	d = opendir(path);
	chdir(path);
  	if (d){
    		while ((dir = readdir(d)) != NULL){
			if(!strcmp(dir->d_name,".") || !strcmp(dir->d_name,"..") || isDirectory(dir->d_name) == false){}
			else{
				printf("%s\n",dir->d_name);
			}    		
		}

   	closedir(d);
  	}		

}

void listDirsWithSizes(const char* path){

	DIR *d;
  	struct dirent *dir;
  	d = opendir(path);
	chdir(path);
  	if (d){
    		while ((dir = readdir(d)) != NULL){
			if(!strcmp(dir->d_name,".") || !strcmp(dir->d_name,"..") || isDirectory(dir->d_name) == false){}
			else{
				total = 0;
				if(ftw(dir->d_name, &sum, 1)){
					perror("ftw");
				}
      				printf("%s is %u bytes length.\n", dir->d_name,total);
			}    		
		}

   	closedir(d);
  	}		

}

int sum(const char *fpath, const struct stat *sb, int typeflag) {

    total += sb->st_size;
    return 0;

}
