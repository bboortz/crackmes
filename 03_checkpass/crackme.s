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
	.section	.rodata.check_password.str1.1,"aMS",@progbits,1
.LC2:
	.string	"1111"
	.section	.text.check_password,"ax",@progbits
	.globl	check_password
	.type	check_password, @function
check_password:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	$4, %esi
	pushl	%ebx
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$60, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	%gs:20, %edx
	movl	%edx, -28(%ebp)
	xorl	%edx, %edx
	movl	$1701868915, -43(%ebp)
	cltd
	movb	$0, -39(%ebp)
	idivl	%esi
	movl	$1664308082, -38(%ebp)
	movb	$0, -34(%ebp)
	movl	$1949524850, -33(%ebp)
	movb	$0, -29(%ebp)
	movl	$663841, -47(%ebp)
	movl	%eax, %esi
	addl	$16, %eax
	shrl	$4, %eax
	sall	$4, %eax
	subl	%eax, %esp
	movl	%esp, %edi
	subl	%eax, %esp
	movl	%esp, -60(%ebp)
	subl	%eax, %esp
	movl	%esp, -64(%ebp)
	subl	%eax, %esp
	movl	%esp, -68(%ebp)
	pushl	%eax
	pushl	%esi
	pushl	%ecx
	movl	%ecx, -72(%ebp)
	pushl	%edi
	call	strncpy@PLT
	movl	-72(%ebp), %ecx
	addl	$12, %esp
	movb	$0, 1(%edi,%esi)
	pushl	%esi
	addl	%esi, %ecx
	pushl	%ecx
	movl	%ecx, -72(%ebp)
	pushl	-60(%ebp)
	call	strncpy@PLT
	movl	-72(%ebp), %ecx
	movl	-60(%ebp), %eax
	addl	$12, %esp
	addl	%esi, %ecx
	movb	$0, 1(%eax,%esi)
	pushl	%esi
	pushl	%ecx
	movl	%ecx, -72(%ebp)
	pushl	-64(%ebp)
	call	strncpy@PLT
	movl	-72(%ebp), %ecx
	movl	-64(%ebp), %eax
	addl	$12, %esp
	addl	%esi, %ecx
	movb	$0, 1(%eax,%esi)
	pushl	%esi
	pushl	%ecx
	pushl	-68(%ebp)
	call	strncpy@PLT
	movl	-68(%ebp), %eax
	addl	$12, %esp
	movb	$0, 1(%eax,%esi)
	leal	-43(%ebp), %eax
	pushl	%esi
	pushl	%eax
	pushl	%edi
	call	strncmp@PLT
	addl	$16, %esp
	testl	%eax, %eax
	je	.L6
.L8:
	xorl	%eax, %eax
	jmp	.L5
.L6:
	subl	$12, %esp
	leal	.LC2@GOTOFF(%ebx), %edi
	pushl	%edi
	call	puts@PLT
	addl	$12, %esp
	leal	-38(%ebp), %eax
	pushl	%esi
	pushl	%eax
	pushl	-60(%ebp)
	call	strncmp@PLT
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L8
	subl	$12, %esp
	pushl	%edi
	call	puts@PLT
	addl	$12, %esp
	leal	-33(%ebp), %eax
	pushl	%esi
	pushl	%eax
	pushl	-64(%ebp)
	call	strncmp@PLT
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L8
	subl	$12, %esp
	pushl	%edi
	call	puts@PLT
	addl	$12, %esp
	leal	-47(%ebp), %eax
	pushl	%esi
	pushl	%eax
	pushl	-68(%ebp)
	call	strncmp@PLT
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L8
	subl	$12, %esp
	pushl	%edi
	call	puts@PLT
	addl	$16, %esp
	movl	$1, %eax
.L5:
	movl	-28(%ebp), %edx
	subl	%gs:20, %edx
	je	.L9
	call	__stack_chk_fail_local
.L9:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
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
	leal	-44(%ebp), %esi
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
	pushl	$16
	pushl	%esi
	call	fgets@PLT
	popl	%eax
	popl	%edx
	pushl	$16
	pushl	%esi
	call	check_password
	addl	$16, %esp
	testl	%eax, %eax
	je	.L13
	call	ok
	jmp	.L14
.L13:
	call	not_ok
.L14:
	movl	-28(%ebp), %eax
	subl	%gs:20, %eax
	je	.L15
	call	__stack_chk_fail_local
.L15:
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
