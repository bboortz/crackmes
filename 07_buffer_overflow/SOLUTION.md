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

# find the 2 fixed variables which will be compares

# smash the stack and insert the address of the stack
* with debug or without any optimization
```
./output/crackme < <(python -c "print('AB-'*3+'\x00'+'AB-'*3+'\x00')")
```
