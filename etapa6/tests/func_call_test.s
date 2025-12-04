	.text
	.section	.data
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
	.string "Enter main)\n"
.LC7:
	.string "\n"
.LC8:
	.string "expected x = 2 | y = 6\n"
.LC9:
	.string "main) x = "
	.globl	__temp0
	.align 4
	.type	__temp0, @object
	.size	__temp0, 4
__temp0:
	.long	0

	.globl	__temp1
	.align 4
	.type	__temp1, @object
	.size	__temp1, 4
__temp1:
	.long	0

	.globl	__temp2
	.align 4
	.type	__temp2, @object
	.size	__temp2, 4
__temp2:
	.long	0

	.globl	__temp3
	.align 4
	.type	__temp3, @object
	.size	__temp3, 4
__temp3:
	.long	0

	.globl	__temp4
	.align 4
	.type	__temp4, @object
	.size	__temp4, 4
__temp4:
	.long	0

	.globl	__temp5
	.align 4
	.type	__temp5, @object
	.size	__temp5, 4
__temp5:
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
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	-4(%rbp), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	-8(%rbp), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC ADD
	movl	-8(%rbp), %eax
	movl	-4(%rbp), %edx
	addl	%edx, %eax
	movl	%eax, __temp0(%rip)

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
	movl	%eax, __temp1(%rip)

# TAC ADD
	movl	-4(%rbp), %edx
	addl	%edx, %eax
	movl	%eax, __temp2(%rip)

# TAC ADD
	movl	-8(%rbp), %edx
	addl	%edx, %eax
	movl	%eax, -12(%rbp)

# TAC PRINT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	-4(%rbp), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	-8(%rbp), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	-12(%rbp), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC7(%rip), %rax
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

# TAC PRINT
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

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
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	x(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	y(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC8(%rip), %rax
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
