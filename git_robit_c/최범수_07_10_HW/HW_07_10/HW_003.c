#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Node에 data와 그 다음 노드를 만들 구조체 선언
typedef struct Node
{
    int data;
    struct Node* next;
} Node;
//head 초기화
Node* head = NULL;

Node* node_node(int data) // 노드 만들기
{
    Node* next_node = (Node*)malloc(sizeof(Node));
    if (next_node == NULL)
        return NULL;

    next_node->data = data; // 새로운 노드 만들기, 먼저 data를 가리키게 해야 함
    next_node->next = NULL; // 그 후 다음 노드를 가리키게 설정

    return next_node;
}
//Enqueue 구현
void Enqueue(int data)
{
    Node* next_node = node_node(data);
    if (head == NULL) {
        head = next_node;
    }
    else {
        Node* temp = head;//새로운 노드 만들고 다음에 저장
        while (temp->next != NULL) {
            temp = temp->next;//다음칸으로 옮겨주기
        }
        temp->next = next_node;
    }
}
//Dequeue 구현
int Dequeue()
{
    if (head == NULL) {
        printf("X\n");
        return -10; //아무것도 없을때
    }

    int dequeue_data = head->data;
    Node* temp = head;//head를 다음칸으로 저장
    head = head->next;
    free(temp);
    return dequeue_data;//Dequeue시킨 데이터를 출력하기 위해 반환
}

int size() // size 함수
{
    int cnt = 0;
    Node* temp = head;
    while (temp != NULL) {
        cnt++;
        temp = temp->next;
    }
    return cnt;//cnt를 증가시키면서 크기를 측정
}

int front()
{
    if (head == NULL) {
        printf("비어 있다.\n");
        return -10; //비어있으면 -10 반환
    }
    return head->data;//아니면 첫번째 반환
}

int rear()
{
    if (head == NULL) {
        printf("비어 있다.\n");
        return -10;//비어있으면 -10 반환
    }

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp->data;//아니면 맨 마지막 데이터 반환
}

int isEmpty()
{
    return head == NULL;//head랑 NULL이 같으면 1 아니면 0
}

void printQueue()
{
    Node* tmp = head;
    while (tmp != NULL)
    {
        printf("%d > ", tmp->data);
        tmp = tmp->next;
    }
    printf("X\n");//아무것도 없으면 X출력
}

int main()
{
    char* sentence = (char*)malloc(100 * sizeof(char));
    int num;

    while (1)
    {
        printf("입력 : ");
        scanf("%s", sentence);

        // 입력받은 것과 함수 명 비교하기
        if (strcmp(sentence, "Enqueue") == 0)
        {
            printf("숫자 : ");
            scanf("%d", &num);
            Enqueue(num);
        }
        else if (strcmp(sentence, "Dequeue") == 0)
        {
            int result = Dequeue();
            if (result != -10) {
                printf("Dequeue된 값 : %d\n", result);
            }
        }
        else if (strcmp(sentence, "size") == 0)
        {
            printf("Size: %d\n", size());
        }
        else if (strcmp(sentence, "front") == 0)
        {
            int front_num = front();
            if (front_num != -10)//-10은 없을 때
            {
                printf("가장 위에 : %d\n", front_num);
            }
        }
        else if (strcmp(sentence, "rear") == 0)
        {
            int rear_num = rear();
            if (rear_num != -10) //아까 -10 반환하면 없는거라서 아닌 경우에 출력
            {
                printf("가장 아래에 : %d\n", rear_num);
            }
        }
        else if (strcmp(sentence, "isEmpty") == 0)
        {
            if (isEmpty() == 1)
                printf("true\n");//비어있으면 아까 반환값이 1 아니면 0
            else
                printf("false\n");
        }
        else if (strcmp(sentence, "printQueue") == 0)
        {
            printQueue();
        }
        else
            printf("다시 시도해주세요\n");
    }

    free(sentence);// 초기화
    return 0;
}