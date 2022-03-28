#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#pragma warning (disable : 4996) //���ε�C4996�;�����Ϣ��

typedef struct my_dict
{
	char *key;
	char *content;
}DICT;

int line = 1; //�����ļ���������
FILE *get_openfile()
{
	FILE *p = fopen("./DICT.txt", "r");	
	char s[100];
	if (!p)
	{
		perror("");
		return NULL;
	}
	else
	{
		while (fgets(s, sizeof(s), p) != NULL)
		{
			if (s[strlen(s) - 1] == '\n')
				line++;
		}
		//printf("���ĵ�����Ϊ��%d\n", line);
	}
	fseek(p, 0, SEEK_SET);  //����������ļ���ͷ��
	return p;
}

void get_guolv(char *buf, int num)
{
	while (buf[num] == ' ' || buf[num] == '\t' || buf[num] == '\n' || buf[num] == '\r')
	{
		num--;
	}
	buf[num+1] = 0;
}

void get_init(DICT **p)
{
	FILE *str = get_openfile();  //���ļ�

	DICT *q = malloc(sizeof(DICT) * (line / 2));
	char *a = NULL; //�����жϣ�fgets()���ݶ��ꣻ
	int i = 0;
	char buf[256];
	while (1)
	{
		a = fgets(buf, sizeof(buf), str);
		if (a == NULL)
			break;
		get_guolv(buf, strlen(buf) - 1);  //���˵�ÿһ��ĩβ��һЩ���ܴ��ڵ��ַ���
		q[i].key = malloc(sizeof(buf) + 1);
		strcpy(q[i].key, buf + 1);  //ȥ��#

		fgets(buf, sizeof(buf), str);
		q[i].content = malloc(sizeof(buf) + 1);
		strcpy(q[i].content, buf + 6);  //ȥ��Trans:

		i++;
	}
	fclose(str);
	*p = q;	
}

int get_start(DICT *p, char *key, char *content, int num)
{
	for (int i = 0; i < num; i++)
	{
		if (strcmp(key, p[i].key) == 0)
		{
			strcpy(content, p[i].content);
			return 1;
		}
	}
	return 0;
}

int main()
{
	//����ͨ2.0
	DICT *p = NULL;
	char key[256];
	char content[256];
	int cout;
	//΢���ʱ��
	double run_time;
	LARGE_INTEGER time_start;	//��ʼʱ��
	LARGE_INTEGER time_over;	//����ʱ��
	double dqFreq;		//��ʱ��Ƶ��
	LARGE_INTEGER f;	//��ʱ��Ƶ��
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	
	//clock_t start_time = 0, end_time = 0;  //ms��ʱ�ģ�

	get_init(&p);  //��ʼ��, ȡ��ַ���Σ���Ϊ���ܹ���ɳ�ʼ��������
	while (1)
	{
		printf("���������跭���Ӣ�ģ�");
		fgets(key, sizeof(key), stdin);
		key[strlen(key) - 1] = 0;
		//start_time = clock();
		QueryPerformanceCounter(&time_start); //��ʼ��ʱ��
		cout = get_start(p, key, content, (line / 2)); //��ʼ�������ķ�����content�У�Ӣ�ķ�����key�У�����2��ʾ�ʵ���������2����
		if (cout == 1)
		{
			printf("����Ϊ��%s\n", content);
		}
		else
			printf("no find!\n");
		//end_time = clock();
		QueryPerformanceCounter(&time_over);  //������ʱ
		run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
		//����1000000�ѵ�λ���뻯Ϊ΢�룬����Ϊ1000 000/��cpu��Ƶ��΢��
		printf("�����ܹ���ʱ��%fus\n", run_time);
		//printf("�����ܹ���ʱ��%dms\n", end_time - start_time);
	}
	system("pause");
	return 0;
}