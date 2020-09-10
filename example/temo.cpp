#include <stdio.h>
#include<math.h>
#include<>

int main(void)
{
  unsigned long long N, i,j;
  unsigned long long a = INFINITY, b = INFINITY;
  double C;
  //scanf("%llu", &N);
  N = 10000000019;
  for (i = 1; i <= sqrt(N); i++)
  {
    C = N / i;
    if(N % i == 0){
      j = N / i;
      if(i + j < a + b - 2){
        a = i;
        b = j;
      }
    }
  }
  //printf("%llu %llu ", a, b);
  printf("%llu", a + b - 2);
}