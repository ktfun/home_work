#include <stdio.h>
#include <stdlib.h>

#define BYTE_1024 1024
#define FILE_SCORE  "C:\\file\\score.txt"  // �����ļ���ŵ�λ�ã�ע�������'\'��Ҫת��

typedef struct ST_SCORE
{
    char id[BYTE_1024];  //
    char name[BYTE_1024];
    int cgrade;
}SCORE;  // ѧ��-�����ṹ��

SCORE score_all[BYTE_1024]; // �洢���еķ�����Ϣ
int score_count = 0;  // ������Ϣ�ĸ���
FILE *fp = NULL;  // �ļ����

// ʹ��˵��
void usage()
{
    printf("----------����ָ��----------\n");
    printf("���������������ַ���س�\n");
    printf("A //��ʾ���гɼ�\n");
    printf("B //�ֶ���ʾ���гɼ�\n");
    printf("C //����ѧ�Ų�ѯ�ɼ�\n");
    printf("D //����������ѯ�ɼ�\n");
    printf("E //����µĳɼ���¼\n");
    printf("F //ͨ��ѧ���޸ĳɼ�������\n");
    printf("G //ͨ�������޸ĳɼ�������\n");
    printf(">> ");
}

// ���ļ��м������ݣ�����ṹ����
void load_file()
{
    fp = fopen(FILE_SCORE, "r+");
    if ( fp == NULL )
    {
        printf("���ļ�%sʧ��!\n", FILE_SCORE);
        return;
    }

    while(!feof(fp))
    {
        fscanf(fp, "%s %s %d", score_all[score_count].id, score_all[score_count].name, &score_all[score_count].cgrade);
        score_count++;
    }
}

