#include<stdio.h>

void int2bin(p){
    
}

int main(void){
    int x = -123456;
    unsigned char *p;

    p = (unsigned char *)&x;
    printf("%02x", *(p + 2));
}