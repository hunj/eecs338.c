#include <stdio.h>
#include <omp.h> 
#define MAX_THREADS 8

int main () { 
	int trial; 
	for (trial = 1; trial <= 100; trial++) {
		int i, sum = 0;
		#pragma omp parallel for
		for (i = 1; i <= 100; i++) {
			#pragma omp critical
			sum = sum + i;
		} /* All threads join master thread and terminate */ 
		printf("%d ", sum);
	}
	printf("\n");
	return 0;
} 
