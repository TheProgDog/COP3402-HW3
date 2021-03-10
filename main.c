#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *input = fopen("input.txt", "r");

  printf("%s\n\n", input);

  printf("Hello, world!\n");

  return 0;
}
