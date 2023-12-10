#include <stdio.h>
#include <string.h>
#include <ctype.h>

// copy n characters of a string from src to dst. dst will include a NULL-termination
int substr(char *dst, char *src, size_t n) {
  int len = snprintf(dst, n, "%s", src);
  if (len < 0 || (unsigned) len >= sizeof dst) return -1;
  return len;
}

void ok() {
  printf("\nAccess granted!\n");
}

void not_ok() {
  printf("\nAccess denied!\n");
}

int check_serial(const char* serial, size_t length) {
  int i, set1 = 0, set2 = 0, set3 = 0, set4 = 0, sum = 0;

  // Verify the serial format: nnnn-nnnn-nnnn-nnnn
  if (strlen(serial) != length) {
    return 0; // Incorrect length
  }

  for (i = 0; i < (int) length; i++) {
    char c = serial[i];
    
    if (i == 4 || i == 9 || i == 14) {
      if (c != '-') {
        return 0; // Invalid separator at positions 4, 9, and 14
      }
    } else if (!isdigit(c)) {
      return 0; // Non-numeric characters found
    }
    sum += c;

    if (i < 4) {
      set1 += c - '0';
    } else if (i < 9) {
      set2 += c - '2';
    } else if (i < 14) {
      if (9 == c) {
        return 0;
      }
      set3 += c - '2';
    } else {
      set4 += c - '0';
    }
  }
  /*
  printf("\n----------------------\n");
  printf("%d\n", set1);
  printf("%d\n", set2);
  printf("%d\n", set3);
  printf("%d\n", set4);
  */

  // Check the computed sums for each set
  if (set1 != 18 || set2 != 18 || set3 != 18 || set4 != 18) {
    return 0; // Invalid sums for sets
  }
  //printf("sum: %d", sum);
  if (1004 != sum) {
    return 0;
  }

  return 1; // Serial is valid
}

int main() {
  printf("\n *** enjoy the crackme ***\n\n");
  int input_n = 21;
  char input[input_n];

  printf("Enter the password: ");
  fgets(input, sizeof(input), stdin);

  // Remove the newline character if it exists
  size_t length = strlen(input);
  if (input[length - 1] == '\n') {
    input[length - 1] = '\0'; // Replace newline with null terminator
  }

  // printf("<%s>\n", input);
  if ( check_serial(input, length -1) ) {
    ok();
  } else {
    not_ok();
  }

  return 0;
}

