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

# find the address of the function you want to call
```
objdump -d output/crackme | grep -i sec
```

# smash the stack and insert the address of the stack
* with debug or without any optimization
```
./output/crackme < <(python -c "print('AB-'*3+'\x00'+'CD-'*3+'\x00'+'EF'*4+'\x56\x11\x40'+'\x00')")
```
