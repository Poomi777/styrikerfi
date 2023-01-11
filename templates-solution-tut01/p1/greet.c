#include "greet.h"
#include <stdio.h>

void greet(int32_t times) {
	
	// Add code here.
	int32_t i;

	for (i=1; i <= times; i++) {
    	printf("%d Hello World!\n", i);
	}

}
