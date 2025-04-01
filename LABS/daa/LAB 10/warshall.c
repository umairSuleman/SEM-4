#include<stdio.h>

void warshall(int R[][10], int n){
  for(int k=0; k<n; k++){
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        R[i][j]=(R[i][j] || ( R[i][k] && R[k][j]));
      }
    }
  }
  printf("Transitive CLosure of Graph:\n");
  for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        printf("%d\t", R[i][j]);
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

  warshall(adjMat, n);
}