// �����ݴӽṹ���е��뵽�ļ���
void save_file()
{
    int index = 0;
    if ( fp == NULL )
    {
        return ;
    }

	// �����ȹر��ļ����ٴ��ļ���Ϊ������ļ�����ԭ�е�����
    fclose(fp);
    fp = fopen(FILE_SCORE, "w+");
    if ( fp == NULL )
    {
        printf("���ļ�%sʧ��!\n", FILE_SCORE);
        return;
    }

	// ���ṹ���е����ݵ����ļ���
    for(index = 0; index < score_count; index++)
    {
		// �������һ�����ݲ�������з��������ٴζ������ݵ�ʱ�򣬻��һ��û�õ�����
        if ( index == score_count - 1)
        {
            fprintf(fp, "%s %s %d", score_all[index].id, score_all[index].name, score_all[index].cgrade);
        }
        else
        {
            fprintf(fp, "%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
        }
    }

	// ˢ���ļ�����
    fflush(fp);
}

// A -> ��ʾ���гɼ�
void show()
{
    int index = 0;

    printf("ѧ��  ����  C�ɼ�\n");
    for(index = 0; index < score_count; index++)
    {
        printf("%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
    }
}

// B -> �ֶ���ʾ���гɼ�
void show_sub()
{
    int index = 0;
    printf("ѧ��  ����  C�ɼ�\n");
    // 60������
    printf("==>60�����µ���<===\n");
    for(index = 0; index < score_count; index++)
    {
        if ( score_all[index].cgrade < 60 )
        {
            printf("%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
        }
    }
    // 60~79
    printf("==>60~79����<===\n");
    for(index = 0; index < score_count; index++)
    {
        if ( score_all[index].cgrade >= 60 && score_all[index].cgrade <= 79 )
        {
            printf("%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
        }
    }
    // 80~89
    printf("==>80~89����<===\n");
    for(index = 0; index < score_count; index++)
    {
        if ( score_all[index].cgrade >= 80 && score_all[index].cgrade <= 89 )
        {
            printf("%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
        }
    }
    // 90������
    printf("==>90�����ϵ���<===\n");
    for(index = 0; index < score_count; index++)
    {
        if ( score_all[index].cgrade >= 90 )
        {
            printf("%s %s %d\n", score_all[index].id, score_all[index].name, score_all[index].cgrade);
        }
    }

}

// ��Ҫ��ѭ��
void main_loop()
{
	// ��ʼ������
    memset(score_all, 0 ,sizeof(SCORE)*BYTE_1024);

    load_file();  // �����ļ�
    while(1)
    {
        char input[BYTE_1024] = "";

        usage();

        scanf("%s", input);

		// A //��ʾ���гɼ�
        if ( strcmp(input, "A") == 0 )
        {
            show();
        }
		// B //�ֶ���ʾ���гɼ�
        else if ( strcmp(input, "B") == 0 )
        {
            show_sub();
        }
		// C //����ѧ�Ų�ѯ�ɼ�
        else if ( strcmp(input, "C") == 0 )
        {
            char id[BYTE_1024] = "";
            int index = 0;
            int is_find = 0;

            printf("������ѧ��: ");
            scanf("%s", id);

            for(index = 0; index < score_count; index++)
            {
				// �ҵ�����֮������ǣ��˳�ѭ��
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
                printf("δ�ҵ�\n");
            }
        }
		// D //����������ѯ�ɼ�
        else if ( strcmp(input, "D") == 0 )
        {
            char name[BYTE_1024] = "";
            int index = 0;
            int is_find = 0;

            printf("����������: ");
            scanf("%s", name);

			// �ҵ�����֮������ǣ��˳�ѭ��
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
                printf("δ�ҵ�\n");
            }
        }
		// E //����µĳɼ���¼
        else if ( strcmp(input, "E") == 0 )
        {
            char id[BYTE_1024];
            char name[BYTE_1024];
            int cgrade;
            int index = 0;
            int is_find = 0;

            printf("�������µ�ѧ��: ");
            scanf("%s", id);

            printf("����������: ");
            scanf("%s", name);

            printf("������C�ɼ�: ");
            scanf("%d", &cgrade);

			// ����ֿ������Ѿ��ж�Ӧѧ�ŵ����ݣ���ܾ����
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
                printf("�Ѵ��ڵ�ѧ��!\n");
            }
            else
            {
                strcpy(score_all[score_count].id, id);
                strcpy(score_all[score_count].name, name);
                score_all[score_count].cgrade = cgrade;
                score_count++;

                save_file();

                printf("��ӳɹ�!\n");
            }
        }
		// F //ͨ��ѧ���޸ĳɼ�������
        else if ( strcmp(input, "F") == 0 )
        {
            char id[BYTE_1024] = "";
            int cgrade;
            int index = 0;
            int is_find = 0;

            printf("������ѧ��: ");
            scanf("%s", id);
            printf("�������µĳɼ�: ");
            scanf("%d", &cgrade);
			
            for(index = 0; index < score_count; index++)
            {
				// ͨ��ѧ���ҵ����ݺ��ǣ�Ȼ���˳�ѭ��
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
                printf("�޸ĳɹ�!\n");
            }
            else
            {
                printf("δ�ҵ�!\n");
            }
        }
		// G //ͨ�������޸ĳɼ�������
        else if ( strcmp(input, "G") == 0 )
        {
            char name[BYTE_1024] = "";
            int cgrade;
            int index = 0;
            int is_find = 0;

            printf("����������: ");
            scanf("%s", name);
            printf("�������µĳɼ�: ");
            scanf("%d", &cgrade);

            for(index = 0; index < score_count; index++)
            {
				// // ͨ�������ҵ����ݺ��ǣ�Ȼ���˳�ѭ��
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
                printf("�޸ĳɹ�!\n");
            }
            else
            {
                printf("δ�ҵ�!\n");
            }
        }
		// δ���������
        else
        {
            printf("δ֪������!\n");
        }

        printf("�������ⰴ������...\n");
        getchar();
        getchar();
    }
}

int main()
{
    main_loop();
    return 0;
}
