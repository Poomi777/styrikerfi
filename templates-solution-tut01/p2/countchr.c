#include "countchr.h"
int countchr(char *string, char c) {

	// Add code here.
	int count = 0;

	while (*string != '\0'){
		if ( (*string = c) ) {
			count++;

		};
		string++;
	}

	return count;
}
