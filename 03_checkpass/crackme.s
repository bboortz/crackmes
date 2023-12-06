	.file	"crackme.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%s"
	.text
	.p2align 4
	.globl	substr
	.type	substr, @function
substr:
.LFB3:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$8, %esp
	.cfi_def_cfa_offset 16
	pushl	20(%esp)
	.cfi_def_cfa_offset 20
	leal	.LC0@GOTOFF(%ebx), %eax
	pushl	%eax
	.cfi_def_cfa_offset 24
	pushl	32(%esp)
	.cfi_def_cfa_offset 28
	pushl	28(%esp)
	.cfi_def_cfa_offset 32
	call	snprintf@PLT
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	cmpl	$3, %eax
	ja	.L6
.L1:
	addl	$8, %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	.cfi_restore_state
	movl	$-1, %eax
	jmp	.L1
	.cfi_endproc
.LFE3:
	.size	substr, .-substr
	.section	.rodata.str1.1
.LC1:
	.string	"Access granted!"
	.text
	.p2align 4
	.globl	ok
	.type	ok, @function
ok:
.LFB4:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$20, %esp
	.cfi_def_cfa_offset 28
	leal	.LC1@GOTOFF(%ebx), %eax
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	puts@PLT
	addl	$24, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE4:
	.size	ok, .-ok
	.section	.rodata.str1.1
.LC2:
	.string	"Access denied!"
	.text
	.p2align 4
	.globl	not_ok
	.type	not_ok, @function
not_ok:
.LFB5:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$20, %esp
	.cfi_def_cfa_offset 28
	leal	.LC2@GOTOFF(%ebx), %eax
	pushl	%eax
	.cfi_def_cfa_offset 32
	call	puts@PLT
	addl	$24, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE5:
	.size	not_ok, .-not_ok
	.p2align 4
	.globl	check_password
	.type	check_password, @function
check_password:
.LFB6:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	subl	$76, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%gs:20, %ecx
	movl	%ecx, -28(%ebp)
	xorl	%ecx, %ecx
	movl	$1701868915, -43(%ebp)
	testl	%eax, %eax
	leal	3(%eax), %esi
	movb	$0, -39(%ebp)
	cmovns	%eax, %esi
	movl	$1664308082, -38(%ebp)
	leal	.LC0@GOTOFF(%ebx), %edi
	movb	$0, -34(%ebp)
	sarl	$2, %esi
	movl	$561263474, -33(%ebp)
	leal	1(%esi), %eax
	movb	$0, -29(%ebp)
	movl	%eax, -60(%ebp)
	leal	16(%esi), %eax
	shrl	$4, %eax
	movl	$663841, -47(%ebp)
	sall	$4, %eax
	subl	%eax, %esp
	movl	%esp, %ecx
	subl	%eax, %esp
	movl	%esp, -64(%ebp)
	subl	%eax, %esp
	movl	%esp, -68(%ebp)
	subl	%eax, %esp
	movl	%esp, -72(%ebp)
	pushl	%edx
	movl	%edx, -76(%ebp)
	pushl	%edi
	pushl	-60(%ebp)
	pushl	%ecx
	movl	%ecx, -80(%ebp)
	call	snprintf@PLT
	movl	-76(%ebp), %edx
	addl	%esi, %edx
	pushl	%edx
	movl	%edx, -76(%ebp)
	pushl	%edi
	pushl	-60(%ebp)
	pushl	-64(%ebp)
	call	snprintf@PLT
	movl	-76(%ebp), %edx
	addl	$32, %esp
	addl	%esi, %edx
	pushl	%edx
	movl	%edx, -76(%ebp)
	pushl	%edi
	pushl	-60(%ebp)
	pushl	-68(%ebp)
	call	snprintf@PLT
	movl	-76(%ebp), %edx
	addl	%esi, %edx
	pushl	%edx
	pushl	%edi
	xorl	%edi, %edi
	pushl	-60(%ebp)
	pushl	-72(%ebp)
	call	snprintf@PLT
	movl	-80(%ebp), %ecx
	addl	$28, %esp
	leal	-43(%ebp), %eax
	pushl	%esi
	pushl	%eax
	pushl	%ecx
	call	strncmp@PLT
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L11
	subl	$4, %esp
	movl	%eax, %edi
	leal	-38(%ebp), %eax
	pushl	%esi
	pushl	%eax
	pushl	-64(%ebp)
	call	strncmp@PLT
	addl	$16, %esp
	testl	%eax, %eax
	je	.L17
.L11:
	movl	-28(%ebp), %eax
	subl	%gs:20, %eax
	jne	.L18
	leal	-12(%ebp), %esp
	movl	%edi, %eax
	popl	%ebx
	.cfi_remember_state
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.p2align 4,,10
	.p2align 3
.L17:
	.cfi_restore_state
	subl	$4, %esp
	leal	-33(%ebp), %eax
	pushl	%esi
	pushl	%eax
	pushl	-68(%ebp)
	call	strncmp@PLT
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L11
	subl	$4, %esp
	leal	-47(%ebp), %eax
	pushl	%esi
	pushl	%eax
	pushl	-72(%ebp)
	call	strncmp@PLT
	addl	$16, %esp
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, %edi
	jmp	.L11
.L18:
	call	__stack_chk_fail_local
	.cfi_endproc
.LFE6:
	.size	check_password, .-check_password
	.section	.rodata.str1.1
.LC3:
	.string	"\n *** enjoy the crackme ***\n"
.LC4:
	.string	"Enter the password: "
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	pushl	%esi
	pushl	%ebx
	.cfi_escape 0x10,0x6,0x2,0x75,0x7c
	.cfi_escape 0x10,0x3,0x2,0x75,0x78
	leal	-44(%ebp), %esi
	call	__x86.get_pc_thunk.bx
	addl	$_GLOBAL_OFFSET_TABLE_, %ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x74,0x6
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
	je	.L20
	subl	$12, %esp
	leal	.LC1@GOTOFF(%ebx), %eax
	pushl	%eax
	call	puts@PLT
	addl	$16, %esp
.L21:
	movl	-28(%ebp), %eax
	subl	%gs:20, %eax
	jne	.L24
	leal	-12(%ebp), %esp
	xorl	%eax, %eax
	popl	%ecx
	.cfi_remember_state
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
.L20:
	.cfi_restore_state
	subl	$12, %esp
	leal	.LC2@GOTOFF(%ebx), %eax
	pushl	%eax
	call	puts@PLT
	addl	$16, %esp
	jmp	.L21
.L24:
	call	__stack_chk_fail_local
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.bx,"axG",@progbits,__x86.get_pc_thunk.bx,comdat
	.globl	__x86.get_pc_thunk.bx
	.hidden	__x86.get_pc_thunk.bx
	.type	__x86.get_pc_thunk.bx, @function
__x86.get_pc_thunk.bx:
.LFB9:
	.cfi_startproc
	movl	(%esp), %ebx
	ret
	.cfi_endproc
.LFE9:
	.hidden	__stack_chk_fail_local
	.ident	"GCC: (GNU) 13.2.1 20230801"
	.section	.note.GNU-stack,"",@progbits
