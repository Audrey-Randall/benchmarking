	.file	"function_call_overhead_rdtsc.c"
	.text
	.globl	stdev
	.type	stdev, @function
stdev:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movl	%esi, -60(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -32(%rbp)
	movl	$0, -40(%rbp)
	jmp	.L2
.L3:
	movl	-40(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	movsd	-32(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -32(%rbp)
	addl	$1, -40(%rbp)
.L2:
	movl	-40(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jl	.L3
	cvtsi2sd	-60(%rbp), %xmm0
	movsd	-32(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -32(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -24(%rbp)
	movl	$0, -36(%rbp)
	jmp	.L4
.L5:
	movl	-36(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movsd	(%rax), %xmm0
	subsd	-32(%rbp), %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	mulsd	-8(%rbp), %xmm0
	movsd	-24(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -24(%rbp)
	addl	$1, -36(%rbp)
.L4:
	movl	-36(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jl	.L5
	cvtsi2sd	-60(%rbp), %xmm0
	movsd	-24(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	call	sqrt@PLT
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	stdev, .-stdev
	.comm	cycles_low,4,4
	.comm	cycles_high,4,4
	.comm	cycles_low1,4,4
	.comm	cycles_high1,4,4
	.type	rdtsc, @function
rdtsc:
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
# 36 "function_call_overhead_rdtsc.c" 1
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
.LFE6:
	.size	rdtsc, .-rdtsc
	.type	rdtsc1, @function
rdtsc1:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
#APP
# 44 "function_call_overhead_rdtsc.c" 1
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
.LFE7:
	.size	rdtsc1, .-rdtsc1
	.globl	test_procedure_0
	.type	test_procedure_0, @function
test_procedure_0:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	test_procedure_0, .-test_procedure_0
	.globl	test_procedure_1
	.type	test_procedure_1, @function
test_procedure_1:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	test_procedure_1, .-test_procedure_1
	.globl	test_procedure_2
	.type	test_procedure_2, @function
test_procedure_2:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	test_procedure_2, .-test_procedure_2
	.globl	test_procedure_3
	.type	test_procedure_3, @function
test_procedure_3:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	test_procedure_3, .-test_procedure_3
	.globl	test_procedure_4
	.type	test_procedure_4, @function
test_procedure_4:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	test_procedure_4, .-test_procedure_4
	.globl	test_procedure_5
	.type	test_procedure_5, @function
test_procedure_5:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	test_procedure_5, .-test_procedure_5
	.globl	test_procedure_6
	.type	test_procedure_6, @function
test_procedure_6:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	test_procedure_6, .-test_procedure_6
	.globl	test_procedure_7
	.type	test_procedure_7, @function
test_procedure_7:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	test_procedure_7, .-test_procedure_7
	.section	.rodata
	.align 8
.LC1:
	.string	"Setting process priority failed!"
.LC2:
	.string	"a+"
.LC3:
	.string	"0_args.txt"
.LC4:
	.string	"%lf, %lf\n"
.LC5:
	.string	"1_args.txt"
.LC6:
	.string	"2_args.txt"
.LC7:
	.string	"3_args.txt"
.LC8:
	.string	"4_args.txt"
.LC9:
	.string	"5_args.txt"
.LC10:
	.string	"6_args.txt"
.LC11:
	.string	"7_args.txt"
	.text
	.globl	main
	.type	main, @function
main:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$248, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	$100, -272(%rbp)
	call	sched_getcpu@PLT
	movl	%eax, -268(%rbp)
	leaq	-192(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %eax
	movl	$16, %edx
	movq	%rsi, %rdi
	movq	%rdx, %rcx
	rep stosq
	movl	-268(%rbp), %eax
	cltq
	movq	%rax, -256(%rbp)
	cmpq	$1023, -256(%rbp)
	ja	.L19
	movq	-256(%rbp), %rax
	shrq	$6, %rax
	leaq	0(,%rax,8), %rdx
	leaq	-192(%rbp), %rcx
	addq	%rcx, %rdx
	movq	(%rdx), %rdx
	movq	-256(%rbp), %rcx
	andl	$63, %ecx
	movl	$1, %esi
	salq	%cl, %rsi
	movq	%rsi, %rcx
	leaq	0(,%rax,8), %rsi
	leaq	-192(%rbp), %rax
	addq	%rsi, %rax
	orq	%rcx, %rdx
	movq	%rdx, (%rax)
.L19:
	call	getpid@PLT
	movl	%eax, %ecx
	leaq	-192(%rbp), %rax
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
	je	.L20
	leaq	.LC1(%rip), %rdi
	call	perror@PLT
	movl	$-1, %edi
	call	exit@PLT
.L20:
	leaq	.LC2(%rip), %rsi
	leaq	.LC3(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -248(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -240(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -264(%rbp)
	movl	-272(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -232(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %r14
	movl	$0, %r15d
	movslq	%eax, %rdx
	movq	%rdx, %r12
	movl	$0, %r13d
	cltq
	salq	$3, %rax
	leaq	7(%rax), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %ecx
	movl	$0, %edx
	divq	%rcx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$7, %rax
	shrq	$3, %rax
	salq	$3, %rax
	movq	%rax, -224(%rbp)
	movl	$0, -276(%rbp)
	jmp	.L21
.L26:
	call	rdtsc
	movl	$0, %eax
	call	test_procedure_0
	call	rdtsc1
	movl	cycles_high(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -216(%rbp)
	movl	cycles_high1(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low1(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	subq	-216(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L22
	cvtsi2sdq	%rax, %xmm0
	jmp	.L23
.L22:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L23:
	movsd	-264(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -264(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L24
	cvtsi2sdq	%rax, %xmm0
	jmp	.L25
.L24:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L25:
	movq	-224(%rbp), %rax
	movl	-276(%rbp), %edx
	movslq	%edx, %rdx
	movsd	%xmm0, (%rax,%rdx,8)
	addl	$1, -276(%rbp)
.L21:
	movl	-276(%rbp), %eax
	cmpl	-272(%rbp), %eax
	jl	.L26
	movq	-224(%rbp), %rax
	movl	-272(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	stdev
	movapd	%xmm0, %xmm2
	cvtsi2sd	-272(%rbp), %xmm0
	movsd	-264(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movq	-248(%rbp), %rax
	movapd	%xmm2, %xmm1
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
	leaq	.LC2(%rip), %rsi
	leaq	.LC5(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -248(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -264(%rbp)
	movl	$0, -276(%rbp)
	jmp	.L27
.L32:
	call	rdtsc
	movl	$1, %edi
	call	test_procedure_1
	call	rdtsc1
	movl	cycles_high(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -216(%rbp)
	movl	cycles_high1(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low1(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	subq	-216(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L28
	cvtsi2sdq	%rax, %xmm0
	jmp	.L29
.L28:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L29:
	movsd	-264(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -264(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L30
	cvtsi2sdq	%rax, %xmm0
	jmp	.L31
.L30:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L31:
	movq	-224(%rbp), %rax
	movl	-276(%rbp), %edx
	movslq	%edx, %rdx
	movsd	%xmm0, (%rax,%rdx,8)
	addl	$1, -276(%rbp)
.L27:
	movl	-276(%rbp), %eax
	cmpl	-272(%rbp), %eax
	jl	.L32
	movq	-224(%rbp), %rax
	movl	-272(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	stdev
	movapd	%xmm0, %xmm2
	cvtsi2sd	-272(%rbp), %xmm0
	movsd	-264(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movq	-248(%rbp), %rax
	movapd	%xmm2, %xmm1
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
	leaq	.LC2(%rip), %rsi
	leaq	.LC6(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -248(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -264(%rbp)
	movl	$0, -276(%rbp)
	jmp	.L33
.L38:
	call	rdtsc
	movl	$2, %esi
	movl	$1, %edi
	call	test_procedure_2
	call	rdtsc1
	movl	cycles_high(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -216(%rbp)
	movl	cycles_high1(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low1(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	subq	-216(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L34
	cvtsi2sdq	%rax, %xmm0
	jmp	.L35
.L34:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L35:
	movsd	-264(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -264(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L36
	cvtsi2sdq	%rax, %xmm0
	jmp	.L37
.L36:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L37:
	movq	-224(%rbp), %rax
	movl	-276(%rbp), %edx
	movslq	%edx, %rdx
	movsd	%xmm0, (%rax,%rdx,8)
	addl	$1, -276(%rbp)
.L33:
	movl	-276(%rbp), %eax
	cmpl	-272(%rbp), %eax
	jl	.L38
	movq	-224(%rbp), %rax
	movl	-272(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	stdev
	movapd	%xmm0, %xmm2
	cvtsi2sd	-272(%rbp), %xmm0
	movsd	-264(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movq	-248(%rbp), %rax
	movapd	%xmm2, %xmm1
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
	leaq	.LC2(%rip), %rsi
	leaq	.LC7(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -248(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -264(%rbp)
	movl	$0, -276(%rbp)
	jmp	.L39
.L44:
	call	rdtsc
	movl	$3, %edx
	movl	$2, %esi
	movl	$1, %edi
	call	test_procedure_3
	call	rdtsc1
	movl	cycles_high(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -216(%rbp)
	movl	cycles_high1(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low1(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	subq	-216(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L40
	cvtsi2sdq	%rax, %xmm0
	jmp	.L41
.L40:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L41:
	movsd	-264(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -264(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L42
	cvtsi2sdq	%rax, %xmm0
	jmp	.L43
.L42:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L43:
	movq	-224(%rbp), %rax
	movl	-276(%rbp), %edx
	movslq	%edx, %rdx
	movsd	%xmm0, (%rax,%rdx,8)
	addl	$1, -276(%rbp)
.L39:
	movl	-276(%rbp), %eax
	cmpl	-272(%rbp), %eax
	jl	.L44
	movq	-224(%rbp), %rax
	movl	-272(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	stdev
	movapd	%xmm0, %xmm2
	cvtsi2sd	-272(%rbp), %xmm0
	movsd	-264(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movq	-248(%rbp), %rax
	movapd	%xmm2, %xmm1
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
	leaq	.LC2(%rip), %rsi
	leaq	.LC8(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -248(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -264(%rbp)
	movl	$0, -276(%rbp)
	jmp	.L45
.L50:
	call	rdtsc
	movl	$6, %ecx
	movl	$5, %edx
	movl	$2, %esi
	movl	$1, %edi
	call	test_procedure_4
	call	rdtsc1
	movl	cycles_high(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -216(%rbp)
	movl	cycles_high1(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low1(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	subq	-216(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L46
	cvtsi2sdq	%rax, %xmm0
	jmp	.L47
.L46:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L47:
	movsd	-264(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -264(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L48
	cvtsi2sdq	%rax, %xmm0
	jmp	.L49
.L48:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L49:
	movq	-224(%rbp), %rax
	movl	-276(%rbp), %edx
	movslq	%edx, %rdx
	movsd	%xmm0, (%rax,%rdx,8)
	addl	$1, -276(%rbp)
.L45:
	movl	-276(%rbp), %eax
	cmpl	-272(%rbp), %eax
	jl	.L50
	movq	-224(%rbp), %rax
	movl	-272(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	stdev
	movapd	%xmm0, %xmm2
	cvtsi2sd	-272(%rbp), %xmm0
	movsd	-264(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movq	-248(%rbp), %rax
	movapd	%xmm2, %xmm1
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
	leaq	.LC2(%rip), %rsi
	leaq	.LC9(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -248(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -264(%rbp)
	movl	$0, -276(%rbp)
	jmp	.L51
.L56:
	call	rdtsc
	movl	$10, %r8d
	movl	$6, %ecx
	movl	$5, %edx
	movl	$2, %esi
	movl	$1, %edi
	call	test_procedure_5
	call	rdtsc1
	movl	cycles_high(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -216(%rbp)
	movl	cycles_high1(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low1(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	subq	-216(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L52
	cvtsi2sdq	%rax, %xmm0
	jmp	.L53
.L52:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L53:
	movsd	-264(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -264(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L54
	cvtsi2sdq	%rax, %xmm0
	jmp	.L55
.L54:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L55:
	movq	-224(%rbp), %rax
	movl	-276(%rbp), %edx
	movslq	%edx, %rdx
	movsd	%xmm0, (%rax,%rdx,8)
	addl	$1, -276(%rbp)
.L51:
	movl	-276(%rbp), %eax
	cmpl	-272(%rbp), %eax
	jl	.L56
	movq	-224(%rbp), %rax
	movl	-272(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	stdev
	movapd	%xmm0, %xmm2
	cvtsi2sd	-272(%rbp), %xmm0
	movsd	-264(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movq	-248(%rbp), %rax
	movapd	%xmm2, %xmm1
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
	leaq	.LC2(%rip), %rsi
	leaq	.LC10(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -248(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -264(%rbp)
	movl	$0, -276(%rbp)
	jmp	.L57
.L62:
	call	rdtsc
	movl	$100, %r9d
	movl	$4, %r8d
	movl	$6, %ecx
	movl	$5, %edx
	movl	$2, %esi
	movl	$1, %edi
	call	test_procedure_6
	call	rdtsc1
	movl	cycles_high(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -216(%rbp)
	movl	cycles_high1(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low1(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	subq	-216(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L58
	cvtsi2sdq	%rax, %xmm0
	jmp	.L59
.L58:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L59:
	movsd	-264(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -264(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L60
	cvtsi2sdq	%rax, %xmm0
	jmp	.L61
.L60:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L61:
	movq	-224(%rbp), %rax
	movl	-276(%rbp), %edx
	movslq	%edx, %rdx
	movsd	%xmm0, (%rax,%rdx,8)
	addl	$1, -276(%rbp)
.L57:
	movl	-276(%rbp), %eax
	cmpl	-272(%rbp), %eax
	jl	.L62
	movq	-224(%rbp), %rax
	movl	-272(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	stdev
	movapd	%xmm0, %xmm2
	cvtsi2sd	-272(%rbp), %xmm0
	movsd	-264(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movq	-248(%rbp), %rax
	movapd	%xmm2, %xmm1
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
	leaq	.LC2(%rip), %rsi
	leaq	.LC11(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -248(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -264(%rbp)
	movl	$0, -276(%rbp)
	jmp	.L63
.L68:
	call	rdtsc
	subq	$8, %rsp
	pushq	$200
	movl	$100, %r9d
	movl	$4, %r8d
	movl	$6, %ecx
	movl	$5, %edx
	movl	$2, %esi
	movl	$1, %edi
	call	test_procedure_7
	addq	$16, %rsp
	call	rdtsc1
	movl	cycles_high(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -216(%rbp)
	movl	cycles_high1(%rip), %eax
	movl	%eax, %eax
	salq	$32, %rax
	movl	cycles_low1(%rip), %edx
	movl	%edx, %edx
	orq	%rdx, %rax
	movq	%rax, -208(%rbp)
	movq	-208(%rbp), %rax
	subq	-216(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L64
	cvtsi2sdq	%rax, %xmm0
	jmp	.L65
.L64:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L65:
	movsd	-264(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -264(%rbp)
	movq	-200(%rbp), %rax
	testq	%rax, %rax
	js	.L66
	cvtsi2sdq	%rax, %xmm0
	jmp	.L67
.L66:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm0
	addsd	%xmm0, %xmm0
.L67:
	movq	-224(%rbp), %rax
	movl	-276(%rbp), %edx
	movslq	%edx, %rdx
	movsd	%xmm0, (%rax,%rdx,8)
	addl	$1, -276(%rbp)
.L63:
	movl	-276(%rbp), %eax
	cmpl	-272(%rbp), %eax
	jl	.L68
	movq	-224(%rbp), %rax
	movl	-272(%rbp), %edx
	movl	%edx, %esi
	movq	%rax, %rdi
	call	stdev
	movapd	%xmm0, %xmm2
	cvtsi2sd	-272(%rbp), %xmm0
	movsd	-264(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movq	-248(%rbp), %rax
	movapd	%xmm2, %xmm1
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	movl	$2, %eax
	call	fprintf@PLT
	call	sched_getcpu@PLT
	movl	%eax, -268(%rbp)
	movl	$0, %eax
	movq	%rbx, %rsp
	movq	-56(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L70
	call	__stack_chk_fail@PLT
.L70:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	main, .-main
	.globl	time_diff_in_ns_v1
	.type	time_diff_in_ns_v1, @function
time_diff_in_ns_v1:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, %rax
	movq	%rsi, %r9
	movq	%rax, %rsi
	movq	%rdx, %rdi
	movq	%r9, %rdi
	movq	%rsi, -32(%rbp)
	movq	%rdi, -24(%rbp)
	movq	%rdx, -48(%rbp)
	movq	%rcx, -40(%rbp)
	movq	%r8, -56(%rbp)
	movq	-48(%rbp), %rdx
	movq	-32(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-40(%rbp), %rdx
	movq	-24(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rax
	cmpq	%rax, %rdx
	jle	.L72
	subq	$1, -16(%rbp)
	addq	$1000000000, -8(%rbp)
.L72:
	movq	-56(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-56(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	time_diff_in_ns_v1, .-time_diff_in_ns_v1
	.ident	"GCC: (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
