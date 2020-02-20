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
    printf("%04ld ", a->n[i]);
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
void clearByZero(NUMBER *a) { *a = clear; }

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

// b is a's abs
void getAbs(NUMBER *a, NUMBER *b) {
  copyNumber(a, b);
  setSign(b, +1);
}

// clearの符号を+にする
void setClear() { setSign(&clear, +1); }

// copy NUMBER a to b
void copyNumber(NUMBER *a, NUMBER *b) { *b = *a; }

// compare a and b
// a > b ... 1 : a == b ... 0 : a < b ... -1
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

// 構造体aが0か確認する
// a == 0 ... 1 : a != 0 ... 0
int isZero(NUMBER *a) {
  int i;
  for(i = 0; i < KETA; i++) {
    if(a->n[i] != 0) {
      return 0;
    }
  }
  return 1;
}

// 構造体aの桁数を探す
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

//mulBy10000を何回も実行する動作と同じ動作を一気に行う関数
int mulByN(NUMBER *a, NUMBER *b, int N) {
  int i;
  for(i = 0; i < KETA - 1; i++) {
    b->n[i + N] = a->n[i];
  }
  setSign(b, getSign(a));
  for(i = 0; i < N; i++) {
    b->n[i] = 0;
  }
  if(a->n[0] != 0) {
    return -1;
  } else {
    return 0;
  }
}

// 足し算
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

// 引き算
int sub(NUMBER *a, NUMBER *b, NUMBER *c) {
  int i, flag = 0, flag2 = 0;
  long ai, bi;
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

// b = a + 1
int increment(NUMBER *a, NUMBER *b) {
  NUMBER one;
  int r;
  setInt(&one, +1);
  r = add(a, &one, b);
  return r;
}

//b = a - 1
int decrement(NUMBER *a, NUMBER *b) {
  NUMBER one;
  int r;
  setInt(&one, 1);
  r = sub(a, &one, b);
  return r;
}

//c = a * b
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
  for(i = 0; i < kj; i++) {
    bi = b->n[i];
    h = 0;
    clearByZero(&d);
    if(bi == 0) { //掛けられる側が0の場合特別扱いをする
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

// a / b = c ... d
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
      mulByN(&f, &temp, SHIFT);
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
      mulByN(&e, &temp, SHIFT);
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

//aの平方根を求める関数
int sqrt_newton(NUMBER *a, NUMBER *b) {
  NUMBER w, x, y, z, zero, two, three, temp, temp2, five, tukawanai;
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

  divide(a, &three, &w, &temp); // w = a  / 3
  if(isZero(&w) == 1)
    copyNumber(a, b);
  if(numComp(&w, &zero) < 0)
    return -1;
  copyNumber(&w, &x); // x = w
  copyNumber(&w, &y); // y = w

  while(1) {
    copyNumber(&x, &y);            // y = x
    copyNumber(&w, &x);            // x = w
    divide(a, &x, &z, &tukawanai); // z = a / x
    add(&x, &z, &temp);            // temp = b + z
    clearByZero(&z);
    setInt(&five, 5000);
    clearByZero(&temp2);
    clearByZero(&w);
    multiple(&temp, &five, &temp2); //temp2 = temp * 5000
    divBy10000(&temp2, &w); // (temp * 5000) / 10000 = temp / 2
    if(numComp(&w, &x) == 0)
      break;
    if(numComp(&w, &y) == 0) {
      if(numComp(&x, &w) < 0)
        copyNumber(&x, &w);
      break;
    }
  }
  copyNumber(&w, b);
  return 0;
}

//整数を多倍長の形にする
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