#include <stdio.h>
	int n1=2,n2,i;
void oddnumber()
{
    while (n1%2==0)//remainder
	{
	printf("enter an odd number n1->");
	scanf("%d", &n1);
	}
	printf("enter n2->");
	scanf("%d", &n2);
}
void wait()
{
int c;
    printf("\n press 0 to quit\n");
    scanf("%d",&c);
}

int main()
{
oddnumber();
//for loop
printf("for-loop\n");
for (i=n1;i<=n2;i+=2)
printf("%d ",i);
printf("\n");
i=n1;//initialization
printf("while-loop\n");
//while loop
while(i<=n2)
{
printf("%d ",i);
i+=2;
}
printf("\n");
i=n1;//initialization
//do-while loop
printf("do-while-loop\n");
do
{
printf("%d ",i);
i+=2;
}
while(i<=n2);
wait();
return 0;
}
