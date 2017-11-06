#include "search.h"


int main(int argc, char* argv[]){

	if(argc != 3){
		fprintf(stderr,"Usage: %s /path/to/file word_to_search\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	listFiles(argv[1],argv[2]);
		
}

bool isFile(char* path){

	struct stat sb;
    	stat(path, &sb);
    	if(S_ISREG(sb.st_mode))
		return true;
	else
		return false;

}

void listFiles(const char* path, char* word){

	DIR *d;
	char temp[512];
	FILE *fp;
  	struct dirent *dir;
  	d = opendir(path);
	chdir(path);
  	if (d){
    		while ((dir = readdir(d)) != NULL){
			if(!strcmp(dir->d_name,".") || !strcmp(dir->d_name,"..") || isFile(dir->d_name) == false){}
			else{
				fp = fopen(dir->d_name, "r");

				while(fgets(temp, 512, fp) != NULL) {
					if((strstr(temp, word)) != NULL) {
						printf("In file %s occurs in line: %s \n",dir->d_name,temp);
						
					} 
				}
				fclose(fp);	
			}    		
		}
   	closedir(d);
  	}		

}

