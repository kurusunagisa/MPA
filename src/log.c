#include<stdio.h>
#include<math.h>

int main(void){
  double x = 0.0;
  double y = 5;
  int i;
  for(i = 0; i < 1000;i++){
    x += (2 / (2 * i + 1)) * pow((y - 1) / (y + 1), 2 * i + 1);
    printf("x = %lf\n", x);
  }
  printf("x = %lf\n", x);
  printf("log3 = %lf\n", log(y));
}