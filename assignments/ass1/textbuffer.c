#include <stdlib.h>
#include "textbuffer.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

//z5204935

// This program is an implmentation of a textbuffer ADT using linked lists

// structure of a textbuffer
// textbuffer * = TB
struct textbuffer {
    struct textbufferNode *head;    // first element of list
    struct textbufferNode *tail;    // last element of list
    int size;                       // number of items in list (0 for empty list)
};

// textbuffer node
struct textbufferNode {
    char *buffer;                       // buffer to store line of characters in
    int line;                           // line number - starting at 0
    struct textbufferNode *next;        // next node 
};

// print
/*
static void print (TB tb) {
    struct textbufferNode *curr = tb->head;
    while (curr != NULL) {
        printf("&&%s&&", curr->buffer);
        curr = curr->next;
    }
}
*/
/*
static void printm (Match tb) {
    Match curr = tb;
    while (curr != NULL) {
        printf("&&%d&&", curr->lineNumber);
        curr = curr->next;
    }
}
*/

// create a new, empty textbuffer
static TB newEmptyTB (void) {
    TB new;
    new = malloc(sizeof (struct textbuffer));   //create a new textbuffer struct
	assert (new != NULL);   // assert malloc worked
	new->head = NULL;
	new->tail = NULL;
	new->size = 0;
	return new;
}

// create new text buffer node initialised with text passed in
static struct textbufferNode *newNode (char text[]) {
    struct textbufferNode *new_node;
    // allocate size for a textbuffer node
	new_node = malloc(sizeof (struct textbufferNode));
	if (new_node == NULL) {
	    printf("Malloc failed");
	    abort();
	}
	// allocate size of string passed in
	new_node->buffer = strdup(text);
	new_node->line = 0; //this will be changed by caller
	new_node->next = NULL;
	return new_node;
}

// put ascending line numbers starting from 0 in a textbuffer

static void line_numbers(TB tb) {
    int line_number = 0;
    struct textbufferNode *curr = tb->head;
    tb->size = 0;
    while (curr != NULL) {
        curr->line = line_number;
        if (curr->next == NULL) {
            tb->tail = curr;
        }
        line_number++;
        tb->size++;
        curr = curr->next;
    }
}

TB newTB (char text[]) {
    TB new = newEmptyTB(); // create empty text buffer	
	char *chunk;
	char *input = text; // copy text into input
	int line_counter = 0;
	
	// if input is just a newline, make a TB with just a newline
	if (strcmp(input, "\n") == 0) {
	    struct textbufferNode *line = newNode(input);
        new->head = line;
        new->tail = line;
        line->line = line_counter;
        new->size = 1;
        line->next = NULL;
        return new;
    }
	// go through the text array and each time you hit \n, put it in a new textbufferNode
	// stop when we hit a null terminator
	while (strcmp(chunk = strsep(&input,"\n"),"\0") != 0) {
        if (new->head == NULL) {
            // if list is empty
            struct textbufferNode *line = newNode(chunk);
            new->head = line;
            new->tail = line;
            line->line = line_counter;
            new->size = 1;
            line->next = NULL;
        } else {
            //adding on to the end of list
            struct textbufferNode *line = newNode(chunk);            
            new->tail->next = line;
            new->tail = line;
            new->size = new->size + 1;
            line->line = line_counter;
            line->next = NULL;
        }   
        line_counter++;
    }	
	return new;
}

/* Free the memory occupied by the given textbuffer.  It is an error to access
 * the buffer afterwards.
 */
void releaseTB (TB tb) {
    // buffer is empty
    if (tb == NULL) {
        return;
    }

    // go through TB, freeing each text buffer component and node
    struct textbufferNode *curr = tb->head;
    while (curr != NULL) {
        struct textbufferNode *temp = curr;
        curr = curr->next;
        assert(temp != NULL);
        free(temp->buffer);
        free(temp);
    }
}

/* Allocate and return an array containing the text in the given textbuffer.
 * add a prefix corrosponding to line number iff showLineNumbers == TRUE
 */
