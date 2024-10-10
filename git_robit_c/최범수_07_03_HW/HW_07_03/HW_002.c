#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

//strcmp 함수 사용
int strcmp();
//전역변수 num, cnt 초기화
int num, cnt = 0;
//문자열 입력받을 배열 초기화
char input[] = {""};
//집합을 출력해 줄 함수 선언
int printprint(int save_print[])
{
	//처음에 20보다 작게 했다가 20이 출력이 안돼서 20보다 작거나 같다로 수정
	for (int i = 0; i <= 20; i++)
	{
		//남아 있는 집합 숫자를 save_print에 저장했는데 저장되지 않은 부분을 0으로 설정해서 0이 아닌 숫자만 출력되게 설정
		if (save_print[i] != 0)
		{
			printf("%d, ", save_print[i]);
		}
	}
}

int main()
{
	//처음에 조건을 0부터 20미만으로 했었는데 20이 출력이 안돼서 배열을 21칸으로 만들고 20까지 출력 앞에 0은 출력안되게 설정
	int save[21] = { 0, };
	int count = 0;
	//예시 부분
	printf("연산을 선택하세요. ( 1 <= x <= 20 )\n");
	printf("add X\n");
	printf("remove X\n");
	printf("check X\n");
	printf("toggle X\n");
	printf("all 0\n");
	printf("empty 0\n");
	printf("\n");
	//무한 반복되게 설정
	while (1)
	{
		printf("input : ");
		scanf("%s", &input);//input인지 remove인지 즉 연산 선택
		//입력받은 것이 add
		if (!strcmp(input, "add"))
		{
			//처음에 위 scanf와 같이 입력받았으나 뒤에 all 0와 empty 0의 0을 문자열과 같이 인식 못해서 각 연산 안에서 숫자 입력받음
			scanf("%d", &num);
				
			printf("{ ");
			//숫자가 1부터 20까지 일 때만 실행
			if (num >= 1 && num <= 20)
			{
				//저장된 숫자가 방금 입력받은 것과 같으면 continue
				for (int i = 0; i < 20; i++)
				{
				if (save[i] == num)
				{
					continue;
				}
				//다르다면 cnt를 1씩 증가시켜서 총 20이 되면 아무것도 중복이 아니라고 판단
				else if (save[i] != num)
				{
					cnt++;
				}
				//중복이 안된경우
				if (cnt == 20)
				{
					save[count] = num;
					//count 숫자를 1 증가해서 배열 1칸 이동
					count++;
					//출력함수에 저장된 숫자 출력
					printprint(save);
					//다시 cnt를 0으로 초기화해서 add를 여러번 사용 가능
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
			//숫자를 1부터 20까지로 설정
			if (num >= 1 && num <= 20)
			{
				//i를 0부터 20미만까지로 설정
				for (int i = 0; i < 20; i++)
				{
					//저장된 숫자가 입력받은 숫자랑 같으면 저장된 숫자를 0으로 설정 이떄 0으로 설정하면 출력안되게 설정
					if (save[i] == num)
					{
						save[i] = 0;
					}
				}
				//그 후 중복이 없으면 그대로 출력
				printprint(save);
			}
			printf(" }");
			printf("\n");
		}
		//check
		else if (!strcmp(input, "check"))
		{
			scanf("%d", &num);
			// 숫자를 1부터 20까지로 설정
			if (num >= 1 && num <= 20)
			{
				//check용 카운트 변수 선언
				int cnt_check = 0;
				for (int k = 0; k < 20; k++)
				{
					//저장된 숫자가 입력받은 숫자와 같으면 1출력
					if (save[k] == num)
					{
						printf("1 ");
					}
					//다르면 check를 1씩 증가시켜서 총 20이 cnt에 찍힌다면 0으로 초기화
					else if (save[k] != num)
					{
						cnt_check++;
					}
				}
				//0으로 설정되면 출력 안되게 설정
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
				//toggle용 cnt 설정
				int cnt_toggle = 0;
				for (int k = 0; k < 20; k++)
				{
					//저장받은 숫자와 입력받은 숫자가 같은지 판단
					if (save[k] == num)
					{
						continue;
					}
					//다르면 toggle을 1씩 증가해서
					else if (save[k] != num)
					{
						cnt_toggle++;
					}
					//총 20번 반복해서 cnt가 20이 된다면 중복이 없는 거니까 출력
				}
				if (cnt_toggle == 20)
				{
					save[count] = num;
					count++;
					printprint(save);
				}
				//만약 20이 아니라면 중복인 거니까 0으로 초기화해서 출력 안되게 설정
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
			//이 연산 때문에 숫자를 연산 안에서 입력받게 설정
			scanf("%d", &num);

			printf("{ ");
			// 0을 입력받았다면 1부터 20까지의 숫자를 배열에 저장시킨 뒤 출력
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
			//0을 입력받았다면 모든 배열에 숫자를 0으로 초기화하고 출력
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
		//이 연산이 아닌 다른 부분을 작성한다면 연산 및 숫자를 다시 입력
		else
		{
			printf("연산 및 숫자를 다시 입력해주세요.");
		}
			


	}
}