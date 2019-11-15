#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
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
uint64_t state;
static uint64_t const multiplier = 6364136223846793005u;
static uint64_t const increment = 1442695040888963407u; // 任意の奇数

void clearByZero(struct NUMBER *);
void dispNumber(struct NUMBER *);
void fdispNumber(struct NUMBER *, FILE *);
void setRnd(struct NUMBER *, int);
void copyNumber(struct NUMBER *, struct NUMBER *);
void getAbs(struct NUMBER *, struct NUMBER *);
int isZero(struct NUMBER *);
int mulBy10(struct NUMBER *, struct NUMBER *);
int divBy10(struct NUMBER *, struct NUMBER *);
int setInt(struct NUMBER *, int);
/*xorshift_function*/
void xorshiftInit(int);
uint32_t rol64(uint32_t, int);
uint32_t xorshift();
/*Permuted congruential generator_function*/
uint32_t rotr32(uint32_t, unsigned);
uint32_t pcg32();
void pcg32_init(uint64_t);