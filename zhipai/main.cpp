#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define SPADE   '3'
#define HEART   '4'
#define CLUB    '5'
#define DIAMOND '6'

#define SIZE_16  16
#define SIZE_128 128

#define MAX_CARD_POINT 13
#define MAX_CARD_COLOR 4
#define MAX_CARD_AMOUNT (MAX_CARD_POINT * MAX_CARD_COLOR)

typedef struct CARD_
{
    char color;
    char point[SIZE_16];
}CARD;

int e_play[MAX_CARD_AMOUNT];  // ��
int s_play[MAX_CARD_AMOUNT];  // ��
int w_play[MAX_CARD_AMOUNT];  // ��
int n_play[MAX_CARD_AMOUNT];  // ��
// ������
CARD ALL_CARDS[MAX_CARD_AMOUNT] = {
    {SPADE, "2"}, {SPADE, "3"}, {SPADE, "4"}, {SPADE, "5"}, {SPADE, "6"}, {SPADE, "7"}, {SPADE, "8"}, {SPADE, "9"}, {SPADE, "10"}, {SPADE, "J"}, {SPADE, "Q"}, {SPADE, "K"}, {SPADE, "A"},
    {HEART, "2"}, {HEART, "3"}, {HEART, "4"}, {HEART, "5"}, {HEART, "6"}, {HEART, "7"}, {HEART, "8"}, {HEART, "9"}, {HEART, "10"}, {HEART, "J"}, {HEART, "Q"}, {HEART, "K"}, {HEART, "A"},
    {CLUB, "2"}, {CLUB, "3"}, {CLUB, "4"}, {CLUB, "5"}, {CLUB, "6"}, {CLUB, "7"}, {CLUB, "8"}, {CLUB, "9"}, {CLUB, "10"}, {CLUB, "J"}, {CLUB, "Q"}, {CLUB, "K"}, {CLUB, "A"},
    {DIAMOND, "2"}, {DIAMOND, "3"}, {DIAMOND, "4"}, {DIAMOND, "5"}, {DIAMOND, "6"}, {DIAMOND, "7"}, {DIAMOND, "8"}, {DIAMOND, "9"}, {DIAMOND, "10"}, {DIAMOND, "J"}, {DIAMOND, "Q"}, {DIAMOND, "K"}, {DIAMOND, "A"}
};

int cards[MAX_CARD_AMOUNT];

// help
void usage()
{
    printf("------ʹ�ð���------\n");
    printf("�����������ַ�ָ����س�:\n");
    printf("A  // ϴ��\n");
    printf("B  // ����\n");
    printf("C  // ����\n");
    printf("D  // �˳�\n");
    printf("E  // ����\n");
    printf("F  // �鿴��\n");
    printf(">> ");
}

void show()
{
    int i = 0;
    int e_num = 0;
    int s_num = 0;
    int w_num = 0;
    int n_num = 0;
    int pool_num = 0;

    printf("  ��: ");
    for(i = 0; i < MAX_CARD_AMOUNT; i++)
    {
        if (e_play[i] == 1)
        {
            printf("%c%s ", ALL_CARDS[i].color, ALL_CARDS[i].point);
            e_num++;
        }
    }
    printf("�ܹ�%d����\n", e_num);

    printf("  ��: ");
    for(i = 0; i < MAX_CARD_AMOUNT; i++)
    {
        if (s_play[i] == 1)
        {
            printf("%c%s ", ALL_CARDS[i].color, ALL_CARDS[i].point);
            s_num++;
        }
    }
    printf("�ܹ�%d����\n", s_num);

    printf("  ��: ");
    for(i = 0; i < MAX_CARD_AMOUNT; i++)
    {
        if (w_play[i] == 1)
        {
            printf("%c%s ", ALL_CARDS[i].color, ALL_CARDS[i].point);
            w_num++;
        }
    }
    printf("�ܹ�%d����\n", w_num);

    printf("  ��: ");
    for(i = 0; i < MAX_CARD_AMOUNT; i++)
    {
        if (n_play[i] == 1)
        {
            printf("%c%s ", ALL_CARDS[i].color, ALL_CARDS[i].point);
            n_num++;
        }
    }
    printf("�ܹ�%d����\n", n_num);

    printf("�Ƴ�: ");
    for(i = 0; i < MAX_CARD_AMOUNT; i++)
    {
        if (cards[i] >= 0)
        {
            printf("%c%s ", ALL_CARDS[cards[i]].color, ALL_CARDS[cards[i]].point);
            pool_num++;
        }
    }
    printf("�ܹ�%d����\n", pool_num);
}


void shuffle()
{
    int i = 0, j = 0;

    memset(cards, 0, sizeof(cards));
    for(i = 0; i < MAX_CARD_AMOUNT; i++)
    {
        cards[i] = i;
        e_play[i] = 0;
        s_play[i] = 0;
        w_play[i] = 0;
        n_play[i] = 0;
    }

    // �������
    srand(time(NULL));

    for(i = 0; i < 1000; i++)
    {
        int tmp;

        int rand_num0 = rand() % MAX_CARD_AMOUNT;
        int rand_num1 = rand() % MAX_CARD_AMOUNT;

        tmp = cards[rand_num0];
        cards[rand_num0] = cards[rand_num1];
        cards[rand_num1] = tmp;
    }
}

void deal()
{
    int i = 0;
    while(i < MAX_CARD_AMOUNT)
    {
        e_play[cards[i++]] = 1;
        s_play[cards[i++]] = 1;
        w_play[cards[i++]] = 1;
        n_play[cards[i++]] = 1;
    }
}

void begin()
{
    int rand_play = rand() % 4;
    if (rand_play == 0)
    {
        printf("���ߵ�����ȳ���\n");
    }
    else if (rand_play == 1)
    {
        printf("�ϱߵ�����ȳ���\n");
    }
    else if (rand_play == 2)
    {
        printf("���ߵ�����ȳ���\n");
    }
    else if (rand_play == 3)
    {
        printf("���ߵ�����ȳ���\n");
    }


}

int main()
{
    while(1)
    {
        char cmd[SIZE_128];

        usage();
        scanf("%s", cmd);

        if ( strcmp(cmd, "A") == 0 )
        {
            shuffle();
        }
        else if ( strcmp(cmd, "B") == 0)
        {
            deal();
        }
        else if ( strcmp(cmd, "C") == 0)
        {
            begin();
        }
        else if ( strcmp(cmd, "D") == 0)
        {
            return 0;
        }
        else if ( strcmp(cmd, "E") == 0)
        {
            continue;
        }
        else
        {
            show();
        }
    }
    return 0;
}
