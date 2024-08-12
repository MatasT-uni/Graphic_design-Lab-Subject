#include <stdio.h>
void print_string()
{
int number;
    int i,mn;
    char M1[]="Hello, World!(message 1)\n";
    char M2[]="Hello, Class!(message 2)\n";
    char M3[]="Hello!(message 3)\n";
    printf("How many times to print?");
    scanf("%d",&number);
    while(number>0)
    {
    printf("Message number->");
    scanf("%d", &mn);
    printf("\n");
    for(i=0;i<number;i++)
    {
    switch(mn)
    {
        case 1:printf(M1);break;
        case 2:printf(M2);break;
        case 3:printf(M3);break;
        default:printf("wrong input");break;
    }
   }
   break;
}
{
    while(number<0){
   printf("wrong input\n");
   print_string();
       break;
   }
   }
}
void wait()
{
int c;
    printf("\n press 0 to quit\n");
    scanf("%d",&c);
}
int main()
{
print_string();
wait();
}
