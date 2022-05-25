// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; new->nE = 0;
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
    assert(g != NULL);
     // never find a path ... you need to fix this
    int *visited = calloc(g->nV,sizeof(int));
    //int path_index;
    int path_index = 0;
    
    Queue q = newQueue();
    QueueJoin(q, src); // Add src location to queue first
    path[path_index] = src;
    path_index++;
    //path[path_index] = 21;
    //path_index++;
    // 1. Check if src == dest 
    if (src == dest) {
        
        //printf("length: %d\n", sizeof(visited)/sizeof(visited[0]));
        
    } else {
    
        // src != dest, BFS to find path
        while (QueueIsEmpty(q) != 1) {
            Vertex y = QueueLeave(q);
            Vertex x = y;
            printf("y is now: %d\n",y);

            // Check if  visited
            if (visited[x]) continue;
            visited[x] = 1;
            printf("%d\n",x);
            int nextCity = -1; // No cities yet
            int distOfNextCityToDest = -1; // No distance yet
            
            for (y = 0; y < g->nV; y++) {
            
                if (y == dest) {
                    // reached destination
                    printf("Reached Destination\n");
                    //path[path_index] = y;
                    //path_index++;
                    //break;
                }
                // no edge from x to y
                if (g->edges[x][y] == 0) {
                    printf("No edge to %d\n", y);
                } else if (visited[y] != 1 && g->edges[x][y] < max) {
                    printf("From %d to %d is %d\n", x, y, g->edges[x][y]);
                    printf("check:From %d to %d is %d\n", y, dest, g->edges[y][dest]);
                    
                    // Check and may decision where to go for shortest
                    if (nextCity == -1 && distOfNextCityToDest == -1) {
                        // Testing First City
                        nextCity = y;
                        distOfNextCityToDest = g->edges[y][dest];
                        
                        
                    } else {
                        // Test for city closer to dest 
                        
                        if (g->edges[y][dest] < distOfNextCityToDest) {
                            // Update as preferred city
                            nextCity = y;
                            distOfNextCityToDest = g->edges[y][dest];
                            printf("Found new\n");
                        }
                    }  
                }
            }
            
            printf("%d\n", path_index);
            path[path_index] = nextCity;
            path_index++;
            printf("Added a city, %d\n", nextCity);
            QueueJoin(q,nextCity);
            if (nextCity == dest) {
                // reached destination
                //printf("Reached Destination\n");
                //exit(1);
                break;
            }
        } // End of while loop
    }
    
    printf("size is: %d\n", path_index);
	
	// Returns length of path
	return path_index;
	
	
	
	
}

