#ifndef NOTES_H
#define NOTES_H

void new(char* category, char* name);
void edit(char* category, char *name);
void renameDir(char *category_name, char *name, char *newname);
void removeNote(char* category, char* name);
void backlink (char* keyword);

#endif