/* 
 * Group number (on canvas): xx
 * Student 1 name: Poomi Krua Aim
 * Student 2 name: xx 
 */


#include "filesystem.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>


FileSystem *initFileSystem(char *diskFile)
{
    if (diskFile == NULL) {
        return NULL;
    }

    // ----------------
    // open file system image and read header (FAT + root dir size) into a FileSystemHeader data structure
    // (memory allocated dynamically with malloc)
    // You may assume that the file system is never re-allocated from memory.
    // ----------------

    int filedesc = open(diskFile, O_RDONLY);
        if (filedesc == -1) {
            return NULL;
        }

    if (filedesc == -1) {
        return NULL;
    }

    struct stat st;
    if (fstat(filedesc, &st) == -1) {
        close(filedesc);
        return NULL;
    }

    size_t fileSize = st.st_size;

    void *mapped = mmap(NULL, fileSize, PROT_READ, MAP_SHARED, filedesc, 0);
    if (mapped == MAP_FAILED) {
        close(filedesc);
        return NULL;
    }

    FileSystem *fs = malloc(sizeof(FileSystem));
    if (fs == NULL) {
        munmap(mapped, fileSize);
        close(filedesc);
        return NULL;
    }

    memcpy(&fs->header, mapped, sizeof(FileSystemHeader));

    close(filedesc);
    munmap(mapped, fileSize);

    return fs;
}

// Create a file handle representing a file that is part of a specific file system (fs),
// starting at block (blockIndex) in that file system, and a file length (length) in bytes
static OpenFileHandle *_openFileAtBlock(FileSystem *fs, uint32_t blockIndex,
    uint32_t length)
{
    assert(fs != NULL);
    assert(blockIndex < FILE_SYSTEM_BLOCKS);

    OpenFileHandle *handle = malloc(sizeof(OpenFileHandle));
    if (handle == NULL) {
        return NULL;
    }

    handle->fileSystem        = fs;
    handle->currentBlock      = blockIndex;
    handle->currentFileOffset = 0;
    handle->length            = length;

    return handle;
}

static int _hasMoreBytes(OpenFileHandle *handle)
{
    assert(handle != NULL);
    assert(handle->currentFileOffset <= handle->length);

    (void)handle;

    // ----------------
    // Check if there are more bytes to read in the file.
    // ----------------

    return (handle->currentFileOffset < handle->length);
}

int _findDirectoryEntry(OpenFileHandle *dir, char *name, DirectoryEntry *dirEntry)
{
    if (dir == NULL || name == NULL || dirEntry == NULL) {
        return -1;
    }

    DirectoryEntry entry;
    while (_hasMoreBytes(dir)) {
        int bytesRead = readFile(dir, (char *)&entry, sizeof(DirectoryEntry));

        if (bytesRead != sizeof(DirectoryEntry)) {
            return -1;
        }

        if (strncmp(entry.name, name, FILE_NAME_LENGTH) == 0) {
            memcpy(dirEntry, &entry, sizeof(DirectoryEntry));
            return 0;
        }
    }

    return -1;
}


OpenFileHandle *openFile(FileSystem *fs, char *dir, char *name)
{
    if ((fs == NULL) || (name == NULL)) {
        return NULL;
    }

    // Open the root directory file.
    OpenFileHandle *root = _openFileAtBlock(fs, ROOT_DIRECTORY_BLOCK,
                                            fs->header.rootDirectorySize);
    if (dir == NULL) {
        dirHandle = _openFileAtBlock(fs, ROOT_DIRECTORY_BLOCK, fs->header.rootDirectorySize);
    }
    else {
        DirectoryEntry dirEntry;
        int result = _findDirectoryEntry(_openFileAtBlock(fs, ROOT_DIRECTORY_BLOCK, fs->header.rootDirectorySize), dir, &dirEntry);
        if (result != 0 || dirEntry.type != FTYPE_DIRECTORY) {
            return NULL;
        }

        dirHandle = _openFileAtBlock(fs, dirEntry.firstBlock, dirEntry.length);
    }

    // ----------------
    // If dir is not NULL:
    // find the directory (in the root directory) with that name
    // open that directory, and use that instead of root for searching the file name
    // ----------------
    DirectoryEntry fileEntry;
    int result = _findDirectoryEntry(root, name, &fileEntry);

    if (result != 0 || fileEntry.type != FTYPE_REGULAR) {
        closeFile(dirHandle);
        return NULL;
    }


    // ----------------
    // Find the directory entry with that name.
    // You can use readFile to read from the directory stream.
    // ----------------

    OpenFileHandle *fileHandle = _openFileAtBlock(fs, fileEntry.firstBlock, fileEntry.length);

    if (fileHandle == NULL) {
        closeFile(dirHandle);

        return NULL;
    }

    closeFile(dirHandle);

    // ----------------
    // Return a file handle if the file could be found.
    // ----------------
    return fileHandle;
}

void closeFile(OpenFileHandle *handle)
{
    if (handle == NULL) {
        return;
    }

    // Since we opened the file system with read access only, we do not have
    // any pending modifications that might need to be written back to the file
    // prior closing. Hence, we can just free the handle and call it a day.
    free(handle);
}

static char _readFileByte(OpenFileHandle *handle)
{
    assert(handle != NULL);
    assert(_hasMoreBytes(handle));
    assert(handle->fileSystem != NULL);
    assert(handle->currentBlock < FILE_SYSTEM_BLOCKS);

    // ----------------
    // Read a byte from the file. This should never fail, because the function
    // must not be called if there are not more bytes to read.
    // ----------------

    uint32_t blockSize = handle->fileSystem->header.blockSize;

    uint32_t *fat = (uint32_t)((char *)handle->fileSystem + blockSize);

    uint32_t fatIndex = handle->currentBlock / (blockSize / sizeof(uint32_t));

    if (handle->currentFileOffset % blockSize == 0) {
        uint32_t nextBlock = fat[fatIndex];
        if (nextBlock == FAT_EOC) {
            return 0;
        }

        handle->currentBlock = nextBlock;
    }

    char *block = (char *)handle->fileSystem + handle->currentBlock * blockSize;
    char byte = block[handle->currentFileOffset % blockSize];


    handle->currentFileOffset++;
    return byte;
}

// This acts like the default linux read() system call on your file.
int readFile(OpenFileHandle *handle, char *buffer, int length)
{
    if ((handle == NULL) || (buffer == NULL)) {
        return -1;
    }

    int n = 0;
    while ((n < length) && _hasMoreBytes(handle)) {
        buffer[n] = _readFileByte(handle);

        ++n;
    }

    return n;
}




