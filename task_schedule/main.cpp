#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

#define MAX_TASK  10
#define MAX_ETIME 30
#define MAX_RTIME 30

struct TASK
{
    TASK *next;
    int etime;  // enter time
    int rtime;  // run time
    int wtime;  // wait time
    int stime;  // start time
    int is_check;
};

struct HEAD
{
    TASK *first;
    TASK *end;
    int count;
};

HEAD *list_head = (HEAD*)malloc(sizeof(HEAD));  // 链表头

// 队列 - 元素个数
int queue_size(HEAD* head)
{
    return head->count;
}

// 队列 - 出队
TASK* queue_pop(HEAD* head)
{
    if(queue_size(head) == 0 || head == NULL || head->first == NULL )
    {
        return NULL;
    }

    TASK* out = head->first;
    head->first = out->next;
    if(head->first == NULL)
    {
        head->end = NULL;
    }
    head->count--;

    return out;
}

// 队列 - 入队
void queue_push(HEAD* head, TASK* tmp)
{
    if(tmp == NULL)
    {
        return;
    }

    if(head->end == NULL)
    {
        head->first = tmp;
        head->end = tmp;
    }
    else
    {
        head->end->next = tmp;
        head->end = tmp;
    }
    head->count++;
}

// 队列 - 清空
void queue_init(HEAD* head)
{
    if(head == NULL)
    {
        return;
    }

    while(head->count)
    {
        TASK *tmp = queue_pop(head);
        free(tmp);
        tmp = NULL;
    }

    head->first = NULL;
    head->end = NULL;
}


void init()
{
    srand(time(NULL));

    int n = rand() % MAX_TASK;
    int i = 0;
    printf("随机生成%d个作业\n", n);

    list_head->first = NULL;
    list_head->end = NULL;
    list_head->count = 0;
    for(i = 0; i < n; i++)
    {
        int etime = rand() % MAX_ETIME;
        int rtime = rand() % MAX_RTIME;
        TASK *tmp = (TASK*)malloc(sizeof(TASK));

        memset(tmp, 0, sizeof(TASK));
        tmp->next = NULL;
        tmp->is_check = 0;

        if ( list_head->end == NULL )
        {
            list_head->first = tmp;
            list_head->end = tmp;
        }
        else
        {
            list_head->end->next = tmp;
            list_head->end = tmp;
        }
        list_head->count++;
    }
}

void fcfs()
{
    HEAD *queue_head = (HEAD*)malloc(sizeof(HEAD));  //  队列
    int count = 0;
    while(count != list_head->count)
    {
        int min = MAX_ETIME + 1;
        TASK* ptr = list_head->first;
        TASK *min_ptr = NULL;

        while(ptr != NULL)
        {
            if(!ptr->is_check && ptr->etime < min)
            {
                min_ptr = ptr;
                min = ptr->etime;
            }
        }

        TASK *new_task = ();
        count++;
    }

    free(queue_head);
    queue_head = NULL;
}

int main()
{
    return 0;
}
