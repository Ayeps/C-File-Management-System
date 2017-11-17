#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


// prototype functions

bool isFile(char* path);
char* getExt(char *filename);
unsigned int fsize(char *name);
void listFiles(const char* path);
void listFilesWithSizes(const char* path);
void listHiddenFiles(const char* path);
void listHiddenFilesWithSizes(const char* path);
void listFilteredFiles(const char* path,char ext[5]);
void listFilteredFilesWithSizes(const char* path,char ext[5]);
void listSearchedFiles(const char* path, char* word);
void maxSizeFile(const char* path);
void minSizeFile(const char* path);
bool isDirectory(char* path);
void listDirs(const char* path);
void listDirsWithSizes(const char* path);
int sum(const char *fpath, const struct stat *sb, int typeflag);

int main(int argc, char* argv[]){
	
	// printf("argv[1] = %s\n",argv[1]);

	if (strcmp (argv[1],"copy") == 0)
	{
		if(argc < 5 || argc > 6){
			fprintf(stderr,"Usage: %s copy /path/to/file file.name /where/to/copy(optional) nameOf.copy\n",argv[0]);
			exit(EXIT_FAILURE);
		}

		chdir(argv[2]);
		if(isFile(argv[3]) == false){
			fprintf(stderr,"Invalid file %s\n",argv[3]);
			exit(EXIT_FAILURE);
		}

		char ch;
		FILE *f1, *f2;
		f1 = fopen(argv[3],"r");
		if(argc == 5){
			f2 = fopen(argv[4],"w");
		}
		else{
			chdir(argv[4]);
			f2 = fopen(argv[5],"w");
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

	} // end of copy function


	else if(strcmp(argv[1], "rename")==0)
	{
		if(argc != 5){
		fprintf(stderr,"Usage: %s rename /path/to/file file.name new.name\n",argv[0]);
		exit(EXIT_FAILURE);
		}

		chdir(argv[2]);

		if(isFile(argv[3]) == false){
			fprintf(stderr,"Invalid file %s\n",argv[3]);
			exit(EXIT_FAILURE);
		}

		if(rename(argv[3], argv[4]) == 0){
			printf("%s has been renamed to %s.\n", argv[3], argv[4]);
		}
		else{
			fprintf(stderr, "Error renaming %s.\n", argv[3]);
		}
	} // end of rename function


	else if(strcmp(argv[1], "changeExt")==0)
	{
		if(argc != 5){
		fprintf(stderr,"Usage: %s changeExt /path/to/file file_name new_extension \n",argv[0]);
		exit(EXIT_FAILURE);
		}
	
		if(chdir(argv[2]) != 0){
			fprintf(stderr,"Invalid path %s \n",argv[2]);
			exit(EXIT_FAILURE);
		}	
	
		if(isFile(argv[3]) == false){
			fprintf(stderr,"Invalid file %s \n",argv[3]);
			exit(EXIT_FAILURE);
		}
	
		char *extension = getExt(argv[3]);
		char *newExtension = argv[4];
		char *fullfileName = argv[3];

		int extensionLen = strlen(extension);
		int fullfileLen = strlen(fullfileName);
		int nameLen = fullfileLen - extensionLen - 1;

		char with_ext[30];
		char without_ext[30];

		strcpy(with_ext,fullfileName);
		strncpy(without_ext,with_ext,nameLen);
		strcat(without_ext,".");
		strcat(without_ext,newExtension);	

		char *without_ext_p = malloc(30*sizeof(char));

		if(without_ext_p == NULL)
			exit(EXIT_FAILURE);

		without_ext_p = without_ext;

		if(rename(fullfileName,without_ext_p)==0){
			printf("Extension changed successfully.\n");
			exit(EXIT_SUCCESS);
		}
	} // end of change extension function


	else if(strcmp(argv[1], "fileSize")==0)
	{
		if(argc == 3){
			unsigned int size = fsize(argv[2]);
			printf("Size of %s is %u bytes.\n",argv[2],size);
		}
		else{
			fprintf(stderr,"Usage: %s fileSize /path/to/file\n",argv[0]);
			exit(EXIT_FAILURE);
		}
	} // end of fileSize function


	else if(strcmp(argv[1], "displayContent")==0)
	{
			if (argc != 3){
			fprintf(stderr,"Usage: %s displayContent /path/to/file \n",argv[0]);
			exit(EXIT_FAILURE);
		}

		if(isFile(argv[2])==false){
			fprintf(stderr,"Invalid file %s. \n",argv[2]);
			exit(EXIT_FAILURE);
		}

		FILE *fptr = fopen(argv[2],"r");
		char ch;	

		while(1){

			ch = fgetc(fptr);
			if(ch == EOF)
				break;
			else
				printf("%c",ch);
		}
	} // end of display Content function


	else if(strcmp(argv[1], "isFile")==0)
	{
		if(argc == 3){
		if(isFile(argv[2]) == true)
			printf("It is a file.\n");
		else
			printf("It is not a file.\n");
		}
		else{
			fprintf(stderr,"Usage: %s isFile /path/to/file\n",argv[0]);
			exit(EXIT_FAILURE);
		}
	} // end of isFile function


	else if(strcmp(argv[1], "listFiles")==0)
	{
		if(argc < 3 || argc > 4){
		fprintf(stderr,"Usage: %s listFiles /path/to/directory -s(optional with sizes)\n", argv[0]);
		exit(EXIT_FAILURE);
		}
		else if(argc == 3)
			listFiles(argv[2]);
		else if(argc == 4 && strcmp(argv[3],"-s") == 0)
			listFilesWithSizes(argv[2]);
		else{
			fprintf(stderr,"Unknown flag %s\n", argv[3]);
			exit(EXIT_FAILURE);
		}	
	} // end of list Files function
	
	
	else if(strcmp(argv[1], "listHiddenFiles")==0)
	{
		if(argc < 3 || argc > 4){
		fprintf(stderr,"Usage: %s listHiddenFiles /path/to/directory -s(optional with sizes)\n", argv[0]);
		exit(EXIT_FAILURE);
		}
		else if(argc == 3)
			listHiddenFiles(argv[2]);
		else if(argc == 4 && strcmp(argv[3],"-s") == 0)
			listHiddenFilesWithSizes(argv[2]);
		else{
			fprintf(stderr,"Unknown flag %s\n", argv[3]);
			exit(EXIT_FAILURE);
		}
	} // end of List Hidden Files function
	
	
	else if(strcmp(argv[1], "filterFiles")==0)
	{
		if(argc < 4 || argc > 5){
		fprintf(stderr,"Usage: %s filterFiles /path/to/directory keyword -s(optional with sizes)\n", argv[0]);
		exit(EXIT_FAILURE);
		}
		else if(argc == 4)
			listFilteredFiles(argv[2],argv[3]);
		else if(argc == 5 && strcmp(argv[4],"-s") == 0)
			listFilteredFilesWithSizes(argv[2],argv[3]);
		else{
			fprintf(stderr,"Unknown flag %s\n", argv[3]);
			exit(EXIT_FAILURE);
		}
	} // end of Filter Files function

	
	else if(strcmp(argv[1], "searchFile")==0)	
	{
		if(argc != 4){
		fprintf(stderr,"Usage: %s searchFile /path/to/file word_to_search\n", argv[0]);
		exit(EXIT_FAILURE);
		}
		listSearchedFiles(argv[2],argv[3]);
		
	} //end of search Files function
	
	
	else if(strcmp(argv[1], "largestFile")==0)	
	{
		if(argc < 3 || argc >4){
		fprintf(stderr,"Usage: %s largestFile /path/to/directory -i(for minimum size)\n", argv[0]);
		exit(EXIT_FAILURE);
		}
		else if(argc == 3)
			maxSizeFile(argv[2]);
		else if(argc == 4 && strcmp(argv[3],"-i") == 0)
			minSizeFile(argv[2]);
		else{
			fprintf(stderr,"Unknown flag %s\n", argv[2]);
			exit(EXIT_FAILURE);
		}	
	} //end of largest file function
	
	
	else if(strcmp(argv[1], "removeFile")==0)	
	{
		if(argc != 4){
		fprintf(stderr,"Usage: %s removeFile /path/to/file file_name\n",argv[0]);
		exit(EXIT_FAILURE);
		}

		chdir(argv[2]);
		if(isFile(argv[3]) == false){
			fprintf(stderr,"Invalid file %s\n",argv[3]);
			exit(EXIT_FAILURE);
		}

		if (remove(argv[3]) == 0){
			printf("%s removed successfully\n",argv[3]);
			exit(EXIT_SUCCESS);
		}
		else{
			printf("Failure removig %s\n",argv[3]);
			exit(EXIT_FAILURE);
		}
	} //end of remove file function
	
	
	else if(strcmp(argv[1], "isDir")==0)	
	{
		if (argc == 3){

		if(isDirectory(argv[2]) == true)
			printf("%s is a directory\n",argv[2]);	
		else
			printf("%s is not a directory\n",argv[2]);
		}
		else{
			fprintf(stderr,"Usage: %s isDir /path/to/directory\n",argv[0]);
			exit(EXIT_FAILURE);

		}
	} //end of isDirectory function
	
	
	else if(strcmp(argv[1], "makeDir")==0)	
	{
		if (argc == 3){
		if(isDirectory(argv[2]) == true)
		{
			printf("Directory already exists\n");	
		}
		else
		{
			mkdir(argv[2], 0777);
			printf("Directory successfully created !\n");
		}
		}
		else
		{
			fprintf(stderr,"Usage: %s makeDir /path/to/directory\n",argv[0]);
			exit(EXIT_FAILURE);
		}
	} //end of makeDirectory function
	
	
	else if(strcmp(argv[1], "changeDir")==0)	
	{
		if (argc == 3){
		if(isDirectory(argv[2]) == true)
		{
			chdir("argv[2]");
			printf("Directory changed successfully , Current Directory %s\n",argv[2]);	
		}
		else
			printf("%s is not a valid directory path\n",argv[2]);
		}
		else
		{
			fprintf(stderr,"Usage: %s changeDir /path/to/directory\n",argv[0]);
			exit(EXIT_FAILURE);
		}
	} // eof change Directory function
	
	
	else if(strcmp(argv[1], "listDir")==0)	
	{
		if(argc < 3 || argc > 4){
		fprintf(stderr,"Usage: %s listDir /path/to/directory -s(optional with sizes)\n", argv[0]);
		exit(EXIT_FAILURE);
		}
		else if(argc == 3)
			listDirs(argv[2]);
		else if(argc == 4 && strcmp(argv[3],"-s") == 0)
			listDirsWithSizes(argv[2]);
		else{
			fprintf(stderr,"Unknown flag %s\n", argv[3]);
			exit(EXIT_FAILURE);
		}	
	} // eof list Directory function
}

bool isFile(char* path){

	struct stat path_stat;
    	stat(path, &path_stat);
    	if(S_ISREG(path_stat.st_mode))
		return true;
	else
		return false;
}

char *getExt(char *filename) {
	
	char *dot = strrchr(filename, '.');
	if(!dot || dot == filename) 
		return "";
    	return dot + 1;
}

unsigned int fsize(char *name){

	struct stat sb;
	if(stat(name,&sb) != 0 || !S_ISREG(sb.st_mode)){
		fprintf(stderr,"%s is not a file.\n",name);
		exit(EXIT_FAILURE);
	}
	return sb.st_size;
}

void listFiles(const char* path){

	DIR *d;
  	struct dirent *dir;
  	d = opendir(path);
	chdir(path);
  	if (d){
    		while ((dir = readdir(d)) != NULL){
			if(!strcmp(dir->d_name,".") || !strcmp(dir->d_name,"..") || isFile(dir->d_name) == false){}
			else{
				printf("%s\n",dir->d_name);
			}    		
		}
   	closedir(d);
  	}		
}

void listFilesWithSizes(const char* path){
	DIR *d;
  	struct dirent *dir;
  	d = opendir(path);
	int fileSize;
	chdir(path);
  	if (d){
    		while ((dir = readdir(d)) != NULL){
			if(!strcmp(dir->d_name,".") || !strcmp(dir->d_name,"..") || isFile(dir->d_name) == false){}
			else{
				fileSize = fsize(dir->d_name);
      				printf("%s file is %u bytes length.\n", dir->d_name,fileSize);
			}    		
		}

   	closedir(d);
  	}		
}
void listHiddenFiles(const char* path){

	DIR *d;
  	struct dirent *dir;
  	d = opendir(path);
	chdir(path);
  	if (d){
    		while ((dir = readdir(d)) != NULL){
			if(dir->d_name[0] == '.' && strcmp(dir->d_name,".") != 0 && strcmp(dir->d_name,"..") != 0 && 
			isFile(dir->d_name)==true){
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

void listSearchedFiles(const char* path, char* word){

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
  	int total;
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
    int total;
    total += sb->st_size;
    return 0;

}
