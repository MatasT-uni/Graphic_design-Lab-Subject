#include <stdio.h>
#include <string.h>
int input_int(char me[20]); //function prototype
int main()
{int mn, number;
    char M1[]="Hello, World!(message 1)\n";
    char M2[]="Hello, Class!(message 2)\n";
    char M3[]="Hello!(message 3)\n";
    number=input_int("How many times to print?");
    mn=input_int("message->");
    int i=0;
    printf("While loop\n");
    while (i++<number)//for(i=0;i<number;i++)
    {
    switch(mn)
    {
        case 1:printf(M1);break;
        case 2:printf(M2);break;
        default:printf(M3);
    }
   }
if (number%2 == 1) printf(".............\n"); else printf("-------------\n");
printf("do while loop\n");
i=1;
do
{
switch(mn)
    {
        case 1:printf(M1);break;
        case 2:printf(M2);break;
        default:printf(M3);
    }
    }
while (i++<=number);
if (number%2==1) printf("$$$$$$$$$$$$$\n"); else printf("*************\n");
int c;
printf("\n press 0 to quit\n");
scanf("%d",&c);
return 0;
}
int input_int(char message[20])
{int m;
printf("%s",message);
scanf("%d",&m);
return m;
};

