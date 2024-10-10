#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>//제곱근 구하는 함수 - 5일차 실습예제 3번

//구조체 선언
typedef struct Loc
{
	int x, y;
	double distance;
} loc;

int main()
{
	//x거리 차이, y거리 차이 선언
	int x_dis;
	int y_dis;

	//구조체 포인터 선언
	loc* location;

	int num = 0;
	int tmp_num = 0;
	printf("입력 : ");
	scanf("%d", &num);
	//구조체 형의 포인터를 사용해서 구조체 사이즈 * 입력받은 숫자 만큼으 크기 할당
	location = (loc*)malloc(sizeof(loc) * num);

	
	
	//첫번째 위치 사이의 거리를 0으로 초기화해주는 과정
	for (int i = 0; i < num; i++) 
	{
		location[i].distance = 0;
	}
	//그 후 나머지 값들 입력받기
	for (int i = 0; i < num; i++)
	{
		scanf("%d %d", &location[i].x, &location[i].y);
	}
	//x끼리의 거리 차이와 y끼리의 거리 차이를 변수에 저장, 두 좌표 사이의 거리만 배열에 저장
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			x_dis = location[i].x - location[j].x;
			y_dis = location[i].y - location[j].y;
			location[i].distance += sqrt((double)(x_dis * x_dis) + (y_dis * y_dis));
		}
	}
	//처음 초기화했던 거리를 max에 입력
	double max = location[0].distance;
	int max_num = 0;
	//최대값 숫자
	
	//5개의 점 사이의 oq거리는 4개이므로 입력받은 숫자보다 한칸 적게
	for (int i = 0; i < num-1; i++)
	{
		//계속 합산해주고 max_num은 1을 더해줘야 최대값임을 알 수 있다.
		if (location[i].distance < location[i + 1].distance)
		{
			max = location[i + 1].distance;
			max_num = i + 1;
		}
	}
	//먼 좌표와 거리 총합 구함
	printf("출력 : 가장 거리가 먼 좌표는 (%d, %d)이며, 다른 좌표의 거리 총합은 약%.1lf입니다.", location[max_num].x, location[max_num].y, location[max_num].distance);
	
	free(location);
}