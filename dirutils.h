#ifndef DIRUTILS_H
#define DIRUTILS_H
#define _XOPEN_SOURCE 700 

#include <ftw.h>
#include <sys/stat.h>
#include <unistd.h>

int handle_path(char *dirpath, char *category, char * name);
int removerf(const char *path, 
            const struct stat *file_info, 
            int item_type,
            struct FTW *nftw_info);

#endif