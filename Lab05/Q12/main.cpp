#include <stdio.h>
void evaluate(int a)
{
    if(a<20)
        printf("this number is less than 20\n");
    else
        printf("this number is greater or equal to 20\n");
    printf("This number is equal to : %d\n",a);
}
double getvar(char a)
{
    double var;
    printf("input %c->",a);
    scanf("%lf",&var);
    return var;
}
void wait()
{
    printf("\n press 0 to quit \n");
    int c;
    scanf("%d",&c);
}
int main(void)
{
    int a;
    int b;
    a = getvar('a');
    evaluate(a);
    b = getvar('b');
    evaluate(b);
    wait();
}
