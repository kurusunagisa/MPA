#include "mulprec.h"

NUMBER clear = {0};
// display Multiple Number
void dispNumber(NUMBER *a) {
  int i;
  if(getSign(a) == +1) {
    printf("+");
  }
  if(getSign(a) == -1) {
    printf("-");
  }
  for(i = KETA - 1; i >= 0; i--) {
    printf("%04ld", a->n[i]);
  }
}

// write Number to File
void fdispNumber(NUMBER *a, FILE *FP) {
  int i;
  if(getSign(a) == +1) {
    fprintf(FP, "+");
  }
  if(getSign(a) == -1) {
    fprintf(FP, "-");
  }
  for(i = KETA - 1; i >= 0; i--) {
    fprintf(FP, "%04ld", a->n[i]);
  }
}

// clear Number by ZERO
void clearByZero(NUMBER *a) {
  setSign(&clear,+1);
  *a = clear;
  /*int i;

  for(i = 0; i < KETA; i++) {
    a->n[i] = 0;
  }
  setSign(a, +1);*/
}

// set a's Signature from s
int setSign(NUMBER *a, int s) {
  if(s == +1)
    a->sign = +1;
  else if(s == -1)
    a->sign = -1;
  else
    return -1;
  return 0;
}

// return a's Signature
int getSign(NUMBER *a) { return a->sign == +1 ? +1 : -1; }

void getAbs(NUMBER *a, NUMBER *b) {
  copyNumber(a, b);
  setSign(b, +1);
}

// copy NUMBER a to b
void copyNumber(NUMBER *a, NUMBER *b) {
  *b = *a;
  /*int i;
  for(i = 0; i < KETA; i++) {
    b->n[i] = a->n[i];
  }
  setSign(b, getSign(a));*/
}

void copyPartOfNumber(NUMBER *a, NUMBER *b, int x, int y) {
  int i;
  int count = 0;
  for(i = x; i < y; i++) {
    b->n[count] = a->n[i];
    count++;
  }
}

// compare a and b
int numComp(NUMBER *a, NUMBER *b) {
  int i;
  if(getSign(a) != getSign(b)) {
    return getSign(a) > getSign(b) ? 1 : -1;
  }
  if(getSign(a) == +1) {
    for(i = KETA - 1; i >= 0; i--) {
      if(a->n[i] > b->n[i]) {
        return 1;
      }
      if(a->n[i] < b->n[i]) {
        return -1;
      }
    }
    return 0;
  }
  if(getSign(a) == -1) {
    for(i = KETA - 1; i >= 0; i--) {
      if(a->n[i] < b->n[i]) {
        return 1;
      }
      if(a->n[i] > b->n[i]) {
        return -1;
      }
    }
    return 0;
  }
  exit(-500);
  return -10000;
}

// swap a with b
void swap(NUMBER *a, NUMBER *b) {
  NUMBER c;
  clearByZero(&c);
  int i;
  for(i = 0; i < KETA; i++) {
    c.n[i] = a->n[i];
  }
  setSign(&c, a->sign);
  for(i = 0; i < KETA; i++) {
    a->n[i] = b->n[i];
  }
  setSign(a, b->sign);
  for(i = 0; i < KETA; i++) {
    b->n[i] = c.n[i];
  }
  setSign(b, c.sign);
}

int isZero(NUMBER *a) {
  int i;
  for(i = 0; i < KETA; i++) {
    if(a->n[i] != 0) {
      return 0;
    }
  }
  return 1;
}

int searchKeta(NUMBER *a) {
  int i;
  for(i = KETA - 1; i >= 0; i--) {
    if(a->n[i] != 0) {
      return i + 1;
    }
  }
  return 0;
}

// left bit shift
int mulBy10000(NUMBER *a, NUMBER *b) {
  int i;
  for(i = 0; i < KETA - 1; i++) {
    b->n[i + 1] = a->n[i];
  }
  setSign(b, getSign(a));
  b->n[0] = 0;
  if(a->n[0] != 0) {
    return -1;
  } else {
    return 0;
  }
}

// left bit shift
int divBy10000(NUMBER *a, NUMBER *b) {
  int i;
  for(i = 0; i < KETA - 1; i++) {
    b->n[i] = a->n[i + 1];
  }
  setSign(b, getSign(a));
  b->n[KETA - 1] = 0;
  if(a->n[KETA - 1] != 0) {
    return -1;
  } else {
    return 0;
  }
}

