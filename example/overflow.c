#include<stdio.h>
#include<float.h>


int main(void){

    int a = 2147483647;
    int b = a + 3;
    int c = -2147483647;
    int d = c - 3;
    double e = 1.7e308;
    double f = 1.8e308;
    double g = 1.2e-308;
    double h = 1.2e-309;
    double i = 1.e-323;
    double j = 1.e-324;
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("c = %d\n", c);
    printf("d = %d\n", d);
    printf("e = %e\n", e);
    printf("f = %e\n", f);
    printf("g = %e\n", g);
    printf("h = %e\n", h);
    printf("i = %e\n", i);
    printf("j = %e\n", j);
    printf("FLT_EPSILON = %e\n", FLT_EPSILON);
    printf("DBL_EPSILON = %e\n", DBL_EPSILON);

    signed int x = 2147483647;
    signed int y = -2147483648;

    printf("%d + 1 = %d\n", x , x + 1);
    printf("%d - 1 = %d\n", y, y - 1);

    //unsigned int a = 4294967295;
    printf("%u + 1 = %u\n", a , a + 1);
    //unsigned int b = 0;
    printf("%u - 1 = %u\n", b, b - 1);
}