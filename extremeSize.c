#include "extremeSize.h"

int main(int argc, char* argv[]){

	if(argc < 2 || argc >3){
		fprintf(stderr,"Usage: %s /path/to/directory -i(for minimum size)\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else if(argc == 2)
		maxSizeFile(argv[1]);
	else if(argc == 3 && strcmp(argv[2],"-i") == 0)
		minSizeFile(argv[1]);
	else{
		fprintf(stderr,"Unknown flag %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

}

void maxSizeFile(const char* path){

	DIR *d;
  	struct dirent *dir;
  	d = opendir(path);
	int max = -1, i = 0, fileSize;
	char *largest;
	chdir(path);
  	if (d){
    		while ((dir = readdir(d)) != NULL){
			if(!strcmp(dir->d_name,".") || !strcmp(dir->d_name,"..") || isFile(dir->d_name) == false){}
			else{
				fileSize = fsize(dir->d_name);
				if(fileSize>max){
					max = fileSize;
					largest = dir->d_name;
				}
			}    		
		}

   	closedir(d);
  	}

	printf("File %s is the file with largest length %d bytes.\n",largest,max);

}

void minSizeFile(const char* path){

	DIR *d;
  	struct dirent *dir;
  	d = opendir(path);
	int array_of_sizes[100];
	array_of_sizes[0] = 999999999;
	int min = array_of_sizes[0], i = 0, fileSize;
	char *lowest;
	chdir(path);
  	if (d){
    		while ((dir = readdir(d)) != NULL){
			if(strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0 || isFile(dir->d_name) == false){}
			else{
				fileSize = fsize(dir->d_name);
				array_of_sizes[i] = fileSize;
				if(fileSize <= min){
					min = fileSize;
					lowest = dir->d_name;
				}
			}    		
		}

   	closedir(d);
  	}

	printf("File %s is the file with lowest length %d bytes.\n",lowest,min);

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
