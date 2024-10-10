#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


char stack[10][10];  // ���� ����
int top = -1;  // ���� ���� top

//���ÿ� �ִ� �κ�
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
    //�׷��� ������ ������ �߰� ����
    else 
    {
        printf("Error\n");
    }
}

//���ÿ��� �����ϴ� �κ�
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

// ���� �� �κ� Ȯ��
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

// ������ ����ִ��� Ȯ���ϴ� �Լ�
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