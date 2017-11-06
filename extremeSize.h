#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

bool isFile(char* path);
unsigned int fsize(char *name);
void maxSizeFile(const char* path);
void minSizeFile(const char* path);
