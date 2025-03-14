#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

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

    size_t size = sizeToNote(category, name) + 1;
    char *filename = malloc(size);
    if (filename == NULL)
    {
        printf("ERROR: Failed to create a new note\n");
        return;
    }
    snprintf(filename, size + 1, "%s/%s/%s.md", notes_path, category, name);

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
    // se tiver tag colocar as tags
    // se não tiver tags deixe um branco.
}

// opens a note to edit
void edit(char* category, char *name)
{
    if (category == NULL)
    {
        printf("Usage: note edit <category> <name>\n");
        return;
    }
   
    size_t size = sizeToNote(category, name) + 1;
    char *filename = malloc(size);
    if (filename == NULL)
    {
        printf("ERROR: Failed to edit the note\n");
        return;
    }
    snprintf(filename, size + 1, "%s/%s/%s.md", notes_path, category, name);

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

void removeNote (char* name) {
    
    // deleta a carta desejada
    // talvez possa deletar alguma tag ou alguma categoria

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