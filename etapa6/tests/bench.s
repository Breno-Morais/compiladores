	.text
	.section	.data
.LC0:
	.string "Finished\n"
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

	.globl	__temp6
	.align 4
	.type	__temp6, @object
	.size	__temp6, 4
__temp6:
	.long	0

	.globl	i
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.long	0
	.globl	max
	.align 4
	.type	max, @object
	.size	max, 4
max:
	.long	2147483645
	.globl	result
	.align 4
	.type	result, @object
	.size	result, 4
result:
	.long	0
	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	10

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

# TAC LABEL
__label1:

# TAC LESS
	movl	max(%rip), %eax
	cmpl	i(%rip), %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, __temp0(%rip)

# TAC IFZ
	movl	__temp0(%rip), %eax
	testl	%eax, %eax
	jz	__label2

# TAC ADD
	movl	x(%rip), %eax
	movl	$0, %edx
	addl	%edx, %eax
	movl	%eax, x(%rip)

# TAC MUL
	movl	x(%rip), %eax
	imull	$1, %eax, %eax
	movl	%eax, x(%rip)

# TAC MUL
	movl	x(%rip), %eax
	imull	$8, %eax, %eax
	movl	%eax, x(%rip)

# TAC DIV
	movl	x(%rip), %eax
	movl	$2, %ecx
	cltd
	idivl	%ecx
	movl	%eax, x(%rip)

# TAC GREATER
	movl	$1000, %eax
	cmpl	x(%rip), %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, __temp5(%rip)

# TAC IFZ
	movl	__temp5(%rip), %eax
	testl	%eax, %eax
	jz	__label0

# TAC MOVE
	movl	$10, x(%rip)

# TAC LABEL
__label0:

# TAC ADD
	movl	i(%rip), %eax
	movl	$1, %edx
	addl	%edx, %eax
	movl	%eax, i(%rip)

# TAC JUMP
	jmp	__label1

# TAC LABEL
__label2:

# TAC PRINT
	leaq	.LC0(%rip), %rax
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
