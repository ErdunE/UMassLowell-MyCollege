		.data
		
TOKEN:		.word 0x20202020:3
Tokspace:	.word 0
TokTable:	.word 0x20202020:60	
		# each entry contains 3 words * 20	
	
inBuf:		.space	80	
		#.byte	' ':80
outBuf:		.space	80
st_prompt:	.asciiz "Enter a new input line. \n"


		.text
main:
		jal 	getline
		
		la 	$s1, Q0		
		# CUR = Q0
		li 	$s0, 1		
		# T = 1
		li 	$s3, 0				
		# inBuf[0]
		li	$s4, 0			
		# TOKEN[0]
		li	$s5, 8		
		# Token space = 8
		li	$s6, 0		
		# TokTable[0]
		li	$t5, 0x20
		
nextState:	lw	$s2, 0($s1)
		jalr	$v1, $s2	
		# Save return addr in $v1
		
		sll 	$s0, $s0, 2	
		# Multiply by 4 for word 
		add	$s1, $s1, $s0
		sra	$s0, $s0, 2
		lw	$s1, 0($s1)
		b 	nextState


cleanup:	jal 	printIn
		jal 	printOut
		jal	clearIn
		#jal	clearOut
		
		b main

exit:		# stop program
		li $v0, 10
		syscall

ACT1:	# curChar = Get next char, T = ChType(curChar)
		lb	$a0, inBuf($s3)
		addi 	$s3, $s3, 1
		jal 	lin_search	
		# T in $s0
		
		jr	$v1
		
ACT2:	# TOKEN = curChar, TokSpace = 7
		li	$s4, 0
		sb	$a0, TOKEN($s4)
		addi	$s4, $s4, 1
		
		addi	$s0, $s0, 0x30
		sb	$s0, TOKEN+8
		subi	$s0, $s0, 0x30
		li	$t9, 0x0a
		sb	$t9, TOKEN+11	
		
		li	$s5, 7	
		# TokSpace = 7
		
		jr	$v1
		
ACT3:	# TOKEN = TOKEN + curChar, TokSpace -= 1
		sb	$a0, TOKEN($s4)
		addi	$s4, $s4, 1
		
		subi	$s5, $s5, 1
		
		jr	$v1
		
ACT4:	# Save TOKEN into Tokens, Clear TOKEN
		lw	$t6, TOKEN
		sw	$t6, TokTable($s6)
		addi	$s6, $s6, 4
		lw	$t6, TOKEN+4
		sw	$t6, TokTable($s6)
		addi	$s6, $s6, 4
		lw	$t6, TOKEN+8
		sw	$t6, TokTable($s6)
		addi	$s6, $s6, 4
		
clearTOKEN:	
		la	$s7, TOKEN
		li	$t6, 0
clearLoop:
		bge	$t6, 12, clearDone
		sb	$t5, ($s7)
		addi	$s7, $s7, 1
		addi	$t6, $t6, 1
		b	clearLoop
clearDone:
		jr	$v1

ERROR:
		jr	$v1

RETURN:
		b 	cleanup

		
#####
#
# function lin_search
# $a0: char key
# $s0: char type, T
#
#####
lin_search:
	li	$t0,0				
	# index to Tabchar
	li	$s0, 7				
	# return value, type T
loopSrch:
	lb	$t1, Tabchar($t0)
	beq	$t1, '\\', charFail
	beq	$t1, $a0, charFound
	addi	$t0, $t0, 8
	b	loopSrch

charFound:
	lw	$s0, Tabchar+4($t0)		
	# return char type
charFail:
	jr	$ra
		
	
printIn:
	li $v0, 4
	la $a0, inBuf
	syscall
	jr $ra
	
printOut:
	li $v0, 4
	la $a0, TokTable
	syscall
	jr $ra
	
clearIn:
	li	$t0,0
