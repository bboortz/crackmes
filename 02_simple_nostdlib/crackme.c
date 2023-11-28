void _start() {
    // Define the correct password
    // char password[] = "password123";
    char password[] = { 0x71, 'a', 's', '1', '\0' }; // RLE-encoded strings

    // Input password (hardcoded for this example)
    char input[] = "pas2";


    // Compare passwords
    int i = 0;
    while (password[i] != '\0' && input[i] != '\0' && password[i] == input[i]) {
        i++;
    }

    // Check if the passwords match
    if (password[i] == '\0' && input[i] == '\0') {
        // Passwords match
        __asm__(
          "movl $1, %eax\n"  // System call number for _exit on 32-bit systems (Linux)
          "movl $0, %ebx\n"   // Exit status (replace with desired value)
          "syscall\n");
    } else {
        // Passwords don't match
        __asm__(
          "movl $1, %eax\n"  // System call number for _exit on 32-bit systems (Linux)
          "movl $2, %ebx\n"   // Exit status (replace with desired value)
          "syscall\n");
    }
}

