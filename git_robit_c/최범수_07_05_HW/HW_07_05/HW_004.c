#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// �� ���� �� �� �켱 ���� ��� X
int month_day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// �������� Ȯ���ϴ� �Լ�
int year_odd(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else {
            return 1;
        }
    }
    else {
        return 0;
    }
}

// ����ü ����
typedef struct Time
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} time;

// �����̸� 366 �ƴϸ� 365
int day_year(time day) {
    if (year_odd(day.year)) {
        return 366;
    }
    else {
        return 365;
    }
}

// �Է¹��� �� ���� ���
int day_calcul(time first, time second) {
    int days = 0;

    // ù��° �Է¹��� ������ �ι�° �Է¹��� ������ ������
    if (first.year == second.year) {
        //�� ��¥ ������ �� �� ���
        for (int i = first.month - 1; i < second.month - 1; ++i) {
            days += month_day[i];
        }
        //�� �� ���
        days += second.day - first.day;
    }
    //ù��° �Է¹��� ������ �ι�° �Է¹��� ������ �ٸ���
    else {
        // ���� ��¥�� �ش� �⵵ ���� �� �� ���
        for (int i = first.month - 1; i < 12; ++i) {
            days += month_day[i];
        }//ù��° �� ���� �ϼ� ����
        days -= first.day;
        //�����̰� 2�� ���������� 1�� �߰�
        if (year_odd(first.year) && first.month <= 2) {
            days += 1;
        }
        //�ƴϸ� ����

        // �Է¹��� �� ���� ���� ������ �� �� ���
        for (int i = first.year + 1; i < second.year; ++i)
        {
            //��� �����ߴٰ� �ϼ��� �����ֱ�
            time temp_day = { i, 1, 1 };
            days += day_year(temp_day);
        }

        // �� ��¥�� �ش� �⵵ ���ۺ��� �� �� ���
        for (int i = 0; i < second.month - 1; ++i) 
        {
            //���� �޸�ŭ �����ֱ�
            days += month_day[i];
        }
        days += second.day;
        //�����̰� 2������ ũ�� 1�� �����ֱ�
        if (year_odd(second.year) && second.month > 2) 
        {
            days += 1;
        }
        //�ƴϸ� ����
    }

    //�������� ������ ���� ��ȯ
    return days;
}

// �� ��¥ ������ �� �ð� ���̸� ����ϴ� �Լ�
void time_differ(time first, time second, int* total_hours, int* minutes, int* seconds) 

{   
    //�� �� ��� �Լ�
    int total_days = day_calcul(first, second);

    // �� ���� ���
    //�ι�° �� - ù��° ��
    *seconds = second.second - first.second;
    if (*seconds < 0)//����ؼ� 0���� ������ 60���ϰ� �п��� -1
    {
        *seconds += 60;
        second.minute--;
    }

    // �� ���� ���
    *minutes = second.minute - first.minute;
    if (*minutes < 0) //����ؼ� 0���� ������ 60���ϰ� �ð����� -1
    {
        *minutes += 60;
        second.hour--;
    }

    // �ð� ���� ���
    *total_hours = ((total_days + 1) * 24) + (second.hour - first.hour);
    if (*total_hours < 0) //����ؼ� 0���� ������ 24���ϰ� �� �� ���� -1
    {
        *total_hours += 24;
        total_days--;
    }
}

int main()
{
    time day1, day2;
    int total_hours, minutes, seconds;

    printf("�Է� : \n");
    scanf("%d %d %d %d %d %d", &day1.year, &day1.month, &day1.day, &day1.hour, &day1.minute, &day1.second);
    scanf("%d %d %d %d %d %d", &day2.year, &day2.month, &day2.day, &day2.hour, &day2.minute, &day2.second);

    
    time_differ(day1, day2, &total_hours, &minutes, &seconds);

    //���� ���
    printf("��� : %d�� %d�� %d��", total_hours, minutes, seconds);

    return 0;
}