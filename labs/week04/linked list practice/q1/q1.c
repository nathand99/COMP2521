/*
 * Question 1
 * By Matthew Di Meglio 31/05/2018
 * cs2521 2018 semester 2
 * 
 * splitAtNode(l, n) should, if n is a node in the list l,
 * split the list just before the node n
 *
 * EXAMPLE 1. If
 * l -> [1] -> [1] -> [1] -> X
 *              ^
 * n -----------+
 * Then after calling splitAtNode(l, n), should have
 * l -> [1] -> X    [1] -> [1] -> X
 *                   ^
 * n ----------------+
 *
 * EXAMPLE 2. If
 * l -> [1] -> [2] -> [3] -> X
 *       ^
 * n ----+
 * Then after calling splitAtNode(l, n), should have
 * l -> X    [1] -> [2] -> [3] -> X
 *            ^
 * n ---------+
 *
 * EXAMPLE 3. If
 * l -> [1] -> [1] -> [1] -> X
 *       
 * n -> [1] -> [1] -> X
 * Then after calling splitAtNode(l, n), should have
 * l -> [1] -> [1] -> [1] -> X
 *       
 * n -> [1] -> [1] -> X
 */

#include "q1.h"

void splitAtNode(List l, Link n) {
    // if list is empty or n is NULL, return
    if (l->head == NULL) {
        return;
    }
    
    // if n is the head, nothing needs to be done
    if (n == l->head) {
        l->head = NULL;
        return;
    }
    
    // go through list until curr->next is n
    Link curr = l->head;
    while (curr->next != n) {
        // end of list reached and n is not in the list
        if (curr->next == NULL) {
            return;
        }
        curr = curr->next;
    }
    // make current(n)->next == NULL to split the list
    curr->next = NULL;
}
