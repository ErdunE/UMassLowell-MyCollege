		.data
inBuf:		.space	80
outBuf:		.space	80
st_prompt:	.asciiz "Enter a new input line. \n"
		.text
main:
		jal getline
		lb $s0, inBuf	
		# for loop i = 0
		li $t9, 0 
	loop:
		# set s0 in inBuf[i]	
		lb $s0, inBuf($t9)
		# put it into the lin_search  
		jal lin_search 
		# to ascii value
		addi $t0, $t0, 0x30
		# set t0 in outBuf[i] 
		sb $t0, outBuf($t9) 
		# if detect a #, end the loop and print result
		beq $s0, '#', endLoop 
		# creat i	
		addi $t9, $t9, 1 
		# if i < 80, do the work again until i >= 80.
		blt $t9, 80, loop 
			
	endLoop:
		jal printIn
		jal printOut
		jal clearIn
		jal clearOut		
	exit:
		li $v0, 10
		syscall
lin_search:
		# tabchar 
		li $t8, 0 
rept:
		# load tabchar to t1
		lb $t1, Tabchar($t8) 
		# compare the input through Tabchar
		beq $s0, $t1, done 
		# add i to 8 bytes
		addi $t8, $t8, 8 
		# return to loop
		blt $t8, 640, rept 
	
done:
		# load the char type to register t0
		lb $t0, Tabchar+4($t8) 
		# return
		jr	$ra
		
	
printIn:
	li $v0, 4
	la $a0, inBuf
	syscall
	
	jr $ra
	
printOut:
	li $v0, 4
	la $a0, outBuf
	syscall
	jr $ra
	
clearIn:
	li	$t0,0
loopIn:
	bge	$t0, 80, doneIn
	# clear inBuf one word at a time
	sw	$zero, inBuf($t0)		
	addi	$t0, $t0, 4
	b	loopIn
doneIn:
	jr	$ra
	
clearOut:
	li	$t0, 0
loopOut:
	bge	$t0, 80, doneOut
	# clear inBuf one word at a time
	sw	$zero, inBuf($t0)		
	addi	$t0, $t0, 4
	b	loopOut
doneOut:
	jr	$ra
			
getline: 
	# Prompt to enter a new line
	la	$a0, st_prompt		
	li	$v0, 4
	syscall
	# read a new line
	la	$a0, inBuf		
	li	$a1, 80	
	li	$v0, 8
	syscall

	jr	$ra


	
		.data
		# Tabchar 
Tabchar: 	.word 	0x0a, 6		
	.word 	' ', 5
 	.word 	'#', 6
	.word 	'$',4
	.word 	'(', 4 
	.word 	')', 4 
	.word 	'*', 3 
	.word 	'+', 3 
	.word 	',', 4 
	.word 	'-', 3 
	.word 	'.', 4 
	.word 	'/', 3 

	.word 	'0', 1
	.word 	'1', 1 
	.word 	'2', 1 
	.word 	'3', 1 
	.word 	'4', 1 
	.word 	'5', 1 
	.word 	'6', 1 
	.word 	'7', 1 
	.word 	'8', 1 
	.word 	'9', 1 

	.word 	':', 4 

	.word 	'A', 2
	.word 	'B', 2 
	.word 	'C', 2 
	.word 	'D', 2 
	.word 	'E', 2 
	.word 	'F', 2 
	.word 	'G', 2 
	.word 	'H', 2 
	.word 	'I', 2 
	.word 	'J', 2 
	.word 	'K', 2
	.word 	'L', 2 
	.word 	'M', 2 
	.word 	'N', 2 
	.word 	'O', 2 
	.word 	'P', 2 
	.word 	'Q', 2 
	.word 	'R', 2 
	.word 	'S', 2 
	.word 	'T', 2 
	.word 	'U', 2
	.word 	'V', 2 
	.word 	'W', 2 
	.word 	'X', 2 
	.word 	'Y', 2
	.word 	'Z', 2

	.word 	'a', 2 
	.word 	'b', 2 
	.word 	'c', 2 
	.word 	'd', 2 
	.word 	'e', 2 
	.word 	'f', 2 
	.word 	'g', 2 
	.word 	'h', 2 
	.word 	'i', 2 
	.word 	'j', 2 
	.word 	'k', 2
	.word 	'l', 2 
	.word 	'm', 2 
	.word 	'n', 2 
	.word 	'o', 2 
	.word 	'p', 2 
	.word 	'q', 2 
	.word 	'r', 2 
	.word 	's', 2 
	.word 	't', 2 
	.word 	'u', 2
	.word 	'v', 2 
	.word 	'w', 2 
	.word 	'x', 2 
	.word 	'y', 2
	.word 	'z', 2
	# if you ‘\’ as the end-of-table symbol	
	.word	'\\', -1	

