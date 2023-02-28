// Name: Poomi Krua Aim (please add your name here)
// Group:  no group

#include "measure_tlb.h"
#include <stdint.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define PAGESIZE 4096

uint64_t getTimeStamp() {
	// Implement this function.
	//https://man7.org/linux/man-pages/man2/settimeofday.2.html

	struct timeval tv;

	gettimeofday(&tv, NULL);
	
	return (uint64_t)tv.tv_sec * 1000000 + (uint64_t)tv.tv_usec;
}


uint64_t measureFunction( void(*function)(void *), void *arg ) {
	// Add code around the invocation of function to measure the execution time
	uint64_t startTime;
	uint64_t endTime;

	startTime = getTimeStamp();
	(*function)(arg);
	endTime = getTimeStamp();


	return endTime - startTime;
}

void measureStatistics( int statcount, Statistics *stat, void(*function)(void *), void*arg) {
	// (void)statcount;
	// (void)function;
	// (void)arg;

	

	// stat->min = 0;
	// stat->avg = 0;
	// stat->max = 0;

	// Implement this function: invoke measureFunction() statcount times and calculate statistics
	uint16_t totalTime = 0;
	uint16_t minTime = UINT16_MAX;
	uint64_t maxTime = 0;

	for (int i = 0; i < statcount; i++) {
		uint64_t time;
		time = measureFunction(function, arg);

		totalTime += time;

		minTime = (time < minTime) ? time : minTime;
		maxTime = (time > maxTime) ? time : maxTime;

	}

	stat->min = minTime;
	stat->max = maxTime;
	stat->avg = totalTime / statcount;

}

void accessMemory(int n, int pages) {
	// (void)n;
	// (void)pages;
	// Implement this function

	void* b = malloc(pages * PAGESIZE);
	if (b == NULL) {
		fprintf(stderr, "Error\n");
		exit(1);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < pages; j++) {
			char* page = (char*)b + j * PAGESIZE;
			*page = 0;
		}
	}


	free(b);
}

void accessMemoryWrapper(void *p) {
	// (void)p;
	// Implement this function

	MeasurementParameters *param = (MeasurementParameters*)p;

	accessMemory(param->n, param->pages);
}

