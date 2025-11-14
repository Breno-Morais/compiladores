	.text
	.section	.data
.LC0:
	.string "A\n"
.LC1:
	.string "B\n"
.LC2:
	.string "main\n"
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
	.long	5
	.globl	y
	.align 4
	.type	y, @object
	.size	y, 4
y:
	.long	2

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
	.globl	A
	.type	A, @function
A:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$65, %eax
	popq	%rbp
	ret
	.size	A, .-A
	.text
	.globl	B
	.type	B, @function
B:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$66, %eax
	popq	%rbp
	ret
	.size	B, .-B
	.text
	.globl	main
	.type	main, @function
main:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	call	A
	movl	%eax, x(%rip)
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	call	B
	movl	%eax, y(%rip)
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
