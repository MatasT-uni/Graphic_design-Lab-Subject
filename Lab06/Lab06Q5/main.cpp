#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int nmin,nmax;
double xmin,xmax,stepx;
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

void Print_Table(){
int n;

printf("x=");
    for(x=xmin;x<=xmax;x+=stepx)
            printf("%5.2lf",x); //for table
            printf("\n");

    for(n=nmin;n<=nmax;n++){

            printf("n=%d",n);

            for(x=xmin;x<=xmax;x+=stepx)
                printf("%5.2lf",func(x,n)); //for table
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
printf("xmin->");
scanf("%lf",&xmin);
printf("xmax->");
scanf("%lf",&xmax);
printf("step->");
scanf("%lf",&stepx);
}
void wait()
{int c;
printf("\n press 0 to quit\n");
scanf("%d",&c);
}
