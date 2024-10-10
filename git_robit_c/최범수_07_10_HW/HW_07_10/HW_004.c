#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node�� data�� �� ���� ��带 ���� ����ü ����
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// stack, queue �ʱ�ȭ
Node* stack_stack = NULL;
Node* queue_queue = NULL;

Node* node_node(char data) { // ��� �����
    Node* next_node = (Node*)malloc(sizeof(Node));
    if (next_node == NULL)
        return NULL;

    next_node->data = data; // ���ο� ��� �����, ���� data�� ����Ű�� �ؾ� ��
    next_node->next = NULL; // �� �� ���� ��带 ����Ű�� ����

    return next_node;
}

void push(char num) { // ���ÿ� push
    Node* next_node = node_node(num); // ���ο� ��� ����� ������ ����
    next_node->next = stack_stack;
    stack_stack = next_node; // ���� ĭ���� �Ű��ֱ�
}

char pop() { // ���ÿ��� ��
    if (stack_stack == NULL) {
        return '\0';
    }
    char pop_num = stack_stack->data;
    Node* tmp = stack_stack;
    stack_stack = stack_stack->next;
    free(tmp);
    return pop_num; // pop �� ���ڸ� ��ȯ
}

void enqueue(char num) { // ť�� enqueue
    Node* next_node = node_node(num); // ���ο� ��� ����� ������ ����
    if (queue_queue == NULL) {
        queue_queue = next_node; // queue�� next��� ����
    }
    else {
        Node* tmp = queue_queue; // 0�� �ƴϸ� �� ���� �ӽ� ��� ����� �ӽ� ��� ������ ��忡 ���� ��� �� ����
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = next_node;
    }
}

char dequeue() { // stack�� popó�� �̹����� �ݴ�� ť�� dequeue, ���� �� ù��°, �� �ڹ�°�� ���ڸ� ���ϱ� ���� ���
    if (queue_queue == NULL) {
        return '\0';
    }
    char dequeue_num = queue_queue->data;
    Node* tmp = queue_queue;
    queue_queue = queue_queue->next;
    free(tmp);
    return dequeue_num; // dequeue�� ���� ��ȯ
}

int main() {
    char sentence[1000] = "";
    char cleaned_sentence[1000] = "";
    int num = 0;

    printf("�Է� : ");
    scanf("%[^\n]", sentence); // ���� �Է¹ް�, ���� ����

    // ���� �����Ͽ� cleaned_sentence�� ����
    for (int i = 0; i < strlen(sentence); i++) {
        if (sentence[i] != ' ') {
            cleaned_sentence[num++] = sentence[i];
        }
    }
    cleaned_sentence[num] = '\0'; // ���ڿ��� ���� �˸��� null ���� �߰�

    // cleaned_sentence�� �� ���ڸ� ���ð� ť�� �ֱ�
    for (int i = 0; i < strlen(cleaned_sentence); i++) {
        push(cleaned_sentence[i]); // push, enqueue�� ���� ���ĺ� �Է�
        enqueue(cleaned_sentence[i]);
    }

    // ���ð� ť���� ������ ��
    int palindraome = 1;
    for (int i = 0; i < strlen(cleaned_sentence); i++) {
        if (pop() != dequeue()) {
            palindraome = 0;
            break;
        }
    }

    if (palindraome == 1) { // ȸ���̸�
        printf("ȸ���̴�.\n");
    }
    else { // ȸ���� �ƴϸ�
        printf("ȸ���� �ƴϴ�.\n");
    }

    return 0;
}
