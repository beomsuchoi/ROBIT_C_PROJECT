#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Counter{
	char name[20];
	int money;
}counter;


int main()
{
	//����ü ������ ����
	counter* count;
	int num = 0;
	char name_name[20];
	int sum = 0;
	

	printf("�Է� : ");
	scanf("%d", &num);

	//����ü ���� �����͸� ����ؼ� ����ü ������ * �Է¹��� ���� ��ŭ�� ũ�� �Ҵ�
	count = (counter*)malloc(sizeof(counter) * num);

	//scanf�� �̸��� ���� �Է¹ޱ�
	for (int i = 0; i < num; i++)
	{
		scanf("%s %d", &count[i].name, &count[i].money);
	}
	
	//�� �������� �̸� �Է¹ޱ�
	scanf("%s", &name_name);

	//���� ���� ������ֱ�
	for (int i = 0; i < num; i++)
	{
		//string�Լ��� �̿��ؼ� �̸��� ������ ��
		if (strcmp(name_name, count[i].name) == 0)
		{
			sum += count[i].money;
		}
	}
	//�ִ� sum ���
	//�̸��� �ٸ��� �ڿ������� sum�� 0���� �ʱ�ȣ �Ǿ������Ƿ� 0 ���
	printf("��� : %d", sum);

	free(count);
}