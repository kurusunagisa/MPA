#include<stdio.h>
#define N 500000000

int main(int argc, char **argv){
  int i;
  double s1 = 0.0;
  double s2 = 0.0;
  double c, t, y;

  for (i = 0; i < N; i++) {
    s1 += 0.1;
  }

  c = 0.0;
  for (i = 0; i < N - 1; i++) {
    y = 0.1 - c;
    t = s2 + y;
    c = (t - s2) - y;
    s2 = t;
  }
  y = 0.1 - c;
  printf("y = %5.5lf\n", y);
  t = s2 + y;
  printf("t = %5.5lf\n", t);
  c = (t - s2) - y;
  printf("c = %5.5lf\n", c);
  s2 = t;

  printf("Simple = %23.15lf\n", s1);
  printf("Kahan = %23.15lf\n", s2);
}