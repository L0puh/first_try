.section .data

nums_start:
.long 3,3,2,10,5,69,100,34
nums_end:

.section .text
.globl _start

_start:
pushl $nums_start
pushl $nums_end

call max 

addl $4, %esp 
movl %eax, %ebx 

_exit:
movl $1, %eax 
int $0x80

#	--- pointer to the start of list  (12)
#  --- pointer to the end of list    (8)
#  --- return address
#  --- base address

.type max,@function
max:
    pushl %ebp
    movl %esp, %ebp
    movl 12(%ebp), %esi    # start 
    movl 8(%ebp),  %edi    # end  

    movl (%esi), %eax      
    addl $4, %esi          

start_loop:
    cmpl %edi, %esi        
    jge end_loop           

    movl (%esi), %ebx     
    cmpl %eax, %ebx        
    jle skip              

    movl %ebx, %eax        
skip:
    addl $4, %esi         
    jmp start_loop

end_loop:
    movl %ebp, %esp
    popl %ebp
    ret
