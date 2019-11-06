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

void clearByZero(struct NUMBER *);
void dispNumber(struct NUMBER *);
void setRnd(struct NUMBER *, int);
void copyNumber(struct NUMBER *, struct NUMBER *);
void getAbs(struct NUMBER *, struct NUMBER *);
int isZero(struct NUMBER *);
int mulBy10(struct NUMBER *, struct NUMBER *);
uint32_t xorshift();

int main(int argc, char *argv[])
{
  struct NUMBER a;
  struct NUMBER b;
  srandom(time(NULL));
  //RAND_priv_bytes(time(NULL));

  printf("a = ");
  dispNumber(&a);
  printf("\n");

  clearByZero(&a);

  printf("a = ");
  dispNumber(&a);
  printf("\n");

  setRnd(&a, KETA);

  printf("a = ");
  dispNumber(&a);
  printf("\n");

  copyNumber(&a, &b);
  a.sign = (a.sign + 1) % 2;

  printf("a = ");
  dispNumber(&a);
  printf("\n");

  copyNumber(&a, &b);

  printf("b = ");
  dispNumber(&b);
  printf("\n");

  setRnd(&a, KETA);
  printf("%d\n", isZero(&a));

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
    printf(" + ");
  }
  else
  {
    printf(" - ");
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
  int flag = 0, i;
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
uint32_t xorshift()
{
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  uint32_t w = random() % 10000000;
  uint32_t t;
  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  w ^= t ^ (t >> 8) ^ (w >> 19);
  return w;
}

/*uint64_t rol64(uint64_t x, int k)
{
  return (x << k) | (x >> (64 - k));
}

struct xoshiro256ss_state
{
  uint64_t s[4];
};

uint64_t xoshiro256ss(struct xoshiro256ss_state *state)
{
  uint64_t(*s)[4] = &state->s;
  uint64_t const result = rol64(*s[1] * 5, 7) * 9;
  uint64_t const t = *s[1] << 17;

  *s[2] ^= *s[0];
  *s[3] ^= *s[1];
  *s[1] ^= *s[2];
  *s[0] ^= *s[3];

  s[2] ^= t;
  s[3] = rol64(s[3], 45);

  return result;
} */