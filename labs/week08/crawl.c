// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders <vince@kyllikki.org>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <curl/curl.h>
#include "stack.h"
#include "set.h"
#include "graph.h"
#include "html.h"
#include "url_file.h"
#include "string.h"

#define BUFSIZE 1024

void setFirstURL(char *, char *);
void normalise(char *, char *, char *, char *, int);

int main(int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int  maxURLs;

	if (argc > 2) {
		strcpy(baseURL,argv[1]);
		setFirstURL(baseURL,firstURL);
		maxURLs = atoi(argv[2]);
		if (maxURLs < 40) maxURLs = 40;
	}
	else {
		fprintf(stderr, "Usage: %s BaseURL MaxURLs\n",argv[0]);
		exit(1);
	}
	
	// Set up stack
	Stack toDo = newStack();
	// add firstURL to the ToDo list
	pushOnto(toDo, firstURL);
	// initialise Graph to hold up to maxURLs
	Graph newG = newGraph(maxURLs);
	// initialise set of Seen URLs
	Set seen = newSet();
	
	
	// while (ToDo list not empty and Graph not filled) {
	while (emptyStack(toDo) == 0 && nVertices(newG) < maxURLs) {  
	printf("%d", nVertices(newG));
	    //    grab Next URL from ToDo list
	    char *next = popFrom(toDo);
	    //    if (not allowed) continue
	    if (strstr(next, "unsw") == NULL) {
	        continue;
	    }
	    
	    // Opens URL
	    URL_FILE *handle = url_fopen(next, "r");
	    //    foreach line in the opened URL 
	    //while (!url_feof(handle)) {
	    char *line;
	    printf("%d", nVertices(newG));
	    while ((line = url_fgets(next, BUFSIZE, handle)) != NULL) {
	   //     char *line = url_fgets(next, BUFSIZE, handle);
	        
	        int numInLine = 0;
            char *tmp = line;
            
            while (strstr(tmp, "href"))
            {
               char *a = strstr(tmp, "href");
               printf("%s\n", a);
               printf("%d", nVertices(newG));
               if (nVertices(newG) < maxURLs ) {
	                // Add an edge from Next to this URL
	                addEdge(newG, next, a);
	                printf("helloooooo\n");
	            }
	            if (!isElem(seen, a)) {
	            
	                // add it to the Seen set
	                insertInto(seen, a);
	                // add it to the ToDo list
	                pushOnto(toDo, a);
	            }
               numInLine++;
             //  printf("%d", numInLine);
               tmp += 16;
            }
	        
	        //printf("%d\n", numInLine);
	        // If there is more than 0 href in line
	        /*
	        while (numInLine != 0) {
	            if (nVertices(newG) < maxURLs ) {
	                // Add an edge from Next to this URL
	                addEdge(newG, next, a);
	                printf("helloooooo\n");
	            }
	            if (!isElem(seen, line)) {
	            
	                // add it to the Seen set
	                insertInto(seen, line);
	                // add it to the ToDo list
	                pushOnto(toDo, line);
	            }
	            numInLine--;
	        
	        }
	        */
	    }
	    url_fclose(handle);
	    sleep(1);
	
	}
	showGraph(newG,1);
	
		
	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list
	// initialise Graph to hold up to maxURLs
	// initialise set of Seen URLs
	// while (ToDo list not empty and Graph not filled) {
	//    grab Next URL from ToDo list
	//    if (not allowed) continue
	//    foreach line in the opened URL {
	//       foreach URL on that line {
	//          if (Graph not filled or both URLs in Graph)
	//             add an edge from Next to this URL
	//          if (this URL not Seen already) {
	//             add it to the Seen set
	//             add it to the ToDo list
	//          }
	//       }
    //    }
	//    close the opened URL
	//    sleep(1)
	// }
	if (!(handle = url_fopen(firstURL, "r"))) {
		fprintf(stderr,"Couldn't open %s\n", next);
		exit(1);
	}
	while(!url_feof(handle)) {
		url_fgets(buffer,sizeof(buffer),handle);
		//fputs(buffer,stdout);
		int pos = 0;
		char result[BUFSIZE];
		memset(result,0,BUFSIZE);
		while ((pos = GetNextURL(buffer, firstURL, result, pos)) > 0) {
			printf("Found: '%s'\n",result);
			memset(result,0,BUFSIZE);
		}
	}
	url_fclose(handle);
	sleep(1);
	return 0;
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
void setFirstURL(char *base, char *first)
{
	char *c;
	if ((c = strstr(base, "/index.html")) != NULL) {
		strcpy(first,base);
		*c = '\0';
	}
	else if (base[strlen(base)-1] == '/') {
		strcpy(first,base);
		strcat(first,"index.html");
		base[strlen(base)-1] = '\0';
	}
	else {
		strcpy(first,base);
		strcat(first,"/index.html");
	}
}

