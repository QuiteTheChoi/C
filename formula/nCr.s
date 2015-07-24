	.file	"nCr.c"
	.text
.globl factorialn
	.type	factorialn, @function
factorialn:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	cmpl	$0, 8(%ebp)
	jne	.L2
	movl	12(%ebp), %eax
	jmp	.L3
.L2:
	movl	12(%ebp), %eax
	imull	8(%ebp), %eax
	cmpl	12(%ebp), %eax
	jge	.L4
	movl	$0, %eax
	jmp	.L3
.L4:
	movl	12(%ebp), %eax
	imull	8(%ebp), %eax
	movl	8(%ebp), %edx
	subl	$1, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	factorialn
.L3:
	leave
	ret
	.size	factorialn, .-factorialn
.globl factorial
	.type	factorial, @function
factorial:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$1, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	factorialn
	leave
	ret
	.size	factorial, .-factorial
.globl nCr
	.type	nCr, @function
nCr:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	factorial
	movl	%eax, -16(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	factorial
	movl	%eax, %ebx
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, (%esp)
	call	factorial
	imull	%ebx, %eax
	movl	%eax, -12(%ebp)
	cmpl	$0, -16(%ebp)
	je	.L9
	cmpl	$0, -12(%ebp)
	jne	.L10
.L9:
	movl	$0, %eax
	jmp	.L11
.L10:
	movl	-16(%ebp), %eax
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	-12(%ebp)
.L11:
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	nCr, .-nCr
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-11)"
	.section	.note.GNU-stack,"",@progbits
