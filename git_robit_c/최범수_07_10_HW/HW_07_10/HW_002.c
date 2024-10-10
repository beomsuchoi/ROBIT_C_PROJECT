#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Node�� data�� �� ���� ��带 ���� ����ü ����
typedef struct Node
{
    int data;
    struct Node* next;
} Node;
//head �ʱ�ȭ
Node* head = NULL;

Node* node_node(int data) // ��� �����
{
    Node* next_node = (Node*)malloc(sizeof(Node));
    if (next_node == NULL)
        return NULL;

    next_node->data = data; // ���ο� ��� �����, ���� data�� ����Ű�� �ؾ� ��
    next_node->next = NULL; // �� �� ���� ��带 ����Ű�� ����

    return next_node;
}

//stack ����
void push(int data)
{
    Node* next_node = node_node(data);//���ο� ��� ����� ������ ����
    next_node->next = head;
    head = next_node;//����ĭ���� �Ű��ֱ�
}
//pop ����
int pop()
{
    if (head == NULL) {
        printf("X\n");
        return -10; //�ƹ��͵� ������
    }

    int pop_data = head->data;
    Node* temp = head;
    head = head->next;//head�� ����ĭ���� ����
    free(temp);
    return pop_data;//pop��Ų �����͸� ����ϱ� ���� ��ȯ
}

int size() // size �Լ�
{
    int cnt = 0;
    Node* temp = head;
    while (temp != NULL) {
        cnt++;
        temp = temp->next;
    }
    return cnt;//cnt�� ������Ű�鼭 ũ�⸦ ����
}

int isEmpty()
{
    return head == NULL;//head�� NULL�� ������ 1 �ƴϸ� 0
}

int top()
{
    if (head == NULL) 
    {
        printf("X\n");//�ƹ��͵� ������ X���
        return -10;
    }
    return head->data;
}

void printStack() // ����Ʈ ����ϴ� �Լ�
{
    Node* tmp = head;
    while (tmp != NULL)
    {
        printf("%d > ", tmp->data);
        tmp = tmp->next;//�ӽ÷� ������ ���� ��� ���� ���� �ű�鼭 print�� ������ִ� ����
    }
    printf("X\n");
}

int main()
{
    char* sentence = (char*)malloc(100 * sizeof(char));//���� �Է¹ޱ�
    int num;

    while (1)
    {
        printf("�Է� : ");
        scanf("%s", sentence);

        // �Է¹��� �Ͱ� �Լ� �� ���ϱ�
        if (strcmp(sentence, "push") == 0)
        {
            printf("���� : ");
            scanf("%d", &num);
            push(num);
        }
        else if (strcmp(sentence, "pop") == 0)
        {
            int pop_num = pop();
            if (pop_num != -10)//�Ʊ� -10 ��ȯ�ϸ� ���°Ŷ� �ƴ� ��쿡 �߷�
            {
                printf("pop�� �� : %d\n", pop_num);
            }
        }
        else if (strcmp(sentence, "size") == 0)
        {
            printf("Size: %d\n", size());
        }
        else if (strcmp(sentence, "top") == 0)
        {
            int top_num = top();
            if (top_num != -10) {//10�� ���� ��
                printf("���� ���� : %d\n", top_num);//���� ������ ���, 
            }
        }
        else if (strcmp(sentence, "isEmpty") == 0)
        {
            if (isEmpty() == 1)
                printf("true\n");//1�̸� ����ִ�
            else
                printf("false\n");//�ƴϸ� ä�����ִ�.
        }
        else if (strcmp(sentence, "printStack") == 0)
        {
            printStack();
        }
        else
            printf("�ٽ� �õ����ּ���.\n");
    }

    free(sentence);
    return 0;
}