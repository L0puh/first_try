.section .data
.section .text

.globl _start

_start:
	pushl $4

	call factorial 
	addl $4, %esp
	movl %eax, %ebx

_exit:
	movl $1, %eax
	int $0x80


.type factorial,@function 
factorial:
	pushl %ebp 
	movl %esp, %ebp
	movl 8(%esp), %eax 

	# base case:
	cmpl $1, %eax 
	je end_factorial

	# enter recursion
	decl %eax 
	pushl %eax 
	call factorial
	addl $4, %esp
	movl 8(%ebp), %ebx # get initial param 
	imull %ebx, %eax   

end_factorial:
	movl %ebp, %esp
	popl %ebp

	ret

