#include <stdio.h>
#include <stdlib.h>


int main () {

  int N, K;

  scanf("%d", &N);
  scanf("%d", &K);

  int A[N+1];

  for (int i =1; i < N+1; i++){
    scanf("%d", &A[i]);
    if (A[i] == K){
      printf("%d\n", 1);
      return 0;
    }
  }



  return 0;

}
