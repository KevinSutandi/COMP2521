// Implementation of the Queue ADT using a circular array

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#define DEFAULT_SIZE 8 // DO NOT change this line

// DO NOT modify this struct
struct queue {
	Item *items;
	int size;
	int capacity;
	int frontIndex;
};

static void increaseCapacity(Queue q);


/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}

	q->items = malloc(DEFAULT_SIZE * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}

	q->size = 0;
	q->capacity = DEFAULT_SIZE;
	q->frontIndex = 0;
	return q;
}

/**
 * Doubles the capacity of the queue
 */
static void increaseCapacity(Queue q) {
  q->capacity = q->capacity * 2; 
	q->items = realloc(q->items, q->capacity * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't resize Queue\n");
		exit(EXIT_FAILURE);
	}

  // Move all the elements from the first half to the second half
  for (int counter = 0; counter < q->frontIndex; counter++) {
    q->items[q->capacity + counter] = q->items[counter];
  }
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	free(q->items);
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
	if (q->size == q->capacity) {   // If queue is full increase capacity
		increaseCapacity(q);       
	}
	q->items[(q->frontIndex + q->size) % q->capacity] = it; // Add to queue
	q->size++;                                              
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	Item front = q->items[q->frontIndex];               // Get front item
	q->frontIndex = (q->frontIndex + 1) % q->capacity;  // set new front index
	q->size--;
	return front;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);
	return q->items[q->frontIndex];
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Prints the items in the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++) {
		fprintf(fp, "%d ", q->items[i]);
	}
	fprintf(fp, "\n");
}

/**
 * Prints out information for debugging
 */
void QueueDebugPrint(Queue q) {
    printf("Front Index is: %d \n", q->frontIndex);
    printf("Capacity is: %d \n", q->capacity);
    
}