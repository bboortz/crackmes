	.file	"crackme.c"
	.text
	.section	.rodata.ok.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Access granted!"
	.section	.text.ok,"ax",@progbits
	.globl	ok
	.type	ok, @function
ok:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$16, %esp
	leal	.LC0@GOTOFF(%ebx), %eax
	pushl	%eax
	call	puts@PLT
	movl	-4(%ebp), %ebx
	addl	$16, %esp
	leave
	ret
	.size	ok, .-ok
	.section	.rodata.not_ok.str1.1,"aMS",@progbits,1
.LC1:
	.string	"Access denied!"
	.section	.text.not_ok,"ax",@progbits
	.globl	not_ok
	.type	not_ok, @function
not_ok:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$16, %esp
	leal	.LC1@GOTOFF(%ebx), %eax
	pushl	%eax
	call	puts@PLT
	movl	-4(%ebp), %ebx
	addl	$16, %esp
	leave
	ret
	.size	not_ok, .-not_ok
	.section	.text.check_password,"ax",@progbits
	.globl	check_password
	.type	check_password, @function
check_password:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$56, %esp
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	leal	-28(%ebp), %eax
	pushl	12(%ebp)
	pushl	%eax
	pushl	8(%ebp)
	movaps	.LC2@GOTOFF(%ebx), %xmm0
	movaps	%xmm0, -56(%ebp)
	movups	%xmm0, -28(%ebp)
	call	strncmp@PLT
	addl	$16, %esp
	testl	%eax, %eax
	sete	%al
	movl	-12(%ebp), %edx
	subl	%gs:20, %edx
	je	.L6
	call	__stack_chk_fail_local
.L6:
	movl	-4(%ebp), %ebx
	movzbl	%al, %eax
	leave
	ret
	.size	check_password, .-check_password
	.section	.rodata.main.str1.1,"aMS",@progbits,1
.LC3:
	.string	"\n *** enjoy the crackme ***\n"
.LC4:
	.string	"Enter the password: "
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
	leal	.LC3@GOTOFF(%ebx), %eax
	pushl	%eax
	call	puts@PLT
	leal	.LC4@GOTOFF(%ebx), %eax
	movl	%eax, (%esp)
	call	printf@PLT
	movl	stdin@GOT(%ebx), %eax
	addl	$12, %esp
	pushl	(%eax)
	pushl	$20
	pushl	%esi
	call	fgets@PLT
	popl	%eax
	popl	%edx
	pushl	$20
	pushl	%esi
	call	check_password
	addl	$16, %esp
	testl	%eax, %eax
	je	.L10
	call	ok
	jmp	.L11
.L10:
	call	not_ok
.L11:
	movl	-28(%ebp), %eax
	subl	%gs:20, %eax
	je	.L12
	call	__stack_chk_fail_local
.L12:
	leal	-12(%ebp), %esp
	xorl	%eax, %eax
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC2:
	.long	1919103859
	.long	1632662579
	.long	813134707
	.long	681074
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
