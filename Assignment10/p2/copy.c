/* 
 * Group number (on canvas): xx
 * Student 1 name: Poomi Krua Aim
 * Student 2 name: xx 
 */

#define _POSIX_C_SOURCE 2
#include "copy.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

// No need to change this. Parses argc into the CopyArgs structure
int parseCopyArgs(int argc, char * const argv[], CopyArgs* args)
{
    if (args == NULL) {
        return -1;
    }

    // Initialize with default values
    args->blocksize  = 1024;

    int opt;
    while ((opt = getopt(argc, argv, "b:")) != -1) {
        switch (opt) {
            case 'b':
                args->blocksize = atoi(optarg);

                if ((errno != 0) || (args->blocksize <= 0)) {
                    return -1; // Invalid blocksize argument.
                }

                break;

            default: /* '?' */
                return -1;
        }
    }

    if (optind != argc - 2) {
        return -1; // We expect two parameters after the options.
    }

    args->from = argv[optind];
    args->to   = argv[optind + 1];

    return 0;
}


int doCopy(CopyArgs* args)
{
    if (args == NULL) {
        return -1;
    }

    // ----------------
    // Copy the file.
    // ----------------

    int source_file = open(args->from, O_RDONLY);

    if (source_file == -1) {
        perror("Failed to open source file");
        return -1;
    }

    struct stat st;

    if (stat(args->to, &st) == 0) {
        fprintf(stderr, "Destination file already exists\n");
        close(source_file);
        return -1;
    }

    int destination_file = open(args->to, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR);

    if (destination_file == -1) {
        perror("Failed to create destination file");
        close(source_file);
        return -1;
    }

    char buffer[args->blocksize];
    int bytes_read;

    while ((bytes_read = read(source_file, buffer, args->blocksize)) > 0) {
        int zeroes = 1;

        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] != 0) {
                zeroes = 0;
                break;
            }
        }

        if (zeroes) {
            if (lseek(destination_file, bytes_read, SEEK_CUR) == -1) {
                perror("Failed to seek destination file");
                close(source_file);
                close(destination_file);
                return -1;
            }
        }

        else {
            if (write(destination_file, buffer, bytes_read) == -1) {
                perror("Failed to write to destination file");
                close(source_file);
                close(destination_file);
                return -1;
            }
        }
    }

    if (bytes_read == -1) {
        perror("Failed to read source file");
        close(source_file);
        close(destination_file);
        return -1;
    }


    if (chmod(destination_file, S_IRUSR) == -1) {
        perror("Failed to set permissions on destination file");
        close(source_file);
        close(destination_file);
        return -1;
    }

    close(source_file);
    close(destination_file);
    return 0;
}
