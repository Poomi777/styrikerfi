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
    int i;
    int converter = 0;

    for (i=1; i <= 4; i++) {
    	if ( (*string == '0') ){
            string++;

            if ( (*string == '1') ){
                converter = converter + (int)*string;
            }
        }
        return converter;
	}

    return -1;
}
