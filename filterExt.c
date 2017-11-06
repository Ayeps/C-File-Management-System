#include "filterExt.h"

int main(int argc, char* argv[]){

	if(argc < 3 || argc > 4){
		fprintf(stderr,"Usage: %s /path/to/directory extension -s(optional with sizes)\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else if(argc == 3)
		listFiles(argv[1],argv[2]);
	else if(argc == 4 && strcmp(argv[3],"-s") == 0)
		listFilesWithSizes(argv[1],argv[2]);
	else{
		fprintf(stderr,"Unknown flag %s\n", argv[3]);
		exit(EXIT_FAILURE);
	}
	
}

void listFiles(const char* path, char ext[5]){

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

void listFilesWithSizes(const char* path, char ext[5]){

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
