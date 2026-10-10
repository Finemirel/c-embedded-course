	.file	"const_volatile_practice.c"
	.text
	.p2align 4
	.type	on_sigint, @function
on_sigint:
.LFB53:
	.cfi_startproc
	endbr64
	movl	$1, magnet_detected(%rip)
	ret
	.cfi_endproc
.LFE53:
	.size	on_sigint, .-on_sigint
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Usage: %s <part 1-6>\n"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"First argument not a number: %s\n"
	.section	.rodata.str1.1
.LC2:
	.string	"Part %ld\n"
.LC3:
	.string	"%d\n"
.LC4:
	.string	"*p2 = 17: %d\n"
.LC5:
	.string	"p2 = &b: %d\n"
.LC6:
	.string	"*p3 = 17: %d\n"
.LC7:
	.string	"p3 = &b: %d\n"
.LC8:
	.string	"p4 = &b: %d\n"
.LC9:
	.string	"*p4 = 17: %d\n"
.LC10:
	.string	"p5 = &b: %d\n"
.LC11:
	.string	"*p5 = 10: %d\n"
.LC12:
	.string	"Before break_const: %d\n"
.LC13:
	.string	"After break_const: %d\n"
	.section	.rodata.str1.8
	.align 8
.LC14:
	.string	"Print from pointer before : %d\n"
	.align 8
.LC15:
	.string	"Print from pointer after : %d\n"
	.align 8
.LC16:
	.string	"global_forbidden before break_const: %d\n"
	.align 8
.LC17:
	.string	"global_forbidden print from pointer before : %d\n"
	.align 8
.LC18:
	.string	"global_forbidden after break_const: %d\n"
	.align 8
.LC19:
	.string	"global_forbidden print from pointer after : %d\n"
	.section	.rodata.str1.1
.LC20:
	.string	"Const int SIZE = %d\n"
.LC21:
	.string	"sizeof(a2) = %zu\n"
	.section	.rodata.str1.8
	.align 8
.LC23:
	.string	"delay_plain: %.6f s (result = %ld)\n"
	.align 8
.LC24:
	.string	"delay_volatile: %.6f s (result = %ld)\n"
	.align 8
.LC25:
	.string	"\320\226\320\264\321\203 \320\274\320\260\320\263\320\275\320\270\321\202 (Ctrl+C)..."
	.align 8
.LC26:
	.string	"\320\234\320\260\320\263\320\275\320\270\321\202 \320\276\320\261\320\275\320\260\321\200\321\203\320\266\320\265\320\275!"
	.section	.rodata.str1.1
.LC27:
	.string	"Unknown part: %ld\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB54:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rsi, %rbx
	subq	$40, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpl	$2, %edi
	je	.L4
	movq	(%rsi), %rcx
	movq	stderr(%rip), %rdi
	leaq	.LC0(%rip), %rdx
	movl	$2, %esi
	call	__fprintf_chk@PLT
.L5:
	movl	$1, %eax
