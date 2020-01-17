#include"mulprec.h"

// display Multiple Number
void dispNumber(struct NUMBER *a){
  int i;
  if (getSign(a) == +1)
  {
    printf("+");
  }
  if (getSign(a) == -1)
  {
    printf("-");
  }
  for (i = KETA - 1; i >= 0; i--)
  {
    printf("%10d", a->n[i]);
  }
}

// write Number to File
void fdispNumber(struct NUMBER *a, FILE *FP)
{
  int i;
  if (getSign(a) == +1)
  {
    fprintf(FP, "+");
  }
  if (getSign(a) == -1)
  {
    fprintf(FP, "-");
  }
  for (i = KETA - 1; i >= 0; i--)
  {
    fprintf(FP, "%9d", a->n[i]);
  }
}

// clear Number by ZERO
void clearByZero(struct NUMBER *a)
{
  int i;

  for (i = 0; i < KETA; i++)
  {
    a->n[i] = 000000000;
  }
  setSign(a, +1);
}

// set a's Signature from s
int setSign(struct NUMBER *a, int s)
{
  if (s == +1)
    a->sign = +1;
  else if (s == -1)
    a->sign = -1;
  else
    return -1;
  return 0;
}

// return a's Signature
int getSign(struct NUMBER *a)
{
  return a->sign == +1 ? +1 : -1;
}
