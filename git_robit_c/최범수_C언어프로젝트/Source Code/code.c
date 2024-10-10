#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// ���� ����� ��� ����ü ����
typedef struct {
    int user_wins;
    int computer_wins;
    int draws;
} GameStats;

// ���������� ���� ���� �Լ�
const char* get_computer_choice();
const char* determine_winner(const char* user_choice, const char* computer_choice);
void start_mode1(FILE* file);

// ���簢�� ĭ ���α׷� ���� �Լ�
typedef struct {
    int count;
    int index;
} Cell;

//���� �Լ� �缱��
void visualize_grid(Cell* grid, int size, int* choices, int num_choices);
int compare(const void* a, const void* b);
void start_mode2(FILE* file);

// ���� ���߱� ���� ���� �Լ�
void start_mode3(FILE* file);

// ����� ���� ���� �Լ�
const char* get_choice_name(int choice);
int get_winner(int player_choice, int computer_choice);
void start_mode4(FILE* file);

int main() 
{
    int mode;

    FILE* file = fopen("program_results.txt", "w");

    if (file == NULL) 
    {
        printf("���� ���� ����\n");
        return 1;
    }

    while (1) 
    {
        printf("��带 �����ϼ��� (1: ����������, 2: ���簢�� ĭ ���α׷�, 3: ���� ���߱� ����, 4: �����, 0: ����): ");
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
            printf("���α׷��� �����մϴ�.\n");
            break;
        }
        else
        {
            printf("�߸��� ����Դϴ�. �ٽ� �����ϼ���.\n");
        }
    }

    fclose(file);
    return 0;
}

// ���������� ���α׷� ���� �Լ� ����
const char* get_computer_choice()
{
    int choice = rand() % 3; // 0, 1, 2 �� �ϳ�
    switch (choice) {
    case 0: return "����";
    case 1: return "����";
    case 2: return "��";
    default: return "�߸��� ����";
    }
}

const char* determine_winner(const char* user_choice, const char* computer_choice) 
{
    if (strcmp(user_choice, computer_choice) == 0)
    {
        return "���";
    }
    else if ((strcmp(user_choice, "����") == 0 && strcmp(computer_choice, "��") == 0) || (strcmp(user_choice, "����") == 0 && strcmp(computer_choice, "����") == 0) || (strcmp(user_choice, "��") == 0 && strcmp(computer_choice, "����") == 0))
    {
        return "����� �¸�";
    }
    else 
    {
        return "��ǻ�� �¸�";
    }
}

void start_mode1(FILE* file) 
{
    GameStats stats = { 0, 0, 0 }; // ���� �ʱ�ȭ

    char user_input[10];

    srand(time(0)); //���� ����

    while (1) 
    {
        printf("����, ����, �� �� �ϳ��� �Է��ϼ��� (�����Ϸ��� 'exit'): ");
        scanf("%s", user_input);

        if (strcmp(user_input, "exit") == 0) 
        {
            // ���� ���� �� ��� ���
            printf("���� ����\n");
            printf("����� �¸� Ƚ��: %d\n", stats.user_wins);
            printf("��ǻ�� �¸� Ƚ��: %d\n", stats.computer_wins);
            printf("��� Ƚ��: %d\n", stats.draws);
            break;
        }

        // ��ǻ���� ����
        const char* computer_choice = get_computer_choice();
        printf("��ǻ���� ����: %s\n", computer_choice);

        // ����
        const char* result = determine_winner(user_input, computer_choice);
        printf("���: %s\n", result);

        // �¸�Ƚ�� ����
        if (strcmp(result, "����� �¸�") == 0) 
        {
            stats.user_wins++;
        }
        else if (strcmp(result, "��ǻ�� �¸�") == 0) 
        {
            stats.computer_wins++;
        }
        else 
        {
            stats.draws++;
        }
    }

    //���� ���
    fprintf(file, "===== ���������� ��� =====\n");
    fprintf(file, "����� �¸� Ƚ��: %d\n", stats.user_wins);
    fprintf(file, "��ǻ�� �¸� Ƚ��: %d\n", stats.computer_wins);
    fprintf(file, "��� Ƚ��: %d\n", stats.draws);
    fprintf(file, "==========================\n\n");
}

// ���簢�� ĭ ���α׷� ���� �Լ�
void visualize_grid(Cell* grid, int size, int* choices, int num_choices) 
{
    int side = (int)sqrt(size); //���簢�� -> �� �� ���� ���

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
        //1�� X�� ����
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
    //����ü ������
    Cell* cellA = (Cell*)a;
    Cell* cellB = (Cell*)b;

    return cellB->count - cellA->count;
}

// ���� ���� �Լ�
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
        // ��ȯ
        temp = grid[max_idx];
        grid[max_idx] = grid[i];
        grid[i] = temp;
    }
}

