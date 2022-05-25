/*
 * Question 2
 * By Zain Afzal 11/08/2018
 * cs2521 2018 semester 2
 * 
 * isPalindrome is a function that takes in a 
 * doubily linked list where each node stores a single 
 * character, i.e 
 *           
 *                 __head___[L]___tail__	
 *                /                     \
 *               v                       v
 *         X <- 'a' <-> 'b' <-> 'c' <-> 'd' -> X
 *
 * And returns true of the word formed by the characters 
 * is a palindrome and false otherwise. i. 
 * 
 * "aaa" -> TRUE   (aaa == aaa)
 * "aba" -> TRUE   (aba == aba)
 * "abb" -> FALSE  (abb != bba)
 * "a"   -> TRUE   (a == a)
 * ""    -> TRUE   ("" == "") (an empty string is said to be a palindrome)
 * 
 * you can assume each character is only a-z lower case.
 * 
 * The original linked list should _NOT_ be altered in any way. 
 */

#include "q2.h"

int isPalindrome(List l) {
	// if list is empty or there is one element in the list, return TRUE
	if (l->head == NULL || l->head->next == NULL) {
	    return TRUE;
	}
	// make a pointer to the head and one at the end
	Link start = l->head;
	Link end = l->tail;
	
	// compare the value at each end of the list, if they are not the same
	// return FALSE
	while (start != NULL && end != NULL) {
	    if (start->value != end->value) {
	        return FALSE;
	    }
	    start = start->next;
	    end = end->prev;
	}
	return TRUE;
}

