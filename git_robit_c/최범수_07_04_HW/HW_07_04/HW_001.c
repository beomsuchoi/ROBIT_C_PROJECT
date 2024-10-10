#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    //동적할당을 위해 배열과 숫자 행, 열 입력받기
    int x, y;
    int** arr;
    int i, j;
    printf("입력 : ");
    scanf("%d %d", &x, &y);

    //숫자가 1일 떄부터 계속 증가하게
    int num = 1;
    //동적할당
    arr = (int**)malloc(sizeof(int*) * x);
    //배열에 데이터 값 넣기
    for (i = 0; i < x; i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * y);
    }
    //반복문을 이용해서 배열에 num값 넣기
    for (i = 1; i <= x; i++)
    {
        for (j = 1; j <= y; j++)
        {
            arr[i - 1][j - 1] = num;
            num++;
        }
    }
    /*
    for (i = 1; i <= x; i++)
    {
        for (j = 1; j <= y; j++)
        {
            arr[i - 1][j - 1];
        }
    }
    */
    //배열에 저장된 데이터 값 출력하는 부분
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            printf("%d  ", arr[i][j]);
        }
        printf("\n");
    }

    //다 쓴 배열에 데이터 값 제거해주기
    for (i = 0; i < x; i++)
    {
        free(arr[i]);
    }
    free(arr);
    return 0;
}