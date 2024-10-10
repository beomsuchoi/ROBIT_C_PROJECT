#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node에 data와 그 다음 노드를 만들 구조체 선언
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// stack, queue 초기화
Node* stack_stack = NULL;
Node* queue_queue = NULL;

Node* node_node(char data) { // 노드 만들기
    Node* next_node = (Node*)malloc(sizeof(Node));
    if (next_node == NULL)
        return NULL;

    next_node->data = data; // 새로운 노드 만들기, 먼저 data를 가리키게 해야 함
    next_node->next = NULL; // 그 후 다음 노드를 가리키게 설정

    return next_node;
}

void push(char num) { // 스택에 push
    Node* next_node = node_node(num); // 새로운 노드 만들고 다음에 저장
    next_node->next = stack_stack;
    stack_stack = next_node; // 다음 칸으로 옮겨주기
}

char pop() { // 스택에서 팝
    if (stack_stack == NULL) {
        return '\0';
    }
    char pop_num = stack_stack->data;
    Node* tmp = stack_stack;
    stack_stack = stack_stack->next;
    free(tmp);
    return pop_num; // pop 한 숫자를 반환
}

void enqueue(char num) { // 큐에 enqueue
    Node* next_node = node_node(num); // 새로운 노드 만들고 다음에 저장
    if (queue_queue == NULL) {
        queue_queue = next_node; // queue에 next노드 저장
    }
    else {
        Node* tmp = queue_queue; // 0이 아니면 그 다음 임시 노드 만들고 임시 노드 다음의 노드에 다음 노드 값 저장
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = next_node;
    }
}

char dequeue() { // stack에 pop처럼 이번에는 반대로 큐에 dequeue, 각각 맨 첫번째, 맨 뒤번째의 숫자를 비교하기 위해 사용
    if (queue_queue == NULL) {
        return '\0';
    }
    char dequeue_num = queue_queue->data;
    Node* tmp = queue_queue;
    queue_queue = queue_queue->next;
    free(tmp);
    return dequeue_num; // dequeue된 숫자 반환
}

int main() {
    char sentence[1000] = "";
    char cleaned_sentence[1000] = "";
    int num = 0;

    printf("입력 : ");
    scanf("%[^\n]", sentence); // 문장 입력받고, 띄어쓰기 포함

    // 띄어쓰기 제거하여 cleaned_sentence에 저장
    for (int i = 0; i < strlen(sentence); i++) {
        if (sentence[i] != ' ') {
            cleaned_sentence[num++] = sentence[i];
        }
    }
    cleaned_sentence[num] = '\0'; // 문자열의 끝을 알리는 null 문자 추가

    // cleaned_sentence의 각 문자를 스택과 큐에 넣기
    for (int i = 0; i < strlen(cleaned_sentence); i++) {
        push(cleaned_sentence[i]); // push, enqueue에 각각 알파벳 입력
        enqueue(cleaned_sentence[i]);
    }

    // 스택과 큐에서 꺼내어 비교
    int palindraome = 1;
    for (int i = 0; i < strlen(cleaned_sentence); i++) {
        if (pop() != dequeue()) {
            palindraome = 0;
            break;
        }
    }

    if (palindraome == 1) { // 회문이면
        printf("회문이다.\n");
    }
    else { // 회문이 아니면
        printf("회문이 아니다.\n");
    }

    return 0;
}
