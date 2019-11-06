#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#define KETA 30

struct NUMBER
{
  int n[KETA];
  int sign;
};
uint64_t xorshift_x;
uint64_t xorshift_y;
uint64_t xorshift_z;
uint64_t xorshift_w;

void clearByZero(struct NUMBER *);
void dispNumber(struct NUMBER *);
void setRnd(struct NUMBER *, int);
void copyNumber(struct NUMBER *, struct NUMBER *);
void getAbs(struct NUMBER *, struct NUMBER *);
int isZero(struct NUMBER *);
int mulBy10(struct NUMBER *, struct NUMBER *);
/*xorshift_function*/
void xorshiftInit(int);
uint64_t rol64(uint64_t, int);
uint64_t xorshift();


int main(int argc, char *argv[])
{
  struct NUMBER a;
  struct NUMBER b;
  /*init random fanction*/
  srandom(time(NULL));
  xorshiftInit(random() % 10000000000);
  xorshift();
  xorshift();
  xorshift();
  xorshift();

  printf("1:a = ");
  dispNumber(&a);
  printf("\n");

  /*init structure*/
  clearByZero(&a);

  printf("2:a = ");
  dispNumber(&a);
  printf("\n");

  /*set random number*/
  setRnd(&a, KETA);

  printf("3:a = ");
  dispNumber(&a);
  printf("\n");

  /*copy Number*/
  copyNumber(&a, &b);

  printf("4:a = ");
  dispNumber(&a);
  printf("\n");

  printf("5:b = ");
  dispNumber(&b);
  printf("\n");

  /*check n is Zero*/
  setRnd(&a, KETA);
  printf("%d\n", isZero(&a));

  /* left shift*/
  printf("%d\n", mulBy10(&a, &b));
  printf("a = ");
  dispNumber(&a);
  printf("\n");
  printf("b = ");
  dispNumber(&b);
  printf("\n");
  return 0;
}

void clearByZero(struct NUMBER *a)
{
  int i;

  for (i = 0; i < KETA; i++)
  {
    a->n[i] = 0;
  }
  a->sign = 1;
}

void dispNumber(struct NUMBER *a)
{
  int i;
  if (a->sign == 1)
  {
    printf("+");
  }
  else
  {
    printf("-");
  }
  for (i = 0; i < KETA; i++)
  {
    printf("%2d", a->n[i]);
  }
}

void setRnd(struct NUMBER *a, int k)
{
  int i = 0;
  for (i = KETA - k; i < KETA; i++)
  {
    a->n[i] = xorshift() % 10;
  }
  a->sign = xorshift() % 2;
}

void copyNumber(struct NUMBER *a, struct NUMBER *b)
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    b->n[i] = a->n[i];
  }
  b->sign = a->sign;
}

void getAbs(struct NUMBER *a, struct NUMBER *b)
{
  copyNumber(a, b);
  b->sign = +1;
}

int isZero(struct NUMBER *a)
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    if (a->n[i] != 0)
    {
      return -1;
    }
  }
  return 0;
}

int mulBy10(struct NUMBER *a, struct NUMBER *b)
{
  int i;
  for (i = 0; i < KETA - 1; i++)
  {
    b->n[i] = a->n[i + 1];
  }
  b->n[KETA - 1] = 0;
  if (a->n[0] != 0)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

/*xorshift_function*/
void xorshiftInit(int seed){
  seed = seed + 0x9E3779B97f4A7C15;
  seed = (seed ^ (seed) >> 30) * 0xBF58476D1CE4E5B9;
  seed = (seed ^ (seed >> 27)) * 0x94D049BB133111EB;
  seed = seed ^ (seed >> 31);
  xorshift_x = seed;
  xorshift_y = seed >> 6;
  seed = seed + 0x9FFFFFFFFFFFFFFF;
  seed = (seed ^ (seed) >> 30) * 0xBF58476D1CE4E5B9;
  seed = (seed ^ (seed >> 28)) * 0x94D049BB133111EB;
  seed = seed ^ (seed >> 31);
  xorshift_z = seed;
  xorshift_w = seed >> 6;
  printf("x y z w : %lld %lld %lld %lld\n", xorshift_x, xorshift_y, xorshift_z, xorshift_w);
}

uint64_t rol64(uint64_t x, int k)
{
  return (x << k) | (x >> (64 - k));
}

uint64_t xorshift()
{
  uint64_t result = rol64(xorshift_y * 5, 7) * 9;
  uint64_t t;
  t = xorshift_x ^ (xorshift_x << 17);
  //t = xorshift_x << 17;
  xorshift_z ^= xorshift_x;
  xorshift_w ^= xorshift_y;
  xorshift_y ^= xorshift_z;
  xorshift_x ^= xorshift_w;
  xorshift_z ^= t;
  //w ^= t ^ (t >> 8) ^ (w >> 19);
  xorshift_w = rol64(xorshift_w, random() % 5 + 40);
  //printf("result = %lld\n", result);
  return result;
}