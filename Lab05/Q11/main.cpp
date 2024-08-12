#include <stdio.h>
int main()
{
    int a;
    printf("input a ->");
    scanf("%d",&a);
    if(a<20)
        printf("a is less than 20\n");
        else
        printf("a is greater or equal to 20\n");
        printf("value of a is:%d\n",a);
        return 0;
}