int mulByN(NUMBER *a, NUMBER *b, int N) {
  int i;
  for(i = 0; i < KETA - 1; i++) {
    b->n[i + N] = a->n[i];
  }
  setSign(b, getSign(a));
  b->n[0] = 0;
  if(a->n[0] != 0) {
    return -1;
  } else {
    return 0;
  }
}

int add(NUMBER *a, NUMBER *b, NUMBER *c) {
  unsigned long i, e = 0, d;
  NUMBER x, y;
  clearByZero(&x);
  clearByZero(&y);
  setSign(c, +1);
  if(getSign(a) == -1 && getSign(b) == -1) {
    getAbs(a, &x);
    getAbs(b, &y);
    setSign(c, -1);
  }
  if(getSign(a) == -1 && getSign(b) == +1) {
    getAbs(a, &x);
    return sub(b, &x, c);
  }
  if(getSign(a) == +1 && getSign(b) == -1) {
    getAbs(b, &y);
    return sub(a, &y, c);
  }
  for(i = 0; i < KETA; i++) {
    d = a->n[i] + b->n[i] + e;
    c->n[i] = d % RADIX;
    e = d / RADIX;
  }
  return e != 0 ? -1 : 0;
}

// 上の桁から引けないときは更に上の桁から引かないといけない
// 300000000 - 88889999とかだと8888のところで300000000側で0000 - 1
// が発生してマイナスになってしまう
int sub(NUMBER *a, NUMBER *b, NUMBER *c) {
  int i, flag = 0, flag2 = 0;
  long ai, bi, ci;
  long h = 0;
  NUMBER x, y;
  clearByZero(&x);
  clearByZero(&y);
  if(getSign(b) == -1) {
    getAbs(b, &y);
    add(a, &y, c);
    return 0;
  }
  if(getSign(a) == -1 && getSign(b) == +1) {
    getAbs(a, &x);
    add(&x, b, c);
    setSign(c, -1);
    return 0;
  }
  if(numComp(a, b) < 0) {
    swap(a, b);
    setSign(c, -1);
    flag = 1;
  } else {
    setSign(c, +1);
  }
  for(i = 0; i < KETA; i++) {
    ai = a->n[i];
    bi = b->n[i];
    ai -= h;
    if(ai < 0) {
      ai = 9999;
      flag2 = 1;
    }
    if(ai >= bi) {
      c->n[i] = ai - bi;
      if(ai == 9999 && flag2 == 1) {
        h = 1;
        flag2 = 0;
      } else {
        h = 0;
      }
    } else {
      c->n[i] = RADIX + ai - bi;
      h = 1;
    }
  }
  if(flag == 1) {
    swap(a, b);
  }
  return h != 0 ? -1 : 0;
}

int increment(NUMBER *a, NUMBER *b) {
  NUMBER one;
  int r;

  setInt(&one, +1);

  r = add(a, &one, b);

  return r;
}

int decrement(NUMBER *a, NUMBER *b) {
  NUMBER one;
  int r;
  setInt(&one, 1);
  r = sub(a, &one, b);
  return r;
}

int multiple(NUMBER *a, NUMBER *b, NUMBER *c) {
  int i = 0, j = 0, r;
  unsigned long aj, e, bi, h = 0;
  NUMBER d, f, x, y;
  if(getSign(a) == -1 && getSign(b) == +1) {
    getAbs(a, &x);
    r = multiple(&x, b, c);
    setSign(c, -1);
    return r;
  }
  if(getSign(a) == +1 && getSign(b) == -1) {
    getAbs(b, &y);
    r = multiple(a, &y, c);
    setSign(c, -1);
    return r;
  }
  if(getSign(a) == -1 && getSign(b) == -1) {
    getAbs(a, &x);
    getAbs(b, &y);
    r = multiple(&x, &y, c);
    return r;
  }
  int ki = searchKeta(a) + 1;
  int kj = searchKeta(b) + 1;
  // int kj = searchKeta(b);
  //printf("ki = %d kj = %d\n", ki, kj);
  for(i = 0; i < kj; i++) {
    bi = b->n[i];
    h = 0;
    clearByZero(&d);
    if(bi == 0) {
      for(j = 0; j < ki; j++) {
        d.n[j + i] = 0;
      }
    } else {
      for(j = 0; j < ki; j++) {
        aj = a->n[j];
        e = aj * bi + h;
        if(j + i >= KETA) {
          if(e != 0) {
            return -1;
          }
          break;
        }
        d.n[j + i] = e % RADIX;
        h = e / RADIX;
      }
    }
    if(h != 0)
      return -1;
    clearByZero(&f);
    if(add(c, &d, &f) == -1)
      return -1;
    copyNumber(&f, c);
  }
  return 0;
}
/*
int karatsuba(NUMBER *a, NUMBER *b, NUMBER *c) {
  NUMBER x1, x0, y1, y0,z2,z1,z0,temp1,temp2,temp3,temp4;
  clearByZero(&x1);
  clearByZero(&x0);
  clearByZero(&y1);
  clearByZero(&y0);
  clearByZero(&z2);
  clearByZero(&z1);
  clearByZero(&z0);
  clearByZero(&temp1);
  clearByZero(&temp2);
  clearByZero(&temp3);
  clearByZero(&temp4);
  int r = searchKeta(a);
  copyPartOfNumber(a, &x1, r / 2, r);
  copyPartOfNumber(a, &x0, 0, r / 2);
  multiple(&x0,&y0,&z0);
  multiple(&x1,&y1,&z2);
  // ここからz1
  add(&z2,&z0,&temp1);
  sub(&x1,&x0,&temp2);
  sub(&y1,&y0,&temp3);
  multiple(&temp2,temp3,temp4);
  sub(&temp1, &temp4,&z1);
  //ここからc
}
*/

