#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

#define INFINITE  99999999
#define MAX_TASK  5000
#define MAX_ETIME 5001
#define MAX_RTIME 51

struct TASK
{
    TASK *next;  // 下一个结点
    int no;  // 任务编号
    int etime;  // enter time
    int rtime;  // run time
    int wtime;  // wait time
    int stime;  // start time
    int is_check;  // 入队列标识，1代表已经入队列，0代表未入队列
};

struct HEAD
{
    TASK *first;  // 第一给结点
    TASK *end;  // 最后一个结点
    int count;  // 结点数（不包括头结点）
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

// 随机生成任务
void init()
{
    srand(time(NULL));

    int n = rand() % MAX_TASK + 1;
    int i = 0;
    printf("随机生成%d个作业\n", n);

    list_head->first = NULL;
    list_head->end = NULL;
    list_head->count = 0;
    for(i = 0; i < n; i++)
    {
        int etime = rand() % MAX_ETIME; // enter time
        int rtime = rand() % (MAX_RTIME - 5) + 5;  // run time
        TASK *tmp = (TASK*)malloc(sizeof(TASK));

        memset(tmp, 0, sizeof(TASK));
        tmp->no = i;
        tmp->next = NULL;
        tmp->is_check = 0;
        tmp->etime = etime;
        tmp->rtime = rtime;

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
        list_head->count++;  // 计数加一
    }
}

// 清理入队标志
void clear_check()
{
    TASK *ptr = list_head->first;

    while(ptr != NULL)
    {
        ptr->is_check = 0;
        ptr->stime = 0;
        ptr->wtime = 0;
        ptr = ptr->next;
    }
}

void fcfs()
{
    clear_check(); // 清理标记
    printf("<===先来先服务===>\n");
    HEAD *queue_head = (HEAD*)malloc(sizeof(HEAD));  //  队列
    int count = 0;
    int now_time = 0;
    int total_wtime = 0;  // 总共等待时间
    int total_rtime = 0;  // 总共运行时间

    memset(queue_head, 0, sizeof(HEAD));

    // 队列的个数等于链表的个数
    while(count != list_head->count)
    {
        int min = INFINITE;
        TASK* ptr = list_head->first;
        TASK *min_ptr = ptr;

        // 找到etime最小的结点
        while(ptr != NULL)
        {
            if(!ptr->is_check && ptr->etime <= min)
            {
                min_ptr = ptr;
                min = ptr->etime;
            }
            ptr = ptr->next;
        }

        TASK *new_task = (TASK*)malloc(sizeof(TASK));
        min_ptr->is_check = 1;
        memcpy(new_task, min_ptr, sizeof(TASK));

        // 计算stime和wtime
        if ( new_task->etime > now_time)
        {
            new_task->stime = new_task->etime;
            new_task->wtime = 0;
            now_time = new_task->etime + new_task->rtime;
        }
        else
        {
            new_task->stime = now_time;
            new_task->wtime = new_task->stime - new_task->etime;
            now_time += new_task->rtime;
        }

        total_wtime += new_task->wtime;
        total_rtime += new_task->rtime;

        // 入队列
        queue_push(queue_head, new_task);
        count++;
    }

    printf("序号 \t 进入 \t 等待 \t 开始 \t 运行 \t 完成\n");
    while(queue_head->count != 0)
    {
        TASK *tmp = queue_pop(queue_head);

        printf("%d \t %d \t %d \t %d \t %d \t %d\n", tmp->no, tmp->etime, tmp->wtime, tmp->stime, tmp->rtime, tmp->stime + tmp->rtime);

        free(tmp);
    }
    printf("平均等待时间: %.2f, 平均运行时间: %.2f\n", total_wtime * 1.0 / count, total_rtime * 1.0 / count);

    free(queue_head);
    queue_head = NULL;
}

// the shortest service time
void tsst()
{
    clear_check(); // 清理标记
    printf("<===最短服务时间===>\n");
    HEAD *queue_head = (HEAD*)malloc(sizeof(HEAD));  //  队列
    int count = 0;
    int now_time = 0;
    int total_wtime = 0;  // 总共等待时间
    int total_rtime = 0;  // 总共运行时间

    memset(queue_head, 0, sizeof(HEAD));

    // 队列的个数等于链表的个数
    while(count != list_head->count)
    {
        TASK* ptr = list_head->first;
        TASK *best_ptr = ptr;
        int is_find = 0; // 是否找到
        int tmin = INFINITE;

        // 在链表中尝试找到etime比now_time小的结点
        while(ptr != NULL)
        {
            // 找到已经进入的结点,从里面找到rtime最小的
            if(!ptr->is_check && ptr->etime <= now_time)
            {
                if ( tmin > ptr->rtime )
                {
                    //printf("tmin -> %d rtime -> %d no -> %d\n", tmin, ptr->rtime, ptr->no);
                    tmin = ptr->rtime;
                    best_ptr = ptr;
                }

                is_find = 1;
            }
            ptr = ptr->next;
        }

        // 所有的任务还未到时间，找一个最早达到的节点，如果有多个，则对比rtime
        if ( !is_find )
        {
            int etmin = INFINITE;
            ptr = list_head->first;

            while(ptr != NULL)
            {
                //printf("check -> %d\n", ptr->is_check);
                if(!ptr->is_check)
                {
                    if( ptr->etime < etmin || ((ptr->etime == etmin) && ptr->rtime < best_ptr->rtime) )
                    {
                        etmin = ptr->etime;
                        best_ptr = ptr;
                    }
                }

                ptr = ptr->next;
            }

            best_ptr->stime = best_ptr->etime;
            best_ptr->wtime = 0;
            now_time = best_ptr->stime + best_ptr->rtime;
        }
        else
        {
            best_ptr->stime = now_time;
            best_ptr->wtime = best_ptr->stime - best_ptr->etime;
            now_time += best_ptr->rtime;
        }

        TASK *new_task = (TASK*)malloc(sizeof(TASK));
        best_ptr->is_check = 1;
        memcpy(new_task, best_ptr, sizeof(TASK));

        total_wtime += new_task->wtime;
        total_rtime += new_task->rtime;

        // 入队列
        queue_push(queue_head, new_task);
        //printf("now_time -> %d\n", now_time);
        count++;
    }

    printf("序号 \t 进入 \t 等待 \t 开始 \t 运行 \t 完成\n");
    while(queue_head->count != 0)
    {
        TASK *tmp = queue_pop(queue_head);

        printf("%d \t %d \t %d \t %d \t %d \t %d\n", tmp->no, tmp->etime, tmp->wtime, tmp->stime, tmp->rtime, tmp->stime + tmp->rtime);

        free(tmp);
    }
    printf("平均等待时间: %.2f, 平均运行时间: %.2f\n", total_wtime * 1.0 / count, total_rtime * 1.0 / count);

    free(queue_head);
    queue_head = NULL;
}

int main()
{
    init();
    fcfs();
    tsst();
    return 0;
}
