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
    if (!directory) {
        fprintf(stderr, "Failed to open directory: %s: %s\n", path, strerror(errno));
        return -1;
    }

    struct dirent *entry;
    struct stat st;

    char filepath(PATH_MAX);
    int returner = 0;

    while ((entry = readdir(directory)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }

        snprintf(full_path, sizeof(filepath), "%s/%s", path, entry->d_name);

        if (stat(filepath, &st) == -1) {
            fprintf(stderr, "Failed to stat the file %s: %s\n", filepath, strerror(errno));
            returner = -1;
            continue;
        }

        if (!S_ISDIR(st.st_mode)) {
            continue;
        }

        if (suffixFilter != NULL && strcmp(suffixFilter, "") != 0) {
            char *suffix = strrchr(entry->d_name, '.');

            if (suffix == NULL || strcmp(suffix, suffixFilter) != 0) {
                continue;
            }
        }

        _printLine(st.st_size, st.st_blocks * 512, entry->d_name);
    }

    if (closedir(directory) == -1) {
        fprintf(stderr, "Failed to close directory %s: %s\n", path, strerror(errno));
        return -1;
    }

    return returner;
}
