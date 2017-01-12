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
    TASK *next;  // ��һ�����
    int no;  // ������
    int etime;  // enter time
    int rtime;  // run time
    int wtime;  // wait time
    int stime;  // start time
    int is_check;  // ����б�ʶ��1�����Ѿ�����У�0����δ�����
};

struct HEAD
{
    TASK *first;  // ��һ�����
    TASK *end;  // ���һ�����
    int count;  // �������������ͷ��㣩
};

HEAD *list_head = (HEAD*)malloc(sizeof(HEAD));  // ����ͷ

// ���� - Ԫ�ظ���
int queue_size(HEAD* head)
{
    return head->count;
}

// ���� - ����
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

// ���� - ���
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

// �����������
void init()
{
    srand(time(NULL));

    int n = rand() % MAX_TASK + 1;
    int i = 0;
    printf("�������%d����ҵ\n", n);

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
        list_head->count++;  // ������һ
    }
}

// ������ӱ�־
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
    clear_check(); // ������
    printf("<===�����ȷ���===>\n");
    HEAD *queue_head = (HEAD*)malloc(sizeof(HEAD));  //  ����
    int count = 0;
    int now_time = 0;
    int total_wtime = 0;  // �ܹ��ȴ�ʱ��
    int total_rtime = 0;  // �ܹ�����ʱ��

    memset(queue_head, 0, sizeof(HEAD));

    // ���еĸ�����������ĸ���
    while(count != list_head->count)
    {
        int min = INFINITE;
        TASK* ptr = list_head->first;
        TASK *min_ptr = ptr;

        // �ҵ�etime��С�Ľ��
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

        // ����stime��wtime
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

        // �����
        queue_push(queue_head, new_task);
        count++;
    }

    printf("��� \t ���� \t �ȴ� \t ��ʼ \t ���� \t ���\n");
    while(queue_head->count != 0)
    {
        TASK *tmp = queue_pop(queue_head);

        printf("%d \t %d \t %d \t %d \t %d \t %d\n", tmp->no, tmp->etime, tmp->wtime, tmp->stime, tmp->rtime, tmp->stime + tmp->rtime);

        free(tmp);
    }
    printf("ƽ���ȴ�ʱ��: %.2f, ƽ������ʱ��: %.2f\n", total_wtime * 1.0 / count, total_rtime * 1.0 / count);

    free(queue_head);
    queue_head = NULL;
}

// the shortest service time
void tsst()
{
    clear_check(); // ������
    printf("<===��̷���ʱ��===>\n");
    HEAD *queue_head = (HEAD*)malloc(sizeof(HEAD));  //  ����
    int count = 0;
    int now_time = 0;
    int total_wtime = 0;  // �ܹ��ȴ�ʱ��
    int total_rtime = 0;  // �ܹ�����ʱ��

    memset(queue_head, 0, sizeof(HEAD));

    // ���еĸ�����������ĸ���
    while(count != list_head->count)
    {
        TASK* ptr = list_head->first;
        TASK *best_ptr = ptr;
        int is_find = 0; // �Ƿ��ҵ�
        int tmin = INFINITE;

        // �������г����ҵ�etime��now_timeС�Ľ��
        while(ptr != NULL)
        {
            // �ҵ��Ѿ�����Ľ��,�������ҵ�rtime��С��
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

        // ���е�����δ��ʱ�䣬��һ������ﵽ�Ľڵ㣬����ж������Ա�rtime
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

        // �����
        queue_push(queue_head, new_task);
        //printf("now_time -> %d\n", now_time);
        count++;
    }

    printf("��� \t ���� \t �ȴ� \t ��ʼ \t ���� \t ���\n");
    while(queue_head->count != 0)
    {
        TASK *tmp = queue_pop(queue_head);

        printf("%d \t %d \t %d \t %d \t %d \t %d\n", tmp->no, tmp->etime, tmp->wtime, tmp->stime, tmp->rtime, tmp->stime + tmp->rtime);

        free(tmp);
    }
    printf("ƽ���ȴ�ʱ��: %.2f, ƽ������ʱ��: %.2f\n", total_wtime * 1.0 / count, total_rtime * 1.0 / count);

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
