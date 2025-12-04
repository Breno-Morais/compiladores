	.text
	.section	.data
.LC0:
	.string "0 == 0 is "
.LC1:
	.string "1 == 0 is "
.LC2:
	.string "1 == 1 is "
.LC3:
	.string "\n"
.LC4:
	.string "false & false is "
.LC5:
	.string "false | false is "
.LC6:
	.string "true & false is "
.LC7:
	.string "true & true is "
.LC8:
	.string "true | false is "
.LC9:
	.string "true | true is "
.LC10:
	.string "~false is "
.LC11:
	.string "~true is "
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

	.globl	f
	.align 4
	.type	f, @object
	.size	f, 1
f:
	.byte	0
	.globl	t
	.align 4
	.type	t, @object
	.size	t, 1
t:
	.byte	1
	.globl	x
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
	.long	0
	.globl	z
	.align 4
	.type	z, @object
	.size	z, 1
z:
	.byte	1

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
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC AND
	movl	t(%rip), %eax
	testl	%eax, %eax
	je	.L12
	movl	f(%rip), %eax
	testl	%eax, %eax
	je	.L12
	movl	$1, %eax
	jmp	.L13
.L12:
	movl	$0, %eax
.L13:
	movl	%eax, __temp0(%rip)

# TAC PRINT
	movzbl	__temp0(%rip), %eax
	testb	%al, %al
	je	.L14
	leaq	.true(%rip), %rax
	jmp	.L15
.L14:
	leaq	.false(%rip), %rax
.L15:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC AND
	movl	t(%rip), %eax
	testl	%eax, %eax
	je	.L16
	movl	t(%rip), %eax
	testl	%eax, %eax
	je	.L16
	movl	$1, %eax
	jmp	.L17
.L16:
	movl	$0, %eax
.L17:
	movl	%eax, __temp1(%rip)

# TAC PRINT
	movzbl	__temp1(%rip), %eax
	testb	%al, %al
	je	.L18
	leaq	.true(%rip), %rax
	jmp	.L19
.L18:
	leaq	.false(%rip), %rax
.L19:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC AND
	movl	f(%rip), %eax
	testl	%eax, %eax
	je	.L20
	movl	f(%rip), %eax
	testl	%eax, %eax
	je	.L20
	movl	$1, %eax
	jmp	.L21
.L20:
	movl	$0, %eax
.L21:
	movl	%eax, __temp2(%rip)

# TAC PRINT
	movzbl	__temp2(%rip), %eax
	testb	%al, %al
	je	.L22
	leaq	.true(%rip), %rax
	jmp	.L23
.L22:
	leaq	.false(%rip), %rax
.L23:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC OR
	movl	t(%rip), %eax
	testl	%eax, %eax
	jne	.L24
	movl	f(%rip), %eax
	testl	%eax, %eax
	je	.L25
.L24:
	movl	$1, %eax
	jmp	.L26
.L25:
	movl	$0, %eax
.L26:
	movl	%eax, __temp3(%rip)

# TAC PRINT
	movzbl	__temp3(%rip), %eax
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
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC OR
	movl	t(%rip), %eax
	testl	%eax, %eax
	jne	.L29
	movl	t(%rip), %eax
	testl	%eax, %eax
	je	.L30
.L29:
	movl	$1, %eax
	jmp	.L31
.L30:
	movl	$0, %eax
.L31:
	movl	%eax, __temp4(%rip)

# TAC PRINT
	movzbl	__temp4(%rip), %eax
	testb	%al, %al
	je	.L32
	leaq	.true(%rip), %rax
	jmp	.L33
.L32:
	leaq	.false(%rip), %rax
.L33:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC OR
	movl	f(%rip), %eax
	testl	%eax, %eax
	jne	.L34
	movl	f(%rip), %eax
	testl	%eax, %eax
	je	.L35
.L34:
	movl	$1, %eax
	jmp	.L36
.L35:
	movl	$0, %eax
.L36:
	movl	%eax, __temp5(%rip)

# TAC PRINT
	movzbl	__temp5(%rip), %eax
	testb	%al, %al
	je	.L37
	leaq	.true(%rip), %rax
	jmp	.L38
.L37:
	leaq	.false(%rip), %rax
.L38:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC EQUAL
	movl	y(%rip), %eax
	cmpl	x(%rip), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp6(%rip)

# TAC PRINT
	movzbl	__temp6(%rip), %eax
	testb	%al, %al
	je	.L39
	leaq	.true(%rip), %rax
	jmp	.L40
.L39:
	leaq	.false(%rip), %rax
.L40:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC EQUAL
	movl	x(%rip), %eax
	cmpl	x(%rip), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp7(%rip)

# TAC PRINT
	movzbl	__temp7(%rip), %eax
	testb	%al, %al
	je	.L41
	leaq	.true(%rip), %rax
	jmp	.L42
.L41:
	leaq	.false(%rip), %rax
.L42:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC EQUAL
	movl	y(%rip), %eax
	cmpl	y(%rip), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp8(%rip)

# TAC PRINT
	movzbl	__temp8(%rip), %eax
	testb	%al, %al
	je	.L43
	leaq	.true(%rip), %rax
	jmp	.L44
.L43:
	leaq	.false(%rip), %rax
.L44:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC NOT
	movl	t(%rip), %eax
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp9(%rip)

# TAC PRINT
	movzbl	__temp9(%rip), %eax
	testb	%al, %al
	je	.L45
	leaq	.true(%rip), %rax
	jmp	.L46
.L45:
	leaq	.false(%rip), %rax
.L46:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC NOT
	movl	f(%rip), %eax
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp10(%rip)

# TAC PRINT
	movzbl	__temp10(%rip), %eax
	testb	%al, %al
	je	.L47
	leaq	.true(%rip), %rax
	jmp	.L48
.L47:
	leaq	.false(%rip), %rax
.L48:
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC3(%rip), %rax
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
