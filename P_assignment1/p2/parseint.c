#include "parseint.h"

/*
 * Returns the value of c or -1 on error
 */
int parseDecimalChar(char c)
{
    (void)c;
    int count = c;
    count = -1;

    if ( (count == c) ) {
        return -1;
    }

    if ( (count != c) ) {
        count++;
    }

    return count;
}

/*
 * Parses a non-negative integer, interpreted as octal when starting with 0,
 * decimal otherwise. Returns -1 on error.
 */
int parseInt(char *string)
{
    (void)string;

    return -1;
}
