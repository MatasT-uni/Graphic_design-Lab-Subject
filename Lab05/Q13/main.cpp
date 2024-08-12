#include<stdio.h>
double Divide(int a, int b)
{
    if (b==0)
        printf("division by zero");
    double r;
    r = (double) a/b;
    if (b!=0)
        printf("Result -> %lf",r);
}
double getvar(char a)//inputs an arbitrary floating point variable
{
    int var;
    printf("Input %c-> ",a);
    scanf("%d", &var);
    return var;
}
void wait()
{
printf("\n press 0 to continue\n");
int c; scanf("%d",&c);
}
int main()
{
    int a,b;
    a = getvar('a');
    b = getvar('b');
    Divide(a,b);
}
