#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Link {
  int hop, dest, wt;
};

struct Network {
  int H, L;
  struct Link* link;
};

int main() {
  int H, L, S, i, j;
  
  printf("Distance Vector routing using Bellman-Ford Algorithm\n");
  
  printf("Enter number of hops: ");
  scanf("%d", &H);
  
  printf("Enter number of links: ");
  scanf("%d", &L);
  
  struct Network* n = (struct Network*)malloc(sizeof(struct Network));
  n->H = H;
  // n->L = L;
  n->link = (struct Link*)malloc(n->L * sizeof(struct Link));

  for (i = 0; i < L; i++) {
    printf("\nLink %d: enter source, destination, and weight: ", i + 1);
    scanf("%d", &n->link[i].hop);
    scanf("%d", &n->link[i].dest);
    scanf("%d", &n->link[i].wt);
  }
  
  printf("Enter source node: ");
  scanf("%d", &S);
  
  int dist[H];
  for (i = 0; i < H; i++) {
    dist[i] = INT_MAX;
  }
  dist[S] = 0;

  for (i = 1; i < H; i++) {
    for (j = 0; j < L; j++) {
      int u = n->link[j].hop;  // Corrected: Assigning the correct values to u and v
      int v = n->link[j].dest;
      int wt = n->link[j].wt;
      
      if (dist[u] + wt < dist[v]) {
        dist[v] = dist[u] + wt;
      }
    }
  }
  
  // Check for negative weight cycle
  for (i = 0; i < L; i++) {
    int u = n->link[i].hop;
    int v = n->link[i].dest;
    int wt = n->link[i].wt;
    
    if (dist[u] + wt < dist[v]) {
      printf("Network contains a negative weight cycle\n");
      return 0;
    }
  }
  
  printf("\nHop\tDistance from source\n");
  for (i = 0; i < H; i++) {
    printf("%d\t%d\n", i, dist[i]);
  }
  
  return 0;
}




