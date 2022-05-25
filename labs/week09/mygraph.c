assert(g != NULL);
	
	int *visited = calloc(g->nV,sizeof(int));
	int i = 0;
    Queue q = newQueue();
    QueueJoin(q, src);
    while (!QueueIsEmpty(q)) {
      Vertex y, x = QueueLeave(q);
      path[i] = x;
      if (x == dest) {
        return i;
      }
      i++;
      if (visited[x]) continue;
      visited[x] = 1;
   //   printf("%d\n",x);
      for (y = 0; y < g->nV; y++) {
         if (g->edges[x][y] > max) continue;
         if (!g->edges[x][y]) continue;
         if (!visited[y]) QueueJoin(q,y);
         
      }  
   }
