#include<stdio.h>

struct curry {
  char name[50];
  int karasa;
  int ryou;
};

void test1(struct curry);
void test2(struct curry *);

int main(int argc, int *argv[]){
  struct curry a;

  sprintf(a.name, "boso curry");
  a.karasa = 3;
  a.ryou = 150;

  printf("\n--- before calling ---\n");
  printf("a.name = %s\n",a.name);
  printf("a,karasa = %d\n",a.karasa);
  printf("a.ryou = %d\n", a.ryou);

  test1(a);
  printf("\n--- after calling ---\n");
  printf("a.name = %s\n", a.name);
  printf("a,karasa = %d\n", a.karasa);
  printf("a.ryou = %d\n", a.ryou);
  test2(&a);

  printf("\n--- after calling ---\n");
  printf("a.name = %s\n", a.name);
  printf("a,karasa = %d\n", a.karasa);
  printf("a.ryou = %d\n", a.ryou);
  return 0;
}

void test1(struct curry c) {
  printf("\n-- Entering test1() ---\n");
  printf("c.name = %s\n", c.name);
  printf("c,karasa = %d\n", c.karasa);
  printf("c.ryou = %d\n", c.ryou);

  c.karasa = 100;
}

void test2(struct curry *c)
{
  printf("\n-- Entering test2() ---\n");
  printf("c.name = %s\n", c->name);
  printf("c,karasa = %d\n", c->karasa);
  printf("c.ryou = %d\n", c->ryou);

  c->karasa = 100;
}