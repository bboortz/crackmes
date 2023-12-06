	.file	"crackme.c"
	.text
	.section	.rodata.main.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Enter the password: "
.LC1:
	.string	"%s"
.LC2:
	.string	"password123"
.LC3:
	.string	"Access granted!"
.LC4:
	.string	"Access denied!"
	.section	.text.startup.main,"ax",@progbits
	.globl	main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	leal	-48(%ebp), %esi
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	pushl	%ecx
	subl	$56, %esp
	movl	%gs:20, %eax
	movl	%eax, -28(%ebp)
	xorl	%eax, %eax
	leal	.LC0@GOTOFF(%ebx), %eax
	pushl	%eax
	call	printf@PLT
	popl	%eax
	leal	.LC1@GOTOFF(%ebx), %eax
	popl	%edx
	pushl	%esi
	pushl	%eax
	call	__isoc99_scanf@PLT
	popl	%ecx
	popl	%eax
	leal	.LC2@GOTOFF(%ebx), %eax
	pushl	%eax
	pushl	%esi
	call	strcmp@PLT
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L2
	subl	$12, %esp
	leal	.LC3@GOTOFF(%ebx), %eax
	jmp	.L6
.L2:
	subl	$12, %esp
	leal	.LC4@GOTOFF(%ebx), %eax
.L6:
	pushl	%eax
	call	puts@PLT
	addl	$16, %esp
	movl	-28(%ebp), %eax
	subl	%gs:20, %eax
	je	.L4
	call	__stack_chk_fail_local
.L4:
	leal	-12(%ebp), %esp
	xorl	%eax, %eax
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
	movl	(%esp), %ebx
	ret
	.hidden	__stack_chk_fail_local
	.ident	"GCC: (GNU) 13.2.1 20230801"
	.section	.note.GNU-stack,"",@progbits
