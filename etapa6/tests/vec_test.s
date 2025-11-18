.LC0:
	.string " "
.LC1:
	.string "Overwrite v with just 5s\n"
.LC2:
	.string "\n"
.LC3:
	.string "v: "
.LC4:
	.string "x: "
.LC5:
	.string "z: "
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

	.globl	__temp9
	.align 4
	.type	__temp9, @object
	.size	__temp9, 4
__temp9:
	.long	0

	.globl	a
	.align 4
	.type	a, @object
	.size	a, 12
a:
	.long	97
	.long	2
	.long	99
	.globl	v
	.align 4
	.type	v, @object
	.size	v, 12
v:
	.long	1
	.long	2
	.long	3
	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	1
	.globl	z
	.align 4
	.type	z, @object
	.size	z, 12
z:
	.zero 3
	.text
	.section	.data

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
	.globl	printV
	.type	printV, @function
printV:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC VECACCESS
	movl	v(%rip), %eax
	movl	%eax, __temp9(%rip)

# TAC PRINT
	movl	__temp9(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC VECACCESS
	movl	4+v(%rip), %eax
	movl	%eax, __temp10(%rip)

# TAC PRINT
	movl	__temp10(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC VECACCESS
	movl	8+v(%rip), %eax
	movl	%eax, __temp11(%rip)

# TAC PRINT
	movl	__temp11(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC RET
	movl	$1, %eax

# TAC ENDFUN
	movq	%rbp, %rsp
	popq	%rbp
	ret
	.size	printV, .-printV

# TAC BEGINFUN
	.text
	.globl	main
	.type	main, @function
main:
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC VECACCESS
	movl	z(%rip), %eax
	movl	%eax, __temp12(%rip)

# TAC PRINT
	movl	__temp12(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC VECACCESS
	movl	4+z(%rip), %eax
	movl	%eax, __temp13(%rip)

# TAC PRINT
	movl	__temp13(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC VECACCESS
	movl	8+z(%rip), %eax
	movl	%eax, __temp14(%rip)

# TAC PRINT
	movl	__temp14(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC CALL
	call	printV
	movl	%eax, x(%rip)

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC MOVEVEC
	movl	$5, v(%rip)

# TAC MOVEVEC
	movl	$5, 4+v(%rip)

# TAC MOVEVEC
	movl	$5, 8+v(%rip)

# TAC CALL
	call	printV
	movl	%eax, x(%rip)

# TAC VECACCESS
	movl	v(%rip), %eax
	movl	%eax, x(%rip)

# TAC PRINT
	leaq	(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	movl	x(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	(%rip), %rax
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
