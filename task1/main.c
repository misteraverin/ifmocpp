#include <stdio.h>
#include <stdlib.h>
#define MAXN int(1e2 + 10)

int main (void)
{
  //int a[MAXN][MAXN];
  int n;
  scanf("%d", &n);
  n++;
  int **a = (int **)malloc(n * sizeof(int));
  int m = n;
  for(int i = 0; i < m; i++)
     a[i] = (int *)malloc(n * sizeof(int));
 
  for(int i = 1; i < n; i++)
    for(int j = 1; j < n; j++)
      a[i][j] = i * j;
  
  int x1, y1, x2, y2;
  while(scanf("%d %d %d %d", &x1, &y1, &x2, &y2) > 0  && x1 != 0){
     for(int i = x1; i <= x2; i++){
      for(int j = y1; j <= y2; j++)
        printf("%d ", a[i][j]);
      printf("\n");
     }   
  }
  for(int i = 0; i < n; i++) 
     free(*(a + i));
  free(a);
  return 0;
}