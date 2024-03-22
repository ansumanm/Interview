#include<stdio.h>

#define BIT_SET(x, n) ((x) |= (1UL << (n)))
#define BIT_CLEAR(x, n) ((x) &= ~(1UL << (n)))

int main(int argc, char *argv[])
{
  int x;
  printf("%d\n", __builtin_ffs(1));
  printf("%d\n", __builtin_ffs(2));
  printf("%d\n", __builtin_ffs(1 << 31));

  x = 0;

  BIT_SET(x, 0);
  printf("x = 0x%x\n", x);

  BIT_CLEAR(x, 0);
  printf("x = 0x%x\n", x);

  return 0;
}