#include "changeExt.h"

int main(int argc, char* argv[]) {

	if(argc != 4){
		fprintf(stderr,"Usage: %s /path/to/file file_name new_extension \n",argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if(chdir(argv[1]) != 0){
		fprintf(stderr,"Invalid path %s \n",argv[1]);
		exit(EXIT_FAILURE);
	}	
	
	if(isFile(argv[2]) == false){
		fprintf(stderr,"Invalid file %s \n",argv[2]);
		exit(EXIT_FAILURE);
	}
	
	char *extension = getExt(argv[2]); 
	char *newExtension = argv[3];
	char *fullfileName = argv[2];

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
	
		
}

char *getExt(char *filename) {
	
	char *dot = strrchr(filename, '.');
	if(!dot || dot == filename) 
		return "";
    	return dot + 1;

}


bool isFile(char* path) {

	struct stat sb;
    	stat(path, &sb);
    	if(S_ISREG(sb.st_mode))
		return true;
	else
		return false;

}
