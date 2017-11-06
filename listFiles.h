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
void listFiles(const char* path);
void listFilesWithSizes(const char* path);

