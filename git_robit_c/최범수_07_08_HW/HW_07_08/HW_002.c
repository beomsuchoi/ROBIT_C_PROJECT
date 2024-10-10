#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
    //숫자 입력받을 배열 선언
    int num[12] = { 0, };
    int* pn;
    pn = num;

    int cnt = 1;
    //처음 cnt를 1로 두기(두번째부터는 next input이여서 처음한번은 그냥 출력하고 나머지를 반복문 안에 넣었습니다.)
    printf("input : ");
    //입력받기
    scanf("%d", &pn[0]);
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d", pn[0]);
        }
        printf("\n");
    }
    printf("\n");
    //3을 4개씩 3줄로 출력
    //이미 한번 돌렸으니 11번만 반복 
    while (cnt <= 11)
    {
        //입력받는 부분 선언, cnt는 1씩 증가하면서 입력받는 중
        printf("next input : ");
        scanf("%d", &pn[cnt]);
        printf("\n");
        //똑같이 4개씩 3줄의 형태 만들기
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                //location이라는 변수 만들어서 1, 5번째를 0*4+1, 1*4+1의 형태로 나누어서 생각하고 그걸cnt+1로 나눈 나머지를 저장하고 출력
                int location = (i * 4 + j) % (cnt + 1);  //cnt+1인 이유는 cnt가 1일 때 입력받은 것은 2개니까 맞춰주기 위해서 1을 더함
                printf("%d", pn[location]);             
            }
            printf("\n");
        }
        printf("\n");
        cnt++;
        //for문이 끝나기 전에 cnt를 1 증가시키고 반복
    }
    return 0;
}