#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


int main() {
    int num;
    printf("�Է� : ");
    scanf("%d", &num);



    char* name[30];
    for (int i = 0; i < num; i++) {
        name[i] = (char*)malloc(30 * sizeof(char));//������ �迭�� 30���� ���� ���⵵ 30
    }


    float* score = (float*)malloc(num * 3 * sizeof(float));
    float* aver = (float*)malloc(num * sizeof(float));

    // �л� �̸��� ���� 3���� �Է� 3���� �����ϱ� 3�� ���, +1, +2�� ĭ�� ����
    for (int i = 0; i < num; i++) {
        scanf("%s %f %f %f", name[i], &score[i * 3], &score[i * 3 + 1], &score[i * 3 + 2]);
        aver[i] = (score[i * 3] + score[i * 3 + 1] + score[i * 3 + 2]) / 3.0;
    }//���� 3�� ����� aver�� ����

    // �л� ����
    for (int i = 0; i < num - 1; i++) 
    {
        for (int j = 0; j < num - i - 1; j++)
        {
            if (aver[j] < aver[j + 1])//����� ������ ��ġ �ٲ��ְ� �̸��� �ٲ��ֱ� ������ �迭�� ��ġ �ٲ�
            {
                
                float tmp_aver = aver[j];
                aver[j] = aver[j + 1];
                aver[j + 1] = tmp_aver;
                // ��� ���� ��ġ ����
                
                char* tmp_name = name[j];
                name[j] = name[j + 1];
                name[j + 1] = tmp_name;
                // �̸� ��ġ ����
                
                for (int k = 0; k < 3; k++)
                {// ���� ��ġ ���� ������ 3���� for�� �ݺ�
                    float tmp_score = score[j * 3 + k];
                    score[j * 3 + k] = score[(j + 1) * 3 + k];
                    score[(j + 1) * 3 + k] = tmp_score;
                }
            }
        }
    }



    printf("��� :\n");
    for (int i = 0; i < num; i++)
    {
        printf("\t%s %.1f\n", name[i], aver[i]);
    
        free(name[i]);
    }
    free(score);
    free(aver);

    return 0;
}