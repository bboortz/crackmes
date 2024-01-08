#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>



int main() {
  char buf1[16] = {0};
  char buf2[16] = "aaabaaacaaadaaae";

  gets(buf1);

  if (strcmp(buf2, "thepassword") == 0) {
    puts("Correct!");
  } else {
    puts("Incorrect!");
  }
  return 0;
}
