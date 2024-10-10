#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

//구조체
typedef struct Student
{
    int number;
    char name[10];
    double grade;
} student;

int main()
{
    //구조체 불러오는 부분
    student s[5];
    //임시 저장 공간
    student tmp;

    printf("입력 : \n");

    //5번 반복
    for (int i = 0; i < 5; i++)
    {
        //각각의 학년 성적 이름 입력받기
        scanf("%d %lf %s", &s[i].number, &s[i].grade, s[i].name);
    }

    //어떤 값이 크고 작은지 비교하는 과정
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            //학년이 다르면 큰 값을 뒤에
            if (s[i].number > s[j].number)
            {
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
            //학년이 같다면
            else if (s[i].number == s[j].number)
            {
                //성적이 다르면 큰 값을 뒤에
                if (s[i].grade > s[j].grade)
                {
                    tmp = s[i];
                    s[i] = s[j];
                    s[j] = tmp;
                }
                //성적이 같다면
                else if (s[i].grade == s[j].grade)
                {
                    for (int k = 0; k < 10; k++)
                    {
                        //이름의 총 자리수를 10칸으로 제한하고 각 자리수의 알파벳 순서대로 첫번째 알파벳이 같으면 두번째 알파벳 비교
                        if ((int)s[i].name[k] > (int)s[j].name[k])
                        {
                            tmp = s[i];
                            s[i] = s[j];
                            s[j] = tmp;
                        }
                    }
                }
            }
        }
    }
    printf("출력 : \n");
    //최종 결과대로 학년 순 성적 순 이름 순으로 출력
    for (int i = 0; i < 5; i++)
    {
        printf("%d %.1lf %s\n", s[i].number, s[i].grade, s[i].name);
    }


    return 0;
}