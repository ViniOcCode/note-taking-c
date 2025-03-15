
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "notes.h"
#include "utils.h"

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
    else if (strcmp(argv[1], "remove") == 0)
    {
        removeNote(argv[2],argv[3]);
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