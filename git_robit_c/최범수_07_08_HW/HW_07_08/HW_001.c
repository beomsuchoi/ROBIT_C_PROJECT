#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

int main()
{
    //���� �Է¹��� �迭 ����
    char sentence[100];
    char* ps;
    ps = sentence;

    int max = 0;
    int cnt_num[52] = { 0, };//���ĺ� ��ҹ��� �� 52��

    printf("�Է� : ");
    //���� ���Կ��� ���� �Է¹޴� ��ȣ
    scanf("%[^\n]s", sentence);

    printf("\n��� : ");
    //�迭�� ũ�⿡�� 1��ŭ �����ͺ��� 0���� ���
    for (int i = strlen(ps) - 1; i >= 0; --i)
    {
        printf("%c", ps[i]);
    }

    //�ҹ����� ��� 0~26��° cnt_num�� �Է¹ޱ�
    for (int i = 0; i < strlen(ps); i++)
    {
        if (ps[i] >= 'a' && ps[i] <= 'z')
        {
            cnt_num[ps[i] - 'a']++;
        }
        //�빮���� ��� 27 ~ 52��° cnt_num�� �Է¹ޱ�
        else if (ps[i] >= 'A' && ps[i] <= 'Z')
        {
            cnt_num[ps[i] - 'A' + 26]++;
        }
    }

    //0~52���� ��ҹ��� �����ؼ� ���� ���� ���� ���ڸ� max�� �����ϱ�
    for (int k = 0; k < 52; k++)
    {
        if (cnt_num[k] > max)
        {
            max = cnt_num[k];
        }
    }

    printf("\n�ִٵ��幮��: ");
    //�ִ밪�� �ҹ����� ��� or �빮���� ��� ������ ���
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