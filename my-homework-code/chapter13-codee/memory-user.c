#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main (int argc, char *argv[]) {

	if (argc == 1) {
		printf("No args input, please specify the array length\n");
		exit(1);
	} else if (argc == 2) {
		printf("please specify the time to run\n");
		exit(1);
	} else if (argc != 3) {
		printf("Num of args should be 2\n");
		exit(1);
	} 

	int length = atoi(argv[1]) * 1024 * 1024 / sizeof(float); // read from input
	float *arr;
	arr = (float *) malloc(length * sizeof(float));
	if (!arr) {
		printf("Memory not allocated, malloc returns NULL\n");
		exit(1);
	}	

	struct timespec start, end;
	double running_time = 0.0;
	double ref_time = (double)atoi(argv[2]);

	while (running_time < ref_time) {
		clock_gettime(CLOCK_MONOTONIC, &start);
		for (int i = 0; i < length; i++) {
			arr[i]++; 
		}
		clock_gettime(CLOCK_MONOTONIC, &end);
		//running_time = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
		running_time += end.tv_sec - start.tv_sec;
	}

	printf("Program done, memory freed\n");
	free(arr);

	return 0;
}
