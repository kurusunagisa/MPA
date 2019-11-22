#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include <fcntl.h>
//#include "CppUTest/CommandLineTestRunner.h"
//#include "CppUTest/TestHarness.h"
#define KETA 30

struct NUMBER
{
  int n[KETA];
  int sign;
};
/*xorshift-field*/
uint64_t xorshift_x;
uint64_t xorshift_y;
uint64_t xorshift_z;
uint64_t xorshift_w;
/*Permuted congruential generator-field*/
uint64_t pcg_state;
static uint64_t const pcg_multiplier = 6364136223846793005u;
static uint64_t const pcg_increment = 1442695040888963407u; // 任意の奇数

// 表示系
void dispNumber(struct NUMBER *);
void fdispNumber(struct NUMBER *, FILE *);
int isZero(struct NUMBER *);
// 設定系
void clearByZero(struct NUMBER *);
void setRnd(struct NUMBER *, int);
void copyNumber(struct NUMBER *, struct NUMBER *);
void getAbs(struct NUMBER *, struct NUMBER *);
int setSign(struct NUMBER *, int);
int getSign(struct NUMBER *);
int numComp(struct NUMBER *, struct NUMBER *);
void swap(struct NUMBER *, struct NUMBER *);
// 計算系
int mulBy10(struct NUMBER *, struct NUMBER *);
int divBy10(struct NUMBER *, struct NUMBER *);
int add(struct NUMBER *, struct NUMBER *, struct NUMBER *);
int sub(struct NUMBER *, struct NUMBER *, struct NUMBER *);
int increment(struct NUMBER *, struct NUMBER *);
int decrement(struct NUMBER *, struct NUMBER *);
int simpleMultiple(int, int, int *);
int multiple(struct NUMBER*, struct NUMBER*, struct NUMBER*);
// 変換系
int setInt(struct NUMBER *, int);
int setIntFromString(struct NUMBER *, char *);
int getInt(struct NUMBER *, int *);
int getIntAsString(struct NUMBER *, char *);
int ctoi(char);
/*xorshift_function*/
void xorshiftInit(int);
uint32_t rol64(uint32_t, int);
uint32_t xorshift();
/*Permuted congruential generator_function*/
uint32_t rotr32(uint32_t, unsigned);
uint32_t pcg32();
void pcg32_init(uint64_t);