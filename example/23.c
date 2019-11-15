#include <stdio.h>

int main(void)
{
  int N, i, j;
  unsigned long a = 999999999999999, b = 99999999999999;
  scanf("%d", &N);
  N = 10;
  for (i = 0; i < N / 2 + 1; i++)
  {
    printf("%d ", i);
    if (N % i == 0 && N / i + i < a + b)
    {
      a = i;
      b = N / i;
    }
  }
  printf("%d", a + b - 2);
}
