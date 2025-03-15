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

int removeNote (char* category, char* name)
{
    char *answer;
    
    if (category == NULL)
    {
        printf("ERROR: Directory not found\n");
        return -1;
    }

    if (name == NULL)
    {
        char *anwser = printf("Do you want remove '%s' directory? y/n\n", category);
        scanf("%c", &anwser);

        if (tolower(anwser) == 'n')
            return -1;
        else if (tolower(anwser) != 's')
            return -1;

        if (strlen(anwser) == 1)
        {
            printf("Only one charcter, please!\n");
            return -1;
        }
        size_t size = sizeCheck(category, name);
        char *dirpath = malloc(size);

        snprintf(dirpath, size, "%s/%s/", notes_path, category);
        
        if (path_validation(dirpath) != 0)
        {
            printf("Directory already doesn't exists!\n");
            free(dirpath);
            return -1;
        }

        if (dirpath == NULL)
        {
            printf("ERROR: Finding file to remove\n");
            free(dirpath);
            return -1;
        }

        if (nftw(dirpath, removerf, 10, FTW_DEPTH) == -1)
        {
            perror("Couldn't pass directory\n");
            free(dirpath);
            return EXIT_FAILURE;
        }

        printf("Directory '%s' removed sucessfully", category);
        free(dirpath);
        return EXIT_SUCCESS;
    }

    size_t size = sizeCheck(category, name);
    char *dirpath = malloc(size);

    snprintf(dirpath, size, "%s/%s/%s.md", notes_path, category, name);

    if (path_validation(dirpath) != 0)
    {
        printf("Directory already doesn't exists!\n");
        free(dirpath);
        return -1;
    }

    if (dirpath == NULL)
    {
        printf("ERROR: Finding file to remove\n");
        free(dirpath);
        return -1;
    }

    if (unlink(dirpath) == 0)
    {
        printf("File '%s' removed sucessfully!\n", name);
        free(dirpath);
        return EXIT_SUCCESS;
    }

    perror("Error removing file\n");
    return EXIT_FAILURE;

    // deleta a carta desejada
    // talvez possa deletar alguma tag ou alguma categoria
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