loopIn:
	bge	$t0, 80, doneIn
	sw	$zero, inBuf($t0)		
	# clear inBuf one word at a time

	addi	$t0, $t0, 4
	b	loopIn
doneIn:
	jr	$ra
	
clearOut:
	li	$t0, 0
loopOut:
	bge	$t0, 240, doneOut
	sw	$zero, TokTable($t0)		
	# clear inBuf one word at a time
	addi	$t0, $t0, 4
	b	loopOut
doneOut:
	jr	$ra
	
			
getline: 
	la	$a0, st_prompt			
	# Prompt to enter a new line
	li	$v0, 4
	syscall

	la	$a0, inBuf			
	# read a new line
	li	$a1, 80	
	li	$v0, 8
	syscall
	jr	$ra
	
	
		.data
STAB:
Q0:     .word  ACT1
        .word  Q1   # T1
        .word  Q1   # T2
        .word  Q1   # T3
        .word  Q1   # T4
        .word  Q1   # T5
        .word  Q1   # T6
        .word  Q11  # T7

Q1:     .word  ACT2
        .word  Q2   # T1
        .word  Q5   # T2
        .word  Q3   # T3
        .word  Q3   # T4
        .word  Q0   # T5
        .word  Q4   # T6
        .word  Q11  # T7

Q2:     .word  ACT1
        .word  Q6   # T1
        .word  Q7   # T2
        .word  Q7   # T3
        .word  Q7   # T4
        .word  Q7   # T5
        .word  Q7   # T6
        .word  Q11  # T7

Q3:     .word  ACT4
        .word  Q0   # T1
        .word  Q0   # T2
        .word  Q0   # T3
        .word  Q0   # T4
        .word  Q0   # T5
        .word  Q0   # T6
        .word  Q11  # T7

Q4:     .word  ACT4
        .word  Q10  # T1
        .word  Q10  # T2
        .word  Q10  # T3
        .word  Q10  # T4
        .word  Q10  # T5
        .word  Q10  # T6
        .word  Q11  # T7

Q5:     .word  ACT1
        .word  Q8   # T1
        .word  Q8   # T2
        .word  Q9   # T3
        .word  Q9   # T4
        .word  Q9   # T5
        .word  Q9   # T6
        .word  Q11  # T7

Q6:     .word  ACT3
        .word  Q2   # T1
        .word  Q2   # T2
        .word  Q2   # T3
        .word  Q2   # T4
        .word  Q2   # T5
        .word  Q2   # T6
        .word  Q11  # T7

Q7:     .word  ACT4
        .word  Q1   # T1
        .word  Q1   # T2
        .word  Q1   # T3
        .word  Q1   # T4
        .word  Q1   # T5
        .word  Q1   # T6
        .word  Q11  # T7

Q8:     .word  ACT3
        .word  Q5   # T1
        .word  Q5   # T2
        .word  Q5   # T3
        .word  Q5   # T4
        .word  Q5   # T5
        .word  Q5   # T6
        .word  Q11  # T7

Q9:     .word  ACT4
        .word  Q1  # T1
        .word  Q1  # T2
        .word  Q1  # T3
        .word  Q1  # T4
        .word  Q1  # T5
        .word  Q1  # T6
        .word  Q11 # T7

Q10:	.word	RETURN
        .word  Q10  # T1
        .word  Q10  # T2
        .word  Q10  # T3
        .word  Q10  # T4
        .word  Q10  # T5
        .word  Q10  # T6
        .word  Q11  # T7

Q11:    .word  ERROR 
	.word  Q4  # T1
	.word  Q4  # T2
	.word  Q4  # T3
	.word  Q4  # T4
	.word  Q4  # T5
	.word  Q4  # T6
	.word  Q4  # T7

Tabchar: 	
	.word 	0x0a, 6		
 	.word 	'#', 6
 	.word	' ', 5
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

	.word	'\\', -1	# if you ‘\’ as the end-of-table symbol

