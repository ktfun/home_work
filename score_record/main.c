#include <stdio.h>
#include <stdlib.h>

#define BYTE_1024 1024
#define FILE_SCORE  "C:\\file\\score.txt"  // 分数文件存放的位置，注意这里的'\'需要转义

typedef struct ST_SCORE
{
    char id[BYTE_1024];  //
    char name[BYTE_1024];
    int cgrade;
}SCORE;  // 学生-分数结构体

SCORE score_all[BYTE_1024]; // 存储所有的分数信息
int score_count = 0;  // 分数信息的个数
FILE *fp = NULL;  // 文件句柄

// 使用说明
void usage()
{
    printf("----------操作指南----------\n");
    printf("请输入下列任意字符后回车\n");
    printf("A //显示所有成绩\n");
    printf("B //分段显示所有成绩\n");
    printf("C //输入学号查询成绩\n");
    printf("D //输入姓名查询成绩\n");
    printf("E //添加新的成绩记录\n");
    printf("F //通过学号修改成绩并存盘\n");
    printf("G //通过姓名修改成绩并存盘\n");
    printf(">> ");
}

// 从文件中加载数据，存入结构体中
void load_file()
{
    fp = fopen(FILE_SCORE, "r+");
    if ( fp == NULL )
    {
        printf("打开文件%s失败!\n", FILE_SCORE);
        return;
    }

    while(!feof(fp))
    {
        fscanf(fp, "%s %s %d", score_all[score_count].id, score_all[score_count].name, &score_all[score_count].cgrade);
        score_count++;
    }
}

