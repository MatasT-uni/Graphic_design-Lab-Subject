#include <stdio.h>
#include <math.h>
#define La 0.14159265 // constant declared. It can not be modified
double A = 0.5;       // global variable all functions and the main can see it
double my_f(double x, double y)
{
    double a, b, c; // local variables only f can see them
    a = A * (1 + y + pow(x, 2) + pow(x, 3));
    b = x + sqrt(x) + La;
    c = a / b;
    return c;
}
double getvar(char a) // inputs an arbitrary floating point variable
{
    double var;
    printf("input %c->", a);
    scanf("%lf", &var);
    return var;
}
void wait()
{
    printf("\n press 0 to quit\n");
    int c;
    scanf("%d", &c);
}
int main()
{
    double x, y, f;
    x = getvar('x');
    y = getvar('y');
    f = my_f(x, y);
    printf("x=%lf, y=%lf, f(x,y)=%lf", x, y, f);
    wait();
}
