#include "print.h"
#include <stdio.h>

void print_line(int64_t number, char *string)
{
    (void) number;
    (void) string;
    // Add code here.
    int64_t i;

    for (i=1; i <= number; i++) {
        printf("%i Hello world!\n", i);
    }
    number++;

}
