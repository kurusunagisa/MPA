#include <stdio.h>

int main(int argc, char **argv)
{
  float x = 3.14159;
  unsigned char *p;
  int i = 0, j = 0;
  p = (unsigned char *)&x;
  while (x > 1){
    x--;
    i++;
  }
  printf("i = %d ", i);
  while(j < 10){
    x = x * 2;
    printf("%02x ", *p);
    if (x > 1) {
      x--;
    }
    j++;
  }
}