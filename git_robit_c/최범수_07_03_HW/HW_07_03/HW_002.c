#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

//strcmp �Լ� ���
int strcmp();
//�������� num, cnt �ʱ�ȭ
int num, cnt = 0;
//���ڿ� �Է¹��� �迭 �ʱ�ȭ
char input[] = {""};
//������ ����� �� �Լ� ����
int printprint(int save_print[])
{
	//ó���� 20���� �۰� �ߴٰ� 20�� ����� �ȵż� 20���� �۰ų� ���ٷ� ����
	for (int i = 0; i <= 20; i++)
	{
		//���� �ִ� ���� ���ڸ� save_print�� �����ߴµ� ������� ���� �κ��� 0���� �����ؼ� 0�� �ƴ� ���ڸ� ��µǰ� ����
		if (save_print[i] != 0)
		{
			printf("%d, ", save_print[i]);
		}
	}
}

int main()
{
	//ó���� ������ 0���� 20�̸����� �߾��µ� 20�� ����� �ȵż� �迭�� 21ĭ���� ����� 20���� ��� �տ� 0�� ��¾ȵǰ� ����
	int save[21] = { 0, };
	int count = 0;
	//���� �κ�
	printf("������ �����ϼ���. ( 1 <= x <= 20 )\n");
	printf("add X\n");
	printf("remove X\n");
	printf("check X\n");
	printf("toggle X\n");
	printf("all 0\n");
	printf("empty 0\n");
	printf("\n");
	//���� �ݺ��ǰ� ����
	while (1)
	{
		printf("input : ");
		scanf("%s", &input);//input���� remove���� �� ���� ����
		//�Է¹��� ���� add
		if (!strcmp(input, "add"))
		{
			//ó���� �� scanf�� ���� �Է¹޾����� �ڿ� all 0�� empty 0�� 0�� ���ڿ��� ���� �ν� ���ؼ� �� ���� �ȿ��� ���� �Է¹���
			scanf("%d", &num);
				
			printf("{ ");
			//���ڰ� 1���� 20���� �� ���� ����
			if (num >= 1 && num <= 20)
			{
				//����� ���ڰ� ��� �Է¹��� �Ͱ� ������ continue
				for (int i = 0; i < 20; i++)
				{
				if (save[i] == num)
				{
					continue;
				}
				//�ٸ��ٸ� cnt�� 1�� �������Ѽ� �� 20�� �Ǹ� �ƹ��͵� �ߺ��� �ƴ϶�� �Ǵ�
				else if (save[i] != num)
				{
					cnt++;
				}
				//�ߺ��� �ȵȰ��
				if (cnt == 20)
				{
					save[count] = num;
					//count ���ڸ� 1 �����ؼ� �迭 1ĭ �̵�
					count++;
					//����Լ��� ����� ���� ���
					printprint(save);
					//�ٽ� cnt�� 0���� �ʱ�ȭ�ؼ� add�� ������ ��� ����
					cnt = 0;
				}
			}
			}
			
			printf(" }");
			printf("\n");
		}
		//remove
		else if (!strcmp(input, "remove"))
		{
			scanf("%d", &num);
			printf("{ ");
			//���ڸ� 1���� 20������ ����
			if (num >= 1 && num <= 20)
			{
				//i�� 0���� 20�̸������� ����
				for (int i = 0; i < 20; i++)
				{
					//����� ���ڰ� �Է¹��� ���ڶ� ������ ����� ���ڸ� 0���� ���� �̋� 0���� �����ϸ� ��¾ȵǰ� ����
					if (save[i] == num)
					{
						save[i] = 0;
					}
				}
				//�� �� �ߺ��� ������ �״�� ���
				printprint(save);
			}
			printf(" }");
			printf("\n");
		}
		//check
		else if (!strcmp(input, "check"))
		{
			scanf("%d", &num);
			// ���ڸ� 1���� 20������ ����
			if (num >= 1 && num <= 20)
			{
				//check�� ī��Ʈ ���� ����
				int cnt_check = 0;
				for (int k = 0; k < 20; k++)
				{
					//����� ���ڰ� �Է¹��� ���ڿ� ������ 1���
					if (save[k] == num)
					{
						printf("1 ");
					}
					//�ٸ��� check�� 1�� �������Ѽ� �� 20�� cnt�� �����ٸ� 0���� �ʱ�ȭ
					else if (save[k] != num)
					{
						cnt_check++;
					}
				}
				//0���� �����Ǹ� ��� �ȵǰ� ����
				if (cnt_check == 20)
					printf("0 ");
			}
		}
		//toggle
		else if (!strcmp(input, "toggle"))
		{
			scanf("%d", &num);

			printf("{ ");
			if (num >= 1 && num <= 20)
			{
				//toggle�� cnt ����
				int cnt_toggle = 0;
				for (int k = 0; k < 20; k++)
				{
					//������� ���ڿ� �Է¹��� ���ڰ� ������ �Ǵ�
					if (save[k] == num)
					{
						continue;
					}
					//�ٸ��� toggle�� 1�� �����ؼ�
					else if (save[k] != num)
					{
						cnt_toggle++;
					}
					//�� 20�� �ݺ��ؼ� cnt�� 20�� �ȴٸ� �ߺ��� ���� �Ŵϱ� ���
				}
				if (cnt_toggle == 20)
				{
					save[count] = num;
					count++;
					printprint(save);
				}
				//���� 20�� �ƴ϶�� �ߺ��� �Ŵϱ� 0���� �ʱ�ȭ�ؼ� ��� �ȵǰ� ����
				else if (cnt_toggle != 20)
				{
					for (int k = 0; k < 20; k++)
					{
						if (save[k] == num)
						{
							save[k] = 0;
						}
					}
					printprint(save);
				}
			}
			printf(" }");
			printf("\n");
		}
		//all 0
		else if (!strcmp(input, "all"))
		{
			//�� ���� ������ ���ڸ� ���� �ȿ��� �Է¹ް� ����
			scanf("%d", &num);

			printf("{ ");
			// 0�� �Է¹޾Ҵٸ� 1���� 20������ ���ڸ� �迭�� �����Ų �� ���
				if (num == 0)
				{
					for (int k = 0; k <= 20; k++)
					{
						save[k] = k;
					}
					printprint(save);
				}
				printf(" }");
				printf("\n");
		}
		else if (!strcmp(input, "empty"))
		{
			scanf("%d", &num);

			printf("{ ");
			//0�� �Է¹޾Ҵٸ� ��� �迭�� ���ڸ� 0���� �ʱ�ȭ�ϰ� ���
				if (num == 0)
				{
					for (int k = 0; k <= 20; k++)
					{
						save[k] = 0;
					}
					printprint(save);
				}
			printf(" }");
			printf("\n");
		}
		//�� ������ �ƴ� �ٸ� �κ��� �ۼ��Ѵٸ� ���� �� ���ڸ� �ٽ� �Է�
		else
		{
			printf("���� �� ���ڸ� �ٽ� �Է����ּ���.");
		}
			


	}
}