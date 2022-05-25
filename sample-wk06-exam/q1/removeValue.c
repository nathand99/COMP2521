// removeValue.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "removeValue" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/



void removeValue(DLList L, int value){
    DLListNode *curr = L->first;
        
    // if list is empty, return
    if (L->first == NULL) {
        return;
    }
    
    // if first needs to be removed, make first->next the new first
    while (L->first != L->last && L->first->value == value) {
        DLListNode *temp = L->first;
        L->first = L->first->next;
        L->first->prev = NULL;
        free(temp);
        L->nitems--;
    }
    
    // if the only element on the list is value, free the list, if the only 
    // element on the list isn't value, return
    if (L->first == L->last && L->first->value == value) {
        free(L);
        L->first = NULL;
        L->last = NULL;
        L->curr = NULL;
        L->nitems = 0;
        return;
    } else if (L->first->next == NULL && L->first->value != value) {
        L->curr = L->first;
        return;
    }
          
    //go through list and remove nodes with "value"
    curr = L->first->next;
    while (curr -> next != NULL) {
        if (curr->value == value) {
            curr->prev->next = curr->next;
            DLListNode *temp = curr;
            curr = curr->next;
            curr->prev = temp->prev;
            free(temp);
            L->nitems--;
        } else {
            curr = curr->next;
        }
    }
    
    // now curr is at the last node, so we check that
    if (curr->value == value) {
        DLListNode *temp = curr;
        L->last = L->last->prev;
        L->last->next = NULL;
        free(temp);
        L->nitems--;
    }
    L->curr = L->first;
	return;
}



