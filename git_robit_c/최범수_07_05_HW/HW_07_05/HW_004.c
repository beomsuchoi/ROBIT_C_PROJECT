#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// 각 달의 일 수 우선 윤년 계산 X
int month_day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// 윤년인지 확인하는 함수
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

// 구조체 선언
typedef struct Time
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} time;

// 윤년이면 366 아니면 365
int day_year(time day) {
    if (year_odd(day.year)) {
        return 366;
    }
    else {
        return 365;
    }
}

// 입력받은 날 사이 계산
int day_calcul(time first, time second) {
    int days = 0;

    // 첫번째 입력받은 연도와 두번째 입력받은 연도가 같으면
    if (first.year == second.year) {
        //두 날짜 사이의 달 수 계산
        for (int i = first.month - 1; i < second.month - 1; ++i) {
            days += month_day[i];
        }
        //일 수 계산
        days += second.day - first.day;
    }
    //첫번째 입력받은 연도와 두번째 입력받은 연도가 다르면
    else {
        // 시작 날짜의 해당 년도 남은 일 수 계산
        for (int i = first.month - 1; i < 12; ++i) {
            days += month_day[i];
        }//첫번째 달 지난 일수 빼기
        days -= first.day;
        //윤년이고 2월 안지났으면 1일 추가
        if (year_odd(first.year) && first.month <= 2) {
            days += 1;
        }
        //아니면 무시

        // 입력받은 두 연도 사이 연도의 일 수 계산
        for (int i = first.year + 1; i < second.year; ++i)
        {
            //잠시 저장했다가 일수에 더해주기
            time temp_day = { i, 1, 1 };
            days += day_year(temp_day);
        }

        // 끝 날짜의 해당 년도 시작부터 일 수 계산
        for (int i = 0; i < second.month - 1; ++i) 
        {
            //지난 달만큼 더해주기
            days += month_day[i];
        }
        days += second.day;
        //윤년이고 2월보다 크면 1일 더해주기
        if (year_odd(second.year) && second.month > 2) 
        {
            days += 1;
        }
        //아니면 무시
    }

    //최종으로 더해진 일을 반환
    return days;
}

// 두 날짜 사이의 총 시간 차이를 계산하는 함수
void time_differ(time first, time second, int* total_hours, int* minutes, int* seconds) 

{   
    //일 수 계산 함수
    int total_days = day_calcul(first, second);

    // 초 단위 계산
    //두번째 초 - 첫번째 초
    *seconds = second.second - first.second;
    if (*seconds < 0)//계산해서 0보다 작으면 60더하고 분에서 -1
    {
        *seconds += 60;
        second.minute--;
    }

    // 분 단위 계산
    *minutes = second.minute - first.minute;
    if (*minutes < 0) //계산해서 0보다 작으면 60더하고 시간에서 -1
    {
        *minutes += 60;
        second.hour--;
    }

    // 시간 차이 계산
    *total_hours = ((total_days + 1) * 24) + (second.hour - first.hour);
    if (*total_hours < 0) //계산해서 0보다 작으면 24더하고 일 수 에서 -1
    {
        *total_hours += 24;
        total_days--;
    }
}

int main()
{
    time day1, day2;
    int total_hours, minutes, seconds;

    printf("입력 : \n");
    scanf("%d %d %d %d %d %d", &day1.year, &day1.month, &day1.day, &day1.hour, &day1.minute, &day1.second);
    scanf("%d %d %d %d %d %d", &day2.year, &day2.month, &day2.day, &day2.hour, &day2.minute, &day2.second);

    
    time_differ(day1, day2, &total_hours, &minutes, &seconds);

    //최종 출력
    printf("출력 : %d시 %d분 %d초", total_hours, minutes, seconds);

    return 0;
}