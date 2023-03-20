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
        perror("opendir failed");
        return -1;
    }

    struct dirent *entry;

    while ((entry = readdir(directory)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }

        char full_path[MAX_FILE_NAME_LENGTH];
        snprintf(full_path, MAX_FILE_NAME_LENGTH, "%s/%s", path, entry->d_name);

        struct stat st;
        
        if (stat(full_path, &st) == -1) {
            perror("failed to stat");
            
            closedir(directory);
            return -1;
        }

        _printLine(st.st_size, st.st_blocks * 512, entry->d_name);
    }

    closedir(directory);
    return 0;
}
