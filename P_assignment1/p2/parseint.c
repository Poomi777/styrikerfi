#include "parseint.h"

/*
 * Returns the value of c or -1 on error
 */
int parseDecimalChar(char c)
{
    if ( (c > 57) ){
        return -1;
    }

    if ( (c < 48) ){
        return -1;
    }

    return c - '0';
}
/*
 * Parses a non-negative integer, interpreted as octal when starting with 0,
 * decimal otherwise. Returns -1 on error.
 */
int parseInt(char *string)
{
    (void)string;
    char first_letter = string[0];


    if ( (first_letter == 0) ){
        return 99;
    }

    return -1;
}
