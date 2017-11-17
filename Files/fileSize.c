#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

unsigned int fsize(char *name);

int main(int argc,char* argv[]){

	if(argc == 2){
		unsigned int size = fsize(argv[1]);
		printf("Size of %s is %u bytes.\n",argv[1],size);
	}
	else{
		fprintf(stderr,"Usage: %s /path/to/file\n",argv[0]);
		exit(EXIT_FAILURE);
	}
}

unsigned int fsize(char *name){

	struct stat sb;
	if(stat(name,&sb) != 0 || !S_ISREG(sb.st_mode)){
		fprintf(stderr,"%s is not a file.\n",name);
		exit(EXIT_FAILURE);
	}
	return sb.st_size;

}
