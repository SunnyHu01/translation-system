#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#pragma warning (disable : 4996) //���ε�C4996�;�����Ϣ��

typedef struct my_dict
{
	char *key;
	char *content;
}DICT;
int line = 0; //�����ļ�����
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
	fseek(fp, 0, SEEK_SET); // �ļ�ָ��������ͷ��
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
	i = i + 3;  //����������֮���3��
	//���û�����̶ֹ���3��Ĺ��ɣ��������´��룬whileѭ�����жϣ�
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
		get_fenli(buf, buf2, strlen(buf));  //����key��content
		p[i].key = malloc(strlen(buf));
		strcpy(p[i].key, buf);

		get_guolv(buf2, strlen(buf2) - 1);  //���������ַ���
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
	//΢���ʱ��
	double run_time;
	LARGE_INTEGER time_start;	//��ʼʱ��
	LARGE_INTEGER time_over;	//����ʱ��
	double dqFreq;		//��ʱ��Ƶ��
	LARGE_INTEGER f;	//��ʱ��Ƶ��
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	while (1)
	{
		printf("��������Ҫ������ַ���");
		fgets(key, sizeof(key),stdin);
		key[strlen(key) - 1] = 0;
		QueryPerformanceCounter(&time_start); //��ʼ��ʱ��
		cout = get_start(key, content, line, str);
		if (cout == 1)
		{
			printf("����Ϊ��%s\n", content);
		}
		else
		{
			printf("No Find!\n");
		}
		QueryPerformanceCounter(&time_over);  //������ʱ
		run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
		//����1000000�ѵ�λ���뻯Ϊ΢�룬����Ϊ1000 000/��cpu��Ƶ��΢��
		printf("�����ܹ���ʱ��%fus\n", run_time);
	}

	/*char buf[256] = "abandonment   n.��������";
	char buf2[256];
	get_fenli(buf, buf2, strlen(buf));  //����key��content
	printf("%s\n%s\n", buf, buf2);*/

	system("pause");
	return 0;
}