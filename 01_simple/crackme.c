#include <stdio.h>
#include <string.h>

void ok() {
  printf("Access granted!\n");
}

void not_ok() {
  printf("Access denied!\n");
}

int check_password(char* input, int n){
  char password[] = "s3cr3tPassw0rd\n";

  if (strncmp(input, password, n) == 0) {
    return 1;
  }
  return 0;
}

int main() {
  printf("\n *** enjoy the crackme ***\n\n");
  int input_n = 20;
  char input[input_n];
  printf("Enter the password: ");
  fgets(input, sizeof(input), stdin);

  // printf("<%s>\n", input);
  // if (strncmp(input, password, input_n) == 0) {
  if ( check_password(input, input_n) ) {
    ok();
  } else {
    not_ok();
  }

  return 0;
}

