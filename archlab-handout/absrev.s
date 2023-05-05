	.file	"absrev.c"
	.text
	.globl	absrev
	.type	absrev, @function
absrev:
.LFB23:
	.cfi_startproc
	endbr64
	leaq	-8(%rsi,%rdx,8), %rcx
	movl	$0, %r8d
.L2:
	testq	%rdx, %rdx
	jle	.L4
	movq	(%rdi), %rax
	movq	%rax, (%rcx)
	movq	%rax, %rsi
	sarq	$63, %rsi
	xorq	%rsi, %rax
	subq	%rsi, %rax
	addq	%rax, %r8
	subq	$1, %rdx
	leaq	-8(%rcx), %rcx
	leaq	8(%rdi), %rdi
	jmp	.L2
.L4:
	movq	%r8, %rax
	ret
	.cfi_endproc
.LFE23:
	.size	absrev, .-absrev
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"sum=%ld\n"
.LC1:
	.string	"%ld "
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$0, %eax
	jmp	.L6
.L11:
	movl	$1, %edx
.L7:
	imulq	%rcx, %rdx
	leaq	src(%rip), %rsi
	movq	%rdx, (%rsi,%rax,8)
	movq	%rcx, %rax
.L6:
	cmpq	$7, %rax
	jg	.L13
	leaq	1(%rax), %rcx
	testb	$1, %al
	je	.L11
	movq	$-1, %rdx
	jmp	.L7
.L13:
	movl	$8, %edx
	leaq	dst(%rip), %rsi
	leaq	src(%rip), %rdi
	call	absrev
	movq	%rax, %rdx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$0, %ebx
	jmp	.L9
.L10:
	leaq	dst(%rip), %rax
	movq	(%rax,%rbx,8), %rdx
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	addq	$1, %rbx
.L9:
	cmpq	$7, %rbx
	jle	.L10
	movq	stdout(%rip), %rsi
	movl	$10, %edi
	call	putc@PLT
	movl	$0, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.comm	dst,64,32
	.comm	src,64,32
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
