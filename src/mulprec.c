#include "mulprec.h"

// xorshiftが何故か死んでいる．何故 -> 関数の初期化をしていなかった

// disp Multiple Number
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

// write Number to File
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

// check Number is ZERO
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

// clear Number by ZERO
void clearByZero(struct NUMBER *a)
{
  int i;

  for (i = 0; i < KETA; i++)
  {
    a->n[i] = 0;
  }
  setSign(a, +1);
}

// set NUMBER by randomNUMBER
void setRnd(struct NUMBER *a, int k)
{
  int i = 0;
  for (i = 0; i < k; i++)
  {
    a->n[i] = pcg32() % 10;
    //a->n[i] = pcg32() % 10;
  }
  setSign(a, (pcg32() % 2 == 0) ? -1 : +1);
  //a->sign = pcg32() % 2;
}

// copy NUMBER a to b
void copyNumber(struct NUMBER *a, struct NUMBER *b)
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    b->n[i] = a->n[i];
  }
  setSign(b, getSign(a));
}

// copy Number a to b and a become +
void getAbs(struct NUMBER *a, struct NUMBER *b)
{
  copyNumber(a, b);
  setSign(a, +1);
}

// set a's Signature from s
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

// return a's Signature
int getSign(struct NUMBER *a)
{
  return a->sign == +1 ? +1 : -1;
}

// compare a and b
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

// swap a and b
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

// left shift
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

// right shift
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

// c = a + b
int add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c)
{
  int i, e = 0, d;
  for (i = 0; i < KETA; i++)
  {
    d = a->n[i] + b->n[i] + e;
    c->n[i] = d % 10;
    e = d / 10;
  }
  return e != 0 ? -1 : 0;
}

int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
  
}

// set integer to NUMBER
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

// stringからi文字ずつint型の配列に入れる
int setIntFromString(struct NUMBER *a, char *x)
{
  int i;
  for (i = 0; i < strlen(x); i++)
  {
    if (i >= KETA && x[strlen(x) - i - 1] != '-')
    {
      printf("over flow\n");
      return -1;
    }
    if (x[strlen(x) - i - 1] == '-')
    {
      setSign(a, -1);
      return 0;
    }
    a->n[i] = ctoi(x[strlen(x) - i - 1]);
    if (a->n[i] < 0 && a->n[i] > 9)
      return -1;
  }
  setSign(a, +1);
  return 0;
}

int ctoi(char x)
{
  return x - '0';
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
// TODO: Int型をChar型にして配列に入れるだけ
int getIntAsString(struct NUMBER *a, char *x) /* *xはx[KETA + 1]と扱う(しかない) */
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    x[KETA - i] = a->n[i] + '0';
  }
  if (getSign(a) != 1)
  {
    x[0] = *("-");
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