	.file	"a.c"
	.text
	.globl	x
	.data
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	1
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
	.long	1
	.text
	.globl	A
	.type	A, @function
A:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$65, %eax
	popq	%rbp
	ret
	.size	A, .-A
	.globl	B
	.type	B, @function
B:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$66, %eax
	popq	%rbp
	ret
	.size	B, .-B
	.globl	main
	.type	main, @function
main:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$0, %eax
	call	A
	movl	%eax, x(%rip)
	movl	$0, %eax
	call	B
	movl	%eax, y(%rip)
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
