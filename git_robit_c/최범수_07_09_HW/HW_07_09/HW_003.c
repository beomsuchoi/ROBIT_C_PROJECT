#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


void print(int* row, int* col, int** pArr);
void arr_ij(int* sizeRow, int* sizeCol, int** pArr);

int main()
{
    int** arr = NULL;
    int row, col, sizeRow, sizeCol; // row: 열, col: 행

    //열, 행 입력
    printf("열의 수를 입력하세요 : ");
    scanf("%d", &sizeRow);
    printf("행의 수를 입력하세요 : ");
    scanf("%d", &sizeCol);

    //동적 할당 2차원 배열
    arr = (int**)malloc(sizeof(int*) * sizeRow);
    for (int i = 0; i < sizeRow; i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * sizeCol);
    }

    row = sizeRow;
    col = sizeCol;

    //배열만드는 함수 선언
    arr_ij(&row, &col, arr);

    //출력 함수 선언
    print(&row, &col, arr);

    //해제
    for (int i = 0; i < row; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

void print(int* row, int* col, int** pArr) //출력함수
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

void arr_ij(int* sizeRow, int* sizeCol, int** pArr) //달팽이 모양 채우는 함수
{
    int num = 1;//배열 숫자

    int cnt_i = 0; //행
    int cnt_j = 0; //열

    //cnt_i와 cnt_j를 이용해서 현재 위치를 알 수 있고, 배열을 출력할 때 방향에 따라 i, j로 나누어서 움직임
    int top = 0, bottom = *sizeRow - 1;
    int left = 0, right = *sizeCol - 1;

    while (top <= bottom && left <= right)//for문이 끝나고 한 칸 씩 움직이는 이유는 배열은 0에서 시작하지만 숫자는 1부터 시작해서 하나를 빼줘야 순서가 맞다. 
    {
        //왼쪽이 0오른쪽이 최대, 숫자 저장
        for (cnt_j = left; cnt_j <= right; cnt_j++)
            pArr[cnt_i][cnt_j] = num++;
        top++;
        cnt_j--;//1을 줄여야 한칸 왼쪽으로 이동 가능

        //맨 위가 0 아래가 최대, 숫자 저장
        for (cnt_i = top; cnt_i <= bottom; cnt_i++)
            pArr[cnt_i][cnt_j] = num++;
        right--;
        cnt_i--;//한칸 위로

        if (top <= bottom)
        {//오른쪽에서 왼쪽
            for (cnt_j = right; cnt_j >= left; cnt_j--)
                pArr[cnt_i][cnt_j] = num++;
            bottom--;
            cnt_j++;//한칸 오른쪽
        }

        if (left <= right)
        {//아래에서 위로
            for (cnt_i = bottom; cnt_i >= top; cnt_i--)
                pArr[cnt_i][cnt_j] = num++;
            left++;
            cnt_i++; //한칸 아래
        }
    }
}
