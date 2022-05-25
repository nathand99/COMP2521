////////////////////////////////////////////////////////////////////////
// COMP2521 18x1 ... the Fury of Dracula
// Map.c: an implementation of a Map type
// You can change this as much as you want!
//
// 2017-11-30   v1.0    Team Dracula <cs2521@cse.unsw.edu.au>

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "Map.h"
#include "Places.h"

static int searchForBoatConnection (LocationID start, LocationID end);

typedef struct vNode *VList;
struct vNode {
    LocationID  v;    // ALICANTE, etc
    TransportID type; // ROAD, RAIL, BOAT
    VList       next; // link to next node
};

struct map {
    int nV; // #vertices
    int nE; // #edges
    VList connections[NUM_MAP_LOCATIONS]; // array of lists
};

static void addConnections(Map);

// Create a new empty graph (for a map)
// #Vertices always same as NUM_PLACES
Map
newMap (void)
{
    Map g = malloc (sizeof *g);
    if (g == NULL) err (EX_OSERR, "couldn't allocate Map");

    (*g) = (struct map){
        .nV = NUM_MAP_LOCATIONS,
        .nE = 0,
        .connections = { NULL }
    };

    addConnections (g);
    return g;
}

// Remove an existing graph
void
disposeMap (Map g)
{
    // wait, what?
    if (g == NULL) return;

    for (int i = 0; i < g->nV; i++) {
        VList curr = g->connections[i];
        while (curr != NULL) {
            VList next = curr->next;
            free (curr);
            curr = next;
        }
    }
    free (g);
}

static VList
insertVList (VList L, LocationID v, TransportID type)
{
    VList new = malloc (sizeof(struct vNode));
    if (new == NULL) err (EX_OSERR, "couldn't allocate vNode");

    (*new) = (struct vNode){
        .v = v,
        .type = type,
        .next = L
    };
    return new;
}

static int
inVList (VList L, LocationID v, TransportID type)
{
    for (VList cur = L; cur != NULL; cur = cur->next)
        if (cur->v == v && cur->type == type)
            return 1;

    return 0;
}

// Add a new edge to the Map/Graph
static void
addLink (Map g, LocationID start, LocationID end, TransportID type)
{
    assert (g != NULL);

    // don't add edges twice
    if (inVList (g->connections[start], end, type)) return;

    g->connections[start] = insertVList(g->connections[start],end,type);
    g->connections[end] = insertVList(g->connections[end],start,type);
    g->nE++;
}

static const char *
typeToString (TransportID t)
{
    switch (t) {
    case ROAD: return "road";
    case RAIL: return "rail";
    case BOAT: return "boat";
    default:   return "????";
    }
}

// Display content of Map/Graph
void
showMap (Map g)
{
    assert (g != NULL);

    printf ("V=%d, E=%d\n", g->nV, g->nE);
    for (int i = 0; i < g->nV; i++)
        for (VList n = g->connections[i]; n != NULL; n = n->next)
            printf ("%s connects to %s by %s\n",
                idToName (i), idToName (n->v), typeToString (n->type));
}

// Return count of nodes
int
numV (Map g)
{
    assert (g != NULL);
    return g->nV;
}

// Return count of edges of a particular type
int
numE (Map g, TransportID type)
{
    assert (g != NULL);
    assert (0 <= type && type <= ANY);

    int nE = 0;
    for (int i = 0; i < g->nV; i++)
        for (VList n = g->connections[i]; n != NULL; n = n->next)
            if (n->type == type || type == ANY)
                nE++;

    return nE;
}

// Add edges to Graph representing map of Europe
static void
addConnections (Map g)
{
#define IS_SENTINEL(x) ((x).v == -1 && (x).w == -1 && (x).t == ANY)
    for (int i = 0; ! IS_SENTINEL (CONNECTIONS[i]); i++)
        addLink (g, CONNECTIONS[i].v, CONNECTIONS[i].w, CONNECTIONS[i].t);
}


// Returns the number of direct connections between two nodes
// Also fills the type[] array with the various connection types
// Returns 0 if no direct connection (i.e. not adjacent in graph)
int connections(Map g, LocationID start, LocationID end, TransportID type[])
{
	int numConn = 0;
	int i = 0;
	int j = 0;
	assert(g != NULL);

	// start: CONNECTIONS[i].v
	// end: CONNECTIONS[i].w
	// type: CONNECTIONS[i].t

	while (CONNECTIONS[i].v != -1) {
		
		if (CONNECTIONS[i].v == start && CONNECTIONS[i].w == end) {
			type[j] = CONNECTIONS[i].t;
			j++;
			numConn++;
		} else if (CONNECTIONS[i].v == end && CONNECTIONS[i].w == start) {
			type[j] = CONNECTIONS[i].t;
			j++;
			numConn++;
		
		}
		
		i++;
	}
	
	if (searchForBoatConnection (start,end) == 1) {
		type[j] = 3;
		j++;
		numConn++;
	
	}

	//printf("Type: %d\n", CONNECTIONS[1].t);
	//printf("%d\n", start);
	//printf("%d\n", end);
	//type[1] = 1;
	//printf("%d\n", numConn);
	return numConn;
}



// Returns 1 for Same Sea and both start and end are port cities
static int searchForBoatConnection (LocationID start, LocationID end) {

    int result = 0;

    if ((start == 53 || start == 47 || start == 16 || start == 29)) {

        if ((end == 53 || end == 47 || end == 16 || end == 29)) {
	        printf("Both Cities are Port Cities in Tyrrhenian Sea\n");
	        result = 1;
        }
        
    } else if ((start == 67 || start ==6)) {

        if ((end == 67 || end == 6)) {
	        printf("Both Cities are Port Cities in Adriatic Sea\n");
	        result = 1;
        }
        
    } else if ((start == 65 || start == 3 || start == 54)) {

        if ((end == 65 || end == 3 || end == 54)) {
	        printf("Both Cities are Port Cities in Ionian Sea\n");
            result = 1;
        }

    } else if ((start == 20 || start == 66)) {
    
        if ((end == 20 || end == 66)) {
            printf("Both Cities are Port Cities in Black Sea\n");
            result = 1;
        }
        
    } else if ((start == 16 || start == 1 || start == 5 || start == 42)) {
    
        if ((end == 16 || end == 1 || end == 5 || end == 42)) {
            printf("Both Cities are Port Cities in Mediterranean Sea\n");
            result = 1;
        }
    } else if ((start == 37 || start == 15 || start == 27)) {

        if ((end == 37 || end == 15 || end == 27)) {
	        printf("Both Cities are Port Cities in Atlantic Ocean\n");
            result = 1;
        }

    } else if ((start == 21 || start == 38 || start == 61)) {

        if ((end == 21 || end == 38 || end == 61)) {
	        printf("Both Cities are Port Cities in Irish Sea\n");
            result = 1;
        }

    } else if ((start == 51 || start == 39 || start == 35)) {

        if ((end == 51 || end == 39 || end == 35)) {
	        printf("Both Cities are Port Cities in English Channel\n");
            result = 1;
        }

    }  else if ((start == 55 || start == 11 || start == 46)) {

        if ((end == 55 || end == 11 || end == 46)) {
	        printf("Both Cities are Port Cities in Bay Of Biscay\n");
            result = 1;
        }

    }   else if ((start == 22 || start == 2 || start == 31)) {

        if ((end == 22 || end == 2 || end == 31)) {
	        printf("Both Cities are Port Cities in North Sea\n");
            result = 1;
        }

    }

    return result;

}



























