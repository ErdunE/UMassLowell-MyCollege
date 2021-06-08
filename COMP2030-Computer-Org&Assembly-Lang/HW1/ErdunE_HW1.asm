	.data 
A: 	.space 12 # because we have 3 element, each of the element have 4 bit
prompt: .asciiz "Enter a integer please: "
	.text 
main:
	jal init # call the init function
	jal avg # call the avg function
	
	li $v0 1 # print out the average value
	add $a0,$v1,$zero
	syscall

	li $v0,10 #end of the program
	syscall
init:
	li $v0,4 # input the first number
	la $a0,prompt
	syscall
	li $v0, 5 # read the integer from input
	syscall
	addi $t0, $zero,0 # put the value into the array
	add $s0,$v0,$zero
	sw $s0, A($t0)
	

	li $v0,4 # input the second number
	la $a0,prompt
	syscall
	li $v0, 5
	syscall
	addi $t0, $t0,4
	add $s0,$v0,$zero
	sw $s0, A($t0)
	

	li $v0,4 # input the third number
	la $a0,prompt
	syscall
	li $v0, 5
	syscall
	addi $t0, $t0,4
	add $s0,$v0,$zero
	sw $s0, A($t0)
	
	jr 	$ra
	
avg:
	addi $t0, $zero,0 # read each number 
	lw $a1 A($zero)
		addi $t0, $t0,4
	lw $a2 A($t0)
		addi $t0, $t0,4
	lw $a3 A($t0)
	
	add $v1 $a1 $a2 # calculate the sum of three numbers
	add $v1 $v1 $a3
	
	div $v1, $v1,3 # calculate the value of  average
	
	jr $ra
