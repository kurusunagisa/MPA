#include<stdio.h>
#include<math.h>

int main(void) {
  int n;
  long k;
  int theta = 2;
  double x = theta;
  k = 1;
  for(n = 0; n < 5;n++){
    x += x * (-pow(theta, 2)) / k;
    k = k * (k + 1) * (k + 2);
  }
  printf("sin = %100lf\n",x);
  printf("sin = %100lf\n", sin(theta));
}