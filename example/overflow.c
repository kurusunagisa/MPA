#include<stdio.h>


int main(void){

    signed int x = 2147483647;
    signed int y = -2147483648;

    printf("%d + 1 = %d\n", x , x + 1);
    printf("%d - 1 = %d\n", y, y - 1);

    unsigned int a = 4294967295;
    printf("%u + 1 = %u\n", a , a + 1);
    unsigned int b = 0;
    printf("%u - 1 = %u\n", b, b - 1);
}