char *dumpTB (TB tb, int showLineNumbers) {
    int size = 0;
    int added_size = 0;
    char *dump = "\0";
    char *temp = "\0";
    
    if (tb == NULL) {
        char *null = "\0";
        size = strlen(null);
        dump = malloc(size);
        if (dump == NULL) {
	    printf("Malloc failed");
	    abort();
	    }
        strcpy(dump, "\0");
        return dump;
    }
    
    struct textbufferNode *curr = tb->head;
    while (curr != NULL) {
        if (showLineNumbers) {
            if (curr == tb->head) {
                assert(curr->buffer != NULL);
                added_size = strlen(curr->buffer);
                temp = malloc(added_size + 1);
                if (temp == NULL) {
	                printf("Malloc failed");
	                abort();
	            }
                temp = strcpy(temp, curr->buffer);
                dump = malloc(added_size + 8);
                if (dump == NULL) {
	                printf("Malloc failed");
	                abort();
	            }
                sprintf(dump, "%d. %s\n", curr->line + 1, temp);
                free(temp);
                
            }
            else {                
                size = strlen(dump);
                added_size = strlen(curr->buffer);
                // allocate size for contents of the array + contents of buffer + newline
                dump = realloc(dump, size + added_size + 10);
                temp = malloc(added_size + 1);
                if (temp == NULL) {
	                printf("Malloc failed");
	                abort();
	            }
                strcpy(temp, curr->buffer);
                sprintf(dump, "%s%d. %s\n", dump, curr->line + 1, temp);
                free(temp);
            }
        }         
        else {
            if (curr == tb->head) {
                added_size = strlen(curr->buffer);
                dump = malloc(added_size + 3);
                if (dump == NULL) {
	                printf("Malloc failed");
	                abort();
	            }
                dump = strcpy(dump, curr->buffer);
                sprintf(dump, "%s\n", dump);
            }
            else { 
                //assert(curr->buffer != NULL);
                size = strlen(dump);
                added_size = strlen(curr->buffer);
                // allocate size for contents of the array + contents of buffer + newline
                dump = realloc(dump, size + added_size + 3);
                dump = strcat(dump, curr->buffer);
                sprintf(dump, "%s\n", dump);
            }
        
        }
        curr = curr->next;
    }    
	return dump;
}

/* Return the number of lines of the given textbuffer.
 */
int linesTB (TB tb){
	return tb->size;
}

/* Add a given prefix to all lines between AND INCLUDING pos1 and pos2
 *
 * - The program is to abort() with an error message if line 'pos1' or line
 *   'pos2' is out of range.  The first line of a textbuffer is at position 0.
 */
void addPrefixTB (TB tb, int pos1, int pos2, char * prefix) {
    // if pos2 is less than pos1, abort
    // if pos1 or pos2 are incorrect, abort
    if (pos2 < pos1 || pos1 < 0 || (pos2 > tb->size)) {
        printf("Invalid pos1 or pos2");
        abort();
    }
    // input string is NULL
    if (prefix == NULL) {
        printf("Invalid prefix: prefix = NULL");
        abort();
    }
    // input string is the empty string - do nothing
    if (strcmp(prefix, "") == 0) {
        return;
    }
    // create a pointer and move it to pos 1
    struct textbufferNode *curr = tb->head;
    while (curr != NULL) {
        if (curr->line == pos1) {
            break;
        }
        curr = curr->next;
    }
    int size = 0;
    int added_size = 0;
    char *tem1;
   
    // curr is now at pos1
    // go through adding prefixes until after pos2
    while ((curr != NULL) && (curr->line != (pos2 + 1))) {
        // allocate size of prefix + buffer
        assert(curr->buffer != NULL);
        tem1 = curr->buffer;
        size = strlen(tem1);
        added_size = strlen(prefix);
        char temp[size + added_size + 1];
        strcpy(temp, curr->buffer);
        curr->buffer = realloc(curr->buffer, size + added_size + 1);
        // add curr->buffer onto the end of the prefix and
        // put the prefix + curr->buffer into the textbuffer
        snprintf(curr->buffer, size + added_size + 1, "%s%s", prefix, temp);
        curr = curr->next;        
    }
    //print(tb);
}

