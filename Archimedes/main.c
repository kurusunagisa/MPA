#include "mulprec.h"

int archimedes(NUMBER *);
int stormer(NUMBER *);

int main(void) {
  NUMBER pi;
  // printf("return = %d\n", archimedes(&pi));
  printf("return = %d\n", stormer(&pi));
}

int archimedes(NUMBER *rpi) {
  struct timeval tv;
  double tstart, tend;
  gettimeofday(&tv, NULL);
  tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  NUMBER a0, b0, an, bn, anext, bnext, two, three, temp, temp2, temp3, modulo;
  unsigned int i = 0;
  clearByZero(&a0);
  clearByZero(&b0);
  clearByZero(&an);
  clearByZero(&bn);
  clearByZero(&anext);
  clearByZero(&bnext);
  clearByZero(&two);
  clearByZero(&three);
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&temp3);
  setClear();
  setInt(&two, 2);
  setInt(&three, 3); // 3を多倍長変数に代入
  mulByN(&three, &temp, DIGIT * 2);
  sqrt_newton(&temp, &temp3);    // squareroot(3)を求める
  setInt(&temp2, 2);             // 2を多倍長変数に代入
  multiple(&temp3, &temp2, &a0); // squareroot(3)*2 を a0に代入
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&temp3);
  copyNumber(&a0, &an); // a0をanにコピー
  setInt(&temp, 3);
  mulByN(&temp, &b0, DIGIT); // b0に3を代入
  copyNumber(&b0, &bn);      // b0をbnにコピー
  printf("a0 = ");
  dispNumber(&an);
  printf("\n");
  printf("b0 = ");
  dispNumber(&bn);
  printf("\n");
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&temp3);
  gettimeofday(&tv, NULL);
  tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  printf("ready time = %lf\n", tend - tstart);
  while(i < DIGIT * 10) {         // 何かしらのwhile文
    multiple(&an, &two, &temp);   // 2 * anを計算
    multiple(&temp, &bn, &temp2); // (2 * an) * bnを計算
    add(&an, &bn, &temp3);        // an + bnを計算
    divide(&temp2, &temp3, &anext,
           &modulo); // (2 * an *  bn) / (an + bn)を計算してanextに代入
    clearByZero(&temp);
    clearByZero(&temp2);
    clearByZero(&temp3);
    if(numComp(&anext, &an) == 0) { // anが収束したときwhile内から抜ける
      break;
    }
    multiple(&anext, &bn, &temp); // anext * bnを計算
    sqrt_newton(&temp, &bnext); // squareroot(anext * bn)を計算してbnextに代入
    copyNumber(&anext, &an); // anextをanにコピー
    copyNumber(&bnext, &bn); // bnextをbnにコピー
    clearByZero(&anext);
    clearByZero(&bnext);
    clearByZero(&temp);
    clearByZero(&temp2);
    clearByZero(&temp3);
    i++; // インクリメント
  }
  printf("n = %d : \n", i);
  printf("pi = ");
  dispNumber(&an); // 表示
  printf("\n");
  gettimeofday(&tv, NULL);
  tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  printf("total time = %lf\n", tend - tstart);
  copyNumber(&an, rpi);
  return 0;
}

int stormer(NUMBER *rpi) {
  struct timeval tv;
  double tstart, tend;
  gettimeofday(&tv, NULL);
  tstart = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  NUMBER a0, an, bn, c, two, tf, notuse, j, temp, temp2, tanA, tanB, tanC,
      eight, sf, fs, fsfs, four, tsn, tsntsn, left, center, right, pi;
  int i = 0;
  setClear();
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&tanA);
  clearByZero(&tanB);
  clearByZero(&left);
  clearByZero(&center);
  clearByZero(&right);
  clearByZero(&pi);
  clearByZero(&c);
  clearByZero(&an);
  setInt(&two, 2);
  setInt(&a0, 1);
  setInt(&eight, 8);
  setInt(&sf, 64);
  setInt(&fs, 57);
  setInt(&fsfs, 57 * 57);
  setInt(&tf, 24);
  setInt(&tsn, 239);
  setInt(&tsntsn, 239 * 239);
  setInt(&j, 3);
  setInt(&four, 4);
  mulByN(&a0, &c, DIGIT);
  divide(&c, &eight, &an, &notuse);
  copyNumber(&an, &bn);
  while(1) {
    divide(&an, &sf, &temp, &notuse);
    if(isZero(&temp) == 1) {
      break;
    }
    copyNumber(&temp, &an);
    divide(&an, &j, &temp2, &notuse);
    clearByZero(&temp);
    if(i == 0) {
      sub(&bn, &temp2, &temp);
      copyNumber(&temp, &bn);
      i = 1;
    } else if(i == 1) {
      add(&bn, &temp2, &temp);
      copyNumber(&temp, &bn);
      i = 0;
    } else {
      return -1;
    }
    clearByZero(&temp);
    clearByZero(&temp2);
    add(&j, &two, &temp);
    copyNumber(&temp, &j);
    clearByZero(&temp);
  }
  copyNumber(&bn, &tanA);
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&c);
  clearByZero(&an);
  i = 0;
  setInt(&a0, 1);
  setInt(&j, 3);
  mulByN(&a0, &c, DIGIT);
  divide(&c, &fs, &an, &notuse);
  copyNumber(&an, &bn);
  while(1) {
    divide(&an, &fsfs, &temp, &notuse);
    if(isZero(&temp) == 1) {
      break;
    }
    copyNumber(&temp, &an);
    divide(&an, &j, &temp2, &notuse);
    if(i == 0) {
      sub(&bn, &temp2, &temp);
      copyNumber(&temp, &bn);
      i = 1;
    } else if(i == 1) {
      add(&bn, &temp2, &temp);
      copyNumber(&temp, &bn);
      i = 0;
    } else {
      return -1;
    }
    clearByZero(&temp);
    clearByZero(&temp2);
    add(&j, &two, &temp);
    copyNumber(&temp, &j);
    clearByZero(&temp);
  }
  copyNumber(&bn, &tanB);

  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&c);
  clearByZero(&an);
  i = 0;
  setInt(&a0, 1);
  setInt(&j, 3);
  mulByN(&a0, &c, DIGIT);
  divide(&c, &tsn, &an, &notuse);
  copyNumber(&an, &bn);
  while(1) {
    divide(&an, &tsntsn, &temp, &notuse);
    if(isZero(&temp) == 1) {
      break;
    }
    copyNumber(&temp, &an);
    divide(&an, &j, &temp2, &notuse);
    if(i == 0) {
      sub(&bn, &temp2, &temp);
      copyNumber(&temp, &bn);
      i = 1;
    } else if(i == 1) {
      add(&bn, &temp2, &temp);
      copyNumber(&temp, &bn);
      i = 0;
    } else {
      return -1;
    }
    clearByZero(&temp);
    clearByZero(&temp2);
    add(&j, &two, &temp);
    copyNumber(&temp, &j);
    clearByZero(&temp);
  }
  copyNumber(&bn, &tanC);
  multiple(&tanA, &tf, &left);
  multiple(&tanB, &eight, &center);
  multiple(&tanC, &four, &right);
  add(&left, &center, &temp);
  add(&temp, &right, &pi);
  printf("pi = ");
  dispNumber(&pi);
  printf("\n");
  gettimeofday(&tv, NULL);
  tend = (double)tv.tv_sec + (double)tv.tv_usec * 1.e-6;
  printf("total time = %lf\n", tend - tstart);
  copyNumber(&pi, rpi);
  return 0;
}