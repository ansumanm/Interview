#include <stdio.h>

#define ALIGN(x,a)              __ALIGN_MASK(x,(typeof(x))(a)-1)
#define __ALIGN_MASK(x,mask)    (((x)+(mask))&~(mask))


int main ()
{
	int x = 12;

	printf("%d \n", ALIGN(12, 4));
	printf("%d \n", (x%4 ? (x + (4 - x%4)) : x ));

	return 0;
}
