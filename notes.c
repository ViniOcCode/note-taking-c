#include "notes.h"
#include "utils.h"

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

    printf("chegue aqui");
    char *filename = pathlloc(category, name);
    printf("%s", filename);

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
        free(filename);
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
        printf("Usage: note edit <category> <name>\n");
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

void renameDir()
{
    // Edita o nome de um carta
    // talvez seja interessante deixar editar a categoria e as tags

    return;
}

void removeNote(char* category, char* name)
{
    if (category == NULL)
    {
        printf("Category cant be null.\n");
        return;
    }

    if ((confirm_removal(category, name)) != 0)
        return;

    char *dirpath = pathlloc(category, name);
    handle_path(dirpath, category, name);

    free(dirpath);
    return; 
}

void backlink (char* keyword) {
    
    // verifica por uma keyword em todas as notas

    return;
}

void oneline (void) {

    // ls com oneline, vai mostrar todas as categorias e notas

    return;
}

void full (void) {

    // ls com full, vai mostrar todas as categorias e notas com preview de 5 linhas

    return;
}