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
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
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
	movl	%eax, __temp11(%rip)
	movzbl	__temp11(%rip), %eax
	testb	%al, %al
	je	.L14
	leaq	.true(%rip), %rax
	jmp	.L15
.L14:
	leaq	.false(%rip), %rax
.L15:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
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
	movl	%eax, __temp12(%rip)
	movzbl	__temp12(%rip), %eax
	testb	%al, %al
	je	.L18
	leaq	.true(%rip), %rax
	jmp	.L19
.L18:
	leaq	.false(%rip), %rax
.L19:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
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
	movl	%eax, __temp13(%rip)
	movzbl	__temp13(%rip), %eax
	testb	%al, %al
	je	.L22
	leaq	.true(%rip), %rax
	jmp	.L23
.L22:
	leaq	.false(%rip), %rax
.L23:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
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
	movl	%eax, __temp14(%rip)
	movzbl	__temp14(%rip), %eax
	testb	%al, %al
	je	.L27
	leaq	.true(%rip), %rax
	jmp	.L28
.L27:
	leaq	.false(%rip), %rax
.L28:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
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
	movl	%eax, __temp15(%rip)
	movzbl	__temp15(%rip), %eax
	testb	%al, %al
	je	.L32
	leaq	.true(%rip), %rax
	jmp	.L33
.L32:
	leaq	.false(%rip), %rax
.L33:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
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
	movl	%eax, __temp16(%rip)
	movzbl	__temp16(%rip), %eax
	testb	%al, %al
	je	.L37
	leaq	.true(%rip), %rax
	jmp	.L38
.L37:
	leaq	.false(%rip), %rax
.L38:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	y(%rip), %eax
	cmpl	x(%rip), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp17(%rip)
	movzbl	__temp17(%rip), %eax
	testb	%al, %al
	je	.L39
	leaq	.true(%rip), %rax
	jmp	.L40
.L39:
	leaq	.false(%rip), %rax
.L40:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	x(%rip), %eax
	cmpl	x(%rip), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp18(%rip)
	movzbl	__temp18(%rip), %eax
	testb	%al, %al
	je	.L41
	leaq	.true(%rip), %rax
	jmp	.L42
.L41:
	leaq	.false(%rip), %rax
.L42:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	y(%rip), %eax
	cmpl	y(%rip), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp19(%rip)
	movzbl	__temp19(%rip), %eax
	testb	%al, %al
	je	.L43
	leaq	.true(%rip), %rax
	jmp	.L44
.L43:
	leaq	.false(%rip), %rax
.L44:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	t(%rip), %eax
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp20(%rip)
	movzbl	__temp20(%rip), %eax
	testb	%al, %al
	je	.L45
	leaq	.true(%rip), %rax
	jmp	.L46
.L45:
	leaq	.false(%rip), %rax
.L46:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	f(%rip), %eax
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, __temp21(%rip)
	movzbl	__temp21(%rip), %eax
	testb	%al, %al
	je	.L47
	leaq	.true(%rip), %rax
	jmp	.L48
.L47:
	leaq	.false(%rip), %rax
.L48:
	movq	%rax, %rdi
	call	printf@PLT
	leaq	.LC3(%rip), %rax
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
