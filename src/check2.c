#include "mulprec.h"

// TODO:フィボナッチ数列あとでやる

int main(int argc, char *argv[])
{
  struct NUMBER a, b, c, d, e, f, g, h, l, m, n;
  int r, i;
  int count = 0;
  int data1;
  int data2;
  char x[] = "500000000000000000000000000002";
  char z[] = "499999999999999999999999999999";
  FILE *FP,*FP1,*FP2;

  /*init random function*/ // 絶対にいる

  /*if ((FP = fopen("/dev/random", O_RDONLY)) == NULL)
  {
    printf("can't open");
    exit(-500);
  }
  unsigned int o[100];
  for (i = 0; i < 100; i++)
  {
    o[i] = 0;
  }
  //int ret;
  for (i = 0; i < 100; i++)
  {
    fread(o[i], sizeof(o), sizeof(o), FP);
  }*/

  srandom(time(NULL));
  xorshiftInit(random() % 10000000000);
  pcg32_init(random());

  setInt(&a, -12345);
  printf("a = ");
  dispNumber(&a);
  printf("\n");

  copyNumber(&a, &b);
  setSign(&b, 1);
  printf("b = ");
  dispNumber(&b);
  printf("\n");

  r = getSign(&b);
  printf("getSign() = %d\n", r);

  r = numComp(&a, &b);
  printf("numComp() = %d\n", r);

  setIntFromString(&c, x);
  setIntFromString(&d, z);
  setSign(&c, +1);
  setSign(&d, +1);
  printf("c = ");
  dispNumber(&c);
  printf("\n");
  printf("d = ");
  dispNumber(&d);
  printf("\n");
  clearByZero(&e);
  printf("over carry = %d\n", add(&c, &d, &e));
  printf("e = ");
  dispNumber(&e);
  printf("\n");

  // setIntFromString
  clearByZero(&f);
  setIntFromString(&f, x);
  printf("f = ");
  dispNumber(&f);
  printf("\n");

  // getIntAsString
  // TODO: 0埋めどうしよう，入力と出力で合わない -> 0の出力を消す？それとも0を足す？
  char y[KETA + 1];
  getIntAsString(&f, y);
  printf("y = ");
  for (i = 0; i < KETA + 1; i++)
  {
    printf("%c", y[i]);
  }
  printf("\n");
  printf("x = ");
  for (i = 0; i < KETA + 1; i++)
  {
    printf("%c", x[i]);
  }
  printf("\n");

  // check add
  /*if ((FP = fopen("check.txt", "w")) == NULL)
  {
    fprintf(stderr, "cannot open the file.");
    exit(-500);
  }
  while (count < 1000000)
  {
    clearByZero(&g);
    clearByZero(&h);
    clearByZero(&l);
    data1 = random() % 1000000000;
    data2 = random() % 1000000000;
    setInt(&g, data1);
    setInt(&h, data2);
    //printf("data1 = %d data2 = %d\n", data1, data2);
    add(&g, &h, &l);
    fdispNumber(&l, FP);
    fprintf(FP, "\n");
    fprintf(FP, (data1 + data2) >= 0 ? "+" : "-");
    fprintf(FP, "%030d\n", data1 + data2);
    count++;
  }
  count = 0;
  fclose(FP);
  char *command = "python checkint.py";
  (void)system(command);*/

  if ((FP1 = fopen("check1.txt", "w")) == NULL)
  {
    fprintf(stderr, "cannot open the file.");
    exit(-500);
  }
  if ((FP2 = fopen("check2.txt", "w")) == NULL)
  {
    fprintf(stderr, "cannot open the file.");
    exit(-500);
  }
  while (count < 1000000)
  {
    clearByZero(&g);
    clearByZero(&h);
    clearByZero(&l);
    data1 = random() % 1000000000;
    data2 = random() % 1000000000;
    setInt(&g, data1);
    setInt(&h, data2);
    //printf("data1 = %d data2 = %d\n", data1, data2);
    add(&g, &h, &l);
    fdispNumber(&l, FP1);
    fprintf(FP1, "\n");
    fprintf(FP2, (data1 + data2) >= 0 ? "+" : "-");
    fprintf(FP2, "%030d\n", data1 + data2);
    count++;
  }
  count = 0;
  fclose(FP1);
  fclose(FP2);

  char *command = "diff check1.txt check2.txt";
  printf("command = %d\n",system(command));

  

  return 0;
}