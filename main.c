
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "notes.h"
#include "utils.h"
#include "dirutils.h"

void print_usage();
int check_args(int argc, int expected, const char *command);

int main(int argc, char *argv[])
{
    if (argv[0] != NULL && argc == 1)
    {
        print_usage();
        return -1;
    }

    if (init_home_path() != 0 || init_notes_directory() != 0)
    {
        fprintf(stderr, "Error: Failed to initialize paths or directories.\n");
        return -1;
    }
    // Validações das funções

    // Processa comandos
    if (strcmp(argv[1], "new") == 0)
    {
        if (check_args(argc, 4, "new"))
        {
            new (argv[2], argv[3]);
        }
    }
    else if (strcmp(argv[1], "edit") == 0)
    {
            edit(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "remove") == 0)
    {
        if (check_args(argc, 4, "remove"))
        {
            removeNote(argv[2], argv[3]);
        }
    }
    else if (strcmp(argv[1], "rename") == 0)
    {
        if (check_args(argc, 5, "rename"))
        {
            renameDir(argv[2], argv[3], argv[4]);
        }
    }
    else if (strcmp(argv[1], "backlink") == 0)
    {
        if (check_args(argc, 3, "backlink"))
        {
            backlink(argv[2]);
        }
    }
    else if (strcmp(argv[1], "ls") == 0)
    {
        if (argc < 3)
        {
            printf("Error: 'ls' requires an option (--oneline or --full).\n");
            print_usage();
        }
        else if (strcmp(argv[2], "--oneline") == 0)
        {
            searchInDir(notes_path, NULL, 0, 0); // Modo oneline
        }
        else if (strcmp(argv[2], "--full") == 0)
        {
            searchInDir(notes_path, NULL, 1, 0); // Modo full
        }
        else
        {
            printf("Error: Unknown option '%s' for 'ls'.\n", argv[2]);
            print_usage();
        }
    }
    else
    {
        printf("Error: Unknown command '%s'.\n", argv[1]);
        print_usage();
    }
    free(notes_path);
   
    return 0;
}

void print_usage()
{
    printf("Usage: Notes <command> [options]\n"
           "Commands:\n"
           "  new <category> <name>      Create a new note\n"
           "  edit <category> <name>     Edit an existing note\n"
           "  remove <category> <name>   Remove a note\n"
           "  rename <old> <new> <name>  Rename a category or note\n"
           "  backlink <keyword>        Search for a given keyword\n"
           "  ls --oneline              List notes in simple format\n"
           "  ls --full                 List notes with details\n");
}

int check_args(int argc, int expected, const char *command)
{
    if (argc > expected)
    {
        printf("ERROR: '%s' only holds %d arguments.\n", command, expected - 2);
        return 0;
    }
    return 1;
}