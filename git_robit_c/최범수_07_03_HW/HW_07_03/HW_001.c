#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
	//�Է¹��� �ּڰ��� �ִ� �ʱ�ȭ, cnt�� ������ �� ���� �ʱ�ȭ
	int min = 0, max = 0;
	int cnt = 0;
	int k, i = 0, j;
	//cnt_result�� ��ü ������ ������ �����ϰ� �� ����
	int cnt_result = 0;
	int arr[10000] = { 0, };

	printf("min : ");
	scanf("%d", &min);
	printf("max : ");
	scanf("%d", &max);

	//i�� �ּҺ��� �ִ����
	for ( i = min; i <= max; i++)
	{
		//j�� 1�� �����ϰ� 2���� �����ؼ� i�� �������� �� �������� 0���� �ƴ��� ���ϱ� ���� ����
		for ( j = 2; j <= i; j++)
		{
			if (i % (j * j) == 0)
			{
				//�������� ������ ���� ���� �ѹ� �������� break
				cnt++;
				break;
			}
		}
		//������ ������ ���� �������� �������� ������ �迭 arr�� ����
		if (i % (j * j) != 0)
		{
			arr[i] = i;
		}

	}
	//���� ����� �ִ뿡�� �ּ� ���� 1�� ���� �� ������ ������ŭ ����
	cnt_result = (max - min + 1) - cnt;
	printf("���� ���� �� : %d��", cnt_result);
	printf("\n");

	//�� ������ ���� ����ϰ� �� ������ �������� �������� ���� ���� ����ϴ� ���� ���κа� ������ ����
	for (i = min; i <= max; i++)
	{
		if (i % (j * j) != 0 && arr[i] != 0)
		{
			printf("%d ", arr[i]);
		}
	}

}