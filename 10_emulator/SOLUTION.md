# do you want to spoiler? scroll down
```
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
.
```

# disassamble the binary
use objdump, ghidra, cutter, or similar tools

# find the encrypted string

# likely, you have to bruteforce the encryption function with a guessed
* convert the binary to a object file
```
objconv -fnasm -wex -xs crackme crackme.s
```

* remove every unnecessary in crackme.s
```
nasm  -felf64 -o crackme.o crackme.s
```

* build a program which is calling the encrypt function with the key
```
gcc -m32 -o main main.c crackme.o && ./main
```


# the right password is
* 5382