/*int divide(NUMBER *a, NUMBER *b, NUMBER *c, NUMBER *d) {
  NUMBER e, f, m, n, p, q, temp, temp2, ten;
  int r;
  setInt(&ten, 10);
  if(getSign(a) == +1 && getSign(b) == -1) {
    getAbs(b, &p);
    r = divide(a, &p, c, d);
    setSign(c, -1);
    return r;
  }
  if(getSign(a) == -1 && getSign(b) == +1) {
    getAbs(a, &p);
    r = divide(&p, b, c, d);
    setSign(c, -1);
    setSign(d, -1);
    return r;
  }
  if(getSign(a) == -1 && getSign(b) == -1) {
    getAbs(a, &p);
    getAbs(b, &q);
    r = divide(&p, &q, c, d);
    setSign(d, -1);
    return r;
  }
  clearByZero(c);
  clearByZero(d);

  if(isZero(b) == 1) {
    return -1;
  }

  copyNumber(a, &n);
  while(1) {
    if(numComp(&n, b) < 0) {
      copyNumber(&n, d);
      break;
    }
    copyNumber(b, &f);
    setInt(&e, 1);
    while(1) {
      copyNumber(&f, &temp2);
      mulBy10000(&f, &temp);
      copyNumber(&temp, &f);
      clearByZero(&temp);
      if(numComp(&n, &f) != 1) {
        copyNumber(&temp2, &f);
        while(1) {
          copyNumber(&f, &temp2);
          multiple(&f, &ten, &temp);
          copyNumber(&temp, &f);
          clearByZero(&temp);
          if(numComp(&n, &f) != 1) {
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
    clearByZero(&m);
    add(c, &e, &m);
    copyNumber(&m, c);
    clearByZero(&m);
  }
  return 0;
}
*/

