.LC0:
	.string " | a = "
.LC1:
	.string " | b2 = "
.LC2:
	.string " | res = "
.LC3:
	.string " | y = "
.LC4:
	.string "A) a1 = "
.LC5:
	.string "B) b1 = "
.LC6:
	.string "\n"
.LC7:
	.string "expected x = 2 | y = 6\n"
.LC8:
	.string "main) x = "
	.globl	__temp7
	.align 4
	.type	__temp7, @object
	.size	__temp7, 4
__temp7:
	.long	0

	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	5
	.globl	y
	.align 4
	.type	y, @object
	.size	y, 4
y:
	.long	2
	.text
	.section	.data

	.section	.rodata
._print_s:
	.string	"%s"
._print_d:
	.string	"%d"
._print_c:
	.string	"%c"
._print_f:
	.string	"%f"

.true:
	.string	"true"
.false:
	.string	"false"

	.text

# TAC BEGINFUN
	.text
	.globl	A
	.type	A, @function
A:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	$1, -8(%rbp)

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	-4(%rbp), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	-8(%rbp), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC ADD
	movl	-8(%rbp), %eax
	movl	-4(%rbp), %edx
	addl	%edx, %eax

# TAC RET

# TAC ENDFUN
	movq	%rbp, %rsp
	popq	%rbp
	ret
	.size	A, .-A

# TAC BEGINFUN
	.text
	.globl	B
	.type	B, @function
B:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	$0, -12(%rbp)

# TAC ARG
	movl	-4(%rbp), %edi

# TAC CALL
	call	A
	movl	%eax, __temp7(%rip)

# TAC ADD
	movl	-4(%rbp), %edx
	addl	%edx, %eax

# TAC ADD
	movl	-8(%rbp), %edx
	addl	%edx, %eax
	movl	%eax, -12(%rbp)

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	-4(%rbp), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	-8(%rbp), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	-12(%rbp), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC RET
	movl	-12(%rbp), %eax

# TAC ENDFUN
	movq	%rbp, %rsp
	popq	%rbp
	ret
	.size	B, .-B

# TAC BEGINFUN
	.text
	.globl	main
	.type	main, @function
main:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp

# TAC ARG
	movl	$1, %edi

# TAC CALL
	call	A
	movl	%eax, x(%rip)

# TAC ARG
	movl	x(%rip), %edi

# TAC ARG
	movl	$1, %esi

# TAC CALL
	call	B
	movl	%eax, y(%rip)

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	x(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	y(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC ENDFUN
	movq	%rbp, %rsp
	popq	%rbp
	ret
	.size	main, .-main

# FILE SECURITY DETAIL
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
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
