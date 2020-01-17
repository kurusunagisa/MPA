#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define KETA 30
#define TEST_MAX 3000000
// unsigned longの上限 4294967295
// 65535まで
struct NUMBER{
  unsigned long n[KETA];
  int sign;
};

// 表示系
void dispNumber(struct NUMBER *);
void fdispNumber(struct NUMBER *, FILE *);
// 設定系
void clearByZero(struct NUMBER *);
void copyNumber(struct NUMBER *, struct NUMBER *);
int numComp(struct NUMBER *, struct NUMBER *);
int setSign(struct NUMBER *, int);
int getSign(struct NUMBER *);
// 計算系
int mulBy10(struct NUMBER *, struct NUMBER *);
int mulByN(struct NUMBER *, int, struct NUMBER *);
int add(struct NUMBER *, struct NUMBER *, struct NUMBER *);
int sub(struct NUMBER *, struct NUMBER *, struct NUMBER *);
int increment(struct NUMBER *, struct NUMBER *);
int multiple(struct NUMBER *, struct NUMBER *, struct NUMBER *);
int divide(struct NUMBER *, struct NUMBER *, struct NUMBER *, struct NUMBER *);
int fastpower(struct NUMBER *, struct NUMBER *, struct NUMBER *);
int squareroot(struct NUMBER *, struct NUMBER *);
int sqrt_newton(struct NUMBER *, struct NUMBER *);
// 変換系
int setInt(struct NUMBER *, int);
int setIntFromString(struct NUMBER *, char *);
int getInt(struct NUMBER *, int *);
int getIntAsString(struct NUMBER *, char *);
int ctoi(char);