
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "notes.h"
#include "utils.h"
#include "dirutils.h"

void print_usage();
int check_args(int argc, int minimum, int maximum, const char *usage);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        print_usage();
        return 0;
    }

    if (strcmp(argv[1], "--help") == 0)
    {
        print_usage();
        return 0;
    }

    if (init_home_path() != 0 || init_notes_directory() != 0)
    {
        fprintf(stderr, "Error: Failed to initialize paths or directories.\n");
        return -1;
    }
    int exit_code = 0;

    if (strcmp(argv[1], "new") == 0)
    {
        if (check_args(argc, 3, 4, "notes new <category> [name]") == 0)
        {
            new(argv[2], argc == 4 ? argv[3] : NULL);
        }
        else exit_code = 1;
    }
    else if (strcmp(argv[1], "edit") == 0)
    {
        if (check_args(argc, 2, 4, "notes edit [category] [name]") == 0)
        {
            edit(argc >= 3 ? argv[2] : NULL, argc == 4 ? argv[3] : NULL);
        }
        else exit_code = 1;
    }
    else if (strcmp(argv[1], "remove") == 0)
    {
        if (check_args(argc, 3, 4, "notes remove <category> [name]") == 0)
        {
            removeNote(argv[2], argc == 4 ? argv[3] : NULL);
        }
        else exit_code = 1;
    }
    else if (strcmp(argv[1], "rename") == 0)
    {
        if (check_args(argc, 4, 5, "notes rename <old> <new> OR notes rename <category> <old> <new>") == 0)
        {
            renameDir(argv[2], argv[3], argc == 5 ? argv[4] : NULL);
        }
        else exit_code = 1;
    }
    else if (strcmp(argv[1], "backlink") == 0)
    {
        if (check_args(argc, 3, 3, "notes backlink <keyword>") == 0)
        {
            backlink(argv[2]);
        }
        else exit_code = 1;
    }
    else if (strcmp(argv[1], "ls") == 0)
    {
        if (check_args(argc, 3, 3, "notes ls <--oneline|--full>") != 0)
        {
            exit_code = 1;
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
            printf("Error: Unknown option '%s' for 'ls'.\nUse [notes --help] to see more\n", argv[2]);
            exit_code = 1;
        }
    }
    else
    {
        printf("Error: Unknown command '%s'.\nUse [notes --help] to see more.\n", argv[1]);
        exit_code = 1;
    }
    free(notes_path);

    return exit_code;
}

void print_usage()
{
    printf("Usage: Notes <command> [options]\n"
           "Commands:\n"
           "  new <category> [name]      Create a new note\n"
           "  edit [category] [name]     Edit a note or the notes directory\n"
           "  remove <category> [name]   Remove a note or category\n"
           "  rename <old> <new>         Rename a category\n"
           "  rename <category> <old> <new>  Rename a note\n"
           "  backlink <keyword>        Search for a given keyword\n"
           "  ls --oneline              List notes in simple format\n"
           "  ls --full                 List notes with details\n");
}

int check_args(int argc, int minimum, int maximum, const char *usage)
{
    if (argc < minimum || argc > maximum)
    {
        printf("Usage: %s\n", usage);
        return -1;
    }
    return 0;
}
