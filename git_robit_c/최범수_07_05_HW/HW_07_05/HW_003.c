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
	//구조체 포인터 선언
	counter* count;
	int num = 0;
	char name_name[20];
	int sum = 0;
	

	printf("입력 : ");
	scanf("%d", &num);

	//구조체 형의 포인터를 사용해서 구조체 사이즈 * 입력받은 숫자 만큼으 크기 할당
	count = (counter*)malloc(sizeof(counter) * num);

	//scanf로 이름과 가격 입력받기
	for (int i = 0; i < num; i++)
	{
		scanf("%s %d", &count[i].name, &count[i].money);
	}
	
	//맨 마지막에 이름 입력받기
	scanf("%s", &name_name);

	//가격 총합 계산해주기
	for (int i = 0; i < num; i++)
	{
		//string함수를 이용해서 이름이 같은지 비교
		if (strcmp(name_name, count[i].name) == 0)
		{
			sum += count[i].money;
		}
	}
	//최대 sum 출력
	//이름이 다르면 자연스럽게 sum은 0으로 초기호 되어있으므로 0 출력
	printf("출력 : %d", sum);

	free(count);
}