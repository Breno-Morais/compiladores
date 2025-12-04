	.text
	.section	.data
.LC0:
	.string " "
.LC1:
	.string "Overwrite v with just 5s\n"
.LC2:
	.string "\n"
.LC3:
	.string "v: "
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
	.long	0
	.globl	z
	.align 4
	.type	z, @object
	.size	z, 40000
z:
	.zero 40000

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
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC VECACCESS
	movl	v(%rip), %eax
	movl	%eax, __temp0(%rip)

# TAC PRINT
	movl	__temp0(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC VECACCESS
	movl	4+v(%rip), %eax
	movl	%eax, __temp1(%rip)

# TAC PRINT
	movl	__temp1(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC VECACCESS
	movl	8+v(%rip), %eax
	movl	%eax, __temp2(%rip)

# TAC PRINT
	movl	__temp2(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC PRINT
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC MOVEVEC
	movl	$5, v(%rip)

# TAC MOVEVEC
	movl	$5, 4+v(%rip)

# TAC MOVEVEC
	movl	$5, 8+v(%rip)

# TAC PRINT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC VECACCESS
	movl	v(%rip), %eax
	movl	%eax, __temp3(%rip)

# TAC PRINT
	movl	__temp3(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC VECACCESS
	movl	4+v(%rip), %eax
	movl	%eax, __temp4(%rip)

# TAC PRINT
	movl	__temp4(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT

# TAC VECACCESS
	movl	8+v(%rip), %eax
	movl	%eax, __temp5(%rip)

# TAC PRINT
	movl	__temp5(%rip), %esi
	leaq	._print_d(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT

# TAC PRINT
	leaq	.LC2(%rip), %rax
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
