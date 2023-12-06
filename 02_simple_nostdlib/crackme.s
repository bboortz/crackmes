	.file	"crackme.c"
	.text
	.section	.text._start,"ax",@progbits
	.globl	_start
	.type	_start, @function
_start:
#APP
# 25 "crackme.c" 1
	movl $1, %eax
movl $2, %ebx
syscall

# 0 "" 2
#NO_APP
	ret
	.size	_start, .-_start
	.ident	"GCC: (GNU) 13.2.1 20230801"
	.section	.note.GNU-stack,"",@progbits
