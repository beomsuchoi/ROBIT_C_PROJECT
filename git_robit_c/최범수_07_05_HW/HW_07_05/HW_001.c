#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

//����ü
typedef struct Student
{
    int number;
    char name[10];
    double grade;
} student;

int main()
{
    //����ü �ҷ����� �κ�
    student s[5];
    //�ӽ� ���� ����
    student tmp;

    printf("�Է� : \n");

    //5�� �ݺ�
    for (int i = 0; i < 5; i++)
    {
        //������ �г� ���� �̸� �Է¹ޱ�
        scanf("%d %lf %s", &s[i].number, &s[i].grade, s[i].name);
    }

    //� ���� ũ�� ������ ���ϴ� ����
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            //�г��� �ٸ��� ū ���� �ڿ�
            if (s[i].number > s[j].number)
            {
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
            //�г��� ���ٸ�
            else if (s[i].number == s[j].number)
            {
                //������ �ٸ��� ū ���� �ڿ�
                if (s[i].grade > s[j].grade)
                {
                    tmp = s[i];
                    s[i] = s[j];
                    s[j] = tmp;
                }
                //������ ���ٸ�
                else if (s[i].grade == s[j].grade)
                {
                    for (int k = 0; k < 10; k++)
                    {
                        //�̸��� �� �ڸ����� 10ĭ���� �����ϰ� �� �ڸ����� ���ĺ� ������� ù��° ���ĺ��� ������ �ι�° ���ĺ� ��
                        if ((int)s[i].name[k] > (int)s[j].name[k])
                        {
                            tmp = s[i];
                            s[i] = s[j];
                            s[j] = tmp;
                        }
                    }
                }
            }
        }
    }
    printf("��� : \n");
    //���� ������ �г� �� ���� �� �̸� ������ ���
    for (int i = 0; i < 5; i++)
    {
        printf("%d %.1lf %s\n", s[i].number, s[i].grade, s[i].name);
    }


    return 0;
}