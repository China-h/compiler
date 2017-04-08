#include <stdio.h>
#include <stdlib.h>
#include "lexical.h"
#include "tools.h"


/*词法分析主函数*/
void lex_main(lex_return *re,char *soustr) 
{
	int utflen;
	re->value = 0;
	re->str = NULL;
	re->byte = 0;
	re->len = 0;
	switch (soustr[0])
	{
		case ' ':
			re->byte = B_SPACE;
			break;
		case '\n':
			re->byte = B_ENTER;
			break;
		case '\"':
			re->value = 1;
			re->byte = B_STR;
			strpose(re,&soustr[1]);
			re->str[0] = soustr[0];
			break;
		case '\'':
			charpose(re,&soustr[1]);
			break;
		default:
			if (isletter(soustr[0]))
			{
				re->byte = B_ID;
				re->value = 1;
				letterpose(re,&soustr[1]);
				re->str[0]=soustr[0];
			}
			else if((utflen = isheadutf(soustr[0])))
			{
				re->byte = B_ID;
				re->value = 1;
				utfscepose(re,&soustr[1],utflen-1);
				re->str[0]=soustr[0];
			}
			break;
	}
}


/*字母处理*/
void letterpose(lex_return *re,char *soustr)
{
	int len = (int)re->value;
	int utflen;
	char c = soustr[0];
	re->value = re->value + 1;
	if (isletter(soustr[0]) || isnumber(soustr[0]))
		letterpose(re,&soustr[1]);
	else if ((utflen = isheadutf(soustr[0])))
		utfscepose(re,&soustr[1],utflen-1);
	else
	{
		re->str = (char*)zmalloc(len+1);
		c = '\0';
	}
	re->str[len] = c;
}
/*UTF-8处理*/
void utfscepose(lex_return *re,char *soustr,int len)
{
	int slen = (int)re->value;
	re->value = re->value + 1;
	char c = soustr[0];
	if (len != 0)
	{
		//未完成非UTF-8编码处理
		utfscepose(re,&soustr[1],len-1);
	}
	else
	{
		if (isnumber(c) || isnumber(c))
			letterpose(re,&soustr[1]);
		else if ((len = isheadutf(c)))
			utfscepose(re,&soustr[1],len-1);
		else
		{
			re->str = (char*)zmalloc(slen + 1);
			c = '\0';
		}
	}
	re->str[slen] = c;
}


/*字符串处理*/
void strpose(lex_return *re,char *soustr)
{
	int slen = (int)re->value;
	char c = soustr[0];
	re->value = re->value + 1;
	if (c == '\0')
	{
			//未完成：错误处理
			printf("字符串错误");
			exit(1);
	}
	else if (c == '\"')
	{
		re->str = (char*)zmalloc(slen + 2);
		re->value = re->value + 1;
		re->str[slen + 1] = '\0';
	}
	else
	{
		if (c == '\\')
		{
			c = transshipc(soustr[1]);
			soustr = soustr + 1;
		}
		strpose(re,&soustr[1]);
	}
	re->str[slen] = c;
}


/*转义*/
char transshipc(char c)
{
	switch (c)
	{
		case 't':
			c = '\t';
			break;
		case  'n':
			c = '\n';
			break;
		case 'r':
			c = '\r';
			break;
		case '\'':
			c = '\'';
			break;
		case '\"':
			c = '\"';
			break;
		default:
			if (c == '\0' || c == EOF)
			{
				printf("错误");
				exit(1);
			}
			else
			{
			//未完成：警告
				printf("警告");
			}
			break;
	}
	return c;
}

/*字符处理*/
void charpose(lex_return *re,char *soustr)
{
	char c = soustr[0];
	re->len = 1;
	if (c == '\\')
	{
		c = transshipc(soustr[1]);
		soustr = soustr + 1;
		re->len = 2;
	}
	else if (c == '\'')
	{
		//错误处理
	}

	if (soustr[1] != '\'')
	{
		printf("字符错误\n");
		exit(1);
	}

	re->byte = B_CHAR;
	re->value = c;
}
