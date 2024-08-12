#include <iostream>
#include <stdio.h>
#include <math.h>

int main()
{
   double F,x;
   printf("Enter x->");
   scanf("%lf",&x);
   F=sin(x)+pow(x,2)+sqrt(x)+pow(sin(x),3);
   F/=x*x+1;
   printf("F(%lf)=%lf\n",x,F);
   int c; scanf("%lf", &c); return 0;
    printf("press 0 to quit\n");
}
