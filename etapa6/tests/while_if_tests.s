	.text
	.section	.data
.LC0:
	.string "5 is equal to 2\n"
.LC1:
	.string "5 is not equal to 2\n"
.LC2:
	.string "Você digitou "
.LC3:
	.string "\n"
.LC4:
	.string "parabéns\n"
.LC5:
	.string "x is "
.LC6:
	.string "x is now "
.LC7:
	.string "x is still higher than 2 because it is "
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

# TAC EQUAL
	movl	y(%rip), %eax
	cmpl	x(%rip), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp0(%rip)

# TAC IFZ
	movl	__temp0(%rip), %eax
	testl	%eax, %eax
	jz	__label0

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC JUMP
	jmp	__label1

# TAC LABEL
__label0:

# TAC PRINT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC LABEL
__label1:

# TAC PRINT
	leaq	.LC5(%rip), %rax
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

# TAC LABEL
__label2:

# TAC GREATER
	movl	$2, %eax
	cmpl	x(%rip), %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, __temp1(%rip)

# TAC IFZ
	movl	__temp1(%rip), %eax
	testl	%eax, %eax
	jz	__label3

# TAC PRINT
	leaq	.LC7(%rip), %rax
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

# TAC SUB
	movl	x(%rip), %eax
	movl	$1, %edx
	subl	%edx, %eax
	movl	%eax, x(%rip)

# TAC JUMP
	jmp	__label2

# TAC LABEL
__label3:

# TAC PRINT
	leaq	.LC6(%rip), %rax
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

# TAC EQUAL
	movl	y(%rip), %eax
	cmpl	x(%rip), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp3(%rip)

# TAC IFZ
	movl	__temp3(%rip), %eax
	testl	%eax, %eax
	jz	__label4

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC JUMP
	jmp	__label5

# TAC LABEL
__label4:

# TAC PRINT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC LABEL
__label5:

# TAC READ
	leaq	x(%rip), %rax
	movq	%rax, %rsi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT

# TAC PRINT
	leaq	.LC2(%rip), %rax
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

# TAC EQUAL
	movl	$1, %eax
	cmpl	x(%rip), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp4(%rip)

# TAC IFZ
	movl	__temp4(%rip), %eax
	testl	%eax, %eax
	jz	__label6

# TAC PRINT
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC LABEL
__label6:

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
