	.text
	.section	.data
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

	.globl	__temp10
	.align 4
	.type	__temp10, @object
	.size	__temp10, 4
__temp10:
	.long	0

	.globl	__temp11
	.align 4
	.type	__temp11, @object
	.size	__temp11, 4
__temp11:
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

	.globl	__temp7
	.align 4
	.type	__temp7, @object
	.size	__temp7, 4
__temp7:
	.long	0

	.globl	__temp8
	.align 4
	.type	__temp8, @object
	.size	__temp8, 4
__temp8:
	.long	0

	.globl	__temp9
	.align 4
	.type	__temp9, @object
	.size	__temp9, 4
__temp9:
	.long	0

	.globl	a
	.align 4
	.type	a, @object
	.size	a, 20
a:
	.zero 20
	.globl	i
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.long	0
	.globl	n
	.align 4
	.type	n, @object
	.size	n, 4
n:
	.long	5
	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	0
	.globl	y
	.align 4
	.type	y, @object
	.size	y, 4
y:
	.long	1
	.globl	z
	.align 4
	.type	z, @object
	.size	z, 4
z:
	.long	0

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
__label2:

# TAC LESS
	movl	n(%rip), %eax
	cmpl	i(%rip), %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, __temp6(%rip)

# TAC IFZ
	movl	__temp6(%rip), %eax
	testl	%eax, %eax
	jz	__label3

# TAC ADD
	movl	y(%rip), %eax
	movl	z(%rip), %edx
	addl	%edx, %eax
	movl	%eax, x(%rip)

# TAC MUL
	movl	i(%rip), %eax
	imull	$6, %eax, %eax
	movl	%eax, __temp8(%rip)

# TAC MUL
	movl	x(%rip), %eax
	movl	x(%rip), %edx
	imull	%edx, %eax
	movl	%eax, __temp9(%rip)

# TAC ADD
	movl	__temp8(%rip), %eax
	movl	__temp9(%rip), %edx
	addl	%edx, %eax
	movl	%eax, __temp10(%rip)

# TAC MOVEVEC
	movl	i(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	__temp10(%rip), %rax
	movl	__temp10(%rip), %eax
	movl	%eax, a(%rip)

# TAC ADD
	movl	i(%rip), %eax
	movl	$1, %edx
	addl	%edx, %eax
	movl	%eax, i(%rip)

# TAC JUMP
	jmp	__label2

# TAC LABEL
__label3:

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
