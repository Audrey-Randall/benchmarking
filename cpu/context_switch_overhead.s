	.file	"context_switch_overhead.c"
	.text
	.comm	cycles_low,4,4
	.comm	cycles_high,4,4
	.comm	cycles_low1,4,4
	.comm	cycles_high1,4,4
	.type	rdtsc, @function
rdtsc:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
#APP
# 19 "context_switch_overhead.c" 1
	RDTSC
	mov %edx, %edi
	mov %eax, %esi
	
# 0 "" 2
#NO_APP
	movl	%edi, cycles_high(%rip)
	movl	%esi, cycles_low(%rip)
	nop
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	rdtsc, .-rdtsc
	.type	rdtsc1, @function
rdtsc1:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
#APP
# 27 "context_switch_overhead.c" 1
	RDTSC
	mov %edx, %edi
	mov %eax, %esi
	
# 0 "" 2
#NO_APP
	movl	%edi, cycles_high1(%rip)
	movl	%esi, cycles_low1(%rip)
	nop
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	rdtsc1, .-rdtsc1
	.section	.rodata
.LC0:
	.string	"Parent PID: %d\n"
.LC1:
	.string	"Parent CPU ID: %d\n"
	.align 8
.LC2:
	.string	"Setting process priority failed!"
	.align 8
.LC3:
	.string	"\nAvg. context switch time: %lf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$100, -204(%rbp)
	call	getpid@PLT
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	call	sched_getcpu@PLT
	movl	%eax, -200(%rbp)
	movl	-200(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-144(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %eax
	movl	$16, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	movl	-200(%rbp), %eax
	cltq
	movq	%rax, -176(%rbp)
	cmpq	$1023, -176(%rbp)
	ja	.L5
	movq	-176(%rbp), %rax
	shrq	$6, %rax
	leaq	0(,%rax,8), %rdx
	leaq	-144(%rbp), %rcx
	addq	%rcx, %rdx
	movq	(%rdx), %rdx
	movq	-176(%rbp), %rcx
	andl	$63, %ecx
	movl	$1, %esi
	salq	%cl, %rsi
	movq	%rsi, %rcx
	leaq	0(,%rax,8), %rsi
	leaq	-144(%rbp), %rax
	addq	%rsi, %rax
	orq	%rcx, %rdx
	movq	%rdx, (%rax)
.L5:
	call	getpid@PLT
	movl	%eax, %ecx
	leaq	-144(%rbp), %rax
	movq	%rax, %rdx
	movl	$128, %esi
	movl	%ecx, %edi
	call	sched_setaffinity@PLT
	call	getpid@PLT
	movl	$-20, %edx
	movl	%eax, %esi
	movl	$0, %edi
	call	setpriority@PLT
	testl	%eax, %eax
	je	.L6
	leaq	.LC2(%rip), %rdi
	call	perror@PLT
	movl	$-1, %edi
	call	exit@PLT
.L6:
	movq	$0, -184(%rbp)
	movl	$0, -208(%rbp)
	jmp	.L7
.L9:
	leaq	-152(%rbp), %rax
	movq	%rax, %rdi
	call	pipe@PLT
	call	rdtsc
	call	fork@PLT
	movl	%eax, -196(%rbp)
	cmpl	$0, -196(%rbp)
	jne	.L8
	call	rdtsc1
	movl	cycles_high(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -168(%rbp)
	movl	cycles_high1(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low1(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -160(%rbp)
	movq	-160(%rbp), %rax
	subq	-168(%rbp), %rax
	movq	%rax, -192(%rbp)
	movl	-152(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-148(%rbp), %eax
	leaq	-192(%rbp), %rcx
	movl	$8, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	movl	-148(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$0, %edi
	call	exit@PLT
.L8:
	movl	-148(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-152(%rbp), %eax
	leaq	-192(%rbp), %rcx
	movl	$8, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	movl	-152(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movq	-192(%rbp), %rax
	addq	%rax, -184(%rbp)
	movl	$0, %edi
	call	wait@PLT
	addl	$1, -208(%rbp)
.L7:
	movl	-208(%rbp), %eax
	cmpl	-204(%rbp), %eax
	jl	.L9
	movq	-184(%rbp), %rax
	testq	%rax, %rax
	js	.L10
	cvtsi2sdq	%rax, %xmm0
	jmp	.L11
.L10:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L11:
	cvtsi2sd	-204(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	leaq	.LC3(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L13
	call	__stack_chk_fail@PLT
.L13:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
