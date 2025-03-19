#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

extern char *notes_path;

int init_notes_directory();
int init_home_path();
void create_category(char *category);
void open_editor(const char* filepath);

int path_validation(char* path);
int confirm_removal(char *category, char *name);

const char* get_editor();
char *pathlloc(char *category, char* name);

size_t sizeCheck(char *category, char *name);

#endif