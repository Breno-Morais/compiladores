	.file	"a.c"
	.text
	.globl	v
	.data
	.align 8
	.type	v, @object
	.size	v, 12
v:
	.long	97
	.long	0
	.long	99
	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	1
	.text
	.globl	main
	.type	main, @function
main:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	v(%rip), %eax
	movl	%eax, 4+v(%rip)
	movl	12+v(%rip), %eax
	movl	%eax, x(%rip)
	movl	$0, %eax
	popq	%rbp
	ret
	.size	main, .-main
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
