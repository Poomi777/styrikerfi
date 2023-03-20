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
    DIR *directory;

    struct dirent *entry;
    struct stat st;

    directory = opendir(path);
    if (directory == NULL) {
        return -1;
    }

    char file[MAX_FILE_NAME_LENGTH];

    while (1) {
        entry = readdir(directory);

        if (entry == NULL) {
            break;
        }

        if (entry->d_name[0] == '.') {
            continue;
        }

        if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0)) {
            continue;
        }

        strcpy(file, path);
        strcat(file, "/");
        strcat(file, entry->d_name);

        if (lstat(file, &info) == -1) {
            return -1;
        }

        unsigned int size = info.st_size;
        unsigned int sizeOnDisk = info.st_blocks * 512;
        _printLine(size, sizeOnDisk, entry->d_name);
    }

    if (closedir(directory) == -1) {
        return -1;
    }

    return 0;

    
}
