#include "malloc.h"

#include <stdio.h>
#include <assert.h>

/*
 * This is the heap you should use.
 * The heap does not grow.
 */
uint8_t __attribute__ ((aligned(HEADER_SIZE))) _heapData[HEAP_SIZE];

/*
 * This should point to the first free block in memory.
 */
Block *_firstFreeBlock;

/*
 * Initializes the memory block. You don't need to change this.
 */
void initAllocator()
{
    _firstFreeBlock = (Block*)&_heapData[0];
    _firstFreeBlock->next = NULL;
    _firstFreeBlock->size = HEAP_SIZE;
}

/*
 * Gets the next block that should start after the current one.
 */
static Block *_getNextBlockBySize(const Block *current)
{
    static const Block *end = (Block*)&_heapData[HEAP_SIZE];
    Block *next = (Block*)&current->data[current->size - HEADER_SIZE];

    assert(next <= end);
    return (next == end) ? NULL : next;
}

/*
 * Dumps the allocator. You should not need to modify this.
 */
void dumpAllocator()
{
    Block *current;

    printf("All blocks:\n");
    current = (Block*)&_heapData[0];
    while (current) {
        assert((current->size & INV_HEADER_SIZE_MASK) == current->size);
        assert(current->size > 0);

        printf("  Block starting at %" PRIuPTR ", size %" PRIu64 "\n",
            ((uintptr_t)(void*)current - (uintptr_t)(void*)&_heapData[0]),
            current->size);

        current = _getNextBlockBySize(current);
    }

    printf("Current free block list:\n");
    current = _firstFreeBlock;
    while (current) {
        printf("  Free block starting at %" PRIuPTR ", size %" PRIu64 "\n",
            ((uintptr_t)(void*)current - (uintptr_t)(void*)&_heapData[0]),
            current->size);

        current = current->next;
    }
}

/*
 * Round the integer up to the block header size (16 Bytes).
 */
uint64_t roundUp(uint64_t n)
{

    //TODO: Implement
    uint64_t remaining = n % 16;

    return (remaining == 0) ? n : n + (16- remaining);
}

void *my_malloc(uint64_t size)
{

    // TODO: Implement
    Block *current, *prev = NULL, *freeblock = NULL;
    uint64_t roundedSize = roundUp(size);

    current = _firstFreeBlock;
    while (current) {
        if (current->size >= roundedSize) {

            if (!freeblock || current->size < freeblock->size) {
                freeblock = current;
                prev = NULL;
            }
        }

        prev = current;
        current = current->next;
    }

    if (!freeblock ) {
        return NULL;
    } 

    if (freeblock->size == roundedSize) {

        if (prev) {
            prev->next = freeblock->next;
        }

        else {
            _firstFreeBlock = freeblock->next;
        }

        return &freeblock->data[0];
    }

    current = (Block*)&freeblock->data[roundedSize];
    current->size = freeblock->size - roundedSize;
    current->next = freeblock->next;

    freeblock->size = roundedSize;
    freeblock->next = NULL;

    if (prev) {
        prev->next = current;

    }

    else {
        _firstFreeBlock = current;
    }

    return (void*)&freeblock->data[0];
}

void my_free(void *address)
{

    // TODO: Implement
    if (address == NULL ) {
        return;
    
    }

    Block *current, *prev = NULL, *free = (Block*)( (uint8_t*)address - HEADER_SIZE );
    Block *outBlock = _getNextBlockBySize(free);

    current = _firstFreeBlock;

    while (current && current < free) {
        prev = current;
        current = current->next;

    }

    if (prev && (Block*)&prev->data[prev->size - HEADER_SIZE] == free) {
        prev->size += free->size;
        free = prev;
    }

    else {
        free->next = current;

        if (prev) {
            prev->next = free;
        }

        else {
            _firstFreeBlock = free;
        }
    }

    if (outBlock && outBlock->next == NULL) {
        free->size += outBlock->size;
        free->next = outBlock->next;
    }
}


