	.file	"a.c"
	.text
	.globl	x
	.data
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
	.globl	A
	.type	A, @function
A:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$13, -4(%rbp)
	movl	-4(%rbp), %eax
	addl	$65, %eax
	popq	%rbp
	ret
	.size	A, .-A
	.globl	B
	.type	B, @function
B:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$24, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, %eax
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	movb	%al, -8(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	A
	movsbl	-8(%rbp), %edx
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	leave
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
	movl	x(%rip), %eax
	movl	$4, %r9d
	movl	$2, %r8d
	movl	$1, %ecx
	movl	$4, %edx
	movl	$5, %esi
	movl	%eax, %edi
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
