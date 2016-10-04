/**
	Hun Jae Lee (hxl224)
	EECS338 HW4
	Due 161003

	Description:
	Shubert function to find the minimum value for -2.0 ≤ x1, x2 ≤ 2.0
	Using multithreading.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "shubert.c"

double min; /* this data is shared by the thread(s) */

void *shubert_compute1(void *param);
void *shubert_compute2(void *param);

int main(int argc, char *argv[]) {
	pthread_t tid1, tid2; /* the thread identifier */
	pthread_attr_t attr1, attr2; /* set of attributes for the thread */

	/* get the default attributes */
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);

	/* create the thread */
	pthread_create(&tid1, &attr1, shubert_compute1, NULL);
	pthread_create(&tid2, &attr2, shubert_compute2, NULL);

	/* now wait for the thread to exit */
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("minimum: %f\n", min);
}

/**
 * The thread will begin control in this function
 */
void *shubert_compute1(void *param) {
	double x1_1, x1_2, y1;
	for (x1_1 = -2; x1_1 <= 2; x1_1 += 0.05) {
	  for (x1_2 = 0; x1_2 <= 2; x1_2 += 0.05) {
	    y1 = shubert(x1_1, x1_2);
	    if (y1 < min) {
	    	min = y1;
	    }
	  }
	}
	pthread_exit(0);
}

void *shubert_compute2(void *param) {
	double x2_1, x2_2, y2;
	for (x2_1 = -2; x2_1 <= 2; x2_1 += 0.05) {
	  for (x2_2 = -2; x2_2 <= 0; x2_2 += 0.05) {
	    y2 = shubert(x2_1, x2_2);
	    if (y2 < min) {
	    	min = y2;
	    }
	  }
	}
	pthread_exit(0);
}
