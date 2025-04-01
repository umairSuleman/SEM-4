#include<stdio.h>

int min(int a, int b){
  return a>b?b:a;
}

void floyd(int D[][10], int n){
  for(int k=0; k<n; k++){
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        D[i][j]=min(D[i][j], D[i][k]+D[k][j]);
      }
    }
  }
  printf("All Pairs of Shortest Paths:\n");
  for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        printf("%d\t", D[i][j]);
      }
      printf("\n");
  }
}

int main(){
  int n;
  printf("Enter number of nodes:");
  scanf("%d", &n);

  int adjMat[n][n];

  printf("Enter the adjacency matrix (%d x %d):\n", n, n);
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
          scanf("%d", &adj[i][j]);
      }
  }

  floyds(adjMat, n);
}
