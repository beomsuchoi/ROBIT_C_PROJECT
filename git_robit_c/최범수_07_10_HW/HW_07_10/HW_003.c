#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
//Enqueue ����
void Enqueue(int data)
{
    Node* next_node = node_node(data);
    if (head == NULL) {
        head = next_node;
    }
    else {
        Node* temp = head;//���ο� ��� ����� ������ ����
        while (temp->next != NULL) {
            temp = temp->next;//����ĭ���� �Ű��ֱ�
        }
        temp->next = next_node;
    }
}
//Dequeue ����
int Dequeue()
{
    if (head == NULL) {
        printf("X\n");
        return -10; //�ƹ��͵� ������
    }

    int dequeue_data = head->data;
    Node* temp = head;//head�� ����ĭ���� ����
    head = head->next;
    free(temp);
    return dequeue_data;//Dequeue��Ų �����͸� ����ϱ� ���� ��ȯ
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

int front()
{
    if (head == NULL) {
        printf("��� �ִ�.\n");
        return -10; //��������� -10 ��ȯ
    }
    return head->data;//�ƴϸ� ù��° ��ȯ
}

int rear()
{
    if (head == NULL) {
        printf("��� �ִ�.\n");
        return -10;//��������� -10 ��ȯ
    }

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp->data;//�ƴϸ� �� ������ ������ ��ȯ
}

int isEmpty()
{
    return head == NULL;//head�� NULL�� ������ 1 �ƴϸ� 0
}

void printQueue()
{
    Node* tmp = head;
    while (tmp != NULL)
    {
        printf("%d > ", tmp->data);
        tmp = tmp->next;
    }
    printf("X\n");//�ƹ��͵� ������ X���
}

int main()
{
    char* sentence = (char*)malloc(100 * sizeof(char));
    int num;

    while (1)
    {
        printf("�Է� : ");
        scanf("%s", sentence);

        // �Է¹��� �Ͱ� �Լ� �� ���ϱ�
        if (strcmp(sentence, "Enqueue") == 0)
        {
            printf("���� : ");
            scanf("%d", &num);
            Enqueue(num);
        }
        else if (strcmp(sentence, "Dequeue") == 0)
        {
            int result = Dequeue();
            if (result != -10) {
                printf("Dequeue�� �� : %d\n", result);
            }
        }
        else if (strcmp(sentence, "size") == 0)
        {
            printf("Size: %d\n", size());
        }
        else if (strcmp(sentence, "front") == 0)
        {
            int front_num = front();
            if (front_num != -10)//-10�� ���� ��
            {
                printf("���� ���� : %d\n", front_num);
            }
        }
        else if (strcmp(sentence, "rear") == 0)
        {
            int rear_num = rear();
            if (rear_num != -10) //�Ʊ� -10 ��ȯ�ϸ� ���°Ŷ� �ƴ� ��쿡 ���
            {
                printf("���� �Ʒ��� : %d\n", rear_num);
            }
        }
        else if (strcmp(sentence, "isEmpty") == 0)
        {
            if (isEmpty() == 1)
                printf("true\n");//��������� �Ʊ� ��ȯ���� 1 �ƴϸ� 0
            else
                printf("false\n");
        }
        else if (strcmp(sentence, "printQueue") == 0)
        {
            printQueue();
        }
        else
            printf("�ٽ� �õ����ּ���\n");
    }

    free(sentence);// �ʱ�ȭ
    return 0;
}