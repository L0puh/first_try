.section .data
.section .text
.globl _start

_start: 

# params (2 is the base, 3 is the power)
pushl $3
pushl $2 

call power 

# move stack pointer back
addl $8, %esp
mov %eax, %ebx

_exit: 
movl $1, %eax 
int $0x80


.type power, @function 

# stack: 
# --- param 1
# --- param 2
# --- return address 
# --- base pointer (%ebp)
# --- [ local storage ] 

power:
	pushl %ebp 
	movl  %esp, %ebp
	subl  $4, %esp 
	
	movl  8(%ebp), %ebx 
	movl 12(%ebp), %ecx 

	movl %ebx,-4(%ebp)

# %ebx - base numer 
# %ecx - power
# %eax - current result 

power_loop:
	cmpl $1, %ecx
	je power_exit 
	movl -4(%ebp), %eax 
	imull %ebx, %eax
	movl %eax, -4(%ebp) 
	decl %ecx
	jmp power_loop


power_exit:
	movl -4(%ebp), %eax 
	movl %ebp, %esp 
	popl %ebp
	ret 
