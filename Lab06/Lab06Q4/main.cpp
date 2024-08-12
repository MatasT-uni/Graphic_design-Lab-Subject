#include <stdio.h>
#include <math.h>
int nmin,nmax;
double x;
double func(double x, int n);
void input();
void Print_Table();
void wait();
int main()
{
input();
Print_Table();
wait();
}
void Print_Table()
{int n;
    for (n=nmin;n<=nmax;n++)
{   printf("n=%d",n);
    for (x=2;x<=4;x+=0.5)
     printf("%5.2lf ",func(x,n));
     printf("\n");
}
}
double func(double x, int n)
{ double sum=0; int i;
for (i=0;i<=n;i++)
sum+=sin(x*i)+cos(2*x*i);
return sum;
}
void input()
{
printf("nmin->");
scanf("%d",&nmin);
printf("nmax->");
scanf("%d",&nmax);
}
void wait()
{int c;
printf("\n press 0 to quit\n");
scanf("%d",&c);
}
