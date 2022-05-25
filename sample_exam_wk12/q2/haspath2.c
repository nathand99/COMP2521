
// BREADTH FIRST SEARCH (QUEUE)
int hasPath(Graph g, Vertex src, Vertex dest)
{
    int i = 0;
    while (i < g->nE) {
        visited[i] = -1;
    }
    
    int found = 0;
    visited[src] = src;
    Queue q = newQueue;
    visited[src] = src;
    QueueJoin(q,src);
    
    while (QueueIsEmpty && !found) {
        Item v = QueueLeave(q);
        if (v == dest) {
            found = 1;
        }
        else {
            int j = 0;
            while (j < g->nE) {
                if (adjacent(g,v,j) && visited[j] == -1) {
                    visited[j]=v;
                    JoinQueue(q, j);
                }
                j++;
            }
        }
    }
    
    if (found) {
        int number = visited[dest];
        printf("%d", dest);
        while (1 == 1) {
        printf("->");
        printf("%d", number);
        number = visited[number];
            if (number == src) {
                printf("%d\n", number);            
            }
        }
        return 1;
    }
    else {
        return 0;
    }
    
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
