#include "mulprec.h"

int main(int argc, char *argv[])
{
  struct NUMBER a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
  int r, z = 0, data, input, output;
  int w, x, y;
  FILE *FP;
  /*init random function*/
  srandom(time(NULL));
  xorshiftInit(random() % 10000000000);
  pcg32_init(random());

  /*init structure*/
  clearByZero(&a);

  printf("a = ");
  dispNumber(&a);
  printf("\n");

  /*set random number*/
  setRnd(&b, KETA);

  printf("b = ");
  dispNumber(&b);
  printf("\n");
  if (getSign(&b) == +1)
  {
    printf("%c\n", '+');
  }
  if (getSign(&b) == -1)
  {
    printf("%c\n", '-');
  }

  /*copy Number*/
  copyNumber(&b, &c);

  printf("c = ");
  dispNumber(&c);
  printf("\n");
  /*10 times*/
  r = mulBy10(&b, &d);
  printf("b * 10 = ");
  dispNumber(&d);
  printf(" r = %d\n", r);

  /*div 10*/
  r = divBy10(&c, &e);
  printf("c / 10 = ");
  dispNumber(&e);
  printf(" r = %d\n", r);

  /*check n is Zero*/
  setRnd(&a, KETA);
  printf("%d\n", isZero(&a));

  /* check a to e != 0*/
  assert(isZero(&a) != 0);
  assert(isZero(&b) != 0);
  assert(isZero(&c) != 0);
  assert(isZero(&d) != 0);
  assert(isZero(&e) != 0);

  clearByZero(&f);
  if ((FP = fopen("check.txt", "w")) == NULL)
  {
    fprintf(stderr, "cannot open the file.");
    exit(-500);
  }
  /* check setInt can transfer */
  while (z < 100000)
  {
    data = pcg32();
    setInt(&f, data);
    data >= 0 ? fprintf(FP, "+%030d\n", data) : fprintf(FP, "%031d\n", data);
    fdispNumber(&f, FP);
    fprintf(FP, "\n");
    z++;
  }
  z = 0;
  fclose(FP);

  /* check getInt can get number */
  output = 0;
  printf("b = ");
  dispNumber(&b);
  printf("\n");
  r = getInt(&b, &output);
  printf("r = %d output = %d\n", r, output);

  while (z < 10000)
  {
    input = xorshift();
    output = 0;
    setInt(&f, input);
    getInt(&f, &output);
    if (input != output)
    {
      printf("input = %d, output = %d\n", input, output);
      break;
    }
    z++;
    if (z == 10000)
    {
      printf("input = %d, output = %d\n", input, output);
    }
  }
  z = 0;

  clearByZero(&g);
  clearByZero(&h);
  while (z < 10000)
  {
    x = xorshift();
    y = xorshift();
    setInt(&g, x);
    setInt(&h, y);
    w = numComp(&g, &h);
    if ((x > y && w != 1) || (x == y && w != 0) || (x < y && w != -1))
    {
      printf("x = %d y = %d w = %d\n", x, y, w);
      break;
    }
    z++;
  }
  z = 0;

  /*check swap a and b */
  printf("a = ");
  dispNumber(&a);
  printf("\n");

  printf("b = ");
  dispNumber(&b);
  printf("\n");

  swap(&a, &b);

  printf("a = ");
  dispNumber(&a);
  printf("\n");

  printf("b = ");
  dispNumber(&b);
  printf("\n");

  for (x = 0; x < KETA - 1;x++){
    for (y = KETA - 1; y > x;y--){
      if(a.n[y - 1] < a.n[y]){
        w = a.n[y - 1];
        a.n[y - 1] = a.n[y];
        a.n[y] = w;
      }
    }
  }

  printf("a = ");
  dispNumber(&a);
  printf("\n");
  /*char ch[] = "1234567892345678902";
  setIntFromString(&g, ch);
  dispNumber(&g);*/

  return 0;
}