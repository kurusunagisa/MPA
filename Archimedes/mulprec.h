#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define KETA 100
#define DIGIT 15
#define TEST_MAX 3000000
#define RADIX 10000
// unsigned longの上限 4294967295
// 9999まで
typedef struct
{
  unsigned long n[KETA];
  int sign;
} NUMBER;

// 表示系
void dispNumber(NUMBER *);
void fdispNumber(NUMBER *, FILE *);
// 設定系
void clearByZero(NUMBER *);
int setSign(NUMBER *, int);
int getSign(NUMBER *);
void getAbs(NUMBER *, NUMBER *);
void copyNumber(NUMBER *, NUMBER *);
int numComp(NUMBER *, NUMBER *);
void swap(NUMBER *, NUMBER *);
int isZero(NUMBER *);
// 計算系
int mulBy10000(NUMBER *, NUMBER *);
int mulByN(NUMBER *, NUMBER *,int);
int add(NUMBER *, NUMBER *, NUMBER *);
int sub(NUMBER *, NUMBER *, NUMBER *);
int increment(NUMBER *, NUMBER *);
int decrement(NUMBER *, NUMBER *);
int multiple(NUMBER *, NUMBER *, NUMBER *);
int karatsuba(NUMBER *, NUMBER *, NUMBER *);
int divide(NUMBER *, NUMBER *, NUMBER *, NUMBER *);
int fastpower(NUMBER *, NUMBER *, NUMBER *);
int squareroot(NUMBER *,NUMBER *);
int sqrt_newton(NUMBER *, NUMBER *);
// 変換系
int setInt(NUMBER *, long);
int getInt(NUMBER *, int*);