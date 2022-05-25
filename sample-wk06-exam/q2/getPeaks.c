// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/

DLList getPeaks(DLList L){

	DLList peaksL = newDLList();
    
    if (L->first->next == NULL) {
        return peaksL;
    }
    
    DLListNode *curr = L->first->next;
    while (curr->next != NULL) {
        if (curr->value > curr->prev->value && curr->value > curr->next->value) {
            if (peaksL->first == NULL) {
                peaksL->first = newDLListNode(curr->value);
                peaksL->curr = peaksL->first;
            } else { 
                peaksL->curr->next = newDLListNode(curr->value);
                peaksL->curr->next->prev = peaksL->curr;
                peaksL->curr = peaksL->curr->next;
            }
            peaksL->nitems++;
        }
        curr = curr->next;
    }
    peaksL->last = peaksL->curr;
    
    //DLListNode *newDLListNode(int val)
	return peaksL;

}



