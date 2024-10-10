#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


void print(int* row, int* col, int** pArr);
void arr_ij(int* sizeRow, int* sizeCol, int** pArr);

int main()
{
    int** arr = NULL;
    int row, col, sizeRow, sizeCol; // row: ��, col: ��

    //��, �� �Է�
    printf("���� ���� �Է��ϼ��� : ");
    scanf("%d", &sizeRow);
    printf("���� ���� �Է��ϼ��� : ");
    scanf("%d", &sizeCol);

    //���� �Ҵ� 2���� �迭
    arr = (int**)malloc(sizeof(int*) * sizeRow);
    for (int i = 0; i < sizeRow; i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * sizeCol);
    }

    row = sizeRow;
    col = sizeCol;

    //�迭����� �Լ� ����
    arr_ij(&row, &col, arr);

    //��� �Լ� ����
    print(&row, &col, arr);

    //����
    for (int i = 0; i < row; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

void print(int* row, int* col, int** pArr) //����Լ�
{
    for (int i = 0; i < *row; i++)
    {
        for (int j = 0; j < *col; j++)
        {
            printf("%4d", pArr[i][j]);
        }
        printf("\n");
    }
}

void arr_ij(int* sizeRow, int* sizeCol, int** pArr) //������ ��� ä��� �Լ�
{
    int num = 1;//�迭 ����

    int cnt_i = 0; //��
    int cnt_j = 0; //��

    //cnt_i�� cnt_j�� �̿��ؼ� ���� ��ġ�� �� �� �ְ�, �迭�� ����� �� ���⿡ ���� i, j�� ����� ������
    int top = 0, bottom = *sizeRow - 1;
    int left = 0, right = *sizeCol - 1;

    while (top <= bottom && left <= right)//for���� ������ �� ĭ �� �����̴� ������ �迭�� 0���� ���������� ���ڴ� 1���� �����ؼ� �ϳ��� ����� ������ �´�. 
    {
        //������ 0�������� �ִ�, ���� ����
        for (cnt_j = left; cnt_j <= right; cnt_j++)
            pArr[cnt_i][cnt_j] = num++;
        top++;
        cnt_j--;//1�� �ٿ��� ��ĭ �������� �̵� ����

        //�� ���� 0 �Ʒ��� �ִ�, ���� ����
        for (cnt_i = top; cnt_i <= bottom; cnt_i++)
            pArr[cnt_i][cnt_j] = num++;
        right--;
        cnt_i--;//��ĭ ����

        if (top <= bottom)
        {//�����ʿ��� ����
            for (cnt_j = right; cnt_j >= left; cnt_j--)
                pArr[cnt_i][cnt_j] = num++;
            bottom--;
            cnt_j++;//��ĭ ������
        }

        if (left <= right)
        {//�Ʒ����� ����
            for (cnt_i = bottom; cnt_i >= top; cnt_i--)
                pArr[cnt_i][cnt_j] = num++;
            left++;
            cnt_i++; //��ĭ �Ʒ�
        }
    }
}
