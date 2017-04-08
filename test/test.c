#include <stdio.h>
#include "tools.h"
#include "lexical.h"
#include "operfile.h"
int main()
{
	char *c = fileopen("a.txt");
	printf("%s\n",c);
	return 0;
}
