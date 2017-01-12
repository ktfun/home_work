#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 
#include <semaphore.h>

#define MAX_COUNT  50

sem_t semid1;
sem_t semid2;

// 司机
void* driver() 
{
	int count = MAX_COUNT;
	while(count--)  
	{           
		printf("[D] driver 正常行车\n");
		printf("[D] driver 到站停车\n");
        sem_post(&semid1);
		sem_wait(&semid2);
		printf("[D] driver 开车\n");
	} 
} 
	
void* passenger() 
{  
	int count = MAX_COUNT;
	while(count--)  
	{         
		printf("[C] conductor 售票\n");
		sem_wait(&semid1);
		printf("[C] conductor 开车门\n");
		printf("[C] conductor 关车门\n");
		sem_post(&semid2);
	} 
}

void run()
{
	printf("**************************************\n");
	printf("*        操作系统原理课程设计        *\n");
	printf("*        班级:                       *\n");
	printf("*        指导老师:                   *\n");
	printf("*        第九小组: 司机和售票员问题  *\n");
	printf("*        小组成员:                   *\n");
	printf("**************************************\n");
	
	sem_init(&semid1,0,0);
	sem_init(&semid2,0,0);
	
	pthread_t tid1,tid2;   
	pthread_create(&tid1,0,driver,0); 
	pthread_create(&tid2,0,passenger,0);
	
	pthread_join(tid1,(void**)0);
	pthread_join(tid2,(void**)0);
}

void display()
{
	while(1)
	{
		int choose;
		
		printf("**************************************\n");
		printf("*               主菜单               *\n");
		printf("*          1. 司机和售票员           *\n");
		printf("*          0. 退出                   *\n");
		printf("**************************************\n");
		printf("请输入您的选择(0-1): ");
		
		scanf("%d", &choose);
		
		if ( choose == 0 )
		{
			return;
		}
		else if (choose == 1)
		{
			run();
		}
		else
		{
			printf("未知的命令!\n");
		}
		
		printf("输入Enter继续\n");
		getchar();
		getchar();
	}
}
	
int main() 
{
	display();
	return 0; 
}

//多进程实现同步：


