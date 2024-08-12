#include <iostream>
#include <stdio.h>
#include <math.h>

int main()
{
    double F,x,y;
    printf("Enter x->");
    scanf("%lf",&x);
    printf("Enter y->");
    scanf("%lf",&y);
    F=1+pow(sin(x),2)+pow(sin(2 * x),2);
    F/=sqrt(cos(6 * x)+pow(x,3)-tan(y));
    printf("F(%lf,%lf)=%lf\n",x,y,F);
    int c; scanf("%lf", &c); return 0;
    printf("press 0 to quit\n");
}
