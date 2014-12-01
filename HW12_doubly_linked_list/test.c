#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores
 * Person data (name, age)
 */
typedef struct person_t
{
    char* name;
    int age;
} Person;

/* Example functions given to you. If you want to truly grasp these concepts, try
 * writing your own structs and functions as well!
 */

// Create a new Person
Person* create_person(const char* name, int age)
{
    Person* p = (Person*) malloc(sizeof(Person));
    p->name = strdup(name);
    p->age = age;
    return p;
}

// Make a deep copy of a Person
void* copy_person(const void* data)
{
    Person *p = (Person*) data;
    return create_person(p->name, p->age);
}

// Print a Person
void print_person(void* data)
{
    if (data == NULL) {
      return;
    }
    Person *p = (Person*) data;
    printf("%s, %d\n", p->name, p->age);
}

// Free a Person
void free_person(void* data)
{
    Person *p = (Person*) data;
    // free any malloc'd pointers contained in the Person struct
    free(p->name);
    free(p);
}

// Return 1 if the person's name is 8+ characters long
int long_name(const void *data)
{
	Person *p = (Person*) data;
	return strlen(p->name) > 7;
}

/* This main function does a little testing
   Like all good CS Majors you should test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void)
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();

  /* What does an empty list contain?  Lets use our handy traversal function */
  printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  traverse(llist, print_person);
	printf("\n");

 	/* Lets add a person from front and then print */
 	push_front(llist, create_person("Andrew", 24));
 	printf("TEST CASE 2\nA List with one person should print that person:\n");
 	traverse(llist, print_person);
 	printf("\n");

  
  /* Lets remove two persons from front and then print */
  remove_front(llist, free_person); // remove a list with more than 1 elements
 	remove_front(llist, free_person); // remove a list with only 1 element
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_person);
 	printf("\n");

 	/* Lets add two people and then print */
 	push_front(llist, create_person("Nick", 22));
 	push_front(llist, create_person("Randal", 21));
 	printf("TEST CASE 4\nA List with two people should print those two people:\n");
 	traverse(llist, print_person);
 	printf("\n");

	/* Lets copy this list */
	list* llist2 = copy_list(llist, copy_person);
	printf("TEST CASE 5\nA copied list should print out the same two people:\n");
 	traverse(llist2, print_person);
 	printf("\n");

  /* Lets kill the list */
  empty_list(llist, free_person);
 	printf("TEST CASE 6\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_person);
	printf("\n");

	/* Let's make a list of people, and remove certain ones! */
	/* Should remove anyone whose name is 8+ characters long */
	push_front(llist, create_person("Josephine", 27));
	push_front(llist, create_person("Dave", 34));
	push_front(llist, create_person("Benjamin", 23));
	push_front(llist, create_person("Lisa", 41));
	push_front(llist, create_person("Maximilian", 24));
	remove_if(llist, long_name, free_person);
	printf("TEST CASE 7\nShould only print 2 people with short names:\n");
	traverse(llist, print_person);
  printf("\n");
  
  /* Testing over clean up*/
  empty_list(llist, free_person);
  free(llist);
  empty_list(llist2, free_person);
  free(llist2);


  // MY TESTS!!!

  // Test case 8 -- create_list(); is_empty() and size() when the list is empty
  list* myList = create_list();
  printf("TEST CASE 8\nShould print 1 and then 0:\n");
  printf("%d\t", is_empty(myList));
  printf("%d\n", size(myList));
  printf("\n");

  // Test case 9 -- front() and back() when the list is empty
  printf("TEST CASE 9\nShould print nothing:\n");
  print_person(front(myList));
  print_person(back(myList));
  printf("\n");

  // Test case 10 -- push_front() and push_back() and traverse()
  push_front(myList, create_person("Dan", 24));
  push_back(myList, create_person("Sun", 24));
  push_front(myList, create_person("Someone", 100));
  push_back(myList, create_person("Somebody", 1));
  printf("TEST CASE 10\nShould print 4 people in the order of Someone-Dan-Sun-Somebody:\n");
  traverse(myList, print_person);
  printf("\n");

  // Test case 11 -- size() and is_empty() when the list is not empty
  printf("TEST CASE 11\nShould return 0 and then 4:\n");
  printf("%d\t", is_empty(myList));
  printf("%d\n", size(myList));
  printf("\n");

  // Test case 12 -- front() and back() when the list is not empty
  printf("TEST CASE 12\nShould print Someone then Somebody:\n");
  print_person(front(myList));
  print_person(back(myList));
  printf("\n");

  // Test case 13 -- copy_list()
  list* myListCopy = copy_list(myList, copy_person);
  printf("TEST CASE 13\nA copied list should print 4 people in the order of Someone-Dan-Sun-Somebody:\n");
  traverse(myListCopy, print_person);
  printf("\n");

  // Test case 14 -- remove_front() and remove_back() when the list is not empty
  remove_front(myList, free_person);
  remove_back(myList, free_person);
  printf("TEST CASE 13\nShould print 2 people in the order of Dan-Sun:\n");
  traverse(myList, print_person);
  printf("\n");

  // Test case 15 -- remove_if()
  push_front(myList, create_person("LLLLLLLLLLLLL", 1));
  push_front(myList, create_person("MMMMMMMMM", 1));
  push_front(myList, create_person("AAA", 3));
  push_back(myList, create_person("DDD", 5));
  push_back(myList, create_person("T", 10));
  push_back(myList, create_person("VVVVVVVVVV", 1));
  remove_if(myList, long_name, free_person);
  printf("TEST CASE 13\nShould print 5 people:\n");
  traverse(myList, print_person);
  printf("\n");

  // Test case 16 -- empty_list()
  empty_list(myList, free_person);
  printf("TEST CASE 16\nShould print nothing:\n");
  traverse(myList, print_person);
  printf("\n");

  // Test case 17 -- remove_front() and remove_back() when the list is empty
  remove_front(myList, free_person);
  remove_back(myList, free_person);
  printf("TEST CASE 17\nNo error should occur: \n");
  printf("\n");

  // Test case 18 -- push big data into the copied list to test push_front() and copy_list()
  for (int i = 0; i < 1000000; i++) {
    push_front(myListCopy, create_person("BIG", 1));
  }
  printf("TEST CASE 18\nShould print 1000004 (add a large number of data): \n");
  printf("%d\n", size(myListCopy));
  printf("\n");

  empty_list(myList, free_person);
  free(myList);

  empty_list(myListCopy, free_person);
  free(myListCopy);

  return 0;
}

