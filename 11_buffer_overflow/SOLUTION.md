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

# find the 2 buffer variables and the fixed string which will be compared

# smash the stack and overwrite the variable buf 1 in order to overwrite buf2 too
```
./output/crackme < <(python -c "print('a'*16+'thepassword')")
```

or using the file `solve.py`