/* Merge 'tb2' into 'tb1' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' can not be used anymore (as if we had used
 *   releaseTB() on it).
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
 
void mergeTB (TB tb1, int pos, TB tb2){
    // invalid pos
    if ((pos < 0) || (pos > tb1->size)) {
        printf("Invalid pos");
        abort();
    }
    // if tb1 = tb2, do nothing
    if (tb1 == tb2) {
        return;
    }
    // if tb1 is empty, merge by making tb1 tb2
    if (tb1 == NULL) {
        tb1 = tb2;
        return;
    }
    // if tb2 is empty, nothing is to be merged, so return
    if (tb2 == NULL) {
        return;
    }
    
    struct textbufferNode *curr = tb1->head;
    struct textbufferNode *temp_pointer;
    
    // if pos == 0
    if (tb1->head->line == pos) {
        temp_pointer = tb1->head;
        tb1->head = tb2->head;
        tb2->tail->next = temp_pointer;
        
        // make line numbers correct in merged list tb1
        line_numbers(tb1);
    }
    // merging onto the end
    else if (tb1->size == pos) {
        tb1->tail->next = tb2->head;
        tb1->tail = tb2->tail;
        
        // make line numbers correct in merged list tb1
        line_numbers(tb1);
    }
    // move to the node before pos in tb1 and link in tb2
    else {   
        while (curr->next->line != pos) {
            curr = curr->next;
        }
        
        temp_pointer = curr->next;
        curr->next = tb2->head;
        tb2->tail->next = temp_pointer;
        
        // make line numbers correct in merged list tb1
        line_numbers(tb1);
    }  
    // tb2 cannot be used anymore so free it    
    free(tb2);
    //print(tb1);
}

/* Copy 'tb2' into 'tb1' at line 'pos'.

 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' is unmodified and remains usable independent
 *   of 'tb1'.
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void pasteTB (TB tb1, int pos, TB tb2) {
    // invalid pos
    if ((pos < 0) || (pos > tb1->size)) {
        printf("Invalid pos");
        abort();
    }
    // if tb1 = tb2, do nothing
    if (tb1 == tb2) {
        return;
    }
    
    struct textbufferNode *curr = tb1->head;
    struct textbufferNode *temp_pointer;
//    struct textbufferNode *tb2p = tb2->head;
//    int lines = 0;
    char *s = dumpTB(tb2, FALSE);
    TB tb3 = newTB(s);
    assert(tb3 != NULL);
    // pos = 0
    if (tb1->head->line == pos) {     
        temp_pointer = tb1->head;
        tb1->head = tb3->head;
        struct textbufferNode *tb3_curr = tb3->head;
        struct textbufferNode *tb3_prev = tb3->head;
        while (tb3_curr != NULL) {
            tb3_prev = tb3_curr;
            tb3_curr = tb3_curr->next;
        }
        tb3_prev->next = temp_pointer;
        
        // make line numbers correct in merged list tb1
        line_numbers(tb1);
    }
    // merging onto the end
    else if (tb1->size == pos) {
        tb1->tail->next = tb3->head;
        // make line numbers correct in merged list tb1
        line_numbers(tb1);
    }
    // move to the node before pos in tb1 and link in tb2
    else {   
        while (curr->line != pos - 1) {
            curr = curr->next;
        }                
        temp_pointer = curr->next;
        curr->next = tb3->head;
        struct textbufferNode *tb3_curr = tb3->head;
        struct textbufferNode *tb3_prev = tb3->head;
        while (tb3_curr != NULL) {
            tb3_prev = tb3_curr;
            tb3_curr = tb3_curr->next;
        }
        tb3_prev->next = temp_pointer;
       
        // make line numbers correct in merged list tb1
        line_numbers(tb1);
    }  
}

/* Cut the lines between and including 'from' and 'to' out of the textbuffer
 * 'tb'.
 *
 * - The result is a new textbuffer (much as one created with newTB()).
 * - The cut lines will be deleted from 'tb'.
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range.
 */
