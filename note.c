#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int path_validation(char* path);
char* note_changes(char* category, char* name);
void new (char* category, char* name);
void edit(char* category, char *name);
void init_notes_directory();
void init_home_path();

char *notes_path = NULL;

int main(int argc, char *argv[])
{
    if (argc == 1 || argc > 4)
    {
        printf("Usage: Notes\n"
            "[new <category> <name>]\n"
            "[edit <category> <name>]\n"
            "[remove <category> <name>]\n"
            "[ls --oneline]\n"
            "[ls --full]\n");
        return -1;
    }

    init_home_path();
    init_notes_directory();

    // Validações das funções
    if (strcmp(argv[1], "new") == 0)
    {
        new(argv[2],argv[3]);
    }
    else if (strcmp(argv[1], "edit") == 0)
    {
        edit(argv[2],argv[3]);
    }
    else 
    { 
    printf("Usage: Notes\n"
    "[new <category> <name>]\n"
    "[edit <category> <name>]\n"
    "[remove <category> <name>]\n"
    "[ls --oneline]\n"
    "[ls --full]\n");
    }

    free(notes_path);
   
    return 0;
}

int path_validation(char* path)
{
    if (path == NULL)
    {
        printf("No path was given\n");
        return -1;
    }

    size_t size = strlen(notes_path) + strlen(path) + 2;
    char *dir = malloc(size);

    if (dir == NULL)
    {
        printf("Was not possible reach a path\n");
        free(dir);
        return -1;
    }

    snprintf(dir, size, "%s/%s", notes_path, path);
    
    struct stat st = {0};
    if (stat(dir, &st) == -1) 
    {
        free(dir);
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
   struct stat st = {0};
   if (stat(notes_path, &st) == -1) 
   {
        if (mkdir(notes_path, 0777) != 0)
        {
           printf("ERROR: Was not possible reach notes directory\n");
        }
   }
}

void create_category(const char *category)
{
    if (category == NULL)
    {
        printf("ERROR: Invalid category\n");
        return;
    }

    size_t path_len = strlen(notes_path) + strlen(category) + 2;
    char *category_path = malloc(path_len);
    if (category_path == NULL)
    {
        printf("ERROR: Was not possible to reach file\n");
        return;
    }

    snprintf(category_path, path_len, "%s/%s", notes_path, category);

    struct stat st = {0};
    if (stat(category_path, &st) == -1)
    {
        if (mkdir(category_path, 0777) != 0)
        {
            printf("ERROR: Was not possible to reach file\n");
        }
    }

    free(category_path);
}

char* note_changes(char* category, char* name)
{

    if (category == NULL || name == NULL)
    {
        printf("Path invalid\n");
    }

    size_t filename_size = strlen(notes_path) + strlen(category) + strlen(name) + 6;
    char *filename = malloc(filename_size);

    if (filename == NULL)
    {
        printf("ERROR: Failed to create a new note\n");
        return NULL;
    }

    snprintf(filename, filename_size, "%s/%s/%s.md", notes_path, category, name);

    return filename;
}

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

    if (path_validation(filename) == 0)
    {
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