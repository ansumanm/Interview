#include<stdio.h>

typedef struct {
	int a;
	int b;
	char c;
	short d;
} x;

#define OFFSET(x, y) \
	(long)&(((x *)0)->y)

int main() 
{
	printf("%ld \n", OFFSET(x, a));
	printf("%ld \n", OFFSET(x, b));
	printf("%ld \n", OFFSET(x, c));
	printf("%ld \n", OFFSET(x, d));

	return 0;
}
