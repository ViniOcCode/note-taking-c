#include "utils.h"

char *notes_path = NULL;

size_t sizeCheck(char *category, char *name)
{
    if (category == NULL)
    {
        printf("ERROR: NULL category\n");
        return 0;
    }
    if (name == NULL || *name == '\0')
    {
        return snprintf(NULL, 0, "%s/%s/", notes_path, category);
    }
    return  snprintf(NULL, 0, "%s/%s/%s.md", notes_path, category, name);
}

char *pathlloc(char *category, char *name)
{
    if (category == NULL) 
    {
        printf("ERROR\n");
        return notes_path;
    }

    size_t size = sizeCheck(category, name);
    char *memlloc = malloc(size + 1);
    if (memlloc == NULL)
    {
        printf("Was not possible to allocate memory\n");
        return notes_path;
    }

    if (name == NULL)
        snprintf(memlloc, size + 1, "%s/%s", notes_path, category);
    else
        snprintf(memlloc, size + 1, "%s/%s/%s.md", notes_path, category, name);

    return memlloc;
}

// This is for checking if a folder or a file is created
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
        return -1; 
    }

    free(dir);

    return 0;
}

int init_home_path()
{
    const char *home = getenv("HOME");
    if (home == NULL) 
    {
        printf("ERROR: Was not possible to reach %s\n", home);
        return -1;
    }

    size_t len = strlen(home) + strlen("/notes") + 1;
    notes_path = malloc(len);
    if (notes_path == NULL)
    {
        printf("ERROR: Failed to check home path\n");
        free(notes_path);
        return -1;
    }
    snprintf(notes_path, len,"%s/notes", home);
    return 0;
}

int init_notes_directory()
{
   if (path_validation(notes_path) != 0) 
   {
        if (mkdir(notes_path, 0777) != 0)
        {
           printf("ERROR: Was not possible reach notes directory\n");
           return -1;
        }
   }
   return 0;
}

void create_category(char *category)
{
    if (category == NULL)
    {
        printf("ERROR: NULL Category\n");
        return;
    }

    char *category_path = pathlloc(category, NULL);
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

const char* get_editor()
{
    // Had to do change this because was
    // actually '\0', and i forgor that
    // and was doing NULL

    const char* editor = getenv("EDITOR");
    const char* visual = getenv("VISUAL");

    if ((editor == NULL || *editor == '\0') && (visual == NULL || *visual == '\0'))
    {
        return "nano";
    }
    if (editor == NULL || *editor == '\0')
    {
        return visual;
    }
    return editor;
}

void open_editor(const char* filepath)
{
    size_t command_size =  snprintf(NULL, 0,"%s \"%s\"", get_editor(), filepath);
    char *command = malloc(command_size + 1);

    snprintf(command, command_size + 1,"%s \"%s\"", get_editor(), filepath);

    if (system(command) != 0)
        printf("Editor was not possible to open.\n");
    

}

int confirm_removal(char *category, char *name)
{
    char response;
    while (1)
    {
        printf("Do you want to remove %s '%s'? y/n\n", name ? "file" : "directory",
                                                       name ? name : category
                                                    );
        response = fgetc(stdin);
        response = tolower(response);

        if (response == 'y') return 0;
        if (response == 'n')
        {
            printf("Operation canceled.\n");
            return -1;
        }
        printf("Invalid input. Please enter 'y' or 'n'.\n\n");
    }
}
