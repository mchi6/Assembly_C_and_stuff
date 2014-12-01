#include <stdlib.h>
#include "./list.h"
#include "my_malloc.h"

/**
 * pushFront
 * Takes in ptr to a list and data to add
 * Should add new node containing the data to the head of the list, and increment size
 */
void pushFront(LIST *list, int data)
{
	NODE *newNode = (NODE*) my_malloc(1 * sizeof(NODE)); // testing my_malloc()
	newNode->data = data;
	if (list->size == 0) {
		list->head = newNode;
		list->tail = newNode;
	} else {
		list->head->prev = newNode;
		newNode->prev = NULL;
		newNode->next = list->head;
		list->head = newNode;
	}
	list->size++;
}

/**
 * pushFront
 * Takes in ptr to a list and data to add
 * Should add new node containing the data to the tail of the list, and increment size
 */
void pushBack(LIST *list, int data)
{
	NODE *newNode = (NODE*) my_malloc(1 * sizeof(NODE)); // testing my_malloc()
	newNode->data = data;
	if (list->size == 0) {
		list->head = newNode;
		list->tail = newNode;
	} else {
		list->tail->next = newNode;
		newNode->next = NULL;
		newNode->prev = list->tail;
		list->tail = newNode;
	}
	list->size++;
}

/**
 * popFront
 * Takes in ptr to a list
 * Remove and free node at the front of the list, and decrement size
 * Return the value of that node
 * Return 0 if the size of the list is 0
 */
int popFront(LIST *list)
{
	NODE *temp = list->head;
	if (list->size == 1) {
		my_free(temp);
		list->head = NULL;
		list->tail = NULL;
		list->size--;
		return 1;
	} else if (list->size > 1) {
		list->head = list->head->next;
		list->head->prev = NULL;
		my_free(temp);
		list->size--;
		return 1;
	}
	return 0;
}

/**
 * popBack
 * Takes in ptr to a list
 * Remove and free node at the back of the list, and decrement size
 * Return the value of that node
 * Return 0 if the size of the list is 0
 */
int popBack(LIST *list)
{
	NODE *temp = list->tail;
	if (list->size == 1) {
		my_free(temp);
		list->head = NULL;
		list->tail = NULL;
		list->size--;
		return 1;
	} else if (list->size != 0) {
		list->tail = list->tail->prev;
		list->tail->next = NULL;
		my_free(temp);
		list->size--;
		return 1;
	}
	return 0;
}


