
/* hasPath.c 
   Written by Ashesh Mahidadia, October 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"

//static int dfsPathCheck(Graph g,Vertex v,Vertex dest);
/* 
    You will submit only this one file.

    Implement the function "hasPath" below. Read the exam paper for 
    detailed specification and description of your task.  

    - You can add helper functions in this file, if required.  

    - DO NOT modify code in the file BSTree.h . 
    - DO NOT add "main" function in this file. 
*/


int *visited;  // array of visited

// recursive method
int hasPath(Graph g,Vertex v, Vertex dest){
   visited[v] = 1; // mark v as visited
   //printf("v is added to visied: %d\n", v);
   int w;
   for (w = 0; w < g->nV; w++) {
    //printf("helo w: %d\n", w);
        if (w == dest && adjacent(g, v, w)) {
            //printf("return (1)\n");
            return 1;
        } else if (!visited[w] && adjacent(g, v, w)) {
            //printf("hello here\n");
           if (hasPath(g,w,dest)) {
            //printf("return (2)\n");
               return 1;
           } 
        }
       
   }
   return 0;
   
}
/*
int hasPath(Graph g, Vertex src, Vertex dest) {
    
    visited[src] = 1;
    
    int j = 0;
    while (j < g->nE) {
        if (adjacent(g, src, j)) {    // for all (src, j)
            if (j == dest) {       // found edge to dest
                return 1;
            }
            else if (visited[j] != 1) {//j has not been visited then
                if (dfsPathCheck(g,j,dest)) {
                    return 1;    // found path via w to dest
                }
            }
        }
        j++;
    }
    return 0;
}
*/
