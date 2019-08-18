#include <stdio.h>
#include <stdint.h>

uint32_t get_mask(int start, int end)
{
	uint32_t mask = -1;
	uint32_t mask_right;
	uint32_t mask_left;

	mask_right = (-1 << start);
	/* XXX For right shifts, if the shift is on a 
	 * signed number, then the signed bit gets added.
	 */
	mask_left = (mask >> (31 - end ));
	mask = mask_right & mask_left;

	return mask;
}
void clear_bits(uint32_t *i, int start, int end)
{
	uint32_t mask = get_mask(start, end);
	*i = *i & ~mask;
}

void set_bits(uint32_t *i, int start, int end)
{
	uint32_t mask = get_mask(start, end);
	*i = *i | mask;
}

int main()
{
	uint32_t i = -1;
	printf("0x%x \n", i);

	clear_bits(&i, 4, 7);
	printf("0x%x \n", i);

	clear_bits(&i, 12, 15);
	printf("0x%x \n", i);

	set_bits(&i, 4, 7);
	printf("0x%x \n", i);

	return 0;
}
