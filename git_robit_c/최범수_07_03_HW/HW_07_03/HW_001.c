#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
	//입력받을 최솟값과 최댓값 초기화, cnt는 제곱수 셀 변수 초기화
	int min = 0, max = 0;
	int cnt = 0;
	int k, i = 0, j;
	//cnt_result는 전체 수에서 제곱수 제외하고 셀 변수
	int cnt_result = 0;
	int arr[10000] = { 0, };

	printf("min : ");
	scanf("%d", &min);
	printf("max : ");
	scanf("%d", &max);

	//i는 최소부터 최대까지
	for ( i = min; i <= max; i++)
	{
		//j는 1을 제외하고 2부터 제곱해서 i를 나누었을 때 나머지가 0인지 아닌지 비교하기 위해 선언
		for ( j = 2; j <= i; j++)
		{
			if (i % (j * j) == 0)
			{
				//제곱수의 개수를 세는 과정 한번 나눠지면 break
				cnt++;
				break;
			}
		}
		//과정이 끝나고 만약 제곱수로 나눠지지 않으면 배열 arr에 저장
		if (i % (j * j) != 0)
		{
			arr[i] = i;
		}

	}
	//최종 결과는 최대에서 최소 빼고 1을 더한 뒤 제곱수 개수만큼 빼기
	cnt_result = (max - min + 1) - cnt;
	printf("제곱 ㄴㄴ 수 : %d개", cnt_result);
	printf("\n");

	//총 개수를 먼저 출력하고 그 다음에 제곱으로 나눠지지 않은 수를 출력하는 과정 윗부분과 조건은 유사
	for (i = min; i <= max; i++)
	{
		if (i % (j * j) != 0 && arr[i] != 0)
		{
			printf("%d ", arr[i]);
		}
	}

}