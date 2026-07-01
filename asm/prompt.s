.section .data
prompt: .ascii "Enter text: "
prompt_len = . - prompt
newline: .ascii "\n"
prompt2: .ascii "echo: "
prompt2_len = . - prompt2

.section .bss
.equ BUF_SIZE, 100
.lcomm BUFFER, BUF_SIZE

.section .text
.globl _start

.equ STDIN,  0
.equ STDOUT, 1

.equ SYS_WRITE, 4
.equ SYS_READ,  3
.equ SYS_EXIT,	 1

.equ LNX_SYSCALL, 0x80

_start:
	movl $SYS_WRITE,  %eax
	movl $STDOUT,		%ebx
	movl $prompt,		%ecx
	movl $prompt_len, %edx
	int $LNX_SYSCALL

	# just enough space for one variable
	# (size of input text)
	pushl %ebp
	movl %esp, %ebp 
	subl $4,	  %esp

	movl $SYS_READ,   %eax
	movl $STDIN,		%ebx
	movl $BUFFER,		%ecx
	movl $BUF_SIZE,   %edx
	int  $LNX_SYSCALL
	
	movl %eax, -4(%ebp)
	
	movl $SYS_WRITE,  %eax
	movl $STDOUT,		%ebx
	movl $prompt2,		%ecx
	movl $prompt2_len,%edx 
	int $LNX_SYSCALL
	
	movl $SYS_WRITE,  %eax
	movl $STDOUT,		%ebx
	movl $BUFFER,		%ecx
	movl -4(%ebp),		%edx
	int $LNX_SYSCALL
	


_exit:
	movl $SYS_EXIT,   %eax
	movl $0,				%ebx
	int  $LNX_SYSCALL
