#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Node�� data�� �� ���� ��带 ���� ����ü ����
typedef struct _Node
{
    int data;
    struct _Node* next;
} Node;

//���� �Ӹ��κ� �ʱ�ȭ
Node* head = NULL;

Node* node_node(int data) // ��� �����
{
    Node* next_node = (Node*)malloc(sizeof(Node));
    if (next_node == NULL)
        return NULL;

    next_node->data = data; // ���ο� ��� �����, ���� data�� ����Ű�� �ؾ� ��
    next_node->next = NULL; // �� �� ���� ��带 ����Ű�� ����

    return next_node;//������� ��� ��ȯ
}

//�Լ��� �Ʒ����� ���� ������ ����
void insert(int num, int data);
void insert_back(int data);
void insert_first(int data);
void delete(int num);
void delete_back();
void delete_first();
int get_entry(int data);
int get_length();
void print_list();
void reverse();

int main()
{
    // �����Ҵ��� �̿��ؼ� sentence�� ���� �Է¹ޱ�
    char* sentence = (char*)malloc(100 * sizeof(char));
    int* num = (int*)malloc(sizeof(int));
    int* data = (int*)malloc(sizeof(int));


    //char sort[100];//get_entry���� data�� ã���� index�� ã���� ���� ����

    // ���ѹݺ� ��Ű��
    while (1)
    {
        printf("�Է� : ");
        scanf("%s", sentence);

        // �Է¹��� �Ͱ� �Լ� �� ���ϱ�
        if (strcmp(sentence, "insert") == 0)
        {
            printf("��ȣ�� ������ : ");
            scanf("%d %d", num, data);
            insert(*num, *data);//insert �Լ�
        }
        else if (strcmp(sentence, "insert_back") == 0)
        {
            printf("������ : ");
            scanf("%d", data);
            insert_back(*data);
        }
        else if (strcmp(sentence, "insert_first") == 0)
        {
            printf("������ : ");
            scanf("%d", data);
            insert_first(*data);
        }
        else if (strcmp(sentence, "delete") == 0)
        {
            printf("��ȣ : ");
            scanf("%d", num);
            delete(*num);
        }
        else if (strcmp(sentence, "delete_first") == 0)
        {
            delete_first();
        }
        else if (strcmp(sentence, "delete_back") == 0)
        {
            delete_back();
        }
        else if (strcmp(sentence, "get_entry") == 0)
        {
            printf("������ : ");
            scanf("%d", data);
            int num = get_entry(*data);


            if (num != -10)
            {
                printf("����Ʈ�� %d ��°��\n", num);
            }
            else 
            {
                printf("����Ʈ�� ����.");
            }
        }
        else if (strcmp(sentence, "get_length") == 0)
        {
            printf("���� : %d\n", get_length());
        }
        else if (strcmp(sentence, "print_list") == 0)
        {
            print_list();
        }
        else if (strcmp(sentence, "reverse") == 0)
        {
            reverse();
        }
        else
        {
            printf("�߸��� ����Դϴ�.\n");
        }
    }

    free(sentence);
    free(num);
    free(data);

    return 0;
}

void insert(int num, int data) // insert �Լ�
{
    Node* next_node = node_node(data);//���ο� node �����

    if (head == NULL) {
        // ����Ʈ�� ����ִ� ���
        if (num == 0) {
            head = next_node;
        }//�ٽ� �����ϰ� ����
        return;
    }
    Node* now = head;
    for (int i = 0; now->next != NULL && i < num; i++) {
        now = now->next;//���� ��带 ���� ��忡 �־ ���ο� ��忡 �����Ϳ� ��ȣ �ޱ�
    }

    next_node->next = now->next;
    now->next = next_node;
}

void insert_back(int data) // insert_back �Լ�
{
    Node* next_node = node_node(data);
    if (head == NULL) {
        head = next_node;
    }//��尡 ���°� �ƴ϶��
    else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = next_node;
        //null�� �ƴҶ����� ������ �������� ã�� �ű⿡ ���ο� ��� �����
    }
}

