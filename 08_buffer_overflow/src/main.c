#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void secretFunction() {
    printf("\nRight password!\n");
    exit(0);
}

/*
void printStack(char *file, int line) {
    unsigned long long* rsp; // Pointer to the stack (for x86_64)

    // Get the current stack pointer (for x86_64)
    __asm__("mov %%rsp, %0" : "=r" (rsp));

    printf("\n------------------------\nPrinting stack (%s, %d):\n", file, line);

    // Traverse and print the stack contents
    for (int i = 0; i < 10; ++i) {
        printf("Stack address [%p]: Value [%llu]\n", rsp + i, *(rsp + i));
    }
    printf("\n------------------------\n");

}
*/

void checkPassword() {
    char space1[] = "111111111";
    char inputPassword[10];
    
    //printStack(__FILE__, __LINE__);
    printf("Enter the password: ");
    scanf("%s", inputPassword);
    // printStack(__FILE__, __LINE__);

    /*
    printf("scanned!!!!1");
    printf("\n");
    printf("space1: %s\n", space1);
    printf("inputPassword: %s\n", inputPassword);
    printf("space2: %s\n", space2);
    */
    
}

int main() {
    printf("\n *** enjoy the crackme ***\n\n");
    //printStack(__FILE__, __LINE__);
    checkPassword();
    printf("\nWrong password!\n");

    return 0;
}