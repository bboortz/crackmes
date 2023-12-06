#include <stdio.h>
#include <string.h>

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
  char password3[] = "rc3t";
  char password4[] = "!!\n";
  char input1[n_quarter + 1]; 
  char input2[n_quarter + 1]; 
  char input3[n_quarter + 1]; 
  char input4[n_quarter + 1]; 

  (void)strncpy(input1, input + (0 * n_quarter), n_quarter);  // copy the first half of the input string
  input1[n_quarter + 1] = '\0';                               // Null-terminate the string
  (void)strncpy(input2, input + (1 * n_quarter), n_quarter);  // copy the second half of the input string
  input2[n_quarter + 1] = '\0';                               // Null-terminate the string
  (void)strncpy(input3, input + (2 * n_quarter), n_quarter);  // copy the third half of the input string
  input3[n_quarter + 1] = '\0';                               // Null-terminate the string
  (void)strncpy(input4, input + (3 * n_quarter), n_quarter);  // copy the forth half of the input string
  input4[n_quarter + 1] = '\0';                               // Null-terminate the string
                             
  if (strncmp(input1, password1, n_quarter) == 0) {
    printf("1111\n");
    if (strncmp(input2, password2, n_quarter) == 0) {
      printf("1111\n");
      if (strncmp(input3, password3, n_quarter) == 0) {
        printf("1111\n");
        if (strncmp(input4, password4, n_quarter) == 0) {
          printf("1111\n");
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

