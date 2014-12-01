/**
 * CS 2110 - Spring 2014 - Homework #12
 * Edited by: Brandon Whitehead, Andrew Wilder
 *
 * list.c: Complete the functions!
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO*/
/* Design consideration only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION DO NOT PUT IT IN OTHER FILES */
typedef struct lnode
{
  struct lnode* prev; /* Pointer to previous node */
  struct lnode* next; /* Pointer to next node */
  void* data; /* User data */
} node;


/* Do not create any global variables here. Your linked list library should obviously work for multiple linked lists */
// This function is declared as static since you should only be calling this inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
    node *newNode;
    newNode = malloc(1 * sizeof(node));
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->data = data;

    return newNode;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void)
{
    list *newList;
    newList = malloc(1 * sizeof(list));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;

    return newList;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void* data)
{
    node *newHead = create_node(data);

    // if the size of the list is 0
    if (llist->size == 0) {
      llist->head = newHead; 
      llist->tail = newHead;
    } else { // if the size of the list is not 0
      node *oldHead = llist->head;
      oldHead->prev = newHead;
      llist->head = newHead;
      newHead->next = oldHead;
    }
    llist->size++;
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void* data)
{
    node *newTail = create_node(data);
    if (llist->size == 0) {
      llist->head = newTail;
      llist->tail = newTail;
    } else {
      node *oldTail = llist->tail;
      oldTail->next = newTail;
      llist->tail = newTail;
      newTail->prev = oldTail;
    }
    llist->size++;
}

/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void* front(list* llist)
{
    if (llist->size == 0) {
      return NULL;
    } else {
      return llist->head->data;
    }
    return NULL;
}

/** back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void* back(list* llist)
{
    if (llist->size == 0) {
      return NULL;
    } else {
      return llist->tail->data;
    }
    return NULL;
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
    if (llist->size == 1) { // if the size of the list equals to 1, empty the list
      empty_list(llist, free_func);
    } else if (llist->size > 1) { // if the size of the list is larger than 1, remove the head
      node *newHead = llist->head->next;
      newHead->prev = NULL;
      free_func(llist->head->data);
      free(llist->head);
      llist->head = newHead;
      llist->size--;
      return 0;
    }
    return -1; // if the size of the list is 0, do nothing
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
    if (llist->size == 1) { // if the size of the list equals to 1, empty the list
      empty_list(llist, free_func);
    } else if (llist->size > 1) { // if the size of the list is larger than 1, remove the head
      node *newTail = llist->tail->prev;
      newTail->next = NULL;
      free_func(llist->tail->data);
      free(llist->tail);
      llist->tail = newTail;
      llist->size--;
      return 0;
    }
    return -1; // if the size of the list is 0, do nothing
}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param llist A pointer to the linked list to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *        data that's being used in this linked list, allocating space for
  *        every part of that data on the heap. This is some function you must
  *        write yourself for testing, tailored specifically to whatever context
  *        you're using the linked list for in your test.
  * @return The linked list created by copying the old one
  */
list* copy_list(list* llist, list_cpy copy_func)
{
	list* newList = create_list();
  // iterate through the old list
  node *current = llist->head;
  while (current != NULL) {
    // put the copied element at the end of the new list 
    // so that it is in the original order
    push_back(newList, copy_func(current->data)); 
    current = current->next;
  }
	return newList;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
    return llist->size;
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
    /// @todo Implement changing the return value!
    /// @note remember to also free all nodes you remove.
    /// @note be sure to call pred_func on the NODES DATA to check if the node needs to be removed.
    /// @note free_func is a function that is responsible for freeing the node's data only.
    int num = 0;
    if (is_empty(llist)) {
      return 0;
    }
    // iterate through the list 
    node *current = llist->head;
    while (current != NULL) {
      node *prevNode = current->prev;
      node *nextNode = current->next;
      if (pred_func(current->data)) { // if pred_func returns true
        num++; // increment the number of removed nodes
        if (current == llist->head) { // if the node to be removed is in the front
          remove_front(llist, free_func);
        } else if (current == llist->tail) { // if the node to be removed is in the back
          remove_back(llist, free_func);
        } else { // if the node to be removed is in the middle
          // free the data of the current node
          free_func(current->data);
          // free the current node
          free(current);
          // redirect the prev and next pointers of the previous node and the next node
          nextNode->prev = prevNode;
          prevNode->next = nextNode;
          // decrement the size of the list
          llist->size--;
        }
      }
      // move to the next node for all cases
      current = nextNode;
    }
    return num;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
    if (llist->size == 0) {
      return 1;
    }
    return 0;
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  */
void empty_list(list* llist, list_op free_func)
{
    /// @todo Implement
    /// @note Free all of the nodes not the linked list itself.
    /// @note do not free llist.
    if (llist->size == 0) {
      return;
    }
    node *current = llist->head;
    while (current != NULL) {
      node *temp = current->next;
      free_func(current->data);
      free(current);
      current = temp;
    }
    llist->size = 0;
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
    if (llist->size == 0) {
      return;
    } 
    node *current = llist->head;
    while (current != NULL) {
      do_func(current->data);
      current = current->next;
    }
}