TB cutTB (TB tb, int from, int to){
    // if to < from, return NULL
    if (to < from) {
        return NULL;
    }    
    // invalid to or from
    if (from < 0 || to > tb->size) {
        printf("Invalid to or from");
        abort();
    }
    // goto position before from
    struct textbufferNode *curr = tb->head;
    struct textbufferNode *from_pointer;
    
    TB new = newEmptyTB();
    struct textbufferNode *new_curr = new->head;
    struct textbufferNode *temp;
    int line_counter = 0;
    
        
    // if we are cutting the whole list
    if (from == 0 && to == tb->size - 1) {
        char *s = dumpTB(tb, FALSE);
        TB new1 = newTB(s);
        deleteTB (tb, from, to);
        //tb = NULL;
        
    //   new = tb;
       // tb->head = NULL;
     //   print(new1);
        return new1;
    }
    
    // if from is the first line, goto to
    if (from == 0) {         //curr->line == from
        while ((curr != NULL) && (curr->line != (to + 1))) {
            if (new->head == NULL) {
                new->head = newNode(curr->buffer);
                new->head->line = line_counter;
                new_curr = new->head;
                new->tail = new->head;
                new->size = 1;
                line_counter++;                
                new_curr->next = NULL;
            }
            else {
                temp = newNode(curr->buffer);
                new_curr->next = temp;
                new_curr = temp;
                new_curr->line = line_counter;
                new->tail = new_curr;
                new_curr->next = NULL;
                new->size++;
                line_counter++;
            }            
            curr = curr->next;
        }
      //  print(new);
        
        tb->head = curr;
     //   print(tb);
        // make line numbers correct in remaining list tb if its not NULL
        if (tb->head != NULL) {
            line_numbers(tb);
        }
    }
    // from is not the first line
    // move to the node before from
    else {
        while (curr->line != (from - 1)) {
            curr = curr->next;
        }
        from_pointer = curr;
        
        curr = curr->next;
        // continue moving curr through the list until to
        while ((curr != NULL) && (curr->line != (to + 1))) {
            if (new->head == NULL) {
                new->head = newNode(curr->buffer);
                new->head->line = line_counter;
                new->tail = new_curr;
                new->size++;
                line_counter++;
                new_curr = new->head;
            }
            else {
                temp = newNode(curr->buffer);
                new_curr->next = temp;
                new_curr = new_curr->next;
                new_curr->line = line_counter;
                new->tail = new_curr;
                new->size++;
                line_counter++;
            }          
            
            curr = curr->next;
        }


        from_pointer->next = curr;
        
        // make line numbers correct in remaining list tb
        line_numbers(tb);
    }
    //print(new);
	return new;
}

/*  Return a linked list of Match nodes of all the matches of string search
 *  in tb
 *
 * - The textbuffer 'tb' will remain unmodified.
 * - The user is responsible of freeing the returned list
 */
 // incomplete
Match searchTB (TB tb, char * search) {
    if (search == NULL) {
        printf("Search == NULL");
        abort();
    }   
        
    Match first = NULL; 
    struct textbufferNode *curr = tb->head;
    char *needle;
    int line_number = 0;
    while (curr != NULL) {
        if ((needle = strstr(curr->buffer, search)) != NULL) {
            
            char *finder = &curr->buffer[0];
            int i = 0;
            while (finder != '\0' && i < strlen(search)) {
                if (&finder == &needle) {
                    if (first == NULL) {
                        // first match
                        first = malloc(sizeof(matchNode));
                        if (first == NULL) {
	                        printf("Malloc failed");
	                        abort();
	                    }
                        first->lineNumber = line_number;
                        first->charIndex = i;
                        first->next = NULL;
                        line_number++;                        
                    }
                    else {
                        // goto the the last match and append the list
                        while (first->next != NULL) {
                            first = first->next;
                        }
                        Match node = malloc(sizeof(matchNode));
                        if (node == NULL) {
	                        printf("Malloc failed");
	                        abort();
	                    }
                        first->next = node;
                        node->lineNumber = line_number;
                        node->charIndex = i;
                        node->next = NULL;
                        line_number++; 
                    }
                }
                finder++;
                i++;
            }
        }
        curr = curr->next;
    }
    return first;
}

