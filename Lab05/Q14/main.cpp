#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void func(double x)
{
    if(x>1 || x<0)
        printf("Negative argument\n");
    double r;
    r = sqrt(x)+sin(x)+sqrt(1-x);
    if(x<=1 && x>=0)
        printf("f = %lf",r);
}
double getvar(char a)
{
    double var;
    printf("Input %c -> ",a);
    scanf("%lf",&var);
    return var;
}
int main()
{
    double x;
    x = getvar('x');
    func(x);
    x = getvar('x');
    func(x);
    x = getvar('x');
    func(x);
    exit(0);

}
