#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    //�����Ҵ��� ���� �迭�� ���� ��, �� �Է¹ޱ�
    int x, y;
    int** arr;
    int i, j;
    printf("�Է� : ");
    scanf("%d %d", &x, &y);

    //���ڰ� 1�� ������ ��� �����ϰ�
    int num = 1;
    //�����Ҵ�
    arr = (int**)malloc(sizeof(int*) * x);
    //�迭�� ������ �� �ֱ�
    for (i = 0; i < x; i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * y);
    }
    //�ݺ����� �̿��ؼ� �迭�� num�� �ֱ�
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
    //�迭�� ����� ������ �� ����ϴ� �κ�
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            printf("%d  ", arr[i][j]);
        }
        printf("\n");
    }

    //�� �� �迭�� ������ �� �������ֱ�
    for (i = 0; i < x; i++)
    {
        free(arr[i]);
    }
    free(arr);
    return 0;
}