#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "notes.h"
#include "utils.h"

void new(char *category, char *name)
{

    // criar uma nota, com uma categoria obrigatória
    // se não tiver uma categoria não deixe criar

    if (category == NULL)
    {
        printf("Usage: note new <category> <name>\n");
        return;
    }

    create_category(category);

    // se tiver nome colocar o nome desejado
    // se não tiver um nome, colocar um nome genérico

    char *default_name = "new_note";
    name = (name != NULL) ? name : default_name;

    size_t filename_size = strlen(notes_path) + strlen(category) + strlen(name) + 6;
    char *filename = malloc(filename_size);

    if (filename == NULL)
    {
        printf("ERROR: Failed to create a new note\n");
        return;
    }

    snprintf(filename, filename_size, "%s/%s/%s.md", notes_path, category, name);

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
        fclose(fptr);
        free(filename);
        return;
    }
    fclose(fptr);

    open_editor(filename);

    free(filename);
    // se tiver tag colocar as tags
    // se não tiver tags deixe um branco.
}

void edit(char* category, char *name)
{
   if (category == NULL)
   {
        printf("Usage: note edit <category> <name>\n");
        return;
   }
   
    if (path_validation(category) != 0)
    {
        printf("This directory doenst exist!\n");
        return;
    }

    size_t filename_size = strlen(notes_path) + strlen(category) + strlen(name) + 6;
    char *filename = malloc(filename_size);

    if (filename == NULL)
    {
        printf("ERROR: Failed to edit the note\n");
        return;
    }

    snprintf(filename, filename_size, "%s/%s/%s.md", notes_path, category, name);

    if ((path_validation(filename)) != 0)
    {
        printf("ERROR: File not found!\n");
        free(filename);
        return;
    }

    open_editor(filename)

    // Edita o nome de um carta
    // talvez seja interessante deixar editar a categoria e as tags

    return;
}

void rename()
{
    
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