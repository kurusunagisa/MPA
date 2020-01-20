#include "mulprec.h"

// display Multiple Number
void dispNumber(NUMBER *a)
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
    printf("%5d", a->n[i]);
  }
}

// write Number to File
void fdispNumber(NUMBER *a, FILE *FP)
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
    fprintf(FP, "%04d", a->n[i]);
  }
}

// clear Number by ZERO
void clearByZero(NUMBER *a)
{
  int i;

  for (i = 0; i < KETA; i++)
  {
    a->n[i] = 0;
  }
  setSign(a, +1);
}

// set a's Signature from s
int setSign(NUMBER *a, int s)
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
int getSign(NUMBER *a)
{
  return a->sign == +1 ? +1 : -1;
}

void getAbs(NUMBER *a, NUMBER *b)
{
  copyNumber(a, b);
  setSign(b, +1);
}

// copy NUMBER a to b
void copyNumber(NUMBER *a, NUMBER *b)
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    b->n[i] = a->n[i];
  }
  setSign(b, getSign(a));
}

// compare a and b
int numComp(NUMBER *a, NUMBER *b)
{
  int i;
  if (getSign(a) != getSign(b))
  {
    return getSign(a) > getSign(b) ? 1 : -1;
  }
  if (getSign(a) == +1)
  {
    for (i = KETA - 1; i >= 0; i--)
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
    for (i = KETA - 1; i >= 0; i--)
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
  exit(-500);
  return -10000;
}

// swap a with b
void swap(NUMBER *a, NUMBER *b)
{
  NUMBER c;
  clearByZero(&c);
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

int isZero(NUMBER *a)
{
  int i;
  for (i = 0; i < KETA; i++)
  {
    if (a->n[i] != 0)
    {
      return 0;
    }
  }
  return 1;
}

// left bit shift
int mulBy10000(NUMBER *a, NUMBER *b)
{
  int i;
  for (i = 0; i < KETA - 1; i++)
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

int mulByN(NUMBER *a, NUMBER *b, int N)
{
  int i;
  for (i = 0; i < KETA - 1; i++)
  {
    b->n[i + N] = a->n[i];
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

int add(NUMBER *a, NUMBER *b, NUMBER *c)
{
  int i, e = 0, d;
  NUMBER x, y;
  clearByZero(&x);
  clearByZero(&y);
  setSign(c, +1);
  if (getSign(a) == -1 && getSign(b) == -1)
  {
    getAbs(a, &x);
    getAbs(b, &y);
    setSign(c, -1);
  }
  if (getSign(a) == -1 && getSign(b) == +1)
  {
    getAbs(a, &x);
    return sub(b, &x, c);
  }
  if (getSign(a) == +1 && getSign(b) == -1)
  {
    getAbs(b, &y);
    return sub(a, &y, c);
  }
  for (i = 0; i < KETA; i++)
  {
    d = a->n[i] + b->n[i] + e;
    c->n[i] = d % RADIX;
    e = d / RADIX;
  }
  return e != 0 ? -1 : 0;
}

// 上の桁から引けないときは更に上の桁から引かないといけない
// 300000000 - 88889999とかだと8888のところで300000000側で0000 - 1 が発生してマイナスになってしまう
int sub(NUMBER *a, NUMBER *b, NUMBER *c)
{
  int i, h = 0, flag = 0;
  NUMBER x, y;
  clearByZero(&x);
  clearByZero(&y);
  if (getSign(b) == -1)
  {
    getAbs(b, &y);
    return add(a, &y, c);
  }
  if (getSign(a) == -1 && getSign(b) == +1)
  {
    getAbs(a, &x);
    setSign(c, -1);
    return add(&x, b, c);
  }
  if (numComp(a, b) < 0)
  {
    swap(a, b);
    setSign(c, -1);
    flag = 1;
  }
  else
  {
    setSign(c, +1);
  }
  for (i = 0; i < KETA; i++)
  {
    if (a->n[i] > 0)
      a->n[i] -= h;
    if (a->n[i] >= b->n[i])
    {
      c->n[i] = a->n[i] - b->n[i];
      h = 0;
    }
    else
    {
        c->n[i] = RADIX + a->n[i] - b->n[i];
        if (h == 1 && a->n[i] == 0)
          c->n[i]--;
        h = 1;
    }
  }
  if (flag == 1)
  {
    swap(a, b);
  }
  return h != 0 ? -1 : 0;
}

int increment(NUMBER *a, NUMBER *b)
{
  NUMBER one;
  int r;

  setInt(&one, +1);

  r = add(a, &one, b);

  return r;
}

int decrement(NUMBER *a, NUMBER *b)
{
  NUMBER one;
  int r;
  setInt(&one, 1);
  r = sub(a, &one, b);
  return r;
}

int multiple(NUMBER *a, NUMBER *b, NUMBER *c)
{
  int i = 0, j = 0, aj, bi, h, e, r;
  NUMBER d, f, x, y;
  if (getSign(a) == -1 && getSign(b) == +1)
  {
    getAbs(a, &x);
    r = multiple(&x, b, c);
    setSign(c, -1);
    return r;
  }
  if (getSign(a) == +1 && getSign(b) == -1)
  {
    getAbs(b, &y);
    r = multiple(a, &y, c);
    setSign(c, -1);
    return r;
  }
  if (getSign(a) == -1 && getSign(b) == -1)
  {
    getAbs(a, &x);
    getAbs(b, &y);
    r = multiple(&x, &y, c);
    return r;
  }
  for (i = 0; i < KETA; i++)
  {
    bi = b->n[i];
    h = 0;
    clearByZero(&d);
    for (j = 0; j < KETA; j++)
    {
      aj = a->n[j];
      e = aj * bi + h;
      if (j + i >= KETA)
      {
        //printf("j = %d i = %d aj = %d bi = %d e = %d\n", j, i, aj, bi, e);
        if (e != 0)
        {
          return -1;
        }
        break;
      }
      d.n[j + i] = e % RADIX;
      h = e / RADIX;
    }
    if (h != 0)
      return -1;
    clearByZero(&f);
    if (add(c, &d, &f) == -1)
      return -1;
    copyNumber(&f, c);
  }
  return 0;
}

int divide(NUMBER *a, NUMBER *b, NUMBER *c, NUMBER *d)
{
  NUMBER e, f, m, n, p, q, temp, temp2, ten;
  int r;
  setInt(&ten, 10);
  if (getSign(a) == +1 && getSign(b) == -1)
  {
    getAbs(b, &p);
    r = divide(a, &p, c, d);
    setSign(c, -1);
    return r;
  }
  if (getSign(a) == -1 && getSign(b) == +1)
  {
    getAbs(a, &p);
    r = divide(&p, b, c, d);
    setSign(c, -1);
    setSign(d, -1);
    return r;
  }
  if (getSign(a) == -1 && getSign(b) == -1)
  {
    getAbs(a, &p);
    getAbs(b, &q);
    r = divide(&p, &q, c, d);
    setSign(d, -1);
    return r;
  }
  clearByZero(c);
  clearByZero(d);

  if (isZero(b) == 1)
  {
    return -1;
  }

  copyNumber(a, &n);
  while (1)
  {
    if (numComp(&n, b) < 0)
    {
      copyNumber(&n, d);
      break;
    }
    copyNumber(b, &f);
    setInt(&e, 1);
    while (1)
    {
      copyNumber(&f, &temp2);
      mulBy10000(&f, &temp);
      copyNumber(&temp, &f);
      clearByZero(&temp);
      if (numComp(&n, &f) != 1)
      {
        copyNumber(&temp2, &f);
        while (1)
        {
          copyNumber(&f, &temp2);
          multiple(&f, &ten, &temp);
          copyNumber(&temp, &f);
          clearByZero(&temp);
          if (numComp(&n, &f) != 1)
          {
            break;
          }
          multiple(&e, &ten, &temp);
          copyNumber(&temp, &e);
          clearByZero(&temp);
        }
        copyNumber(&temp2, &f);
        break;
      }
      mulBy10000(&e, &temp);
      copyNumber(&temp, &e);
      clearByZero(&temp);
    }
    sub(&n, &f, &m);
    copyNumber(&m, &n);
    /*printf("f = ");
    dispNumber(&f);
    printf("\n");
    printf("e = ");
    dispNumber(&e);
    printf("\n");
    printf("n = ");
    dispNumber(&n);
    printf("\n");*/
    clearByZero(&m);
    add(c, &e, &m);
    copyNumber(&m, c);
    clearByZero(&m);
  }
  return 0;
}
/*
int multiple(NUMBER *a, NUMBER *b, NUMBER *c)
{
  // カラツバ
}

int divide(NUMBER *a, NUMBER *b, NUMBER *c)
{
  //逆元をとってmultiple
}*/

// c = a^b
int fastpower(NUMBER *a, NUMBER *b, NUMBER *c)
{
  int x = 0;
  NUMBER n;
  NUMBER m;
  NUMBER o;
  NUMBER p;
  clearByZero(c);
  clearByZero(&n);
  clearByZero(&m);
  clearByZero(&o);
  clearByZero(&p);
  getInt(b, &x);
  if (x == 0)
  {
    setInt(c, +1);
  }
  if (x == 1)
  {
    copyNumber(a, c);
    return x;
  }
  if (x % 2 == 0)
  {
    copyNumber(a, &n);
    multiple(a, &n, &m);
    setInt(&o, x / 2);
    clearByZero(&p);
    fastpower(&m, &o, &p);
    /*printf("p1 = ");
    dispNumber(&p);
    printf("\n");*/
  }
  decrement(b, &n);
  //copyNumber(&n, b);
  //clearByZero(&n);
  clearByZero(&p);
  fastpower(a, &n, &p);
  /*printf("p0 = ");
  dispNumber(&p);
  printf("\n");*/
  multiple(a, &p, c);
}
int squareroot(NUMBER *a, NUMBER *b)
{
  NUMBER c, temp, two;
  clearByZero(&c);
  clearByZero(&temp);
  clearByZero(&two);
  if (numComp(a, &temp) == -1)
  {
    return -1;
  }
  setInt(&c, 1);
  setInt(&two, 2);
  while (numComp(a, &c) != -1)
  {
    sub(a, &c, &temp);
    copyNumber(&temp, a);
    clearByZero(&temp);
    add(&c, &two, &temp);
    copyNumber(&temp, &c);
    clearByZero(&temp);
    increment(b, &temp);
    copyNumber(&temp, b);
    clearByZero(&temp);
    //printf("b = ");
    //dispNumber(b);
    //printf("\n");
  }
}

int sqrt_newton(NUMBER *a, NUMBER *b)
{
  NUMBER w, x, y, z, zero, two, temp, tukawanai;
  clearByZero(&w);
  clearByZero(&x);
  clearByZero(&y);
  clearByZero(&z);
  clearByZero(&zero);
  clearByZero(&two);
  clearByZero(&temp);
  setInt(&two, 2);

  divide(a, &two, &w, &temp); //w = a  /2
  //printf("w = ");
  //dispNumber(&w);
  //printf("\n");
  if (isZero(&w) == 1)
    copyNumber(a, b);
  if (numComp(&w, &zero) < 0)
    return -1;
  copyNumber(&w, &x); // x = w
  copyNumber(&w, &y); //y = w

  while (1)
  {
    copyNumber(&x, &y); // y = x
    copyNumber(&w, &x); // x = w
    //printf("wall1\n");
    /*printf("a = ");
    dispNumber(a);
    printf("\n");
    printf("x = ");
    dispNumber(&x);
    printf("\n");*/
    divide(a, &x, &z, &tukawanai); // z = a / x
    //printf("z = ");
    //dispNumber(&z);
    //printf("\n");
    add(&x, &z, &temp); // temp = b + z
    //printf("temp = ");
    //dispNumber(&temp);
    //printf("\n");
    clearByZero(&z);
    //printf("wall2\n");
    divide(&temp, &two, &w, &tukawanai); // w = (b + N / b) / 2
    /*printf("w = ");
    dispNumber(&w);
    printf("\n\n");*/
    if (numComp(&w, &x) == 0)
      break;
    if (numComp(&w, &y) == 0)
    {
      if (numComp(&x, &w) < 0)
        copyNumber(&x, &w);
      break;
    }
  }
  copyNumber(&w, b);
}

/*
int sqrt_newton(NUMBER *a, NUMBER *b)
{
  NUMBER w, x, y, z, zero, two, three, temp, tukawanai;
  clearByZero(&w);
  clearByZero(&x);
  clearByZero(&y);
  clearByZero(&z);
  clearByZero(&zero);
  clearByZero(&two);
  clearByZero(&temp);
  setInt(&two, 2);
  setInt(&three, 3);

  divide(a, &two, &w, &temp); //w = a  /2
  //printf("w = ");
  //dispNumber(&w);
  //printf("\n");
  if (isZero(&w) == 1)
    copyNumber(a, b);
  if (numComp(&w, &zero) < 0)
    return -1;
  copyNumber(&w, &x); // x = w
  copyNumber(&w, &y); //y = w

  while (1)
  {
    copyNumber(&x, &y); // y = x
    copyNumber(&w, &x); // x = w
    printf("w0 = ");
    dispNumber(&w);
    printf("\n\n");
    fastpower(&w, &three, &temp);
    multiple(a, &temp, &z);
    clearByZero(&temp);
    sub(&three, &z, &temp);
    clearByZero(&z);
    divide(&w, &two, &z, &tukawanai);
    multiple(&temp, &z, &w);
    clearByZero(&temp);
    clearByZero(&z);
   // divide(a, &x, &z, &temp); // z = a / x
    //printf("z = ");
    //dispNumber(&z);
    //printf("\n");
   // add(&x, &z, &temp); // temp = b + z
    //printf("temp = ");
    //dispNumber(&temp);
    //printf("\n");
   // divide(&temp, &two, &w, &tukawanai); // w = (b + N / b) / 2
    printf("w = ");
    dispNumber(&w);
    printf("\n\n");
    if (numComp(&w, &x) == 0)
      break;
    if (numComp(&w, &y) == 0)
    {
      if (numComp(&x, &w) < 0)
        copyNumber(&x, &w);
      break;
    }
  }
  printf("end\n");
  copyNumber(&w, b);
}
*/

int setInt(NUMBER *a, int x)
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
    a->n[i] = x % RADIX;
    x -= x % RADIX;
    x /= RADIX;
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

int getInt(NUMBER *a, int *x)
{
  int i;
  long temp = 1;
  *x = 0;
  for (i = 0; i < 9; i++)
  {
    if (*x > INT32_MAX - (a->n[i] * temp))
    {
      return -1;
    }
    else
    {
      *x += a->n[i] * temp;
      //printf("a->n[%d] = %d\n", i, a->n[i]);
      temp *= RADIX;
      //printf("*x = %d\n", *x);
    }
  }
  if (getSign(a) != 1)
  {
    *x -= *x * 2;
  }
  return 0;
}