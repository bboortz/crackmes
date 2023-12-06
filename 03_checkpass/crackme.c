#include <stdio.h>
#include <string.h>

// copy n characters of a string from src to dst. dst will include a NULL-termination
int substr(char *dst, char *src, size_t n) {
  int len = snprintf(dst, n, "%s", src);
  if (len < 0 || (unsigned) len >= sizeof dst) return -1;
  return len;
}

void ok() {
  printf("Access granted!\n");
}

void not_ok() {
  printf("Access denied!\n");
}

int check_password(char* input, int n){
  int n_quarter = n/4;
  char password1[] = "supe";
  char password2[] = "rS3c";
  char password3[] = "r3t!";
  char password4[] = "!!\n";
  char input1[n_quarter + 1]; 
  char input2[n_quarter + 1]; 
  char input3[n_quarter + 1]; 
  char input4[n_quarter + 1]; 

  (void)substr(input1, input + (0 * n_quarter), n_quarter + 1);
  (void)substr(input2, input + (1 * n_quarter), n_quarter + 1);
  (void)substr(input3, input + (2 * n_quarter), n_quarter + 1);
  (void)substr(input4, input + (3 * n_quarter), n_quarter + 1);
                             
  if (strncmp(input1, password1, n_quarter) == 0) {
    if (strncmp(input2, password2, n_quarter) == 0) {
      if (strncmp(input3, password3, n_quarter) == 0) {
        if (strncmp(input4, password4, n_quarter) == 0) {
          return 1;
        }
      }
    }
  }

  return 0;
}

int main() {
  printf("\n *** enjoy the crackme ***\n\n");
  int input_n = 16;
  char input[input_n];
  printf("Enter the password: ");
  fgets(input, sizeof(input), stdin);

  // printf("<%s>\n", input);
  if ( check_password(input, input_n) ) {
    ok();
  } else {
    not_ok();
  }

  return 0;
}