int divide(NUMBER *a, NUMBER *b, NUMBER *c, NUMBER *d) {
  NUMBER e, f, m, n, p, q, temp, temp2, ten;
  int r;
  setInt(&ten, 10);
  if(getSign(a) == +1 && getSign(b) == -1) {
    getAbs(b, &p);
    r = divide(a, &p, c, d);
    setSign(c, -1);
    return r;
  }
  if(getSign(a) == -1 && getSign(b) == +1) {
    getAbs(a, &p);
    r = divide(&p, b, c, d);
    setSign(c, -1);
    setSign(d, -1);
    return r;
  }
  if(getSign(a) == -1 && getSign(b) == -1) {
    getAbs(a, &p);
    getAbs(b, &q);
    r = divide(&p, &q, c, d);
    setSign(d, -1);
    return r;
  }
  clearByZero(c);
  clearByZero(d);

  if(isZero(b) == 1) {
    return -1;
  }

  copyNumber(a, &n);
  while(1) {
    if(numComp(&n, b) < 0) {
      copyNumber(&n, d);
      break;
    }
    copyNumber(b, &f);
    setInt(&e, 1);
    while(1) {
      copyNumber(&f, &temp2);
      mulBy10000(&f, &temp);
      copyNumber(&temp, &f);
      clearByZero(&temp);
      if(numComp(&n, &f) != 1) {
        copyNumber(&temp2, &f);
        while(1) {
          copyNumber(&f, &temp2);
          multiple(&f, &ten, &temp);
          copyNumber(&temp, &f);
          clearByZero(&temp);
          if(numComp(&n, &f) != 1) {
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

int divide(NUMBER *a, NUMBER *b, NUMBER *c)
{
  //逆元をとってmultiple
}*/

// c = a^b
int fastpower(NUMBER *a, NUMBER *b, NUMBER *c) {
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
  if(x == 0) {
    setInt(c, +1);
  }
  if(x == 1) {
    copyNumber(a, c);
    return x;
  }
  if(x % 2 == 0) {
    copyNumber(a, &n);
    multiple(a, &n, &m);
    setInt(&o, x / 2);
    clearByZero(&p);
    fastpower(&m, &o, &p);
  }
  decrement(b, &n);
  clearByZero(&p);
  fastpower(a, &n, &p);
  multiple(a, &p, c);
}
int sqrt_newton(NUMBER *a, NUMBER *b) {
  NUMBER w, x, y, z, zero, two,three, temp,temp2,temp3,five, tukawanai;
  clearByZero(&w);
  clearByZero(&x);
  clearByZero(&y);
  clearByZero(&z);
  clearByZero(&two);
  clearByZero(&temp);
  clearByZero(&temp2);
  setInt(&two, 2);
  setInt(&three, 3);
  setInt(&five, 5000);

  //multiple(a,&five,&temp);
  //divBy10000(&temp, &w);
  divide(a, &three, &w, &temp); // w = a  / 3
  if(isZero(&w) == 1)
    copyNumber(a, b);
  if(numComp(&w, &zero) < 0)
    return -1;
  copyNumber(&w, &x); // x = w
  copyNumber(&w, &y); // y = w

  while(1) {
    copyNumber(&x, &y); // y = x
    copyNumber(&w, &x); // x = w
    // printf("wall1\n");
    /*printf("a = ");
    dispNumber(a);
    printf("\n");
    printf("x = ");
    dispNumber(&x);
    printf("\n");*/
    divide(a, &x, &z, &tukawanai); // z = a / x
    // printf("z = ");
    // dispNumber(&z);
    // printf("\n");
    add(&x, &z, &temp); // temp = b + z
    /*printf("t = ");
    dispNumber(&temp);
    printf("\n");*/
    clearByZero(&z);
    // printf("wall2\n");
    setInt(&five, 5000);
    //clearByZero(&temp);
    clearByZero(&temp2);
    clearByZero(&temp3);
    clearByZero(&w);
    multiple(&temp, &five,&temp2);
    divBy10000(&temp2, &w);
    //divide(&temp, &two, &w, &tukawanai); // w = (b + N / b) / 2
    /*printf("w = ");
    dispNumber(&w);
    printf("\n\n");*/
    if(numComp(&w, &x) == 0)
      break;
    if(numComp(&w, &y) == 0) {
      if(numComp(&x, &w) < 0)
        copyNumber(&x, &w);
      break;
    }
  }
  copyNumber(&w, b);
}

/*
int sqrt_newton(NUMBER *a, NUMBER *b)
{
  NUMBER w, x, y, z, zero, two, three,ten, keta, temp, tukawanai;
  clearByZero(&w);
  clearByZero(&x);
  clearByZero(&y);
  clearByZero(&z);
  clearByZero(&zero);
  clearByZero(&two);
  clearByZero(&temp);
  setInt(&two, 2);
  setInt(&three, 3);
  setInt(&ten, 10);
  int r = searchKeta(a);
  setInt(&keta, r);
  setSign(&keta, -1);
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

int setInt(NUMBER *a, long x) {
  int i = 0;
  if(x < 0) {
    setSign(a, -1);
    x -= x * 2;
  } else {
    setSign(a, +1);
  }
  for(i = 0; i < KETA; i++) {
    a->n[i] = x % RADIX;
    x -= x % RADIX;
    x /= RADIX;
  }
  if(x == 0) {
    return 0;
  } else {
    return -1;
  }
}

int getInt(NUMBER *a, int *x) {
  int i;
  long temp = 1;
  *x = 0;
  for(i = 0; i < 9; i++) {
    if(*x > INT32_MAX - (a->n[i] * temp)) {
      return -1;
    } else {
      *x += a->n[i] * temp;
      temp *= RADIX;
    }
  }
  if(getSign(a) != 1) {
    *x -= *x * 2;
  }
  return 0;
}