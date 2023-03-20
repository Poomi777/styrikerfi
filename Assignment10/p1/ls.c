/* 
 * Group number (on canvas): xx
 * Student 1 name: Poomi Krua Aim
 * Student 2 name: xx 
 */

#include "ls.h"
// You may not need all these headers ...
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

// Use this function to display the files. DO NOT CHANGE IT.
void _printLine(unsigned int size, unsigned int sizeOnDisk, const char* name)
{
    printf("%10u   %10u   %s\n", size, sizeOnDisk, name);
}

// Assume this to be the maximum length of a file name returned by readdir
#define MAX_FILE_NAME_LENGTH 255

int list(const char* path, const char *suffixFilter)
{
    DIR *directory = opendir(path);
    if (directory == NULL) {
        perror("Failed to open directory");
        return -1;
    }

    struct dirent *entry;
    struct stat st;

    while ((entry = readdir(directory)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }

        char file_path(PATH_MAX);
        snprintf(file_path, PATH_MAX, "%s/%s", path, entry->d_name);

        if (lstat(file_path, &st) == -1) {
            perror("Failed to stat file");
            return -1;
        }

        if (S_ISDIR(st.st_mode)) {
            list(file_path, suffixFilter);
        }

        else {
            unsigned int size = st.st_size;
            unsigned int sizeOnDisk = st.st_blocks * 512;

            char *file_name = strrchr(file_path, '/') + 1;
            _printLine(size, sizeOnDisk, file_name);
        }
    }


    if (errno != 0) {
        perror("Failed to read directory");
        return -1;
    }

    if (closedir(directory) == -1) {
        perror("Failed to close directory");
        return -1;
    }

    return 0;
    
}
