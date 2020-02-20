#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *FP1, *FP2;
  int i = 0;
  char c1, c2;
  if((FP1 = fopen("output1.txt", "r")) == NULL) {
    fprintf(stderr, "cannot open the file.");
    exit(-500);
  }
  if((FP2 = fopen("output2.txt", "r")) == NULL) {
    fprintf(stderr, "cannot open the file.");
    exit(-500);
  }
  while(1) {
    c1 = fgetc(FP1);
    if((c1 >= '1' && c1 <= '9') || c1 == EOF)
      break;
  }
  while(1) {
    c2 = fgetc(FP2);
    if((c2 >= '1' && c2 <= '9') || c2 == EOF)
      break;
  }
  if(c1 != EOF && c2 != EOF) {
    while(1) {
      c1 = fgetc(FP1);
      c2 = fgetc(FP2);
      //printf("c1 = %c", c1);
      //printf("c2 = %c", c2);
      if(c1 == ' ' || c1 == '.') {
        c1 = fgetc(FP1);
      }
      if(c2 == ' ' || c2 == '.') {
        c2 = fgetc(FP2);
      }
      //printf("c1 = %c", c1);
      //printf("c2 = %c", c2);
      if(c1 == EOF || c2 == EOF || c1 != c2) {
        break;
      }
      if(c1 == c2 && c1 != ' ') {
        i++;
      } else {
        break;
      }
    }
  }
  printf("same keta = %d\n", i);
  fclose(FP1);
  fclose(FP2);
  return 0;
}