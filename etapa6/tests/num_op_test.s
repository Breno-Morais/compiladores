	.text
	.section	.data
.LC0:
	.string "5 % 2 is "
.LC1:
	.string "5 * 2 is "
.LC2:
	.string "5 + 2 is "
.LC3:
	.string "5 - 2 is "
.LC4:
	.string "5 / 2 is "
.LC5:
	.string "\n"
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
	.globl	main
	.type	main, @function
main:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp

# TAC PRINT
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC ADD
	movl	x(%rip), %eax
	movl	y(%rip), %edx
	addl	%edx, %eax
	movl	%eax, __temp0(%rip)

# TAC PRINT
	movl	__temp0(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC SUB
	movl	x(%rip), %eax
	movl	y(%rip), %edx
	subl	%edx, %eax
	movl	%eax, __temp1(%rip)

# TAC PRINT
	movl	__temp1(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC MUL
	movl	x(%rip), %eax
	movl	y(%rip), %edx
	imull	%edx, %eax
	movl	%eax, __temp2(%rip)

# TAC PRINT
	movl	__temp2(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC DIV
	movl	x(%rip), %eax
	movl	y(%rip), %ecx
	cltd
	idivl	%ecx
	movl	%eax, __temp3(%rip)

# TAC PRINT
	movl	__temp3(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC MOD
	movl	x(%rip), %eax
	movl	y(%rip), %esi
	cltd
	idivl	%esi
	movl	%edx, %ecx
	movl	%ecx, %eax
	movl	%eax, __temp4(%rip)

# TAC PRINT
	movl	__temp4(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC5(%rip), %rax
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
