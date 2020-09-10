#include<stdio.h>

int main(int argc, char **argv)
{
    float x = -12.3456;
    unsigned char *p;

    p = (unsigned char *)&x;
    printf("%02x %02x %02x %02x\n", *p, *(p + 1), *(p + 2), *(p + 3));

    return 0;
}