/* C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void rtrim_inplace(char *s) {
  if (!s) return;
  size_t n = strlen(s);
  while (n > 0 && isspace((unsigned char)s[n - 1])) {
    s[n - 1] = '\0';
    n--;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error: expected exactly one argument.\n");
    return 1;
  }

  const char *input_arg = argv[1];
  char *input = (char *)malloc(strlen(input_arg) + 1);
  if (!input) {
    fprintf(stderr, "Error: out of memory.\n");
    return 2;
  }
  strcpy(input, input_arg);

  printf("%s\n", input);
  rtrim_inplace(input);
  printf("%s\n", input);

  free(input);
  return 0;
}