.L3:
	movq	24(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L23
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L4:
	.cfi_restore_state
	movq	8(%rbx), %rdi
	movl	$10, %edx
	leaq	8(%rsp), %rsi
	call	strtol@PLT
	movq	8(%rsp), %rdx
	cmpb	$0, (%rdx)
	jne	.L24
	leaq	-1(%rax), %rcx
	cmpq	$5, %rcx
	ja	.L7
	leaq	.L9(%rip), %rdx
	movslq	(%rdx,%rcx,4), %rax
	addq	%rdx, %rax
	notrack jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L9:
	.long	.L14-.L9
	.long	.L13-.L9
	.long	.L12-.L9
	.long	.L11-.L9
	.long	.L10-.L9
	.long	.L8-.L9
	.section	.text.startup
.L24:
	movq	8(%rbx), %rcx
	movq	stderr(%rip), %rdi
	leaq	.LC1(%rip), %rdx
	xorl	%eax, %eax
	movl	$2, %esi
	call	__fprintf_chk@PLT
	jmp	.L5
.L10:
	movl	$5, %edx
	leaq	.LC2(%rip), %rsi
	movl	$2, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	leaq	on_sigint(%rip), %rsi
	movl	$2, %edi
	call	signal@PLT
	leaq	.LC25(%rip), %rdi
	call	puts@PLT
	cmpl	$0, magnet_detected(%rip)
	jne	.L19
.L20:
	jmp	.L20
.L14:
	movl	$1, %edx
	leaq	.LC2(%rip), %rsi
	movl	$2, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	leaq	.LC3(%rip), %rbx
	movl	$12, %edx
	xorl	%eax, %eax
	movq	%rbx, %rsi
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$20, %edx
	movq	%rbx, %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$12, %edx
	leaq	.LC4(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$20, %edx
	leaq	.LC5(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$12, %edx
	leaq	.LC6(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$20, %edx
	leaq	.LC7(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$12, %edx
	leaq	.LC8(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$17, %edx
	leaq	.LC9(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$17, %edx
	leaq	.LC10(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$17, %edx
	leaq	.LC11(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	xorl	%eax, %eax
	jmp	.L3
.L8:
	movl	$6, %edx
	leaq	.LC2(%rip), %rsi
	movl	$2, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	xorl	%eax, %eax
	jmp	.L3
.L12:
	movl	$3, %edx
	leaq	.LC2(%rip), %rsi
	movl	$2, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movl	$8, %edx
	leaq	.LC20(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$20, %edx
	leaq	.LC21(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	xorl	%eax, %eax
	jmp	.L3
.L13:
	movl	$2, %edx
	leaq	.LC2(%rip), %rsi
	movl	$2, %edi
	xorl	%eax, %eax
	leaq	.LC12(%rip), %rbp
	leaq	.LC13(%rip), %rbx
	call	__printf_chk@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$999, %edx
	movq	%rbx, %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$5, %edx
	movq	%rbp, %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$5, %edx
	leaq	.LC14(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$5, %edx
	movq	%rbx, %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$5, %edx
	leaq	.LC15(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$7, %edx
	leaq	.LC16(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$7, %edx
	leaq	.LC17(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$7, %edx
	leaq	.LC18(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	movl	$7, %edx
	leaq	.LC19(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	call	__printf_chk@PLT
	xorl	%eax, %eax
	jmp	.L3
.L11:
	movl	$4, %edx
	leaq	.LC2(%rip), %rsi
	movl	$2, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	call	clock@PLT
	movq	%rax, %rbx
	call	clock@PLT
	pxor	%xmm0, %xmm0
	movl	$500000000, %edx
	leaq	.LC23(%rip), %rsi
	subq	%rbx, %rax
	movl	$2, %edi
	cvtsi2sdq	%rax, %xmm0
	movl	$1, %eax
	divsd	.LC22(%rip), %xmm0
	call	__printf_chk@PLT
	call	clock@PLT
	movq	%rax, %rbx
	xorl	%eax, %eax
	movq	%rax, 16(%rsp)
	jmp	.L17
.L18:
	movq	16(%rsp), %rax
	addq	$1, %rax
	movq	%rax, 16(%rsp)
.L17:
	movq	16(%rsp), %rax
	cmpq	$499999999, %rax
	jle	.L18
	movq	16(%rsp), %rbp
	call	clock@PLT
	pxor	%xmm0, %xmm0
	movl	$2, %edi
	leaq	.LC24(%rip), %rsi
	subq	%rbx, %rax
	movq	%rbp, %rdx
	cvtsi2sdq	%rax, %xmm0
	movl	$1, %eax
	divsd	.LC22(%rip), %xmm0
	call	__printf_chk@PLT
	xorl	%eax, %eax
	jmp	.L3
.L19:
	leaq	.LC26(%rip), %rdi
	call	puts@PLT
	xorl	%eax, %eax
	jmp	.L3
.L7:
	movq	stderr(%rip), %rdi
	movq	%rax, %rcx
	movl	$2, %esi
	xorl	%eax, %eax
	leaq	.LC27(%rip), %rdx
	call	__fprintf_chk@PLT
	xorl	%eax, %eax
	jmp	.L3
.L23:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE54:
	.size	main, .-main
	.text
	.p2align 4
	.globl	break_const
	.type	break_const, @function
break_const:
.LFB55:
	.cfi_startproc
	endbr64
	movl	$999, (%rdi)
	ret
	.cfi_endproc
.LFE55:
	.size	break_const, .-break_const
	.p2align 4
	.globl	delay_plain
	.type	delay_plain, @function
delay_plain:
.LFB56:
	.cfi_startproc
	endbr64
	xorl	%eax, %eax
	testq	%rdi, %rdi
	cmovns	%rdi, %rax
	ret
	.cfi_endproc
.LFE56:
	.size	delay_plain, .-delay_plain
	.p2align 4
	.globl	delay_volatile
	.type	delay_volatile, @function
delay_volatile:
.LFB57:
	.cfi_startproc
	endbr64
	movq	$0, -8(%rsp)
	movq	-8(%rsp), %rax
	cmpq	%rax, %rdi
	jle	.L28
	.p2align 4,,10
	.p2align 3
.L29:
	movq	-8(%rsp), %rax
	addq	$1, %rax
	movq	%rax, -8(%rsp)
	movq	-8(%rsp), %rax
	cmpq	%rdi, %rax
	jl	.L29
.L28:
	movq	-8(%rsp), %rax
	ret
	.cfi_endproc
.LFE57:
	.size	delay_volatile, .-delay_volatile
	.local	magnet_detected
	.comm	magnet_detected,4,4
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC22:
	.long	0
	.long	1093567616
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
