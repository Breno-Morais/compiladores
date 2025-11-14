	.text
	.section	.data
.LC0:
	.string "\n"
.LC1:
	.string "greater 1 > 1 is "
.LC2:
	.string "greater 1 > 2 is "
.LC3:
	.string "greater 2 > 1 is "
.LC4:
	.string "greater or equal 1 >= 1 is "
.LC5:
	.string "greater or equal 1 >= 2 is "
.LC6:
	.string "greater or equal 2 >= 1 is "
.LC7:
	.string "less 1 < 1 is "
.LC8:
	.string "less 1 < 2 is "
.LC9:
	.string "less 2 < 1 is "
.LC10:
	.string "less or equal 1 <= 1 is "
.LC11:
	.string "less or equal 1 <= 2 is "
.LC12:
	.string "less or equal 2 <= 1 is "
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

	.globl	__temp12
	.align 4
	.type	__temp12, @object
	.size	__temp12, 4
__temp12:
	.long	0

	.globl	__temp13
	.align 4
	.type	__temp13, @object
	.size	__temp13, 4
__temp13:
	.long	0

	.globl	__temp14
	.align 4
	.type	__temp14, @object
	.size	__temp14, 4
__temp14:
	.long	0

	.globl	__temp15
	.align 4
	.type	__temp15, @object
	.size	__temp15, 4
__temp15:
	.long	0

	.globl	__temp16
	.align 4
	.type	__temp16, @object
	.size	__temp16, 4
__temp16:
	.long	0

	.globl	__temp17
	.align 4
	.type	__temp17, @object
	.size	__temp17, 4
__temp17:
	.long	0

	.globl	__temp18
	.align 4
	.type	__temp18, @object
	.size	__temp18, 4
__temp18:
	.long	0

	.globl	__temp19
	.align 4
	.type	__temp19, @object
	.size	__temp19, 4
__temp19:
	.long	0

	.globl	__temp2
	.align 4
	.type	__temp2, @object
	.size	__temp2, 4
__temp2:
	.long	0

	.globl	__temp20
	.align 4
	.type	__temp20, @object
	.size	__temp20, 4
__temp20:
	.long	0

	.globl	__temp21
	.align 4
	.type	__temp21, @object
	.size	__temp21, 4
__temp21:
	.long	0

	.globl	__temp22
	.align 4
	.type	__temp22, @object
	.size	__temp22, 4
__temp22:
	.long	0

	.globl	__temp23
	.align 4
	.type	__temp23, @object
	.size	__temp23, 4
__temp23:
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
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$1, %eax
	cmpl	$2, %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, __temp12(%rip)
	movzbl	__temp12(%rip), %eax
	testb	%al, %al
	je	.L13
	leaq	.true(%rip), %rax
	jmp	.L14
.L13:
	leaq	.false(%rip), %rax
.L14:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$1, %eax
	cmpl	$1, %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, __temp13(%rip)
	movzbl	__temp13(%rip), %eax
	testb	%al, %al
	je	.L15
	leaq	.true(%rip), %rax
	jmp	.L16
.L15:
	leaq	.false(%rip), %rax
.L16:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$2, %eax
	cmpl	$1, %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, __temp14(%rip)
	movzbl	__temp14(%rip), %eax
	testb	%al, %al
	je	.L17
	leaq	.true(%rip), %rax
	jmp	.L18
.L17:
	leaq	.false(%rip), %rax
.L18:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$1, %eax
	cmpl	$2, %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, __temp15(%rip)
	movzbl	__temp15(%rip), %eax
	testb	%al, %al
	je	.L19
	leaq	.true(%rip), %rax
	jmp	.L20
.L19:
	leaq	.false(%rip), %rax
.L20:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$1, %eax
	cmpl	$1, %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, __temp16(%rip)
	movzbl	__temp16(%rip), %eax
	testb	%al, %al
	je	.L21
	leaq	.true(%rip), %rax
	jmp	.L22
.L21:
	leaq	.false(%rip), %rax
.L22:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$2, %eax
	cmpl	$1, %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, __temp17(%rip)
	movzbl	__temp17(%rip), %eax
	testb	%al, %al
	je	.L23
	leaq	.true(%rip), %rax
	jmp	.L24
.L23:
	leaq	.false(%rip), %rax
.L24:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$1, %eax
	cmpl	$2, %eax
	setle	%al
	movzbl	%al, %eax
	movl	%eax, __temp18(%rip)
	movzbl	__temp18(%rip), %eax
	testb	%al, %al
	je	.L25
	leaq	.true(%rip), %rax
	jmp	.L26
.L25:
	leaq	.false(%rip), %rax
.L26:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$1, %eax
	cmpl	$1, %eax
	setle	%al
	movzbl	%al, %eax
	movl	%eax, __temp19(%rip)
	movzbl	__temp19(%rip), %eax
	testb	%al, %al
	je	.L27
	leaq	.true(%rip), %rax
	jmp	.L28
.L27:
	leaq	.false(%rip), %rax
.L28:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$2, %eax
	cmpl	$1, %eax
	setle	%al
	movzbl	%al, %eax
	movl	%eax, __temp20(%rip)
	movzbl	__temp20(%rip), %eax
	testb	%al, %al
	je	.L29
	leaq	.true(%rip), %rax
	jmp	.L30
.L29:
	leaq	.false(%rip), %rax
.L30:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$1, %eax
	cmpl	$2, %eax
	setge	%al
	movzbl	%al, %eax
	movl	%eax, __temp21(%rip)
	movzbl	__temp21(%rip), %eax
	testb	%al, %al
	je	.L31
	leaq	.true(%rip), %rax
	jmp	.L32
.L31:
	leaq	.false(%rip), %rax
.L32:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$1, %eax
	cmpl	$1, %eax
	setge	%al
	movzbl	%al, %eax
	movl	%eax, __temp22(%rip)
	movzbl	__temp22(%rip), %eax
	testb	%al, %al
	je	.L33
	leaq	.true(%rip), %rax
	jmp	.L34
.L33:
	leaq	.false(%rip), %rax
.L34:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$2, %eax
	cmpl	$1, %eax
	setge	%al
	movzbl	%al, %eax
	movl	%eax, __temp23(%rip)
	movzbl	__temp23(%rip), %eax
	testb	%al, %al
	je	.L35
	leaq	.true(%rip), %rax
	jmp	.L36
.L35:
	leaq	.false(%rip), %rax
.L36:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
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
