#include <stdio.h>

int main(int argc, char *argv[]){
  float a = 1.23456123456;
  float b = 1.23456123452;
  float c;

  c = a - b;
  printf("a = %13.20f\n", a);
  printf("b = %13.20f\n", b);
  printf("c = %13.20f\n", c);
}