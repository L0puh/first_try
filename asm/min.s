# return minimum value with edge cases
# program is meant for practice 

.section .data
nums:
.long 255,3,4,10,23,245,22,10,45,10,45,59
nums_end:

.section .text
.globl _start
_start:
movl $nums,%esi		# pointer to start of nums
movl (%esi), %eax		# current min 
movl %eax, %ebx
addl $4, %esi			# second element 

_start_loop:

cmpl $nums_end, %esi
jge _end_loop

movl (%esi),%eax			# current number 

cmpl $0,%eax
jle _skip

cmpl $255,%eax
jg _skip

cmpl %eax,%ebx
jle _skip

movl %eax, %ebx


_skip:
addl $4, %esi
jmp _start_loop

_end_loop:

#ebx has the min
movl $1, %eax 
int $0x80
