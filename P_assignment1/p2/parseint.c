#include "parseint.h"

/*
 * Returns the value of c or -1 on error
 */
int parseDecimalChar(char c)
{
    if ( ((c - '0') < 0) ){
        return -1;
    }

    return '0' - c;
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
