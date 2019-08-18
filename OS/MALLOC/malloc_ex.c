#include <stdio.h>
#include <stdlib.h>

#define ONEK (1<<9)
int main()
{
	int *x, *y, *z, *m, *n, *o;

	printf("*** FIRST ALLOCATION *** ");
	x = malloc(ONEK);
	printf("*** SECOND ALLOCATION *** ");
	y = malloc(ONEK);
	printf("*** THIRD ALLOCATION *** ");
	z = malloc(ONEK);
	printf("*** FOURTH ALLOCATION *** ");
	m = malloc(ONEK);
	printf("*** FIFTH ALLOCATION *** ");
	n = malloc(ONEK);
	printf("*** SIXTH ALLOCATION *** ");
	o = malloc(ONEK);

	return 0;
}
