#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


int main() {
    int num;
    printf("입력 : ");
    scanf("%d", &num);



    char* name[30];
    for (int i = 0; i < num; i++) {
        name[i] = (char*)malloc(30 * sizeof(char));//위에서 배열을 30까지 만들어서 여기도 30
    }


    float* score = (float*)malloc(num * 3 * sizeof(float));
    float* aver = (float*)malloc(num * sizeof(float));

    // 학생 이름과 성적 3가지 입력 3개씩 들어오니까 3의 배수, +1, +2의 칸에 저장
    for (int i = 0; i < num; i++) {
        scanf("%s %f %f %f", name[i], &score[i * 3], &score[i * 3 + 1], &score[i * 3 + 2]);
        aver[i] = (score[i * 3] + score[i * 3 + 1] + score[i * 3 + 2]) / 3.0;
    }//성적 3개 평균을 aver에 저장

    // 학생 정렬
    for (int i = 0; i < num - 1; i++) 
    {
        for (int j = 0; j < num - i - 1; j++)
        {
            if (aver[j] < aver[j + 1])//평균이 작으면 위치 바꿔주고 이름도 바꿔주기 저장할 배열도 위치 바꿈
            {
                
                float tmp_aver = aver[j];
                aver[j] = aver[j + 1];
                aver[j + 1] = tmp_aver;
                // 평균 저장 위치 변경
                
                char* tmp_name = name[j];
                name[j] = name[j + 1];
                name[j + 1] = tmp_name;
                // 이름 위치 변경
                
                for (int k = 0; k < 3; k++)
                {// 점수 위치 변경 점수는 3개라서 for문 반복
                    float tmp_score = score[j * 3 + k];
                    score[j * 3 + k] = score[(j + 1) * 3 + k];
                    score[(j + 1) * 3 + k] = tmp_score;
                }
            }
        }
    }



    printf("출력 :\n");
    for (int i = 0; i < num; i++)
    {
        printf("\t%s %.1f\n", name[i], aver[i]);
    
        free(name[i]);
    }
    free(score);
    free(aver);

    return 0;
}