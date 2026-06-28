.section .data
.section .text 
.globl _start
_start:
movl $1, %eax # system call number to exit 
movl $0, %ebx # status number 
int $0x80	  # run by the kernel 
