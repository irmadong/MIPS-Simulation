# This file implements a program that recursively computes binomial coefficients
# using a recursive function called "binomial".
# binomial takes two integer parameters, n and k (in that order)
# and assumes that both are nonnegative.  If n < k, then
# the result should be -1.  If n = k, or k = 0, the result should
# be 1.  Otherwise, the result is determined recursively using the relation
# binomial(n,k) = binomial(n-1, k-1) + binomial(n-1,k)
	
	.data
n:	.word 7
k:	.word 2
prompt_to_user_1:       .asciiz   "Please enter n: "
prompt_to_user_2:       .asciiz   "Please enter k: "
result_string_prefix:	.asciiz   "binomial("
result_string_middle1:	.asciiz   ","
result_string_middle2:	.asciiz   ") -> "	
newline:	        .asciiz  "\n"  # new line
	.text
	.align 2
	.globl main
	.ent main
main:

	# out of habit, I'll save the return address on the stack
	addi $sp, $sp, -4               # make room on stack
	sw $ra, 0($sp)                  # push return address onto stack

	# $s4 is loop index
	li $s4, 0
	li $s5, 5  # $s5 is stop index

LOOP:	
	
	# prompt the user for n
	la $a0, prompt_to_user_1  	# load address of result string into $a0
	li $v0, 4			        # set up print syscall 
	syscall                 	# execute system call

	# read the response
	li $v0, 5			# set up read int syscall 
	syscall                 	# execute system call
	addi $s0, $v0, 0                # put n in $s0

	# prompt the user for k
	la $a0, prompt_to_user_2  	# load address of result string into $a0
	li $v0, 4			# set up print syscall 
	syscall                 	# execute system call

	# read the response
	li $v0, 5			# set up read int syscall 
	syscall                 	# execute system call
	addi $s1, $v0, 0                # put k in $s1

	# load n and k in $a0 and $a1, for function call
	addi $a0, $s0, 0
	addi $a1, $s1, 0

	# call binomial function
	jal binomial

	addi $s2, $v0, 0                # place result in $s2

	# Now print out the string
	la $a0, result_string_prefix    # load address of result string into $a0
	li $v0, 4                       # set code for print string syscall
	syscall

	# print out n
	addi $a0, $s0, 0                # load n into $a0
	li $v0, 1                       # set code for print string syscall
	syscall

	# Now print out the comma
	la $a0, result_string_middle1   # load address of result string into $a0
	li $v0, 4                       # set code for print string syscall
	syscall

	# print out k
	addi $a0, $s1, 0                # load k into $a0
	li $v0, 1                       # set code for print string syscall
	syscall

	# Now print out the last part of result string
	la $a0, result_string_middle2   # load address of result string into $a0
	li $v0, 4                       # set code for print string syscall
	syscall

	# along with the result string
	addi $a0, $s2, 0                # put result into $a0
	li $v0, 1                       # set code for print int syscall
	syscall

	# Now print out the newline
	la $a0, newline			# load address of middle part of result string into $a0
	li $v0, 4                       # set code for print string syscall
	syscall

	addi $s4, $s4, 1                #increment loop index
	blt $s4, $s5, LOOP              # do another increment if less than 5 times through
	
	#restore $ra
	lw $ra, 0($sp)                  # read value from stack
	addi $sp, $sp, 4                # complete pop by adjusting $sp

	jr $ra 				# return from main method

.end main

	.globl binomial
	.ent binomial
binomial:
	
	addi $sp, $sp, -16				# allocate stack
	sw $ra, 0 ($sp)
	sw $s0, 4 ($sp)
	sw $s1, 8 ($sp)
	sw $s2, 12 ($sp)

	

	slt $t1, $a0, $a1				# if n < k set t1 = 1
	li $t2, 1
	beq $t1, $t2, Base_one			# branch if n < k

	beq $a0,$a1, Base_two			# branch if n == k

	beq $a1, $0, Base_two			# branch if k == 0


	add $s0, $a0, $0 				# save n in s0
	add $s1, $a1, $0 				# save k in s1

	addi $a0, $a0, -1				# n-1
	addi $a1, $a1, -1				# k-1
	jal binomial

	add $s2, $v0, $0				# save v0 in s2

	addi $a0, $s0, -1				# a0 = n-1
	add $a1, $s1, $0				# a1 = k
	jal binomial

	add $v0, $v0, $s2 				# result
	b End



Base_one: 
	li $v0, -1
	b End
Base_two:
	li $v0, 1


End:
	lw $ra, 0 ($sp)					# restore stack
	lw $s0, 4 ($sp)
	lw $s1, 8 ($sp)
	lw $s2, 12 ($sp)
	addi $sp, $sp, 16
	jr $ra

.end binomial








	