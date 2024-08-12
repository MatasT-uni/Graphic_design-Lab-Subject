#include <stdio.h>
#include <math.h>
#define imax 10
#define jmax 10
void print_2D(int A[imax][jmax], int);
void wait();
int na;
int main()
{
int A[]={2,5,7,8};
int V[imax][jmax];//declare a 2D array
int i,j,n;
na=sizeof(A)/sizeof(int);
printf("size of A=%d\n",na);
printf("Enter n(max power)->");
scanf("%d",&n);
for (i=0;i<na;i++)
for (j=0;j<=n;j++)
V[i][j]=pow(A[i],j);
print_2D(V,n);
wait();
return 0;
}
void print_2D(int A[imax][jmax], int n)
{int i,j;
for (i=0;i<na;i++)
{
for (j=0;j<=n;j++)
printf("%6d ",A[i][j]);
printf("\n");
}
}
void wait(void)
{int c;
printf("\n press 0 to quit\n");
scanf("%d",&c);
}
