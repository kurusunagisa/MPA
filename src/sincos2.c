#include<stdio.h>
#include<math.h>

int main(void) {
  int theta = 1, i;
  int x = pow(10, 6) * (x * -pow(theta, 2) / 1);
  int k = 1;
  for(i = 0; i < 5;i++){
    x += pow(10,6) * (x * -pow(theta, 2) / k);
    k = k * (k + 1) * (k + 2);
  }
  printf("x = %d", x);
}