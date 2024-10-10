#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


char stack[10][10];  // 스택 만듦
int top = -1;  // 가장 위를 top

//스택에 넣는 부분
void push(char* tag) 
{
    if (top < 9)
    {
        top++;
        int i = 0;
        while (tag[i] != '\0' && i < 9) 
        {
            stack[top][i] = tag[i];
            i++;
        }
        stack[top][i] = '\0';
    }
    //그렇지 않으면 오류가 뜨게 설정
    else 
    {
        printf("Error\n");
    }
}

//스택에서 제거하는 부분
char* pop()
{
    if (top >= 0) 
    {
        return stack[top--];
    }
    else 
    {
        return NULL;
    }
}

// 가장 위 부분 확인
char* top_top() 
{
    if (top >= 0) 
    {
        return stack[top];
    }
    else 
    {
        return NULL;
    }
}

// 스택이 비어있는지 확인하는 함수
int No_stack() {
    return top == -1;
}

int main()
{
    int **arr;
    int num;

    arr = (int**)malloc(sizeof(int*) * num);
    for (int i = 0; i < num; i++)
    {
        arr[i] = (int*)malloc(sizeof(int) * num);
    }
}