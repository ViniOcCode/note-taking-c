#ifndef UTILS_H
#define UTILS_H

#define _XOPEN_SOURCE 700 

#include <ftw.h>
#include <sys/stat.h>
#include <unistd.h>

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern char *notes_path;

void init_notes_directory();
void init_home_path();
void create_category(char *category);
void open_editor(const char* filepath);

int path_validation(char* path);
int handle_path(char *dirpath, char *category, char * name);
int confirm_removal(char *category, char *name);
int removerf(const char *path, 
            const struct stat *file_info, 
            int item_type,
            struct FTW *nftw_info);

const char* get_editor();
char *pathlloc(char *category, char* name);

size_t sizeCheck(char *category, char *name);

#endif