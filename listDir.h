#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ftw.h>

bool isDirectory(char* path);
void listDirs(const char* path);
void listDirsWithSizes(const char* path);
int sum(const char *fpath, const struct stat *sb, int typeflag);

