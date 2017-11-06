#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>

bool isFile(char* path);
void listFiles(const char* path,char ext[5]);
void listFilesWithSizes(const char* path,char ext[5]);
unsigned int fsize(char* name);

