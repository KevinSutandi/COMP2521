
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#define MAX 10000000

int main(void) {
	Queue q = QueueNew();

  for (int i = 0; i < MAX; i++) {
    QueueEnqueue(q, i);
  }


  for (int i = 0; i < MAX; i++) {
    QueueDequeue(q);
  }

	QueueFree(q);
}

/*
Paste the results of the time commands here:

100 elements

benchmarkArrayQueue time : 0m 0.010 sec
benchmarkCircularArrayQueue time : 0m 0.011 sec

10000 elements

benchmarkArrayQueue time : 0m 0.009 sec
benchmarkCircularArrayQueue time : 0m 0.012 sec

100000 elements

benchmarkArrayQueue time : 1m 38.204 sec
benchmarkCircularArrayQueue time : 0m 0.20 sec
*/

