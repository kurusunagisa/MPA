#include <stdio.h>

void int2bit(unsigned char *p)
{
    int i, j, temp;
    int n[32] = {0};
    for (i = 0; i < 3; i++)
    {
        j = 0;
        temp = *(p + i);
        printf("temp = %d\n", temp);
        while (temp > 1)
        {
            printf("%d", temp % 2);
            temp = temp / 2;
        }
    }
}

    int main(void)
    {
        int x = -123456;
        unsigned char *p;

        p = (unsigned char *)&x;
        printf("%02x %02x %02x %02x\n", *p, *(p + 1), *(p + 2), *(p + 3));
        int2bit(p);
    }