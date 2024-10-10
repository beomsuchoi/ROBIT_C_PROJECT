#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//stack 구현
void push(int data)
{
    Node* next_node = node_node(data);//새로운 노드 만들고 다음에 저장
    next_node->next = head;
    head = next_node;//다음칸으로 옮겨주기
}
//pop 구현
int pop()
{
    if (head == NULL) {
        printf("X\n");
        return -10; //아무것도 없을때
    }

    int pop_data = head->data;
    Node* temp = head;
    head = head->next;//head를 다음칸으로 저장
    free(temp);
    return pop_data;//pop시킨 데이터를 출력하기 위해 반환
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

int isEmpty()
{
    return head == NULL;//head랑 NULL이 같으면 1 아니면 0
}

int top()
{
    if (head == NULL) 
    {
        printf("X\n");//아무것도 없으면 X출력
        return -10;
    }
    return head->data;
}

void printStack() // 리스트 출력하는 함수
{
    Node* tmp = head;
    while (tmp != NULL)
    {
        printf("%d > ", tmp->data);
        tmp = tmp->next;//임시로 저장한 값을 계속 다음 노드로 옮기면서 print를 계속해주는 과정
    }
    printf("X\n");
}

int main()
{
    char* sentence = (char*)malloc(100 * sizeof(char));//문장 입력받기
    int num;

    while (1)
    {
        printf("입력 : ");
        scanf("%s", sentence);

        // 입력받은 것과 함수 명 비교하기
        if (strcmp(sentence, "push") == 0)
        {
            printf("숫자 : ");
            scanf("%d", &num);
            push(num);
        }
        else if (strcmp(sentence, "pop") == 0)
        {
            int pop_num = pop();
            if (pop_num != -10)//아까 -10 반환하면 없는거라서 아닌 경우에 추력
            {
                printf("pop된 값 : %d\n", pop_num);
            }
        }
        else if (strcmp(sentence, "size") == 0)
        {
            printf("Size: %d\n", size());
        }
        else if (strcmp(sentence, "top") == 0)
        {
            int top_num = top();
            if (top_num != -10) {//10은 없을 때
                printf("가장 위에 : %d\n", top_num);//가장 위에값 출력, 
            }
        }
        else if (strcmp(sentence, "isEmpty") == 0)
        {
            if (isEmpty() == 1)
                printf("true\n");//1이면 비어있다
            else
                printf("false\n");//아니면 채워져있다.
        }
        else if (strcmp(sentence, "printStack") == 0)
        {
            printStack();
        }
        else
            printf("다시 시도해주세요.\n");
    }

    free(sentence);
    return 0;
}