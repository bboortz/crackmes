#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


void not_ok(void) {
    printf("\nWrong password!\n");
    exit(0);
}


void encrypt(char *str, char *key) {

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        int j = i % 4;
        str[i] = str[i] ^ key[j];
        // printf("%d,", str[i]);
    }
}

int qsum(char *str) {
    int result = 0;

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        result += str[i];
    }

    return result;
}

void c(char *buf, ...) {
	va_list args;
	va_start (args, buf);     /* Initialize the argument args. */

	char arg = va_arg(args, int);
	
	while( arg ) {
		sprintf(buf, "%s%c", buf, arg);
		arg = va_arg(args, int);
	}

	va_end (args);            /* Clean up. */
}

int strip_input(char *str) {
    // Remove the newline character if it exists
    size_t len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0'; // Replace newline with null terminator
    }
    return len - 1;
}


int main() {
    printf("\n *** enjoy the crackme ***\n\n");
    char str[30];
    char key[30];
	// c(str, 'C','o','r','r','e', 'c', 't', ' ', 'P', 'a', 's', 's', 'w', 'o', 'r', 'd', '!');
    // c(str, 'v', '\\', 'J', '@', 'P', 'P', 'L', 'e', 'R', 'K', 'A', 'B', '\\', 'J', 'V');
    c(str, 118,92,74,64,80,80,76,18,101,82,75,65,66,92,74,86,20);
    //c(key, '5','3','8','2');

    printf("Enter the password: ");
    fgets(key, sizeof(key), stdin);

    int len = strip_input(key);
    if (20 <= len) {
        //not_ok();
    }
    
    // printf("enc:\n<%s>\n", str);
    encrypt(str, key);
    //printf("dec:\n<%s>\n", str);

    int q_sum = qsum(str);
    if (1638 != q_sum) {
        not_ok();
    } else {
        printf("%s\n", str);
    }
    
    //encrypt(str, key);
    /*
    printf("\n<%s>\n", str);
    printf("\nWrong password!\n");
    */

    return 0;
}