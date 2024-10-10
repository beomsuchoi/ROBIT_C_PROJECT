#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

int main()
{
    //문장 입력받을 배열 생성
    char sentence[100];
    char* ps;
    ps = sentence;

    int max = 0;
    int cnt_num[52] = { 0, };//알파벳 대소문자 총 52개

    printf("입력 : ");
    //띄어쓰기 포함에서 문장 입력받는 기호
    scanf("%[^\n]s", sentence);

    printf("\n출력 : ");
    //배열의 크기에서 1만큼 작은것부터 0까지 출력
    for (int i = strlen(ps) - 1; i >= 0; --i)
    {
        printf("%c", ps[i]);
    }

    //소문자인 경우 0~26번째 cnt_num에 입력받기
    for (int i = 0; i < strlen(ps); i++)
    {
        if (ps[i] >= 'a' && ps[i] <= 'z')
        {
            cnt_num[ps[i] - 'a']++;
        }
        //대문자인 경우 27 ~ 52번째 cnt_num에 입력받기
        else if (ps[i] >= 'A' && ps[i] <= 'Z')
        {
            cnt_num[ps[i] - 'A' + 26]++;
        }
    }

    //0~52까지 대소문자 포함해서 가장 많이 나온 문자를 max에 저장하기
    for (int k = 0; k < 52; k++)
    {
        if (cnt_num[k] > max)
        {
            max = cnt_num[k];
        }
    }

    printf("\n최다등장문자: ");
    //최대값이 소문자인 경우 or 대문자인 경우 나눠서 출력
    for (int k = 0; k < 52; k++)
    {
        if (cnt_num[k] == max)
        {
            if (k < 26)
            {
                printf("%c", k + 'a');
            }
            else
            {
                printf("%c", k - 26 + 'A');
            }
        }
    }

    return 0;
}