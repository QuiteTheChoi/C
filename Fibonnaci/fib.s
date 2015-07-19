	.file	"fib.c"
	.comm	num,800,32
	.text
.globl add
	.type	add, @function
add:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	leal	(%edx,%eax), %eax
	popl	%ebp
	ret
	.size	add, .-add
.globl compute_fib
	.type	compute_fib, @function
compute_fib:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	8(%ebp), %eax
	movl	num(,%eax,4), %eax
	cmpl	$-1, %eax
	je	.L4
	movl	8(%ebp), %eax
	movl	num(,%eax,4), %eax
	movl	%eax, -12(%ebp)
	jmp	.L5
.L4:
	movl	$-1, -12(%ebp)
	cmpl	$0, 8(%ebp)
	jne	.L6
	movl	$0, -12(%ebp)
	jmp	.L5
.L6:
	cmpl	$1, 8(%ebp)
	jne	.L7
	movl	$1, -12(%ebp)
	jmp	.L5
.L7:
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, (%esp)
	call	compute_fib
	movl	%eax, %ebx
	movl	8(%ebp), %eax
	subl	$2, %eax
	movl	%eax, (%esp)
	call	compute_fib
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
	call	add
	movl	%eax, -12(%ebp)
.L5:
	movl	8(%ebp), %eax
	movl	num(,%eax,4), %eax
	cmpl	$-1, %eax
	jne	.L8
	movl	8(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%edx, num(,%eax,4)
.L8:
	movl	8(%ebp), %eax
	movl	num(,%eax,4), %eax
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	compute_fib, .-compute_fib
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	atoi
	movl	%eax, 24(%esp)
	movl	$0, 28(%esp)
	jmp	.L11
.L12:
	movl	28(%esp), %eax
	movl	$-1, num(,%eax,4)
	addl	$1, 28(%esp)
.L11:
	cmpl	$199, 28(%esp)
	jle	.L12
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	compute_fib
	movl	$.LC0, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	printf
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-11)"
	.section	.note.GNU-stack,"",@progbits
