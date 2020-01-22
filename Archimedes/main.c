//TODO:カラツバ 平方根の逆数を求めてNを掛ける方法 逆数をとる除算
//MEMO:桁数は上からsearchすればほぼO(1)でできる
#include "mulprec.h"

int archimedes(void);

int main(void) {
  //printf("return = %d\n", archimedes());
  NUMBER a,b,c;
  setInt(&a,1739292929);
  mulByN(&a, &b, 1);
  clearByZero(&c);
  copyPartOfNumber(&b, &c, 1, 3);
  printf("c = ");
  dispNumber(&c);
  printf("\n");
  //printf("keta = %d\n",searchKeta(&b));
  /*NUMBER a, b, c, d;
  int count = 0, data1, data2,data3;
  FILE *FP, *FP2;
  srandom(time(NULL));
  clearByZero(&a);
  clearByZero(&b);
  clearByZero(&c);
  clearByZero(&d);
  printf("a = ");
  dispNumber(&a);
  printf("\n");
  setInt(&a, 1739212129);
  setInt(&b, 888888888);
  if((FP = fopen("check.txt", "w")) == NULL) {
    fprintf(stderr, "cannot open the file.");
    exit(-500);
  }
  if((FP2 = fopen("check2.txt", "w")) == NULL) {
    fprintf(stderr, "cannot open the file.");
    exit(-500);
  }
  while(count < 1000000) {
    clearByZero(&a);
    clearByZero(&b);
    clearByZero(&c);
    data1 = random() % 100000000;
    data2 = random() % 100 + 1;
    setInt(&a, data1);
    setInt(&b, data2);
    setSign(&a, random() % 2 == 1 ? +1 : -1);
    if(getSign(&a) == -1){
      data1 -= data1 * 2;
    }
    setSign(&b, random() % 2 == 1 ? +1 : -1);
    if(getSign(&b) == -1) {
      data2 -= data2 * 2;
    }
    // printf("data1 = %d data2 = %d\n", data1, data2);
    divide(&a, &b, &c,&d);
    data3 = data1 / data2;
    setInt(&d, data3);
    if(numComp(&c, &d) != 0 && isZero(&c) == 0) {
      printf("a = %d\n", data1);
      printf("b = %d\n", data2);
      printf("c = %d\n", data3);
      dispNumber(&c);
      printf("\n");
      break;
    }
    fdispNumber(&c, FP);
    fprintf(FP, "\n");
    fprintf(FP2, (data3) >= 0 ? "+" : "-");
    fprintf(FP2, "%080d\n", abs(data3));
    count++;
  }
  fclose(FP);
  fclose(FP2);
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
  while(i < 1000) { // 何かしらのwhile文
    printf("%d回目 : \n", i + 1);
    /*printf("an = ");
    dispNumber(&an);
    printf("\n");*/
    multiple(&two, &an, &temp); // 2 * anを計算 -> an * bnをカラツバで計算
    /*printf("temp = ");
    dispNumber(&temp);
    printf("\n");*/
    // printf("A\n");
    multiple(&temp, &bn, &temp2); // (2 * an) * bnを計算 -> (an * bn) * 2をmultipleで計算
    /*printf("temp2 = ");
    dispNumber(&temp2);
    printf("\n");*/
    // printf("B\n");
    add(&an, &bn, &temp3); // an + bnを計算
    /*printf("temp3 = ");
    dispNumber(&temp3);
    printf("\n");*/
    divide(&temp2, &temp3, &anext,
           &modulo); // (an * bn * 2) / (an + bn)を計算してanextに代入
    /*printf("anext = ");
    dispNumber(&anext);
    printf("\n");*/
    // printf("C\n");
    clearByZero(&temp);
    clearByZero(&temp2);
    clearByZero(&temp3);
    // mulByN(&anext, &temp2, 1);
    // opyNumber(&temp2, &anext);
    multiple(&anext, &bn, &temp); // anext * bnを計算 -> anext * bnをカラツバで計算
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