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
	.globl	main
	.type	main, @function
main:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$5, %eax
	movl	$1, %edx
	addl	%edx, %eax
	movl	%eax, y(%rip)
	movl	y(%rip), %esi
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
