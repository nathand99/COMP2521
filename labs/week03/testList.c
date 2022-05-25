// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

int main(int argc, char *argv[])
{
	
	// 1. Empty List 
	// (L->curr == L->first == L->last == NULL)
	// L->nitems == 0
	DLList testOneList;
	testOneList = newDLList();
	
	// 1a. Enter before on empty List
    DLListBefore(testOneList, "This is the first Line\n");
	putDLList(stdout,testOneList);
	assert(DLListLength(testOneList) == 1);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));

	// Delete to revert back to empty list
	DLListDelete(testOneList);
	assert(DLListLength(testOneList) == 0);
	assert(DLListIsEmpty(testOneList) == 1);
	
	// 1b. Enter After on empty List
	DLListAfter(testOneList, "Hello World\n");
	putDLList(stdout,testOneList);
	assert(DLListLength(testOneList) == 1);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	
	printf("Passed Test 1 (Empty List)\n");
	printf("---------------------------------------------\n");

	// 2a. Enter before on list with 1 node
	// (L->curr == L->first == L->last == Node("Hello World"))
	// L->nitems == 1
	DLListBefore(testOneList, "This is the first Line\n");
	putDLList(stdout,testOneList);
	assert(DLListLength(testOneList) == 2);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	
	// 2b. Enter After
	DLListAfter(testOneList, "This will be the third Line\n");
	putDLList(stdout,testOneList);
	assert(DLListLength(testOneList) == 3);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	
	printf("Passed Test 2 (List with 1 node)\n");
	printf("---------------------------------------------\n");
	
	//DLList myList;
	//myList = getDLList(stdin);
	//putDLList(stdout,myList);
	//assert(validDLList(myList));

	// 3a. 
	// L->first = "This is the first node"
	// L->last = "Hello World"
	// L->nitems == 3
	
	// Move to the first item and Enter before on List
	DLListMoveTo(testOneList, 1);
	DLListBefore(testOneList, "This is the new First Line\n");
	putDLList(stdout,testOneList);
	assert(DLListLength(testOneList) == 4);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	
	// 3b. Enter After 
	DLListAfter(testOneList, "This is the new second Line\n");
	putDLList(stdout,testOneList);
	assert(DLListLength(testOneList) == 5);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	
	// 3c. delete the 3rd line (which says "this is the first line")
	DLListMoveTo(testOneList, 3);
	DLListDelete(testOneList);
	putDLList(stdout,testOneList);
	assert(DLListLength(testOneList) == 4);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	
	// 3c. Insert after
	DLListAfter(testOneList, "This should be the 4th and last Line\n");
	putDLList(stdout,testOneList);
	assert(DLListLength(testOneList) == 5);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	
	
	
	printf("Passed Test 3\n");
	printf("---------------------------------------------\n");
	
	// 4a. test delete function
	// L->first = "This is the new First Line"
	// L->last = "This is the 4th and last Line"
	// L->nitems == 5
	
	// Delete last node ("Hello World")
	DLListMoveTo(testOneList, 5);
	DLListDelete(testOneList);
	putDLList(stdout,testOneList);
	assert(DLListLength(testOneList) == 4);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	
	// 4b. Delete last node again
	DLListDelete(testOneList);
	putDLList(stdout,testOneList);
	assert(DLListLength(testOneList) == 3);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	
	// 4c. Move to and delete first node
	DLListMoveTo(testOneList, 1);
	DLListDelete(testOneList);
	putDLList(stdout,testOneList);
	assert(DLListLength(testOneList) == 2);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	
	//4d. Delete first again
	DLListDelete(testOneList);
	putDLList(stdout,testOneList);
	assert(DLListLength(testOneList) == 1);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	
	//4e. Delete remaining node
	DLListDelete(testOneList);
	assert(DLListLength(testOneList) == 0);
	assert(DLListIsEmpty(testOneList) == 1);
	
	printf("Passed Test 4\n");
	printf("---------------------------------------------\n");
	
	
	
	// 5a. Testing insertion at head and at end.
    DLListAfter(testOneList, "The First Line\n");
    DLListBefore(testOneList, "This is the new First Line\n");
	assert(DLListLength(testOneList) == 2);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	
	DLListAfter(testOneList, "This is between the First Line and new First Line\n");
	DLListMoveTo(testOneList, 3);
	DLListAfter(testOneList, "Number Four Line\n");
	
	assert(DLListLength(testOneList) == 4);
	assert(DLListIsEmpty(testOneList) == 0);
	assert(validDLList(testOneList));
	putDLList(stdout,testOneList);
	
	// 5b. Deleting first node:
	DLListMoveTo(testOneList, 1);
	DLListDelete(testOneList);
	assert(DLListLength(testOneList) == 3);
	
	// 5c. Deleting second node
	DLListMoveTo(testOneList, 1);
	DLListDelete(testOneList);
	assert(DLListLength(testOneList) == 2);
	
	// 5d. Deleting another node
	DLListMoveTo(testOneList, 1);
	DLListDelete(testOneList);
	assert(DLListLength(testOneList) == 1);
	
	// 5e. Delete List
	DLListDelete(testOneList);
	assert(DLListLength(testOneList) == 0);
	assert(DLListIsEmpty(testOneList) == 1);
	
	printf("Passed Test 5\n");
	printf("All Tests Passed\n");
	
	return 0;
}


