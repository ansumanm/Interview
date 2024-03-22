#include<stdio.h>
#include<string.h>

void strrev(char *str) {
  int length = strlen(str);
  char tmp;

  for (int i = 0; i < length/2; i++) {
    tmp = str[i];
    str[i] = str[length - 1 - i];
    str[length - 1 - i] = tmp;
  }
}

int main(int argc, char *argv[])
{
  char str[] = "Reverse";

  printf("%s\n", str);
  strrev(str);
  printf("%s\n", str);

  return 0;
}