void start_mode2(FILE* file) 
{
    int n; // ĭ ����

    printf("�׸� ĭ�� ������ �Է��ϼ��� (��: 9, 16, 25 �� ���� ������): ");
    scanf("%d", &n);

    // ���� �޸� �Ҵ�
    Cell* grid = (Cell*)malloc(n * sizeof(Cell));

    if (grid == NULL) //���� ��
    {
        printf("�޸� �Ҵ� ����\n");
        return;
    }

    // �ʱ�ȭ �����ִ� ����
    for (int i = 0; i < n; i++) 
    {
        grid[i].count = 0;
        grid[i].index = i;
    }

    char command[10];
    srand(time(0)); //���� ���� ����

    while (1)
    {
        int num_choices = (rand() % 2) + 1; // 1�� �Ǵ� 2�� �ִ� 2��
        //���� �޸� �Ҵ�
        int* choices = (int*)malloc(num_choices * sizeof(int));

        if (choices == NULL) 
        //���� ��
        {
            printf("�޸� �Ҵ� ����\n");
            free(grid);
            return;
        }

        // �ߺ�X ĭ ����
        for (int i = 0; i < num_choices; i++) 
        {
            int choice;
            //do~while��
            do 
            {
                choice = rand() % n;
            } 
            while (i > 0 && choice == choices[i - 1]);

            choices[i] = choice;
            grid[choice].count++; // ���� ĭ Ƚ�� ����
        }

        // ��ºκ�
        printf("���� ����:\n");
        visualize_grid(grid, n, choices, num_choices);

        printf("����Ϸ��� 'continue'��, �����Ϸ��� 'exit'�� �Է�: ");
        scanf("%s", command);

        if (strcmp(command, "exit") == 0) 
        {
            // ���� ��� ���Ͽ� ���
            fprintf(file, "===== ���簢�� ĭ ���α׷� ��� =====\n");
            for (int i = 0; i < n; i++) 
            {
                fprintf(file, "ĭ %d: %d��\n", grid[i].index, grid[i].count);
            }

            // �������� ����
            sort_sort(grid, n);

            // ���� ��� ���� ���
            fprintf(file, "�������� ���� ���:\n");

            for (int i = 0; i < n; i++) 
            {
                fprintf(file, "ĭ %d: %d��\n", grid[i].index, grid[i].count);
            }
            fprintf(file, "=================================\n\n");

            // �ֿܼ� ���
            printf("���� �� ĭ�� 1 ǥ�� Ƚ�� (�������� ����):\n");
            for (int i = 0; i < n; i++) 
            {
                printf("ĭ %d: %d��\n", grid[i].index, grid[i].count);
            }

            free(choices);
            break;
        }
        else if (strcmp(command, "continue") != 0) //continue �ƴ� ��
        {
            printf("�߸��� ����Դϴ�. �ٽ� �Է��ϼ���.\n");
        }

        free(choices);
    }

    // free
    free(grid);
}

// ���� ���߱� ���� ���� �Լ�
void start_mode3(FILE* file) 
{
    int target, guess, attempts = 0;
    srand(time(0));
    //������ ��
    target = rand() % 100 + 1; // 1���� 100 ������ ����

    fprintf(file, "===== ���� ���߱� ���� ��� =====\n");
    printf("1���� 100 ������ ���ڸ� ���纸����!\n");

    while (1)
    {
        printf("���ڸ� �Է��ϼ���: ");
        scanf("%d", &guess);
        attempts++;//�õ� Ƚ��

        if (guess > target) 
        {
            printf("�� ���� ����\n");
        }
        else if (guess < target)
        {
            printf("�� ���� ����\n");
        }
        else 
        {
            printf("����!, �õ� Ƚ��: %d\n", attempts);
            fprintf(file, "����: %d (�õ� Ƚ��: %d)\n", target, attempts);
            break;
        }
    }

    fprintf(file, "===============================\n\n");
}

// ����� ���� ���� �Լ� ����
const char* get_choice_name(int choice) 
{
    switch (choice) 
    {
    case 1: return "����";
    case 2: return "����";
    case 3: return "��";
    default: return "�߸��� ����";
    }
}

int get_winner(int player_choice, int computer_choice) 
{
    if (player_choice == computer_choice)
    {
        return 0; // ���
    }
    if ((player_choice == 1 && computer_choice == 3) || (player_choice == 2 && computer_choice == 1) || (player_choice == 3 && computer_choice == 2)) 
    {
        return 1; // ����� �¸�
    }
    return -1; // ��ǻ�� �¸�
}

void start_mode4(FILE* file) {
    int player_choice, computer_choice, result;
    char playAgain;
    int first_winner; // 1: ����� �¸�, 0: ��ǻ�� �¸�
    int final_winner;
    srand(time(NULL)); // ������ �ʱ�ȭ

    while (1) 
    {
        // ���������� ù��°
        printf("ù ��° ����(1), ����(2), ��(3) �� �ϳ��� �����ϼ���: ");
        scanf("%d", &player_choice);
        computer_choice = (rand() % 3) + 1;
        printf("��ǻ���� ����: %s\n", get_choice_name(computer_choice));

        result = get_winner(player_choice, computer_choice);

        if (result == 0) 
        {
            printf("�����ϴ�. �ٽ� �õ��ϼ���.\n");
            continue;
        }

        first_winner = (result == 1) ? 1 : 0;
        final_winner = -1;

        // ����� ����
        while (final_winner == -1)
        {
            printf("����(1), ����(2), ��(3) �� �ϳ��� �����ϼ���: ");
            scanf("%d", &player_choice);
            computer_choice = (rand() % 3) + 1;//1���� 3����
            printf("��ǻ���� ����: %s\n", get_choice_name(computer_choice));

            if (player_choice == computer_choice)
            {
                final_winner = first_winner;
            }
            else 
            {
                result = get_winner(player_choice, computer_choice);
                if (result == 0)
                {
                    printf("�����ϴ�. �ٽ� �õ��ϼ���.\n");
                }
                else
                {
                    first_winner = (result == 1) ? 1 : 0;
                }
            }
        }

        if (final_winner == 1) 
        {
            printf("�÷��̾ �̰���ϴ�!\n");
        }
        else
        {
            printf("��ǻ�Ͱ� �̰���ϴ�!\n");
        }

        printf("�ٽ� �Ͻðڽ��ϱ�? y or n : ");
        scanf(" %c", &playAgain);

        if (playAgain != 'y') 
        {
            break;
        }
    }

    printf("������ �����մϴ�.\n"); 
}
