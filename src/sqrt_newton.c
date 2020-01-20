#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int sqrt_newton(int);

int main(int argc, int **argv)
{
  int i, r, r1, r2, d;

  srand(time(NULL));

  for (i = 0; i < 10; i++)
  {
    r = rand();
    printf("r = %d\n", r);
    r1 = sqrt_newton(r);
    r2 = (int)sqrt((double)r);
    d = r1 - r2;
    printf("%6d - %6d  - %d\n", r1, r2, d);
  }
  return 0;
}

int sqrt_newton(int N)
{
  int x, b, c;

  x = N / 2;
  if (x == 0)
    return (N);
  if (x < 0)
    return (-1);
  b = x;
  c = x;

  while (1)
  {
    c = b;
    b = x;
    x = (b + (N / b)) / 2;
    if (x == b)
      break;
    if (x == c)
    {
      if (b < x)
        x = b;
      break;
    }
  }
  return (x);
}

int sqrt_newton(NUMBER *a, NUMBER *b)
{
  NUMBER w, x, y, z, zero, two, temp, tukawanai;
  clearByZero(&w);
  clearByZero(&x);
  clearByZero(&y);
  clearByZero(&z);
  clearByZero(&zero);
  clearByZero(&two);
  clearByZero(&temp);
  setInt(&two, 2);

  divide(a, &two, &w, &temp); //w = a  /2
  //printf("w = ");
  //dispNumber(&w);
  //printf("\n");
  if (isZero(&w) == 1)
    copyNumber(a, b);
  if (numComp(&w, &zero) < 0)
    return -1;
  copyNumber(&w, &x); // x = w
  copyNumber(&w, &y); //y = w

  while (1)
  {
    copyNumber(&x, &y);       // y = x
    copyNumber(&w, &x);       // x = w
    divide(a, &x, &z, &temp); // z = a / x
    //printf("z = ");
    //dispNumber(&z);
    //printf("\n");
    add(&x, &z, &temp); // temp = b + z
    //printf("temp = ");
    //dispNumber(&temp);
    //printf("\n");
    divide(&temp, &two, &w, &tukawanai); // w = (b + N / b) / 2
    printf("w = ");
    dispNumber(&w);
    printf("\n\n");
    if (numComp(&w, &x) == 0)
      break;
    if (numComp(&w, &y) == 0)
    {
      printf("case1\n");
      if (numComp(&x, &w) < 0)
        copyNumber(&x, &w);
      break;
    }
  }
  printf("end\n");
  copyNumber(&w, b);
}