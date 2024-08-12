#include <stdio.h>
#include <math.h>
#define A1 7.89161 // constant declared. It can not be modified
double A = 0.5;       // global variable all functions and the main can see it
double my_f(double x, double y, double z)
{
    double a, b; // local variables only f can see them
    a = sqrt(fabs(tan(A1*x)+10*atan(z*y)));
    b = A * a;
    return b;
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
void calculate_fxyz()
{
    double x, y, z, f;
    x = getvar('x');
    y = getvar('y');
    z = getvar('z');
    f = my_f(x, y, z);
    printf("x=%lf, y=%lf, f(x,y)=%lf", x, y, f);
}
int main()
{
    calculate_fxyz();
    calculate_fxyz();
    calculate_fxyz();
    wait();
}
