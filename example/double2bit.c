#include<stdio.h>

int main(int argc, char **argv)
{
    double x = -3.14159;
    unsigned char *p;

    p = (unsigned char *)&x;
    printf("%02x %02x %02x %02x %02x %02x %02x %02x\n", *p, *(p + 1), *(p + 2), *(p + 3), *(p + 4), *(p + 5), *(p + 6), *(p + 7));

    return 0;
}