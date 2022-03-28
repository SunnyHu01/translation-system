#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996) //屏蔽掉C4996型警告信息；

//定义一个结构体字典
typedef struct my_dict 
{
	//char key[256];   //英文
	//char content[256];  //译文
	char *key;  
	char *content;
}DICT;

void get_init(DICT **str)
{
	DICT *p = malloc(sizeof(DICT) * 2);  //申请空间；
	p[0].key = malloc(sizeof("hello")+1);
	strcpy(p[0].key, "hello");
	p[0].content = malloc(sizeof("嗨") + 1);
	strcpy(p[0].content, "嗨");
	p[1].key = malloc(sizeof("you") + 1);
	strcpy(p[1].key, "you");
	p[1].content = malloc(sizeof("你") + 1);
	strcpy(p[1].content, "你");
	*str = p;  //二级*
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
	///简版翻译通；
	DICT *str = NULL;
	char key[256];
	char content[256]; 
	int cout;
	get_init(&str);  //初始化，取地址做参，是为了能够完成初始化操作；
	//printf("%s\n", str[0].key);
	while (1)
	{
		printf("请输入所需翻译的英文：");
		fgets(key, sizeof(key), stdin);
		key[strlen(key) - 1] = 0;
		cout = get_start(str, key, content, 2); //开始，将译文放置在content中，英文放置在key中；数字2表示词典中数据有2个；
		if (cout == 1)
		{
			printf("译文为：%s\n", content);
		}
		else
			printf("no find!\n");
	}

	system("pause");
	return 0;
}