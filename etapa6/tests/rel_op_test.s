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

# TAC PRINT
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC LESS
	movl	$1, %eax
	cmpl	$2, %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, __temp0(%rip)

# TAC PRINT
	movzbl	__temp0(%rip), %eax
	testb	%al, %al
	je	.L13
	leaq	.true(%rip), %rax
	jmp	.L14
.L13:
	leaq	.false(%rip), %rax
.L14:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC LESS
	movl	$1, %eax
	cmpl	$1, %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, __temp1(%rip)

# TAC PRINT
	movzbl	__temp1(%rip), %eax
	testb	%al, %al
	je	.L15
	leaq	.true(%rip), %rax
	jmp	.L16
.L15:
	leaq	.false(%rip), %rax
.L16:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC LESS
	movl	$2, %eax
	cmpl	$1, %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, __temp2(%rip)

# TAC PRINT
	movzbl	__temp2(%rip), %eax
	testb	%al, %al
	je	.L17
	leaq	.true(%rip), %rax
	jmp	.L18
.L17:
	leaq	.false(%rip), %rax
.L18:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC GREATER
	movl	$1, %eax
	cmpl	$2, %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, __temp3(%rip)

# TAC PRINT
	movzbl	__temp3(%rip), %eax
	testb	%al, %al
	je	.L19
	leaq	.true(%rip), %rax
	jmp	.L20
.L19:
	leaq	.false(%rip), %rax
.L20:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC GREATER
	movl	$1, %eax
	cmpl	$1, %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, __temp4(%rip)

# TAC PRINT
	movzbl	__temp4(%rip), %eax
	testb	%al, %al
	je	.L21
	leaq	.true(%rip), %rax
	jmp	.L22
.L21:
	leaq	.false(%rip), %rax
.L22:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC GREATER
	movl	$2, %eax
	cmpl	$1, %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, __temp5(%rip)

# TAC PRINT
	movzbl	__temp5(%rip), %eax
	testb	%al, %al
	je	.L23
	leaq	.true(%rip), %rax
	jmp	.L24
.L23:
	leaq	.false(%rip), %rax
.L24:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC GREATEREQUAL
	movl	$1, %eax
	cmpl	$2, %eax
	setle	%al
	movzbl	%al, %eax
	movl	%eax, __temp6(%rip)

# TAC PRINT
	movzbl	__temp6(%rip), %eax
	testb	%al, %al
	je	.L25
	leaq	.true(%rip), %rax
	jmp	.L26
.L25:
	leaq	.false(%rip), %rax
.L26:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC GREATEREQUAL
	movl	$1, %eax
	cmpl	$1, %eax
	setle	%al
	movzbl	%al, %eax
	movl	%eax, __temp7(%rip)

# TAC PRINT
	movzbl	__temp7(%rip), %eax
	testb	%al, %al
	je	.L27
	leaq	.true(%rip), %rax
	jmp	.L28
.L27:
	leaq	.false(%rip), %rax
.L28:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC GREATEREQUAL
	movl	$2, %eax
	cmpl	$1, %eax
	setle	%al
	movzbl	%al, %eax
	movl	%eax, __temp8(%rip)

# TAC PRINT
	movzbl	__temp8(%rip), %eax
	testb	%al, %al
	je	.L29
	leaq	.true(%rip), %rax
	jmp	.L30
.L29:
	leaq	.false(%rip), %rax
.L30:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC LESSEQUAL
	movl	$1, %eax
	cmpl	$2, %eax
	setge	%al
	movzbl	%al, %eax
	movl	%eax, __temp9(%rip)

# TAC PRINT
	movzbl	__temp9(%rip), %eax
	testb	%al, %al
	je	.L31
	leaq	.true(%rip), %rax
	jmp	.L32
.L31:
	leaq	.false(%rip), %rax
.L32:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC LESSEQUAL
	movl	$1, %eax
	cmpl	$1, %eax
	setge	%al
	movzbl	%al, %eax
	movl	%eax, __temp10(%rip)

# TAC PRINT
	movzbl	__temp10(%rip), %eax
	testb	%al, %al
	je	.L33
	leaq	.true(%rip), %rax
	jmp	.L34
.L33:
	leaq	.false(%rip), %rax
.L34:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC LESSEQUAL
	movl	$2, %eax
	cmpl	$1, %eax
	setge	%al
	movzbl	%al, %eax
	movl	%eax, __temp11(%rip)

# TAC PRINT
	movzbl	__temp11(%rip), %eax
	testb	%al, %al
	je	.L35
	leaq	.true(%rip), %rax
	jmp	.L36
.L35:
	leaq	.false(%rip), %rax
.L36:
	movq	%rax, %rdi
	call	printf@PLT

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
