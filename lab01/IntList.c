// IntList.c - Implementation of the IntList ADT
// Lists of integers
// Made and Edited by Kevin Edbert Sutandi (z5352065)

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "IntList.h"



// data structures representing IntList
struct IntListNode {
	int data;
	struct IntListNode *next;  // pointer to next node
};

struct IntListRep {
	int size;                  // number of elements in the list
	struct IntListNode *first; // pointer to node containing first value
	struct IntListNode *last;  // pointer to node containing last value
};

static struct IntListNode *newIntListNode(int v);

/**
 * Creates a new, empty IntList.
 */
IntList IntListNew(void) {
	struct IntListRep *l = malloc(sizeof(*l));
	if (l == NULL) {
		err(EX_OSERR, "couldn't allocate IntList");
	}

	l->size = 0;
	l->first = NULL;
	l->last = NULL;
	return l;
}

/**
 * Frees all memory associated with an IntList.
 */
void IntListFree(IntList l) {
	struct IntListNode *curr = l->first;
	while (curr != NULL) {
		struct IntListNode *temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(l);
}

/**
 * Creates an IntList by reading values from a file.
 * Assumes that the file is open for reading.
 */
IntList IntListRead(FILE *in) {
	IntList l = IntListNew();

	int v;
	while (fscanf(in, "%d", &v) == 1) {
		IntListAppend(l, v);
	}
	return l;
}

/**
 * Prints an IntList to stdout, one integer per line.
 */
void IntListShow(IntList l) {
	IntListPrint(l, stdout);
}

/**
 * Appends an integer to an IntList.
 */
void IntListAppend(IntList l, int v) {
	struct IntListNode *n = newIntListNode(v);
	if (l->first == NULL) {
		l->first = l->last = n;
	} else {
		l->last->next = n;
		l->last = n;
	}
	l->size++;
}

/**
 * Creates a new IntListNode with value v
 * (this function is local to this ADT)
 */
static struct IntListNode *newIntListNode(int v) {
	struct IntListNode *n = malloc(sizeof(*n));
	if (n == NULL) {
		err(EX_OSERR, "couldn't allocate IntList node");
	}
	n->data = v;
	n->next = NULL;
	return n;
}

/**
 * Inserts an integer into the appropriate place in a sorted IntList,
 * such that the list remains sorted.
 * Assumes that the given list is sorted.
 */
void IntListInsertInOrder(IntList l, int v) {
	// TODO: Task 1 - Implement this function

												
	struct IntListNode *n = newIntListNode(v);	        // Create new value as a node

	if (l->size == 0) {						            // If List is empty assign first and last to be the node
		l->first = l->last = n;
	} else if (v <= l->first->data) { 		            // Scenario where the value v is the smallest
		n->next = l->first; 				            // Move the current first node into the second node position
		l->first = n;						            // First node becomes the new value	
	} else if (v >= l->last->data)	{ 		            // Scenario where the value v is the largest
		l->last->next = n;					            // Place the value after the last node
		l->last = n;
	} else {
		for (struct IntListNode *counter = l->first;    // Scenario where the value v is in between the smallest and largest
		counter != NULL; counter = counter->next) {
			if (v <= counter->next->data) {
				n->next = counter->next;
				counter->next = n;
				break;
			}
		}
	}
	l->size++;  							            // Increase the size by 1 as adding one more node

}

/**
 * Returns the number of elements in an IntList.
 */
int IntListLength(IntList l) {
	return l->size;
}

/**
 * Creates a copy of an IntList.
 */
IntList IntListCopy(IntList l) {
	IntList copy = IntListNew();
	for (struct IntListNode *curr = l->first;
			curr != NULL; curr = curr->next) {
		IntListAppend(copy, curr->data);
	}
	return copy;
}

/**
 * Creates a sorted copy of an IntList.
 */
IntList IntListSortedCopy(IntList l) {
	// TODO: Task 2 - Implement this function
	// Note: You *must* use IntListInsertInOrder
	IntList NewSorted = IntListNew();
	for (struct IntListNode *sort = l->first; 
    sort != NULL; sort = sort->next) {
		IntListInsertInOrder(NewSorted, sort->data);
	}
	// TODO: Replace this with your return value
	return NewSorted;
}

/**
 * Checks whether an IntList is sorted in ascending order.
 * Returns true if the list is sorted, and false otherwise.
 */
bool IntListIsSorted(IntList l) {
	if (l->first == NULL) {
		return true;
	}

	// scan the list, looking for an out-of-order pair
	for (struct IntListNode *curr = l->first;
			curr->next != NULL; curr = curr->next) {
		if (curr->data > curr->next->data) {
			return false;
		}
	}

	// nothing out-of-order, so the list must be sorted
	return true;
}

/**
 * Checks the internal consistency of an IntList.
 * Returns true if the list is consistent, and false otherwise.
 *
 * An IntList is internally consistent if it satisfies the following
 * conditions:
 * 1) If the list is empty, then both the first and last fields point
 *    to NULL
 * 2) The number of nodes in the list is equal to the size field
 * 3) If the list is not empty, then the last field point to the last
 *    node in the list
 *
 * This function checks the above three conditions.
 */
bool IntListOK(IntList l) {
	if (l->size == 0) {
		return (l->first == NULL && l->last == NULL);
	}

	// scan to (but not past) last node
	struct IntListNode *curr = l->first;
	struct IntListNode *prev = NULL;
	int numNodes = 0;
	
	while (curr != NULL) {
		numNodes++;
		prev = curr;
		curr = curr->next;
	}

	return (numNodes == l->size && prev == l->last);
}

/**
 * Prints an IntList to a file, one integer per line.
 * Assumes that the file is open for writing.
 */
void IntListPrint(IntList l, FILE *out) {
	for (struct IntListNode *curr = l->first;
			curr != NULL; curr = curr->next) {
		fprintf(out, "%d\n", curr->data);
	}
}

