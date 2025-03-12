#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

void new (char* category, char* name);
void init_notes_directory();
void init_home_path();

char *notes_path = NULL;

int main(int argc, char *argv[])
{
    if (argc == 1 || argc > 4)
    {
        printf("Usage: cuzinho legal\n");
        return -1;
    }

    init_home_path();
    init_notes_directory();
    // Validações das funções
    New(argv[1], argv[2]);
    return 0;
}

void init_home_path()
{
    const char *home = getenv("HOME");
    if (home == NULL) 
    {
        printf("ERROR: Was not possible to reach %s", home);
        return;
    }

    size_t len = strlen(home) + strlen("/notes") + 1;

    notes_path = malloc(len);
    if (notes_path == NULL)
    {
        printf("ERROR: Failed to check home path");
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
        printf("ERROR: Invalid category");
        return;
    }

    size_t path_len = strlen(notes_path) + strlen(category) + 2;
    char *category_path = malloc(path_len);
    if (category_path == NULL)
    {
        printf("ERROR: Was not possible to reach file");
        return;
    }

    snprintf(category_path, path_len, "%s/%s", notes_path, category);

    struct stat st = {0};
    if (stat(category_path, &st) == -1)
    {
        if (mkdir(category_path, 0777) != 0)
        {
            printf("ERROR: Was not possible to reach file");
        }
    }

    free(category_path);
}
void new(char *category, char *name)
{

    // criar uma nota, com uma categoria obrigatória
    // se não tiver uma categoria não deixe criar

    if (category == NULL)
    {
        printf("Note need a category\n");
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
        printf("ERROR: Failed to create a new note");
        return;
    }

    snprintf(filename, filename_size, "%s/%s/%s.md", notes_path, category, name);

    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("Criação de arquivo não deu certo");
        free(filename);
        return;
    }
    fclose(fptr);

    free(filename);
    // se tiver tag colocar as tags
    // se não tiver tags deixe um branco.
}

void edit(char *name)
{

    // Edita o nome de um carta
    // talvez seja interessante deixar editar a categoria e as tags

    return;
}

void remove (char* name) {
    
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