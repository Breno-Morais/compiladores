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

	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	10

._print_s:
	.string	"%s\n"
._print_d:
	.string	"%d\n"
._print_c:
	.string	"%c\n"
._print_f:
	.string	"%f\n"

	.text
	.globl	main
	.type	main, @function
main:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$4, __temp2(%rip)
	movl	x(%rip), %eax
	movl	__temp2(%rip), %edx
	addl	%edx, %eax
	movl	%eax, __temp3(%rip)
	movl	__temp3(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
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
