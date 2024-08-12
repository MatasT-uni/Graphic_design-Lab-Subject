#include <stdio.h>
#include <stdlib.h>


double A[2][2],AT[2][2];
int i,j;

void input()
{
    for (i = 0;i < 2;++i)
    for(j = 0;j < 2;++j){
        printf("Enter A[%d,%d]->",i,j);
        scanf("%lf",&A[i][j]);
    }
}

void Print_Matrix()
{
    printf("matrix A\n");
    for (i = 0;i <= 1;i++){
        for (j = 0;j <= 1;j++){
            printf("%5.2lf ",A[i][j]);
        }
        printf("\n");
    }
}

void Print_MatrixTranspose()
{
    printf("matrix AT\n");
    for(i = 0;i < 2;i++){
        for (j = 0;j<2;j++)
            AT[j][i] = A[i][j];
    }

    for (i = 0; i< 2; i++) {
        for (j = 0; j < 2; j++){
            printf("%5.2lf ", AT[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    input();
    Print_Matrix();
    Print_MatrixTranspose();
    return 0;
}
