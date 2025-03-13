#ifndef UTILS_H
#define UTILS_H

extern char *notes_path;

int path_validation(char* path);
char* note_changes(char* category, char* name);
void init_notes_directory();
void init_home_path();
void create_category(const char *category);
const char* get_editor();
void open_editor(const char* filepath);

#endif