/* Remove the lines between and including 'from' and 'to' from the textbuffer
 * 'tb'.
 *
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range.
 */
void deleteTB (TB tb, int from, int to){
    // invalid to or from
    if (from > to || from < 0 || to > tb->size) {
        printf("Invalid to or from");
        abort();
    }

    // goto position before from
    struct textbufferNode *curr = tb->head;
    struct textbufferNode *from_pointer;
    
    // if from is the first line, goto 1 past to
    if (curr->line == from) {
        while (curr != NULL && curr->line != to + 1) {
            curr = curr->next;
        }        
        tb->head = curr;
        
        // make line numbers correct in remaining list tb
        line_numbers(tb);
    }
    // from is not the first line
    // move to the node before from
    else {
        while (curr->line != from - 1) {
            curr = curr->next;
        }
        from_pointer = curr;
        
        // continue moving curr through the list until to
        while (curr != NULL && curr->line != to + 1) {
            curr = curr->next;
        }
        
        from_pointer->next = curr;
        
        // make line numbers correct in remaining list tb
        line_numbers(tb);
    }
}


/* Search every line of tb for each occurrence of a set of specified subsitituions
 * and alter them accordingly
 *
 * refer to spec for table.
 */
 // incomplete
void formRichText (TB tb){
  //  char *dump = "\0";
    char *temp = "\0";
    int size = 0;
//    char matcher;
 //   int start;
 //   int end;
    struct textbufferNode *curr = tb->head;
    while (curr != NULL) {
        int i = 0;
        // go through loop and look for *, _ or # (# must be at the start)
        while (curr->buffer[i] != '\0') {
            if (curr->buffer[i] == '*' || curr->buffer[i] == '_') {
            //    matcher = curr->buffer[i];
             //   start = i;
            }
            else if (curr->buffer[0] == '#') {
                size = strlen(curr->buffer);
                temp = strcpy(temp, curr->buffer);
                curr->buffer = realloc(curr->buffer, size + 10);
                sprintf(curr->buffer, "<h1>%s<h1>", temp);
                printf("%s", curr->buffer);
                goto end;
            }
            else {
                //stuff
            }
            i++;
        }
        
        // now look for concluding, matching special character
        // if there isnt one, we have to go back to the start of the buffer and find the
        // special character after the one that didnt have a concluding character
        i++;
        /*
        while (curr->buffer[i] != '\0') {
             if (curr->buffer[i] == matcher) {
                end = i;
             
             }
             i++;
        }
        */
        end:
        curr = curr->next;
    }

}
/* Your whitebox tests
 */
