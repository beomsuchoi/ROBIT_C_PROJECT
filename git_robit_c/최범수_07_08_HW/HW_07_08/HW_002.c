#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
    //���� �Է¹��� �迭 ����
    int num[12] = { 0, };
    int* pn;
    pn = num;

    int cnt = 1;
    //ó�� cnt�� 1�� �α�(�ι�°���ʹ� next input�̿��� ó���ѹ��� �׳� ����ϰ� �������� �ݺ��� �ȿ� �־����ϴ�.)
    printf("input : ");
    //�Է¹ޱ�
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
    //3�� 4���� 3�ٷ� ���
    //�̹� �ѹ� �������� 11���� �ݺ� 
    while (cnt <= 11)
    {
        //�Է¹޴� �κ� ����, cnt�� 1�� �����ϸ鼭 �Է¹޴� ��
        printf("next input : ");
        scanf("%d", &pn[cnt]);
        printf("\n");
        //�Ȱ��� 4���� 3���� ���� �����
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                //location�̶�� ���� ���� 1, 5��°�� 0*4+1, 1*4+1�� ���·� ����� �����ϰ� �װ�cnt+1�� ���� �������� �����ϰ� ���
                int location = (i * 4 + j) % (cnt + 1);  //cnt+1�� ������ cnt�� 1�� �� �Է¹��� ���� 2���ϱ� �����ֱ� ���ؼ� 1�� ����
                printf("%d", pn[location]);             
            }
            printf("\n");
        }
        printf("\n");
        cnt++;
        //for���� ������ ���� cnt�� 1 ������Ű�� �ݺ�
    }
    return 0;
}