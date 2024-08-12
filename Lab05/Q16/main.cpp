#include <stdio.h>
#include <math.h>
int getvar(char a)
{
    int var;
    printf("input %c->",a);
    scanf("%d",&var);
    return var;
}
void wait()
{
    printf("press 0 to continue\n");
    int c; scanf("%d",&c);
}
int main(void)
{
    int n;
    double f;
    n = getvar('n');
    switch(n)
    {
        case 1:printf("outputx=1\n");
        break;
        case 2:printf("outputx=2\n");
        break;
        case 5:printf("outputx=5\n");
        break;
        default:
            if(n != 1 || n != 2 || n != 5)
            {
                printf("wrong input");
                wait();
            }
    };
    wait();

}
