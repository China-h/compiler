#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
char *fileopen(char *path)
{
	int flen;
	char *c;
	FILE *fp = fopen(path,"r");
	if (fp == NULL)
	{
		printf("打开文件 %s 失败\n",path);
		exit(1);
	}
	fseek(fp,0L,SEEK_END);
	flen = ftell(fp);
	fseek(fp,0L,SEEK_SET);
	c = (char*)zmalloc(flen);
	fread(c,flen-1,1,fp);
	fclose(fp);
	return c;
}
