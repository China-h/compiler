#include <stdio.h>
#include <stdlib.h>


/*分配内存*/
void *zmalloc(unsigned int len)
{
	register unsigned int i;
	char *p = (char*)malloc(len);
	if (p == NULL)
	{
		printf("内存分配失败!\n");
		exit(1);
	}
	for (i = 0;i < len;i++)
		p[i] = '\0';

	return (void*)p;
}


int isletter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int isnumber(char c)
{
	return (c >= '0' && c <= '9');
}


int isheadutf(unsigned char c)
{
#define UC unsigned char
	int i=0;
	if (c >= (UC)0xC0 && c <= (UC)0xDF)
		i = 2;
	else if (c >= (UC)0xE0 && c <= (UC)0xEF)
		i = 3;
	else if (c >= (UC)0xF0 && c <= (UC)0xF7)
		i = 4;
	else if (c >= (UC)0xF8 && c <= (UC)0xFB)
		i = 5;
	else if (c >= (UC)0xFC && c <= (UC)0xFD)
		i = 6;
	return i;
}

int issecutf(unsigned char c)
{
	return (c >= (UC)0x80 && c <=(UC)0xBF);
}
#undef UC