void whiteBoxTests() {
    /* TEST newTB */    
    char line1[] = "Hi\nhow\nare\nthings\n\0";
    TB tb1 = newTB(line1);
    
    struct textbufferNode *node0 = tb1->head;
    struct textbufferNode *node1 = tb1->head->next;
    struct textbufferNode *node2 = tb1->head->next->next;
    struct textbufferNode *node3 = tb1->head->next->next->next;
    
    assert(tb1->size == 4);
    assert(node0 == tb1->head);
    assert(node3 == tb1->tail);
    
    assert(node0->line == 0);
    assert(node0 == tb1->head);
    assert(strcmp(node0->buffer, "Hi") == 0);
    
    assert(node1->line == 1);
    assert(node1 == tb1->head->next);
    assert(strcmp(node1->buffer, "how") == 0);
    
    assert(node2->line == 2);
    assert(node2 == tb1->head->next->next);
    assert(strcmp(node2->buffer, "are") == 0);
    
    assert(node3->line == 3);
    assert(node3 == tb1->head->next->next->next);
    assert(strcmp(node3->buffer, "things") == 0);
    
    char line2[] = "\n\0";
    TB tb2 = newTB(line2);    
    struct textbufferNode *line2_node0 = tb2->head;
     
    assert(tb2->size == 1);
    assert(line2_node0 == tb2->head);
    assert(line2_node0 == tb2->tail);
    
     char line3[] = "\0";
     TB tb3 = newTB(line3);
     assert(tb3->size == 0);
     
    /* TEST linesTB */     
    assert(linesTB(tb1) == 4);
    assert(linesTB(tb2) == 1);
    
    /* TEST dumpTB */
    // without showLineNumbers
    char *dump1 = dumpTB (tb1, FALSE);
    assert(strcmp(dump1, "Hi\nhow\nare\nthings\n\0") == 0);
    // with showLineNumbers
    char *dump12 = dumpTB (tb1, TRUE);
    assert(strcmp(dump12, "1. Hi\n2. how\n3. are\n4. things\n\0") == 0);
    
    // without showLineNumbers - will put another newline on the end
    char *dump2 = dumpTB (tb2, FALSE);
    assert(strcmp(dump2, "\n\n\0") == 0);
    // with showLineNumbers
    char *dump22 = dumpTB (tb2, TRUE);
    assert(strcmp(dump22, "1. \n\n\0") == 0);
    
    // without showLineNumbers
    char *dump3 = dumpTB(tb3, FALSE);
    assert(strcmp(dump3, "\0") == 0);
    // with showLineNumbers - should be the same since its an empty TB
    char *dump32 = dumpTB(tb3, TRUE);
    assert(strcmp(dump32, "\0") == 0);
    
    /* TEST addPrefixTB */ 
    // adding a prefix to the first 3 nodes of the textbuffer
    addPrefixTB (tb1, 0, 2, "prefix ");
    assert(node0->line == 0);
    assert(node0 == tb1->head);
    assert(strcmp(node0->buffer, "prefix Hi") == 0);
    
    assert(node1->line == 1);
    assert(node1 == tb1->head->next);
    assert(strcmp(node1->buffer, "prefix how") == 0);
    
    assert(node2->line == 2);
    assert(node2 == tb1->head->next->next);
    assert(strcmp(node2->buffer, "prefix are") == 0);
    
    assert(node3->line == 3);
    assert(node3 == tb1->head->next->next->next);
    assert(strcmp(node3->buffer, "things") == 0);
    
    //assert the nodes have no changed memory address
    assert(node0 == tb1->head);
    assert(node1 == tb1->head->next);
    assert(node2 == tb1->head->next->next);
    assert(node3 == tb1->head->next->next->next);
    
    /* TEST mergeTB */ 
    char line4[] = "Im\ngood\nthanks\n\0";
    char line5[] = "Random\nwords\n\0";
    TB tb4 = newTB(line4);
    TB tb5 = newTB(line5);
    // marging tb4 into tb5 at line 1
    mergeTB (tb5, 1, tb4);

    struct textbufferNode *merge0 = tb5->head;
    struct textbufferNode *merge1 = tb5->head->next;
    struct textbufferNode *merge2 = tb5->head->next->next;
    struct textbufferNode *merge3 = tb5->head->next->next->next;
    struct textbufferNode *merge4 = tb5->head->next->next->next->next;
    
    
    assert(tb5->size == 5);
    
    assert(strcmp(merge0->buffer, "Random") == 0);
    assert(merge0->next == merge1);
    
    assert(strcmp(merge1->buffer, "Im") == 0);
    assert(merge1->next == merge2);
    
    assert(strcmp(merge2->buffer, "good") == 0);
    assert(merge2->next == merge3);
    
    assert(strcmp(merge3->buffer, "thanks") == 0);
    assert(merge3->next == merge4);
    
    assert(strcmp(merge4->buffer, "words") == 0);
    assert(merge4 == tb5->tail);    
 
    /* TEST pasteTB */ 
    
    char line6[] = "Im\ngood\nthanks\nfor\nasking\n\0";
    char line7[] = "Random\nwords\n\0";
    TB tb6 = newTB(line6);
    TB tb7 = newTB(line7);
    pasteTB (tb6, 3, tb7);

    struct textbufferNode *paste0 = tb6->head;
    struct textbufferNode *paste1 = tb6->head->next;
    struct textbufferNode *paste2 = tb6->head->next->next;
    struct textbufferNode *paste3 = tb6->head->next->next->next;
    struct textbufferNode *paste4 = tb6->head->next->next->next->next;
    struct textbufferNode *paste5 = tb6->head->next->next->next->next->next;
    struct textbufferNode *paste6 = tb6->head->next->next->next->next->next->next;
    
        
    assert(tb6->size == 7);
    
    assert(strcmp(paste0->buffer, "Im") == 0);
    assert(paste0->next == paste1);
    
    assert(strcmp(paste1->buffer, "good") == 0);
    assert(paste1->next == paste2);
    
    assert(strcmp(paste2->buffer, "thanks") == 0);
    assert(paste2->next == paste3);
    
    assert(strcmp(paste3->buffer, "Random") == 0);
    assert(paste3->next == paste4);
    
    assert(strcmp(paste4->buffer, "words") == 0);
    assert(paste4->next == paste5);
    
    assert(strcmp(paste5->buffer, "for") == 0);
    assert(paste5->next == paste6);
    
    assert(strcmp(paste6->buffer, "asking") == 0);
    assert(paste6 == tb6->tail);
    
    // ensure that tb7 is unchanged by pasteTB
    assert(tb7->size == 2);
    assert(strcmp(tb7->head->buffer, "Random") == 0);
    assert(tb7->head->next == tb7->tail);
    assert(strcmp(tb7->head->next->buffer, "words") == 0);
    
    /* TEST cutTB */ 
    char line8[] = "This\nis\na\ntext\nbuffer\n\0";
    TB tb8 = newTB(line8);
    TB tb9 = cutTB(tb8, 0, 2);
    
    // this should cut "This is a" into tb9 and leave "text buffer" in line8
    struct textbufferNode *cut80 = tb8->head;
    struct textbufferNode *cut81 = tb8->head->next;
    
    struct textbufferNode *cut90 = tb9->head;
    struct textbufferNode *cut91 = tb9->head->next;
    struct textbufferNode *cut92 = tb9->head->next->next;
   
    assert(tb8->size == 2);
    assert(strcmp(cut80->buffer, "text") == 0);
    assert(cut80->next == cut81);
    
    assert(strcmp(cut81->buffer, "buffer") == 0);
    assert(tb8->tail == cut81);
    
    assert(tb9->size == 3);
    assert(strcmp(cut90->buffer, "This") == 0);
    assert(cut90->next == cut91);
    
    assert(strcmp(cut91->buffer, "is") == 0);
    assert(cut91->next == cut92);
    
    assert(strcmp(cut92->buffer, "a") == 0);
    assert(tb9->tail == cut92);
    
    
    /* TEST deleteTB */ 
    char line9[] = "This\nis\nanother\ntext\nbuffer\nfor\nthe\nsecond\time\n\0";
    TB tb10 = newTB(line9);
    deleteTB(tb10, 5, 8);
    
    // delete "for the second time"
    struct textbufferNode *delete0 = tb10->head;
    struct textbufferNode *delete1 = tb10->head->next;
    struct textbufferNode *delete2 = tb10->head->next->next;
    struct textbufferNode *delete3 = tb10->head->next->next->next;
    struct textbufferNode *delete4 = tb10->head->next->next->next->next;

    assert(tb10->size == 5);
    assert(strcmp(delete0->buffer, "This") == 0);
    assert(delete0->next == delete1);
    
    assert(strcmp(delete1->buffer, "is") == 0);
    assert(delete1->next == delete2);
    
    assert(strcmp(delete2->buffer, "another") == 0);
    assert(delete2->next == delete3);
    
    assert(strcmp(delete3->buffer, "text") == 0);
    assert(delete3->next == delete4);
    
    assert(strcmp(delete4->buffer, "buffer") == 0);
    assert(delete4 == tb10->tail);
    
    /* TEST searchTB */ 
    /*
    char line10 [] = "Hello there";
    TB tb11 = newTB(line10);
    Match node = searchTB(tb11, "there");
    assert(node->lineNumber == 2);
    assert(node->charIndex == 0);
    */
    
    /* TEST formrichtext */ 
    /*
    char line11 [] = "#Hello there";
    TB tb12 = newTB(line11);
    formRichText(tb12);
    char *dumprichtext = dumpTB(tb12, FALSE);
    assert(strcmp(dumprichtext,"<h1>Hello there<h1>" ) == 0);
    */
}
