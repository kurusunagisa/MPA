#include "mulprec.h"

int archimedes(void);

int main(void) {
   printf("return = %d\n", archimedes());
  /*NUMBER a, b, c, d;
  srand(time(NULL));
  clearByZero(&a);
  clearByZero(&b);
  clearByZero(&c);
  clearByZero(&d);
  printf("a = ");
  dispNumber(&a);
  printf("\n");
  setInt(&a,39999999);
  setInt(&b, 99);
  // divide(&a, &b, &c, &d);
  // fastpower(&a, &b, &c);
  // squareroot(&a, &c);
  // sqrt_newton(&a,&c);
  // mulBy10000(&b,&a);
  // mulByN(&a, &b, 8);
  //add(&a, &b, &c);
   //sub(&a, &b, &c);
  // decrement(&a, &c);
   multiple(&a, &b, &c);
  // fastpower(&a, &b, &c);
  printf("a = ");
  dispNumber(&a);
  printf("\n");
  printf("b = ");
  dispNumber(&b);
  printf("\n");
  printf("c = ");
  dispNumber(&c);
  printf("\n");
  printf("d = ");
  dispNumber(&d);
  printf("\n");*/
}

int archimedes(void) {
  NUMBER a0, b0, an, bn, anext, bnext, two, three, temp, temp2, temp3, modulo;
  unsigned int i = 0;
  float x;
  int y, z;
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
  setInt(&two, 2);
  setInt(&three, 3); // 3を多倍長変数に代入
  mulByN(&three, &temp, DIGIT * 2);
  printf("temp = ");
  dispNumber(&temp);
  printf("\n");
  sqrt_newton(&temp, &temp3); // squareroot(3)を求める
  setInt(&temp2, 2);          // 2を多倍長変数に代入
  // mulByN(&two, &temp2, 3);
  printf("temp2 = ");
  dispNumber(&temp2);
  printf("\n");
  printf("temp3 = ");
  dispNumber(&temp3);
  printf("\n");
  multiple(&temp2, &temp3, &a0); // squareroot(3)*2 を a0に代入
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&temp3);
  /*x = sqrt(3) * 2 * pow(10,8);
  printf("x = %lf\n", x);
  y = (int)x;
  printf("y = %d\n",y);
  setInt(&a0, y);*/
  printf("a0 = ");
  dispNumber(&a0);
  printf("\n");
  setInt(&temp, 3);
  mulByN(&temp, &b0, DIGIT); // b0に3を代入
  printf("b0 = ");
  dispNumber(&b0);
  printf("\n");
  copyNumber(&a0, &an); // a0をanにコピー
  copyNumber(&b0, &bn); // b0をbnにコピー
  printf("an = ");
  dispNumber(&an);
  printf("\n");
  printf("bn = ");
  dispNumber(&bn);
  printf("\n");
  clearByZero(&temp);
  clearByZero(&temp2);
  clearByZero(&temp3);
  printf("before\n");
  while(i < 100) { // 何かしらのwhile文
    /*printf("an = ");
    dispNumber(&an);
    printf("\n");*/
    multiple(&two, &an, &temp); // 2 * anを計算
    /*printf("temp = ");
    dispNumber(&temp);
    printf("\n");*/
    // printf("A\n");
    multiple(&temp, &bn, &temp2); // (2 * an) * bnを計算
    /*printf("temp2 = ");
    dispNumber(&temp2);
    printf("\n");*/
    // printf("B\n");
    add(&an, &bn, &temp3); // an + bnを計算
    /*printf("temp3 = ");
    dispNumber(&temp3);
    printf("\n");*/
    divide(&temp2, &temp3, &anext,
           &modulo); // (2 * an * bn) / (an * bn)を計算してanextに代入
    /*printf("anext = ");
    dispNumber(&anext);
    printf("\n");*/
    // printf("C\n");
    clearByZero(&temp);
    clearByZero(&temp2);
    clearByZero(&temp3);
    // mulByN(&anext, &temp2, 1);
    // opyNumber(&temp2, &anext);
    multiple(&anext, &bn, &temp); // anext * bnを計算
    /*printf("anext * bn = ");
    dispNumber(&temp);
    printf("\n");*/
    // printf("D\n");
    sqrt_newton(&temp, &bnext); // squareroot(anext * bn)を計算してbnextに代入
    /*printf("bn = ");
    dispNumber(&bn);
    printf("\n");*/
    // printf("E\n");
    /// mulByN(&bnext, &temp3, 1);
    /// copyNumber(&temp3, &bnext);
    copyNumber(&anext, &an); // anextをanにコピー
    copyNumber(&bnext, &bn); // bnextをbnにコピー
    clearByZero(&anext);
    clearByZero(&bnext);
    clearByZero(&temp);
    clearByZero(&temp2);
    clearByZero(&temp3);
    printf("an = ");
    dispNumber(&an); // 表示
    printf("\n");
    i++; // インクリメント
  }
}