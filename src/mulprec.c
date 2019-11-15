#include "mulprec.h"

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

void fdispNumber(struct NUMBER *a, FILE *FP)
{
  int i;
  if (a->sign == 1)
  {
    fprintf(FP, "+");
  }
  else
  {
    fprintf(FP, "-");
  }
  for (i = 0; i < KETA; i++)
  {
    fprintf(FP, "%d", a->n[i]);
  }
}

void setRnd(struct NUMBER *a, int k)
{
  int i = 0;
  for (i = KETA - k; i < KETA; i++)
  {
    a->n[i] = xorshift() % 10;
    //a->n[i] = pcg32() % 10;
  }
  a->sign = xorshift() % 2;
  //a->sign = pcg32() % 2;
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
  b->sign = a->sign;
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

int divBy10(struct NUMBER *a, struct NUMBER *b)
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    b->n[i] = a->n[i - 1];
  }
  b->sign = a->sign;
  b->n[0] = 0;
  if (a->n[KETA - 1] != 0)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

int setInt(struct NUMBER *a, int x)
{
  int i = 0;
  if (x < 0)
  {
    a->sign = -1;
    x -= x * 2;
  }
  else
  {
    a->sign = 1;
  }
  for (i = KETA - 1; i >= 0; i--)
  {
    a->n[i] = x % 10;
    x -= x % 10;
    x /= 10;
  }
  if (x == 0)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

/*xorshift_function*/
void xorshiftInit(int seed)
{
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
  xorshift();
  xorshift();
  xorshift();
  xorshift();
}

uint32_t rol64(uint32_t x, int k)
{
  return (x << k) | (x >> (64 - k));
}

uint32_t xorshift()
{
  uint32_t result = rol64(xorshift_y * 5, 7) * 9;
  uint64_t t;
  t = xorshift_x ^ (xorshift_x << 17);
  xorshift_z ^= xorshift_x;
  xorshift_w ^= xorshift_y;
  xorshift_y ^= xorshift_z;
  xorshift_x ^= xorshift_w;
  xorshift_z ^= t;
  //w ^= t ^ (t >> 8) ^ (w >> 19);
  xorshift_w = rol64(xorshift_w, 45);
  //printf("result = %lld\n", result);
  return result;
}

/*Permuted congruential generator*/

uint32_t rotr32(uint32_t x, unsigned r)
{
  return x >> r | x << (-r & 31);
}

uint32_t pcg32(void)
{
  uint64_t x = state;
  unsigned count = (unsigned)(x >> 59); // 59 = 64 - 5

  state = x * multiplier + increment;
  x ^= x >> 18;                              // 18 = (64 - 27)/2
  return rotr32((uint32_t)(x >> 27), count); // 27 = 32 - 5
}

void pcg32_init(uint64_t seed)
{
  state = seed + increment;
  (void)pcg32();
}