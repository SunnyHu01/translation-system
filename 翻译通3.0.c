#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#pragma warning (disable : 4996) //屏蔽掉C4996型警告信息；

typedef struct my_dict
{
	char *key;
	char *content;
}DICT;
int line = 0; //计算文件行数
FILE *get_openfile()
{
	FILE *fp = fopen("./DICT.txt", "r");
	char s[100];
	if (!fp)
	{
		perror("");
		return NULL;
	}
	while (fgets(s,sizeof(s),fp) != NULL)
	{
		line++;
	}
	printf("%d\n", line);
	fseek(fp, 0, SEEK_SET); // 文件指针移至开头；
	return fp;
}

void get_guolv(char *buf, int num)
{
	while (buf[num] == '\t' || buf[num] == '\n' || buf[num] == '\r' || buf[num] == ' ')
	{
		num--;
	}
	buf[num + 1] = 0;
}

void get_fenli(char *buf, char *buf2, int num)
{
	int i = 0, j = 0;
	while (buf[i] != ' ')
	{
		i++;
	}
	buf[i] = 0;
	i = i + 3;  //单词与译文之间空3格；
	//如果没有这种固定空3格的规律，就用如下代码，while循环来判断；
	/*while (buf[i + 1] == ' ')
	{
		i++;
	}*/
	for (; i < num;i++)
	{
		buf2[j++] = buf[i];
	}
	buf2[j] = 0;
}

void get_init(DICT **str)
{
	FILE *fp = get_openfile();
	DICT *p = malloc(sizeof(DICT)*line);
	int i = 0;
	char *q = NULL;
	char buf[256];
	char buf2[256];
	while (1)
	{
		q = fgets(buf, sizeof(buf), fp);
		if (q == NULL)
			break;
		get_fenli(buf, buf2, strlen(buf));  //分离key和content
		p[i].key = malloc(strlen(buf));
		strcpy(p[i].key, buf);

		get_guolv(buf2, strlen(buf2) - 1);  //过滤隐形字符；
		p[i].content = malloc(strlen(buf2));
		strcpy(p[i].content, buf2);
		i++;
	}
	fclose(fp);
	*str = p;
}

int get_start(char *key, char *content, int num, DICT *str)
{
	for (int i = 0; i < num; i++)
	{
		if (strcmp(key, str[i].key) == 0)
		{
			strcpy(content, str[i].content);
			return 1;
		}
	}
	return 0;
}

int main()
{
	DICT *str = NULL;
	get_init(&str);
	char key[256];
	char content[256];
	int cout = 0;
	//微秒计时；
	double run_time;
	LARGE_INTEGER time_start;	//开始时间
	LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	while (1)
	{
		printf("请输入需要翻译的字符：");
		fgets(key, sizeof(key),stdin);
		key[strlen(key) - 1] = 0;
		QueryPerformanceCounter(&time_start); //开始计时；
		cout = get_start(key, content, line, str);
		if (cout == 1)
		{
			printf("译文为：%s\n", content);
		}
		else
		{
			printf("No Find!\n");
		}
		QueryPerformanceCounter(&time_over);  //结束计时
		run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
		//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
		printf("翻译总共用时：%fus\n", run_time);
	}

	/*char buf[256] = "abandonment   n.放弃生命";
	char buf2[256];
	get_fenli(buf, buf2, strlen(buf));  //分离key和content
	printf("%s\n%s\n", buf, buf2);*/

	system("pause");
	return 0;
}