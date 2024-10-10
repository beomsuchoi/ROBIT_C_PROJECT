#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// 게임 결과를 기록 구조체 선언
typedef struct {
    int user_wins;
    int computer_wins;
    int draws;
} GameStats;

// 가위바위보 게임 관련 함수
const char* get_computer_choice();
const char* determine_winner(const char* user_choice, const char* computer_choice);
void start_mode1(FILE* file);

// 정사각형 칸 프로그램 관련 함수
typedef struct {
    int count;
    int index;
} Cell;

//여러 함수 재선언
void visualize_grid(Cell* grid, int size, int* choices, int num_choices);
int compare(const void* a, const void* b);
void start_mode2(FILE* file);

// 숫자 맞추기 게임 관련 함수
void start_mode3(FILE* file);

// 묵찌빠 게임 관련 함수
const char* get_choice_name(int choice);
int get_winner(int player_choice, int computer_choice);
void start_mode4(FILE* file);

int main() 
{
    int mode;

    FILE* file = fopen("program_results.txt", "w");

    if (file == NULL) 
    {
        printf("파일 열기 실패\n");
        return 1;
    }

    while (1) 
    {
        printf("모드를 선택하세요 (1: 가위바위보, 2: 정사각형 칸 프로그램, 3: 숫자 맞추기 게임, 4: 묵찌빠, 0: 종료): ");
        scanf("%d", &mode);

        if (mode == 1)
        {
            start_mode1(file);
        }
        else if (mode == 2) 
        {
            start_mode2(file);
        }
        else if (mode == 3)
        {
            start_mode3(file);
        }
        else if (mode == 4) 
        {
            start_mode4(file);
        }
        else if (mode == 0)
        {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else
        {
            printf("잘못된 모드입니다. 다시 선택하세요.\n");
        }
    }

    fclose(file);
    return 0;
}

// 가위바위보 프로그램 관련 함수 정의
const char* get_computer_choice()
{
    int choice = rand() % 3; // 0, 1, 2 중 하나
    switch (choice) {
    case 0: return "가위";
    case 1: return "바위";
    case 2: return "보";
    default: return "잘못된 선택";
    }
}

const char* determine_winner(const char* user_choice, const char* computer_choice) 
{
    if (strcmp(user_choice, computer_choice) == 0)
    {
        return "비김";
    }
    else if ((strcmp(user_choice, "가위") == 0 && strcmp(computer_choice, "보") == 0) || (strcmp(user_choice, "바위") == 0 && strcmp(computer_choice, "가위") == 0) || (strcmp(user_choice, "보") == 0 && strcmp(computer_choice, "바위") == 0))
    {
        return "사용자 승리";
    }
    else 
    {
        return "컴퓨터 승리";
    }
}

void start_mode1(FILE* file) 
{
    GameStats stats = { 0, 0, 0 }; // 게임 초기화

    char user_input[10];

    srand(time(0)); //랜덤 설정

    while (1) 
    {
        printf("가위, 바위, 보 중 하나를 입력하세요 (종료하려면 'exit'): ");
        scanf("%s", user_input);

        if (strcmp(user_input, "exit") == 0) 
        {
            // 게임 종료 시 통계 출력
            printf("게임 종료\n");
            printf("사용자 승리 횟수: %d\n", stats.user_wins);
            printf("컴퓨터 승리 횟수: %d\n", stats.computer_wins);
            printf("비긴 횟수: %d\n", stats.draws);
            break;
        }

        // 컴퓨터의 선택
        const char* computer_choice = get_computer_choice();
        printf("컴퓨터의 선택: %s\n", computer_choice);

        // 승자
        const char* result = determine_winner(user_input, computer_choice);
        printf("결과: %s\n", result);

        // 승리횟수 저장
        if (strcmp(result, "사용자 승리") == 0) 
        {
            stats.user_wins++;
        }
        else if (strcmp(result, "컴퓨터 승리") == 0) 
        {
            stats.computer_wins++;
        }
        else 
        {
            stats.draws++;
        }
    }

    //파일 출력
    fprintf(file, "===== 가위바위보 결과 =====\n");
    fprintf(file, "사용자 승리 횟수: %d\n", stats.user_wins);
    fprintf(file, "컴퓨터 승리 횟수: %d\n", stats.computer_wins);
    fprintf(file, "비긴 횟수: %d\n", stats.draws);
    fprintf(file, "==========================\n\n");
}

// 정사각형 칸 프로그램 관련 함수
void visualize_grid(Cell* grid, int size, int* choices, int num_choices) 
{
    int side = (int)sqrt(size); //정사각형 -> 한 변 길이 계산

    for (int i = 0; i < size; i++)
    {
        if (i % side == 0 && i != 0)
        {
            printf("\n");
        }

        int found = 0;

        for (int j = 0; j < num_choices; j++) 
        {
            if (i == choices[j])
            {
                found = 1;
                break;
            }
        }
        //1과 X로 구성
        if (found) 
        {
            printf(" 1 ");
        }
        else 
        {
            printf(" X ");
        }
    }
    printf("\n\n");
}

int compare(const void* a, const void* b) 
{
    //구조체 포인터
    Cell* cellA = (Cell*)a;
    Cell* cellB = (Cell*)b;

    return cellB->count - cellA->count;
}

// 선택 정렬 함수
void sort_sort(Cell* grid, int size) {
    int i, j, max_idx;
    Cell temp;

    for (i = 0; i < size - 1; i++) {
        max_idx = i;
        for (j = i + 1; j < size; j++) {
            if (grid[j].count > grid[max_idx].count) {
                max_idx = j;
            }
        }
        // 교환
        temp = grid[max_idx];
        grid[max_idx] = grid[i];
        grid[i] = temp;
    }
}

void start_mode2(FILE* file) 
{
    int n; // 칸 개수

    printf("네모 칸의 개수를 입력하세요 (예: 9, 16, 25 등 완전 제곱수): ");
    scanf("%d", &n);

    // 동적 메모리 할당
    Cell* grid = (Cell*)malloc(n * sizeof(Cell));

    if (grid == NULL) //없을 때
    {
        printf("메모리 할당 실패\n");
        return;
    }

    // 초기화 시켜주는 과정
    for (int i = 0; i < n; i++) 
    {
        grid[i].count = 0;
        grid[i].index = i;
    }

    char command[10];
    srand(time(0)); //랜덤 숫자 설정

    while (1)
    {
        int num_choices = (rand() % 2) + 1; // 1개 또는 2개 최대 2개
        //동적 메모리 할당
        int* choices = (int*)malloc(num_choices * sizeof(int));

        if (choices == NULL) 
        //없을 떄
        {
            printf("메모리 할당 실패\n");
            free(grid);
            return;
        }

        // 중복X 칸 선택
        for (int i = 0; i < num_choices; i++) 
        {
            int choice;
            //do~while문
            do 
            {
                choice = rand() % n;
            } 
            while (i > 0 && choice == choices[i - 1]);

            choices[i] = choice;
            grid[choice].count++; // 선택 칸 횟수 증가
        }

        // 출력부분
        printf("현재 상태:\n");
        visualize_grid(grid, n, choices, num_choices);

        printf("계속하려면 'continue'를, 종료하려면 'exit'를 입력: ");
        scanf("%s", command);

        if (strcmp(command, "exit") == 0) 
        {
            // 최종 결과 파일에 출력
            fprintf(file, "===== 정사각형 칸 프로그램 결과 =====\n");
            for (int i = 0; i < n; i++) 
            {
                fprintf(file, "칸 %d: %d번\n", grid[i].index, grid[i].count);
            }

            // 내림차순 정렬
            sort_sort(grid, n);

            // 최종 결과 정렬 출력
            fprintf(file, "내림차순 정렬 결과:\n");

            for (int i = 0; i < n; i++) 
            {
                fprintf(file, "칸 %d: %d번\n", grid[i].index, grid[i].count);
            }
            fprintf(file, "=================================\n\n");

            // 콘솔에 출력
            printf("최종 각 칸별 1 표시 횟수 (내림차순 정렬):\n");
            for (int i = 0; i < n; i++) 
            {
                printf("칸 %d: %d번\n", grid[i].index, grid[i].count);
            }

            free(choices);
            break;
        }
        else if (strcmp(command, "continue") != 0) //continue 아닐 때
        {
            printf("잘못된 명령입니다. 다시 입력하세요.\n");
        }

        free(choices);
    }

    // free
    free(grid);
}

// 숫자 맞추기 게임 관련 함수
void start_mode3(FILE* file) 
{
    int target, guess, attempts = 0;
    srand(time(0));
    //무작위 수
    target = rand() % 100 + 1; // 1부터 100 사이의 숫자

    fprintf(file, "===== 숫자 맞추기 게임 결과 =====\n");
    printf("1부터 100 사이의 숫자를 맞춰보세요!\n");

    while (1)
    {
        printf("숫자를 입력하세요: ");
        scanf("%d", &guess);
        attempts++;//시도 횟수

        if (guess > target) 
        {
            printf("더 낮은 숫자\n");
        }
        else if (guess < target)
        {
            printf("더 높은 숫자\n");
        }
        else 
        {
            printf("정답!, 시도 횟수: %d\n", attempts);
            fprintf(file, "정답: %d (시도 횟수: %d)\n", target, attempts);
            break;
        }
    }

    fprintf(file, "===============================\n\n");
}

// 묵찌빠 게임 관련 함수 정의
const char* get_choice_name(int choice) 
{
    switch (choice) 
    {
    case 1: return "가위";
    case 2: return "바위";
    case 3: return "보";
    default: return "잘못된 선택";
    }
}

int get_winner(int player_choice, int computer_choice) 
{
    if (player_choice == computer_choice)
    {
        return 0; // 비김
    }
    if ((player_choice == 1 && computer_choice == 3) || (player_choice == 2 && computer_choice == 1) || (player_choice == 3 && computer_choice == 2)) 
    {
        return 1; // 사용자 승리
    }
    return -1; // 컴퓨터 승리
}

void start_mode4(FILE* file) {
    int player_choice, computer_choice, result;
    char playAgain;
    int first_winner; // 1: 사용자 승리, 0: 컴퓨터 승리
    int final_winner;
    srand(time(NULL)); // 무작위 초기화

    while (1) 
    {
        // 가위바위보 첫번째
        printf("첫 번째 가위(1), 바위(2), 보(3) 중 하나를 선택하세요: ");
        scanf("%d", &player_choice);
        computer_choice = (rand() % 3) + 1;
        printf("컴퓨터의 선택: %s\n", get_choice_name(computer_choice));

        result = get_winner(player_choice, computer_choice);

        if (result == 0) 
        {
            printf("비겼습니다. 다시 시도하세요.\n");
            continue;
        }

        first_winner = (result == 1) ? 1 : 0;
        final_winner = -1;

        // 묵찌빠 과정
        while (final_winner == -1)
        {
            printf("가위(1), 바위(2), 보(3) 중 하나를 선택하세요: ");
            scanf("%d", &player_choice);
            computer_choice = (rand() % 3) + 1;//1부터 3까지
            printf("컴퓨터의 선택: %s\n", get_choice_name(computer_choice));

            if (player_choice == computer_choice)
            {
                final_winner = first_winner;
            }
            else 
            {
                result = get_winner(player_choice, computer_choice);
                if (result == 0)
                {
                    printf("비겼습니다. 다시 시도하세요.\n");
                }
                else
                {
                    first_winner = (result == 1) ? 1 : 0;
                }
            }
        }

        if (final_winner == 1) 
        {
            printf("플레이어가 이겼습니다!\n");
        }
        else
        {
            printf("컴퓨터가 이겼습니다!\n");
        }

        printf("다시 하시겠습니까? y or n : ");
        scanf(" %c", &playAgain);

        if (playAgain != 'y') 
        {
            break;
        }
    }

    printf("게임을 종료합니다.\n"); 
}
