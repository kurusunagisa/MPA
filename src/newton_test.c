#include <stdio.h>
#include <math.h>

double newton(double);
double f(double);
double fdash(double);

int main(int argc, int **argv)
{
  double x;
  double x0;
  int i;
  FILE *fp;

  for (i = -5; i < 5; i++)
  {
    x0 = (double)i;
    x = newton(x0);
    printf("x0=%10.61f,   x=%10.61f\n", x0, x);
  }

  if ((fp = fopen("test.txt", "w")) == NULL)
  {
    return -500;
  }
  for (i = -5; i < 5; i++)
  {
    x0 = (double)i;
    x = newton(x0);
    fprintf(fp, "%10.61f   %10.61f\n", x0, x);
  }

  fclose(fp);

  return 0;
}

double newton(double x0)
{
  double x;
  double b;
  double e;

  e = 1.e-7;
  x = x0;
  b = x0;

  while (1)
  {
    b = x;
    x = b - (f(b) / fdash(b));
    if (fabs(x - b) < e)
      break;
  }
  return x;
}

double f(double x)
{
  return (1 / 3) * x * x * x + 2 * x * x - 9.0 * x;
}

double fdash(double x)
{
  return x * x + 4 * x - 9.0;
}