void insert_first(int data) // insert_first �Լ�
{
    Node* next_node = node_node(data);
    next_node->next = head;
    head = next_node;
    //�׳� �ٷ� ó�� �κп� ���ο� ��� ����� �ȴ�.
}

void delete(int num) // delete �Լ�
{
    if (head == NULL)
        return;//�ƹ��͵� ���� ��

    if (num == 0) { // ù ��° ��带 �����ϴ� ���
        Node* temp = head;
        head = head->next;
        free(temp);
        return;//delete_first ��� �Ұ���, ���� delete_first�� ������, �ȵż� ���ǹ����� �ٽ� �������
    }

    Node* tmp = head;
    for (int i = 0; i < num - 1; ++i) 
    {
        if (tmp->next == NULL)
            return;
        tmp = tmp->next;//������ null�̶�� �ٽ� ����
    }

    Node* delete_delete = tmp->next;//���� ��� �����

    if (delete_delete == NULL)
        return; //������ �� ���� ��
    tmp->next = delete_delete->next;//�ӽ÷� ������ ��忡 ���� ��� �Է�
    free(delete_delete);//�ʱ�ȭ
}


void delete_back() // delete_back �Լ�
{
    if (head == NULL)//���� ��
        return;

    if (head->next == NULL)
    {
        free(head);
        head = NULL;
        return;
    }

    Node* tmp = head;
    while (tmp->next->next != NULL) 
    {
        tmp = tmp->next;
    }//�ӽ� ���������� null�� �ƴ� ������ �ӽÿ� ������ ����

    free(tmp->next);
    tmp->next = NULL;//�׸��� ����
}

void delete_first() // delete_first �Լ�
{
    if (head == NULL) return;
    Node* tmp = head;
    head = head->next;
    free(tmp);
}//insert_first�� ���������� �׳� �ٷ� ó���� �����

int get_entry(int data) // get_entry �Լ�
{
    Node* tmp = head;//�� ó������ ����
    int num = 0;
    while (tmp != NULL) //�ӽð� ���� �ƴ� ����
    {
        if (tmp->data == data)//�����ѰͰ� data�� ������ �� ���� ��ȯ
        {
            return num;
        }
        tmp = tmp->next;
        num++;//���� ��� �������Ѽ� ���� Ȯ��
    }
    return -10; // �����Ͱ� ���� ���
}

int get_length() // get_length �Լ�
{
    int cnt = 0;//count�ϴ°�

    Node* tmp = head;
    while (tmp != NULL) //�ӽð� ���� �ƴѵ���
    {
        cnt++;
        tmp = tmp->next;//ī��Ʈ ����, �ӽÿ��� ��� ���� ��带 ����
    }
    return cnt;//�׷��� ��ȯ�� ī��Ʈ�� ��ȯ�ؼ� ���̸� �˰� ��
}

void print_list() // ����Ʈ ����ϴ� �Լ�
{
    Node* tmp = head;
    while (tmp != NULL)//���� �ƴ� ������
    {
        printf("%d > ", tmp->data);
        tmp = tmp->next;//data�� ����ϰ� �� ���� ���� �̵�
    }
    printf("X\n");//�� �������� X�� ������ ��Ÿ����.
}

void reverse() // ����Ʈ ������ �Լ�
{
    Node* left = NULL;
    Node* cur = head;
    Node* right = NULL;

    while (cur != NULL)//�߽��� ���� �ƴϸ�
    {
        right = cur->next;//������ �����Ϳ� ���� ��� ����
        cur->next = left;//���� ��忡 ���� ������
        left = cur;//������ ����
        cur = right;//����� ������ ������ ����
    }
    head = left;//�׸��� ��ĭ�� �������� �̵�
}
