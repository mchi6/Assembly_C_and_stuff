#include <stdlib.h>
#include "my_malloc.h"
#include "list.h"
#include "my_malloc.h"
#include <string.h>

// static function prototypes
static void traverse(LIST* llist);

int main() {

	printf("\nSTART TESTS!\n");
	/*~~~~~~~~~~~TEST my_malloc() and my_free()~~~~~~~~~~~*/
	// create a list
	LIST *llist = (LIST*) my_malloc(1 * sizeof(LIST));
	llist->head = NULL;
	llist->tail = NULL;
	llist->size = 0;

	// push some elements
	printf("\nTEST CASE1 [my_malloc()]: Should print series from 120 to 0, and then from 0 to 120\n");
	printf("RESULT: ");
	for (int i = 0; i <= 120; i++) {
		pushFront(llist, i);
		pushBack(llist, i);
	}
	traverse(llist);
	printf("\n\n\nTEST CASE2 [my_free()]: Should remove the first 120 elements, and print series from 0 to 120\n");
	printf("RESULT: ");
	for (int i = 0; i <= 120; i++) {
		popFront(llist);
	}
	traverse(llist);
	printf("\n\n\nTEST CASE3 my_free() then my_malloc()]: Should print the original 240 elements\n");
	printf("RESULT: ");
	for (int i = 0; i <= 120; i++) {
		pushFront(llist, i);
	}
	traverse(llist);


	/*~~~~~~~~~~~TEST my_calloc()~~~~~~~~~~~*/
	// create another linked list
	LIST *llist2 = (LIST*) my_calloc(1, sizeof(LIST));
	llist2->head = NULL;
	llist2->tail = NULL;
	llist2->size = 0;
	// push some elements
	for (int i = 0; i <= 3; i++) {
		pushFront(llist2, -i);
		pushBack(llist2, -i);
	}

	printf("\n\n\nTEST CASE4 [my_calloc()]: Should print -3 to 0, and then 0 to -3\n");
	printf("RESULT: ");
	traverse(llist2);


	/*~~~~~~~~~~~TEST my_memmove()~~~~~~~~~~~*/
	char* string1 = my_malloc(20);
	char* string2 = my_malloc(20);

	printf("\n\n\nTEST CASE5 [my_memmove()]: Should print str1: a game\tstr2: game\n");
	string1 = "a game";
	printf("RESULT: str1: %s\t", string1);
	my_memmove(string2, string1 + 2, 4);
	printf("str2: %s\n", string2);

	// free two lists
	my_free(llist);
	my_free(llist2);
	
	return 0;
}

static void traverse(LIST* llist) {
	NODE *current = llist->head;
	while (current != NULL) {
		printf("%d  ", current->data);
		current = current->next;
	}
	printf("\n");
}
