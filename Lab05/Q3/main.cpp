#include <iostream>
#include <stdio.h>

int main()
{
    float R1, R2, Product;
    printf("Enter the first floating number; ");
    scanf("%f",&R1);
    printf("Enter the second floating number; ");
    scanf("%f",&R2);
    Product=R1*R2;
    printf("%f*%f=%f\n",R1,R2,Product);
    printf("press 0 to quit\n");
    int c;scanf("%f",&c);
    return 0;
}
