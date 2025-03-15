#include "dirutils.h"
#include "utils.h"

// nftw directory seek
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

