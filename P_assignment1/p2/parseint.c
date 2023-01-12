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
    char dec_converter = "0";
    
    if ( (*string != '0') ){
        for (i=1; i <= 4; i++){
            dec_converter = dec_converter + (char)*string;
            string++;
        }
        return dec_converter;
    }

    if ( (*string == '0') ){
        for (i=1; i <= 3; i++) {
            string++;

            if ( (*string == '1') ){
                converter = converter + 8;
            }
        }
    }
    return converter;

    return -1;
}
