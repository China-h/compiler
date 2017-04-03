#ifndef _LEXICAL_H
#define _LEXICAL_H

/*函数处理的值*/
typedef struct lex_return
{
	int byte;		/*类型*/
	double value;	/*某些类型的值,如果是字符串就记录长度*/
	int len;		//长度，用于记录字符的偏移等
	char *str;		/*字符串，标志符等的值*/
}lex_return;

enum LEX_BYTE_LIST
{
	B_ID,//标识符
	B_STR,//字符串
	B_CHAR,//字符
	B_ENTER, //回车
	B_SPACE, //空白符
};

extern void lex_main(lex_return *re,char *soustr);
extern void letterpose(lex_return *re,char *soustr);
extern void utfscepose(lex_return *re,char *soustr,int len);
extern void strpose(lex_return *re,char *soustr);
extern char transshipc(char c);
extern void charpose(lex_return *re,char *soustr);
#endif
