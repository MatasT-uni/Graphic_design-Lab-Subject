#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func1(double x){
    double r = 0;
    for (double i = 0; i <= 5;i++){
        r += sin(i*x) + cos(2*i*x);
    }
    return r;
}

double func2(double x){
    double r = 1;
    for (double i = 1; i <= 12;i++){
        r *= sin(i*x);
    }
    return r;
}

double func3(double x){
    double r = 0;
    r = sin(x*x) + cos(x) - sqrt(x);
    return r;
}

int main (){
    for(int i = -1; i <=3; i++){
        printf("n = %i",i);
        for(double x = 2; x <= 5; x+= 0.5){
            double r;
            switch(i)
            {
            case 1:
                printf(" %5.2lf\t",func1(x));
                break;
            case 0:
                printf(" %5.2lf\t",func2(x));
                break;
            case -1:
                printf(" %5.2lf\t",func3(x));
                break;
            default:printf("  - \t");break;
            }
        }
        printf("\n");
    }
}
