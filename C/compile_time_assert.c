#include<stdio.h>
#include<stdint.h>

#define compile_time_assert(cond, x) \
	    char x[(cond) ? 1 : -1]

typedef struct
{
	uint8_t MODE;
	uint32_t DATA;
	uint32_t COUNT;
} timer;

compile_time_assert(sizeof(timer) == 4, SIZEOF_TIMER_MUST_BE_4);

int main()
{
	printf("%ld\n", sizeof(timer));

	return 0;
}
