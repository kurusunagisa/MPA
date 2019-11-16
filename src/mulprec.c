#include "mulprec.h"


void dispNumber(struct NUMBER *a)
{
  int i;
  if (getSign(a) == +1)
  {
    printf("+");
  }
  if (getSign(a) == -1)
  {
    printf("-");
  }
  for (i = KETA - 1; i >= 0; i--)
  {
    printf("%2d", a->n[i]);
  }
}

void fdispNumber(struct NUMBER *a, FILE *FP)
{
  int i;
  if (getSign(a) == +1)
  {
    fprintf(FP, "+");
  }
  if (getSign(a) == -1)
  {
    fprintf(FP, "-");
  }
  for (i = KETA - 1; i >= 0; i--)
  {
    fprintf(FP, "%d", a->n[i]);
  }
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

void clearByZero(struct NUMBER *a)
{
  int i;

  for (i = 0; i < KETA; i++)
  {
    a->n[i] = 0;
  }
  setSign(a, +1);
}

void setRnd(struct NUMBER *a, int k)
{
  int i = 0;
  for (i = 0; i < KETA; i++)
  {
    a->n[i] = xorshift() % 10;
    //a->n[i] = pcg32() % 10;
  }
  setSign(a, (xorshift() % 2 == 0) ? -1 : +1);
  //a->sign = pcg32() % 2;
}

void copyNumber(struct NUMBER *a, struct NUMBER *b)
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    b->n[i] = a->n[i];
  }
  setSign(b, getSign(a));
}

void getAbs(struct NUMBER *a, struct NUMBER *b)
{
  copyNumber(a, b);
  setSign(a, +1);
}

int setSign(struct NUMBER *a, int s)
{
  if (s == +1)
    a->sign = +1;
  else if (s == -1)
    a->sign = -1;
  else
    return -1;
  return 0;
}

int getSign(struct NUMBER *a)
{
  return a->sign == +1 ? +1 : -1;
}

int numComp(struct NUMBER *a, struct NUMBER *b)
{
  int i;
  if (getSign(a) != getSign(b))
  {
    return getSign(a) > getSign(b) ? 1 : -1;
  }
  if (getSign(a) == +1)
  {
    for (i = 0; i < KETA; i++)
    {
      if (a->n[i] > b->n[i])
      {
        return 1;
      }
      if (a->n[i] < b->n[i])
      {
        return -1;
      }
    }
    return 0;
  }
  if (getSign(a) == -1)
  {
    for (i = 0; i < KETA; i++)
    {
      if (a->n[i] < b->n[i])
      {
        return 1;
      }
      if (a->n[i] > b->n[i])
      {
        return -1;
      }
    }
    return 0;
  }
  return -10000;
}

void swap(struct NUMBER *a, struct NUMBER *b)
{
  struct NUMBER c;
  int i;
  for (i = 0; i < KETA; i++)
  {
    c.n[i] = a->n[i];
  }
  setSign(&c, a->sign);
  for (i = 0; i < KETA; i++)
  {
    a->n[i] = b->n[i];
  }
  setSign(a, b->sign);
  for (i = 0; i < KETA; i++)
  {
    b->n[i] = c.n[i];
  }
  setSign(b, c.sign);
}

int mulBy10(struct NUMBER *a, struct NUMBER *b)
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    b->n[i + 1] = a->n[i];
  }
  setSign(b, getSign(a));
  b->n[0] = 0;
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
    b->n[i] = a->n[i + 1];
  }
  setSign(b, getSign(a));
  b->n[KETA - 1] = 0;
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
    setSign(a, -1);
    x -= x * 2;
  }
  else
  {
    setSign(a, +1);
  }
  for (i = 0; i < KETA; i++)
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
// TODO: intからstringに変えたい
int setIntFromString(struct NUMBER *a, char *x)
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    a->n[i] = atoi(x[i]);
  }
  return 0;
}

int getInt(struct NUMBER *a, int *x)
{
  int i, temp = 1;
  for (i = 0; i < KETA; i++)
  {
    if (*x > INT32_MAX - (a->n[i] * temp))
    {
      return -1;
    }
    else
    {
      *x += a->n[i] * temp;
      temp *= 10;
    }
  }
  if (getSign(a) != 1)
  {
    *x -= *x * 2;
  }
  return 0;
}
// TODO: 難しいね
int getIntAsString(struct NUMBER *a, char *x)
{
  int i, temp = 1;
  if (getSign(a) != 1)
  {
    x[0] = "-";
  }
  for (i = 0; i < KETA; i++)
  {
    *(x + (KETA - i)) += a->n[i] * temp;
    temp *= 10;
  }
  return 0;
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