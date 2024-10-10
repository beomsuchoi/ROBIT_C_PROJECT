#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>//������ ���ϴ� �Լ� - 5���� �ǽ����� 3��

//����ü ����
typedef struct Loc
{
	int x, y;
	double distance;
} loc;

int main()
{
	//x�Ÿ� ����, y�Ÿ� ���� ����
	int x_dis;
	int y_dis;

	//����ü ������ ����
	loc* location;

	int num = 0;
	int tmp_num = 0;
	printf("�Է� : ");
	scanf("%d", &num);
	//����ü ���� �����͸� ����ؼ� ����ü ������ * �Է¹��� ���� ��ŭ�� ũ�� �Ҵ�
	location = (loc*)malloc(sizeof(loc) * num);

	
	
	//ù��° ��ġ ������ �Ÿ��� 0���� �ʱ�ȭ���ִ� ����
	for (int i = 0; i < num; i++) 
	{
		location[i].distance = 0;
	}
	//�� �� ������ ���� �Է¹ޱ�
	for (int i = 0; i < num; i++)
	{
		scanf("%d %d", &location[i].x, &location[i].y);
	}
	//x������ �Ÿ� ���̿� y������ �Ÿ� ���̸� ������ ����, �� ��ǥ ������ �Ÿ��� �迭�� ����
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			x_dis = location[i].x - location[j].x;
			y_dis = location[i].y - location[j].y;
			location[i].distance += sqrt((double)(x_dis * x_dis) + (y_dis * y_dis));
		}
	}
	//ó�� �ʱ�ȭ�ߴ� �Ÿ��� max�� �Է�
	double max = location[0].distance;
	int max_num = 0;
	//�ִ밪 ����
	
	//5���� �� ������ oq�Ÿ��� 4���̹Ƿ� �Է¹��� ���ں��� ��ĭ ����
	for (int i = 0; i < num-1; i++)
	{
		//��� �ջ����ְ� max_num�� 1�� ������� �ִ밪���� �� �� �ִ�.
		if (location[i].distance < location[i + 1].distance)
		{
			max = location[i + 1].distance;
			max_num = i + 1;
		}
	}
	//�� ��ǥ�� �Ÿ� ���� ����
	printf("��� : ���� �Ÿ��� �� ��ǥ�� (%d, %d)�̸�, �ٸ� ��ǥ�� �Ÿ� ������ ��%.1lf�Դϴ�.", location[max_num].x, location[max_num].y, location[max_num].distance);
	
	free(location);
}