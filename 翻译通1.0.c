#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996) //���ε�C4996�;�����Ϣ��

//����һ���ṹ���ֵ�
typedef struct my_dict 
{
	//char key[256];   //Ӣ��
	//char content[256];  //����
	char *key;  
	char *content;
}DICT;

void get_init(DICT **str)
{
	DICT *p = malloc(sizeof(DICT) * 2);  //����ռ䣻
	p[0].key = malloc(sizeof("hello")+1);
	strcpy(p[0].key, "hello");
	p[0].content = malloc(sizeof("��") + 1);
	strcpy(p[0].content, "��");
	p[1].key = malloc(sizeof("you") + 1);
	strcpy(p[1].key, "you");
	p[1].content = malloc(sizeof("��") + 1);
	strcpy(p[1].content, "��");
	*str = p;  //����*
}

int get_start(DICT *str, char *key, char *content, int num)
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
	///��淭��ͨ��
	DICT *str = NULL;
	char key[256];
	char content[256]; 
	int cout;
	get_init(&str);  //��ʼ����ȡ��ַ���Σ���Ϊ���ܹ���ɳ�ʼ��������
	//printf("%s\n", str[0].key);
	while (1)
	{
		printf("���������跭���Ӣ�ģ�");
		fgets(key, sizeof(key), stdin);
		key[strlen(key) - 1] = 0;
		cout = get_start(str, key, content, 2); //��ʼ�������ķ�����content�У�Ӣ�ķ�����key�У�����2��ʾ�ʵ���������2����
		if (cout == 1)
		{
			printf("����Ϊ��%s\n", content);
		}
		else
			printf("no find!\n");
	}

	system("pause");
	return 0;
}