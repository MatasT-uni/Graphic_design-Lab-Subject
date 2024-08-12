#include<stdio.h>
double formula(double x)
{double f;
if ((x>=0) && (x<=1)) f=1;
if ((x<0) || (x>1)) f=x*x+1;
return f;
}
double getvar(char a)//inputs an arbitrary floating point variable
{double var;
printf("input %c->",a);
scanf("%lf",&var);
return var;
}
void wait()
{
printf("\n press 0 to continue\n");
int c; scanf("%d",&c);
}
int main()
{
//your code here
double x,f;
x = getvar('x');
f = formula(x);
printf("x=%lf,f(x,y)=%lf",x,f);
wait();
x = getvar('x');
f = formula(x);
printf("x=%lf,f(x,y)=%lf",x,f);

}
