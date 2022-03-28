#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#pragma warning (disable : 4996) //屏蔽掉C4996型警告信息；

typedef struct my_dict
{
	char *key;
	char *content;
}DICT;

int line = 1; //定义文件内容行数
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
		//printf("该文档行数为：%d\n", line);
	}
	fseek(p, 0, SEEK_SET);  //将光标移至文件开头；
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
	FILE *str = get_openfile();  //打开文件

	DICT *q = malloc(sizeof(DICT) * (line / 2));
	char *a = NULL; //用来判断，fgets()数据读完；
	int i = 0;
	char buf[256];
	while (1)
	{
		a = fgets(buf, sizeof(buf), str);
		if (a == NULL)
			break;
		get_guolv(buf, strlen(buf) - 1);  //过滤掉每一行末尾的一些可能存在的字符；
		q[i].key = malloc(sizeof(buf) + 1);
		strcpy(q[i].key, buf + 1);  //去掉#

		fgets(buf, sizeof(buf), str);
		q[i].content = malloc(sizeof(buf) + 1);
		strcpy(q[i].content, buf + 6);  //去掉Trans:

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
	//翻译通2.0
	DICT *p = NULL;
	char key[256];
	char content[256];
	int cout;
	//微秒计时；
	double run_time;
	LARGE_INTEGER time_start;	//开始时间
	LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	
	//clock_t start_time = 0, end_time = 0;  //ms计时的；

	get_init(&p);  //初始化, 取地址做参，是为了能够完成初始化操作；
	while (1)
	{
		printf("请输入所需翻译的英文：");
		fgets(key, sizeof(key), stdin);
		key[strlen(key) - 1] = 0;
		//start_time = clock();
		QueryPerformanceCounter(&time_start); //开始计时；
		cout = get_start(p, key, content, (line / 2)); //开始，将译文放置在content中，英文放置在key中；数字2表示词典中数据有2个；
		if (cout == 1)
		{
			printf("译文为：%s\n", content);
		}
		else
			printf("no find!\n");
		//end_time = clock();
		QueryPerformanceCounter(&time_over);  //结束计时
		run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
		//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
		printf("翻译总共用时：%fus\n", run_time);
		//printf("翻译总共用时：%dms\n", end_time - start_time);
	}
	system("pause");
	return 0;
}