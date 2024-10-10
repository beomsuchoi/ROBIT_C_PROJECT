#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student{
    int number;
    char name[30];
    char country[30];
    char city[30];
    char gu[30];
    char grade;
} student;

student* students[50];
int student_count = 0;

void print_students()
{
    for (int i = 0; i < student_count; i++) 
    {
        printf("�л�: %d, %s, %s, %s, %s, %c\n", students[i]->number, students[i]->name, students[i]->country, students[i]->city, students[i]->gu, students[i]->grade);
    }
}

void sort_student(int sort)
{
    int i, j;
    student* tmp_sort;
    for (i = 0; i < student_count - 1; i++)
    {
        for (j = i + 1; j < student_count; j++)
        {
            int tmp = 0;
            switch (sort)
            {
                case 1: tmp = students[i]->number - students[j]->number; break;
                case 2: tmp = strcmp(students[i]->name, students[j]->name); break;
                case 3:tmp = strcmp(students[i]->country, students[j]->country);

                if (tmp == 0) 
                {
                    tmp = strcmp(students[i]->city, students[j]->city);
                    if (tmp == 0) {
                        tmp = strcmp(students[i]->gu, students[j]->gu);
                    }
                }
                break;

                case 4: tmp = students[i]->grade - students[j]->grade; break;
            }
            if (tmp > 0)
            {
                tmp_sort = students[i];
                students[i] = students[j];
                students[j] = tmp_sort;
            }
        }
    }
    print_students();
}

void find_student()
{
    int sort, num = 0;
    char sentence[100];
    printf("(1 : ��ȣ) (2 : �ּ�) (3 : ����)\n");
    scanf("%d", &sort);

    if (sort == 1) 
    {
        printf("��ȣ �Է�: ");
        scanf("%d", &num);
        for (int i = 0; i < student_count; i++) 
        {
            if (students[i]->number == num)
            {
                printf("�л�: %d, %s, %s, %s, %s, %c\n", students[i]->number, students[i]->name, students[i]->country, students[i]->city, students[i]->gu, students[i]->grade);
            }
        }
    }
    else if (sort == 2) 
    {
        printf("�ּ� �Է�: ");
        scanf("%s", sentence);
        for (int i = 0; i < student_count; i++) 
        {
            if (strstr(students[i]->country, sentence) != NULL || strstr(students[i]->city, sentence) != NULL || strstr(students[i]->gu, sentence) != NULL) {
                printf("�л�: %d, %s, %s, %s, %s, %c\n", students[i]->number, students[i]->name, students[i]->country, students[i]->city, students[i]->gu, students[i]->grade);
            }
        }
    }
    else if (sort == 3)
    {
        printf("���� �Է�: ");
        scanf(" %c", sentence);
        for (int i = 0; i < student_count; i++) 
        {
            if (students[i]->grade == sentence[0]) 
            {
                printf("�л�: %d, %s, %s, %s, %s, %c\n", students[i]->number, students[i]->name, students[i]->country, students[i]->city, students[i]->gu, students[i]->grade);
            }
        }
    }
}

void add_student() 
{
    if (student_count < 50) 
    {
        students[student_count] = (student*)malloc(sizeof(student));
        if (students[student_count] != NULL)
        {
            printf("��ȣ �Է�: ");
            scanf("%d", &students[student_count]->number);
            printf("�̸� �Է�: ");
            scanf("%s", students[student_count]->name);
            printf("���� �Է�: ");
            scanf("%s", students[student_count]->country);
            printf("���� �Է�: ");
            scanf("%s", students[student_count]->city);
            printf("�� �Է�: ");
            scanf("%s", students[student_count]->gu);
            printf("���� �Է�: ");
            scanf(" %c", &students[student_count]->grade);
            student_count++;
        }
    }
    else 
    {
        printf("�л� ���� ���� á���ϴ�.\n");
    }
}

void delete_student() 
{
    int num;
    printf("������ �л� ��ȣ �Է�: ");
    scanf("%d", &num);
    for (int i = 0; i < student_count; i++)
    {
        if (students[i]->number == num)
        {
            free(students[i]);
            for (int j = i; j < student_count - 1; j++)
            {
                students[j] = students[j + 1];
            }
            student_count--;
            break;
        }
    }
}

void save_students()
{
    FILE* file = fopen("students.txt", "w");
    if (file != NULL)
    {
        for (int i = 0; i < student_count; i++)
        {
            fprintf(file, "%d %s %s %s %s %c\n", students[i]->number, students[i]->name, students[i]->country, students[i]->city, students[i]->gu, students[i]->grade);
        }
        fclose(file);
    }
}

void load_students()
{
    FILE* save = fopen("students.txt", "r");
    if (save != NULL) 
    {
        student_count = 0;
        while (1) {
            students[student_count] = (student*)malloc(sizeof(student));
            if (fscanf(save, "%d %s %s %s %s %c", &students[student_count]->number, students[student_count]->name, students[student_count]->country, students[student_count]->city, students[student_count]->gu, &students[student_count]->grade) != -1) 
            {
                student_count++;
            }
            else 
            {
                free(students[student_count]);
                break;
            }
        }
        fclose(save);
    }
    else
    {
        printf("�Ұ�\n");
    }
}

int main() 
{
    while (1) 
    {
        int sort;
        printf("��� ���� : (1 : �л� ����)(2 : �л� ã��)(3 : �л� �߰�)(4 : �л� ����)(5 : �⼮�� ����)(6 : �⼮�� �ҷ�����)(7 : ����)\n");
        scanf("%d", &sort);

        if (sort == 1) 
        {
            int num;
            printf("(1 : ��ȣ��) (2 : �̸���) (3 : �ּҼ�) (4 : ������)\n");
            scanf("%d", &num);
            sort_student(num);
        }
        else if (sort == 2) 
        {
            find_student();
        }
        else if (sort == 3) 
        {
            add_student();
        }
        else if (sort == 4) 
        {
            delete_student();
        }
        else if (sort == 5) 
        {
            save_students();
        }
        else if (sort == 6) 
        {
            load_students();
        }
        else if (sort == 7)
        {
            for (int i = 0; i < student_count; i++) 
            {
                free(students[i]);
            }
            break;
        }
    }
    return 0;
}
