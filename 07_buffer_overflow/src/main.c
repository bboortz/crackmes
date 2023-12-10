#include <stdio.h>
#include <string.h>

int main() {
    printf("\n *** enjoy the crackme ***\n\n");
    char inputPassword[10];
    char rightPassword[10];

    printf("Enter the password: ");
    scanf("%s", inputPassword);

    if (0 == strcmp(inputPassword, rightPassword)) {
      printf("\nCorrect password!\n");
    } else {
      printf("\nWrong password!\n");
    }
    

    return 0;
}