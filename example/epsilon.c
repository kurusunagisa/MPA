#include <stdio.h>
#include <float.h>

int main(int argc, char **argv)
{
  float e = 1.0;
  while (1)
  {
    e = e / 2.0f;
    if (1.0f + e == 1.0f)
    {
      printf("e = %.50f\n", e);
      break;
    }
  }
  printf("FLT_EPSILON = %.50f\n", FLT_EPSILON);

  double ed = 1.0;
  while (1)
  {
    ed = ed / 2.0;
    if (1.0 + ed == 1.0)
    {
      printf("ed = %.60lf\n", ed);
      break;
    }
  }
  printf("DBL_IPSILON = %.60lf\n", DBL_EPSILON);
}