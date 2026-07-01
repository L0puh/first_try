.section .data

#### system calls #### 
.equ SYS_OPEN,  5
.equ SYS_WRITE, 4
.equ SYS_READ,  3
.equ SYS_CLOSE, 6
.equ SYS_EXIT,  1 

####   options   ####
.equ O_RDONLY, 0
.equ O_CREAT_WRONLY_TRUNC, 03101

#### descriptors #### 
.equ STDIN,  0 
.equ STDOUT, 1
.equ STDERR, 2 

#### interrupts  ####
.equ LNX_SYSCALL, 0x80
.equ END_FILE,		0
.equ ARGC,			2	

.section .bss
.equ BUF_SIZE, 500
.lcomm BUFFER, BUF_SIZE

.section .text

####   stack  	####
.equ STACK_SIZE,  8
.equ ST_FD_IN,   -4
.equ ST_FD_OUT,  -8
.equ ST_ARGC,	   0
.equ ST_ARGV_0,	4 
.equ ST_ARGV_1,	8 
.equ ST_ARGV_2,	12

.globl _start

_start:

# prepare stack 
movl %esp, %ebp
subl $STACK_SIZE, %esp 

open_files:
open_fd_in: 

# open input file for reading
# param 1: name
# param 2: flags 
# param 3: mode 

movl $SYS_OPEN,		 %eax
movl ST_ARGV_1(%ebp), %ebx 
movl $O_RDONLY,		 %ecx
movl $0666,				 %edx
int $LNX_SYSCALL


# save opened file descriptor 
store_fd_in:
movl %eax, ST_FD_IN(%ebp) 

# open output file 
# for writing 
open_fd_out:
movl $SYS_OPEN,				 %eax  
movl ST_ARGV_2(%ebp),		 %ebx 
movl $O_CREAT_WRONLY_TRUNC, %ecx
movl $0666,						 %edx
int  $LNX_SYSCALL

store_fd_out:
movl %eax, ST_FD_OUT(%ebp)


# read syscall:
# input fd
# location of buffer
# size of buffer
read_loop_begin:
movl $SYS_READ,		%eax 
movl ST_FD_IN(%ebp), %ebx 
movl $BUFFER,			%ecx
movl $BUF_SIZE,		%edx 
int  $LNX_SYSCALL

cmpl $END_FILE, %eax 
jle read_loop_end 

# convert block to upper case
continue_read_loop:
pushl $BUFFER    
pushl %eax       # size of the buffer 
call convert_to_upper
popl  %eax		  # get size back
addl $4, %esp 

write_block:
movl %eax,				 %edx 
movl $SYS_WRITE,	    %eax 
movl ST_FD_OUT(%ebp), %ebx
movl $BUFFER,			 %ecx
int $LNX_SYSCALL

jmp read_loop_begin

read_loop_end:
movl $SYS_CLOSE,		 %eax 
movl ST_FD_OUT(%ebp), %ebx
int $LNX_SYSCALL

movl $SYS_CLOSE,		 %eax 
movl ST_FD_IN(%ebp),  %ebx
int $LNX_SYSCALL

_exit:
movl $SYS_EXIT,		 %eax
movl $0,					 %ebx
int $LNX_SYSCALL

.equ LOWER_A, 'a'
.equ LOWER_Z, 'z'
.equ UPPER_CONVERT, 'A' - 'a'
.equ ST_BUF_LEN, 8
.equ ST_BUFFER,  12
convert_to_upper:
pushl %ebp
movl  %esp, %ebp

movl ST_BUFFER(%ebp),  %eax
movl ST_BUF_LEN(%ebp), %ebx
movl $0,					  %edi 

cmpl $0, %ebx 
je convert_loop_end

convert_loop:
movb (%eax, %edi, 1), %cl # current byte
cmpb $LOWER_A, %cl
jl next_byte
cmpb $LOWER_Z, %cl
jg next_byte

addb $UPPER_CONVERT, %cl
movb %cl, (%eax, %edi, 1)

next_byte:
incl %edi
cmpl %edi, %ebx
jne convert_loop

convert_loop_end:
movl %ebp, %esp
popl %ebp
ret 
