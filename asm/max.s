.section .data

nums:
.long 3,3,2,10,5,69,100,34,0 # 0 terminates 

.section .text
.globl _start

_start:
movl $0, %edi							# index register
movl nums(,%edi,4), %eax			# load first byte
movl %eax, %ebx						# %ebx is the location
											# for the max num
											# %edi is the index

start_loop:
cmpl $0, %eax							# check the end
je loop_exit 
incl %edi								# next value
movl nums(,%edi,4), %eax			
cmpl %ebx, %eax 
jle start_loop
movl %eax, %ebx 
jmp start_loop

loop_exit:
movl $1, %eax 
int $0x80
