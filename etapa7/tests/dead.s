	.text
	.section	.data
	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	0
	.globl	__temp0
	.align 4
	.type	__temp0, @object
	.size	__temp0, 4
__temp0:
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

# TAC EQUAL
	movl	$1, %eax
	cmpl	x(%rip), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp0(%rip)

# TAC IFZ
	movl	__temp0(%rip), %eax
	testl	%eax, %eax
	jz	__label0

# TAC RET
	movl	$5, %eax

# TAC LABEL
__label0:

# TAC MOVE
	movl	$2, x(%rip)

# TAC LABEL
__label1:

# TAC RET
	movl	x(%rip), %eax

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
