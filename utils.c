#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "utils.h"

char *notes_path = NULL;

size_t sizeToNote(char *category, char *name)
{
    if (category == NULL)
    {
        printf("ERROR: NULL category");
        return 0;
    }

    size_t sizeToNote = snprintf(NULL, 0, "%s/%s/%s.md", notes_path, category, name);

    return sizeToNote;
}
int path_validation(char* path)
{
    if (path == NULL)
    {
        printf("No path was given\n");
        return -1;
    }

    size_t size = strlen(path) + 1;
    char *dir = malloc(size);

    if (dir == NULL)
    {
        printf("Was not possible reach a path\n");
        free(dir);
        return -1;
    }

    snprintf(dir, size, "%s", path);
    
    struct stat st = {0};
    // If directory does not exist.
    if (stat(dir, &st) == -1) 
    {
        free(dir);
        // return -1
        return -1; 
    }

    free(dir);

    return 0;
}

void init_home_path()
{
    const char *home = getenv("HOME");
    if (home == NULL) 
    {
        printf("ERROR: Was not possible to reach %s\n", home);
        return;
    }

    size_t len = strlen(home) + strlen("/notes") + 1;

    notes_path = malloc(len);
    if (notes_path == NULL)
    {
        printf("ERROR: Failed to check home path\n");
        free(notes_path);
        return;
    }
    snprintf(notes_path, len,"%s/notes", home);
}

void init_notes_directory()
{
   if (path_validation(notes_path) != 0) 
   {
        if (mkdir(notes_path, 0777) != 0)
        {
           printf("ERROR: Was not possible reach notes directory\n");
        }
   }
}

void create_category(const char *category)
{
    size_t path_len = snprintf(NULL, 0, "%s/%s", notes_path, category);
    char *category_path = malloc(path_len);
    if (category_path == NULL)
    {
        printf("ERROR: Was not possible to reach file\n");
        free(category_path);
        return;
    }
    snprintf(category_path, path_len + 1, "%s/%s", notes_path, category);

    // If folder already exists just return.
    if (path_validation(category_path) == 0)
    {
        free(category_path);
        return;
    }

    if (mkdir(category_path, 0777) != 0)
    {
        printf("ERROR: Was not possible to reach file\n");
    }

    free(category_path);
}

char* note_changes(char* category, char* name)
{

    if (category == NULL || name == NULL)
    {
        printf("Path invalid\n");
    }

    size_t size = sizeToNote(category, name);
    char *filename = malloc(size + 1);

    if (filename == NULL)
    {
        printf("ERROR: Failed to create a new note\n");
        return NULL;
    }

    snprintf(filename, size + 1, "%s/%s/%s.md", notes_path, category, name);

    return filename;
}

const char* get_editor()
{
    if (getenv("EDITOR") == NULL && getenv("VISUAL") == NULL)
    {
        return "vim";
    }
    
    if (getenv("EDITOR") == NULL)
    {
        return getenv("VISUAL");
    }

    return getenv("EDITOR");
}

void open_editor(const char* filepath)
{
    size_t command_size =  snprintf(NULL, 0,"%s %s", get_editor(), filepath);
    char *command = malloc(command_size);

    snprintf(command, command_size,"%s %s", get_editor(), filepath);

    if (system(command) != 0)
    {
        printf("womp womp\n");
    }

}