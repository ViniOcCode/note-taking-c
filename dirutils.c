#include "dirutils.h"
#include "utils.h"

#define MAX_LINE 1024
#define MAX_PATH 4096

int removerf(const char *path, const struct stat *file_info, int item_type, struct FTW *nftw_info)
{
    int result = (item_type == FTW_D) ? rmdir(path) : unlink(path);
    if (result == -1)
    {   
        perror(path);
    }
    return 0;
}

int handle_path(char *dirpath, char *category, char *name)
{
    if (dirpath == NULL)
    {
        printf("ERROR: Finding file to remove.\n");
        return - 1;
    }

    if (path_validation(dirpath) != 0)
    {
        printf("%s already doesn't exist!\n", name ? "File" : "Directory");
        return -1;
    }

    if (name == NULL)
    {
        if (nftw(dirpath, removerf, 10, FTW_DEPTH) == -1)
        {
            perror("Couldn't pass directory\n");
            return EXIT_FAILURE;
        }
        rmdir(dirpath);

        printf("Directory '%s' removed sucessfully.\n", category);
    }
    else
    {
        if (unlink(dirpath) != 0)
        {
            perror("Error removing file\n");
            return EXIT_FAILURE;
        }
        printf("File '%s' removed sucessfully!\n", name);
    }

    return EXIT_SUCCESS;
}

void searchInFile(char *filepath, char *word, int mode)
{
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        printf("ERROR: Failed to open file.\n");
        return;
    }

    char line[MAX_LINE];
    int linenumber = 0;
    
    if (mode == 1)
    {
        printf("First 5 lines:\n");
        while (fgets(line, MAX_LINE, file) != NULL && linenumber < 5)
        {
            linenumber++;
            printf("    Line %d: %s", linenumber, line);
        }
    }
    else if (word != NULL)
    {
        while (fgets(line, MAX_LINE, file) != NULL)
        {
            linenumber++;
            if (strstr(line, word) != NULL)
            {
                printf("Found in '%s', line %d: %s", filepath, linenumber, line);
            }
        }
    }

    fclose(file);
}

void print_indent(int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("|  ");
    }
}

void searchInDir(char *dirbase, char *word, int mode, int depth)
{
    DIR *dir = opendir(dirbase);
    if (dir == NULL)
    {
        printf("ERROR: Failed to open directory.\n");
        return;
    }

    struct dirent *entry;
    struct stat info;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        
        char dirpath[MAX_PATH];
        snprintf(dirpath, MAX_PATH, "%s/%s", dirbase, entry->d_name);

        if (stat(dirpath, &info) == -1)
        {
            printf("ERROR: Failed to search file.\n");
            continue;
        }

        if (mode == 0)
        {
            printf("%s\n", entry->d_name);
        }
        else if(mode == 1)
        {
            print_indent(depth);
            printf("|-- %s\n", entry->d_name);
            print_indent(depth);
            printf("|  Type: %s\n", S_ISDIR(info.st_mode) ? "Directory" : "File");
            print_indent(depth);
            printf("|  Size: %ld bytes\n", (long)info.st_size);
            
            if (S_ISREG(info.st_mode) && strstr(entry->d_name, ".md"))
            {
                print_indent(depth);
                printf("|  ");
                searchInFile(dirpath, NULL, mode);
            }
            print_indent(depth);
        }

        if (S_ISDIR(info.st_mode))
        {
            searchInDir(dirpath, word, mode, depth + 1);
        }
    }
    closedir(dir);
}