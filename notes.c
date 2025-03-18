#include "notes.h"
#include "utils.h"
#include "dirutils.h"

// create a new note
void new(char *category, char *name)
{

    // Category can't be null. 
    // Has to have an argument to create a folder.

    if (category == NULL)
    {
        printf("Usage: note new <category> <name>\n");
        return;
    }

    create_category(category);

    // If name is null define a default name.
    if (name == NULL)
    {
        name = "new_note";
    }

    char *filename = pathlloc(category, name);
    if ((path_validation(filename)) == 0)
    {
        printf("File already exists!\n");
        open_editor(filename);
        free(filename);
        return;
    }

    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("ERROR: File creation was not possible\n");
        return;
    }

    fclose(fptr);
    open_editor(filename);
    free(filename);
}

// opens a note to edit
void edit(char* category, char *name)
{
    if (category == NULL)
    {
        open_editor(notes_path);
        return;
    }
   
    char *filename = pathlloc(category, name);
    if ((path_validation(filename)) != 0)
    {
        printf("ERROR: File or directory not found!\n");
        free(filename);
        return;
    }

    open_editor(filename);
    return;
}

void renameDir(char *category_name, char *name, char *newname)
{
    // Edita o nome de um carta
    // talvez seja interessante deixar editar a categoria e as tags

    if (category_name == NULL || name == NULL)  
    {
       printf("Usage: notes rename <category> <old name> <new name>\n.");
       return;
    }

    if (newname == NULL)
    {
         // get the desired folder name       // get the folder names
         char *filepath_name = pathlloc(name, NULL);

        if (path_validation(filepath_name) == 0)
        {
            printf("This directory's name is already being used.\n");
            return;
        }

        // to pathlloc not put .md 
        // we null the second argument

        // get the older name
        char *filepath = pathlloc(category_name, NULL);
        // and renamed it
        if (rename(filepath, filepath_name) != 0)
        {
            printf("Was not possible rename directory.\n");
            return;
        }
        printf("'%s' directory changed to '%s'\n", category_name, name); 

        free(filepath);
        free(filepath_name);
        return;
    }

    // same thing, but here name its going to have
    // an second argument in pathlloc to put .md in filenames
    char *filepath = pathlloc(category_name, name);
    char *filepath_name = pathlloc(category_name, newname);
    if (rename(filepath, filepath_name) != 0)
    {
        printf("Was not possible rename directory.\n");
        return;
    }
    printf("'%s' filenames changed to '%s'\n", name, newname);

    free(filepath);
    free(filepath_name);
    return;
}

void removeNote(char* category, char* name)
{
    if (category == NULL)
    {
        printf("Usage: notes remove <category> <name>");
        return;
    }

    char *dirpath = pathlloc(category, name);

    if ((path_validation(dirpath)) != 0)
    {
        free(dirpath);
        printf("Directory don't exists.\n");
        return;
    }

    if ((confirm_removal(category, name)) != 0)
    {    
        free(dirpath);
        return;
    }
    handle_path(dirpath, category, name);

    free(dirpath);
    return; 
}

void backlink (char* keyword) 
{
    if (keyword == NULL) 
    {
        printf("usage: notes backlink <keyword>");
        return;
    }

    printf("Searching for '%s' in '%s' ... \n", keyword, notes_path);
    searchInDir(notes_path, keyword, 2, 0);

    return;
}