// 将数据从结构体中导入到文件中
void save_file()
{
    int index = 0;
    if ( fp == NULL )
    {
        return ;
    }

	// 这里先关闭文件，再打开文件是为了清空文件里面原有的内容
    fclose(fp);
    fp = fopen(FILE_SCORE, "w+");
    if ( fp == NULL )
    {
        printf("打开文件%s失败!\n", FILE_SCORE);
        return;
    }

	// 将结构体中的数据导入文件中
    for(index = 0; index < score_count; index++)
    {
		// 这里最后一组数据不输出换行符，否则再次读入数据的时候，会多一组没用的数据
        if ( index == score_count - 1)
        {
            fprintf(fp, "%s %s %d", score_all[index].id, score_all[index].name, score_all[index].cgrade);
        }
        else
        {
            fprintf(fp, "%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
        }
    }

	// 刷新文件缓存
    fflush(fp);
}

// A -> 显示所有成绩
void show()
{
    int index = 0;

    printf("学号  姓名  C成绩\n");
    for(index = 0; index < score_count; index++)
    {
        printf("%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
    }
}

// B -> 分段显示所有成绩
void show_sub()
{
    int index = 0;
    printf("学号  姓名  C成绩\n");
    // 60分以下
    printf("==>60分以下的有<===\n");
    for(index = 0; index < score_count; index++)
    {
        if ( score_all[index].cgrade < 60 )
        {
            printf("%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
        }
    }
    // 60~79
    printf("==>60~79的有<===\n");
    for(index = 0; index < score_count; index++)
    {
        if ( score_all[index].cgrade >= 60 && score_all[index].cgrade <= 79 )
        {
            printf("%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
        }
    }
    // 80~89
    printf("==>80~89的有<===\n");
    for(index = 0; index < score_count; index++)
    {
        if ( score_all[index].cgrade >= 80 && score_all[index].cgrade <= 89 )
        {
            printf("%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
        }
    }
    // 90分以上
    printf("==>90分以上的有<===\n");
    for(index = 0; index < score_count; index++)
    {
        if ( score_all[index].cgrade >= 90 )
        {
            printf("%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
        }
    }

}

// 主要的循环
void main_loop()
{
	// 初始化数据
    memset(score_all, 0 ,sizeof(SCORE)*BYTE_1024);

    load_file();  // 加载文件
    while(1)
    {
        char input[BYTE_1024] = "";

        usage();

        scanf("%s", input);

		// A //显示所有成绩
        if ( strcmp(input, "A") == 0 )
        {
            show();
        }
		// B //分段显示所有成绩
        else if ( strcmp(input, "B") == 0 )
        {
            show_sub();
        }
		// C //输入学号查询成绩
        else if ( strcmp(input, "C") == 0 )
        {
            char id[BYTE_1024] = "";
            int index = 0;
            int is_find = 0;

            printf("请输入学号: ");
            scanf("%s", id);

            for(index = 0; index < score_count; index++)
            {
				// 找到数据之后做标记，退出循环
                if (strcmp(score_all[index].id, id) == 0)
                {
                    is_find = 1;
                    break;
                }
            }

            if(is_find)
            {
                printf("%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
            }
            else
            {
                printf("未找到\n");
            }
        }
		// D //输入姓名查询成绩
        else if ( strcmp(input, "D") == 0 )
        {
            char name[BYTE_1024] = "";
            int index = 0;
            int is_find = 0;

            printf("请输入姓名: ");
            scanf("%s", name);

			// 找到数据之后做标记，退出循环
            for(index = 0; index < score_count; index++)
            {
                if (strcmp(score_all[index].name, name) == 0)
                {
                    is_find = 1;
                    break;
                }
            }

            if(is_find)
            {
                printf("%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
            }
            else
            {
                printf("未找到\n");
            }
        }
		// E //添加新的成绩记录
        else if ( strcmp(input, "E") == 0 )
        {
            char id[BYTE_1024];
            char name[BYTE_1024];
            int cgrade;
            int index = 0;
            int is_find = 0;

            printf("请输入新的学号: ");
            scanf("%s", id);

            printf("请输入姓名: ");
            scanf("%s", name);

            printf("请输入C成绩: ");
            scanf("%d", &cgrade);

			// 如果仓库里面已经有对应学号的数据，则拒绝添加
            for(index = 0; index < score_count; index++)
            {
                if(strcmp(score_all[index].id, id) == 0)
                {
                    is_find = 1;
                    break;
                }
            }

            if (is_find)
            {
                printf("已存在的学号!\n");
            }
            else
            {
                strcpy(score_all[score_count].id, id);
                strcpy(score_all[score_count].name, name);
                score_all[score_count].cgrade = cgrade;
                score_count++;

                save_file();

                printf("添加成功!\n");
            }
        }
		// F //通过学号修改成绩并存盘
        else if ( strcmp(input, "F") == 0 )
        {
            char id[BYTE_1024] = "";
            int cgrade;
            int index = 0;
            int is_find = 0;

            printf("请输入学号: ");
            scanf("%s", id);
            printf("请输入新的成绩: ");
            scanf("%d", &cgrade);
			
            for(index = 0; index < score_count; index++)
            {
				// 通过学号找到数据后标记，然后退出循环
                if(strcmp(score_all[index].id, id) == 0)
                {
                    is_find = 1;
                    break;
                }
            }

            if(is_find)
            {
                score_all[index].cgrade = cgrade;
                save_file();
                printf("修改成功!\n");
            }
            else
            {
                printf("未找到!\n");
            }
        }
		// G //通过姓名修改成绩并存盘
        else if ( strcmp(input, "G") == 0 )
        {
            char name[BYTE_1024] = "";
            int cgrade;
            int index = 0;
            int is_find = 0;

            printf("请输入姓名: ");
            scanf("%s", name);
            printf("请输入新的成绩: ");
            scanf("%d", &cgrade);

            for(index = 0; index < score_count; index++)
            {
				// // 通过姓名找到数据后标记，然后退出循环
                if(strcmp(score_all[index].name, name) == 0)
                {
                    is_find = 1;
                    break;
                }
            }

            if(is_find)
            {
                score_all[index].cgrade = cgrade;
                save_file();
                printf("修改成功!\n");
            }
            else
            {
                printf("未找到!\n");
            }
        }
		// 未定义的命令
        else
        {
            printf("未知的命令!\n");
        }

        printf("输入任意按键继续...\n");
        getchar();
        getchar();
    }
}

int main()
{
    main_loop();
    return 0;
}
