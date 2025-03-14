#ifndef UTILS_H
#define UTILS_H

#define _XOPEN_SOURCE 700 // Habilita recursos POSIX, incluindo nftw

#include <ftw.h>
#include <unistd.h>

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

extern char *notes_path;

int path_validation(char* path);
char* note_changes(char* category, char* name);
void init_notes_directory();
void init_home_path();
void create_category(const char *category);
const char* get_editor();
void open_editor(const char* filepath);
size_t sizeToNote(char *category, char *name);
int removerf(const char *path, const struct stat *file_info, int item_type, struct FTW *nftw_info);

#endif