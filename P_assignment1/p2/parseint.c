#include "parseint.h"

/*
 * Returns the value of c or -1 on error
 */
int parseDecimalChar(char c)
{
    (void)c;
    int count = c;
    count = 0;

    if ( (count == c) ) {
        return count;
    }

    if ( (count != c) ) {
        count++;
    }

    else {
        return -1;
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
