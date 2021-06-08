		.data

symTab:		.word	0x20202020:40

LOC:		.word	0x0400
		# NULL or 0 in tokArray prematurely terminates dumping
		#   tokArray. Use blanks instead.
TOKEN:		.word 	0x20202020:3
		# 2-word TOKEN & its TYPE			
tokArray:	.word	0x20202020:60
		# initializing with blanks			

inBuf:		.space	80
pound:		.byte	'#'
		# end an input line with '#'				

st_prompt:	.asciiz	"Enter a new input line. \n"
st_error:	.asciiz	"An error has occurred. \n"	
error:		.asciiz	"Double Definition Error"
tableHead:	.asciiz "  TOKEN        TYPE\n"


	
	.text
#######################################################################
#
# Main
#
#	read an input line
#	call scanner driver
#	clear buffers
#
#  	Global Registers
#	  $t5: index to inBuf in bytes
#	  $s0: char type, T
#	  $s1: next state Qx
#  	  $s3: index to the new char space in TOKEN
#  	  $a3: index to tokArray in 12 bytes per entry
#
######################################################################

newline:
	jal	getline
	# get a new input string			
	
	li	$t5, 0
	# $t5: index to inBuf			
	li	$t7, 0
	# symTab index in $t7			
	li	$a3,0
	# $a3: index to tokArray			
	lw	$s4, LOC
	# LOC in $s4		

	# State table driver
	la	$s1, Q0	
	# initial state Q0		
driver:	lw	$s2, 0($s1)
	# get the action routine			
	jalr	$v1, $s2
	# execute the action		

	sll	$s0, $s0, 2
	# compute byte offset of T		
	add	$s1, $s1, $s0
	# locate the next state		
	la	$s1, ($s1)
	lw	$s1, ($s1)
	# next State in $s1		
	sra	$s0, $s0, 2
	# reset $s0 for T		
	b	driver
	# go to the next state			
	
doSymb:
	lb	$s0, tokArray
	beq	$s0, '#', exit
	
	li	$t0, 0

nextTok:
	lb	$s0, tokArray+12
	bne	$s0, ':', operator
	
	lw	$s0, tokArray
	lw	$s1, tokArray+4
	li	$s2, 1
	
	jal 	Variable
	# function Variable returns valVar	
	
	addi	$t0, $t0, 24
	
operator:
	addi	$t0, $t0, 12
	
	li	$a0, 1
	# $a0 = isComma		

chkVar:
	lb	$s0, tokArray($t0)
	beq	$s0, '#', dump
	beqz	$a0, nextVar
	lw	$s1, tokArray+8($t0)
	bne	$s1, 2, nextVar
	
	lw	$s0, tokArray($t0)
	lw	$s1, tokArray+4($t0)
	li	$s2, 0
	# DEFN flag in $s2		
	
	jal 	Variable

nextVar:
	lb	$s0, tokArray($t0)
	seq	$a0, $s0, ','
	addi	$t0, $t0, 12
	b 	chkVar

dump:	jal	printline
	# echo print input string	
	jal	printsymTab		
	# output token array
	jal	clearInBuf
	# clear input buffer		
	jal	clearTokArray
	# clear token array		

	addi	$s4, $s4, 4
	# LOC += 4		
	b 	newline

exit:
	li $v0, 10
	syscall


Variable:
	jal	srchSymTab
	# symIndex in $t8		
	bge	$t8, $zero, else
	# if symIndex >= 0, goto else	
	li	$s0, 0x4
	or	$s1, $s0, $s2
	# newStatus in $s1, DEFN in $s2		
	jal	saveSymTab
	b	varNext
else:
	lw	$t2, symTab+12($t8)
	# oldStatus in $t2	
	and	$t3, $t2, 0x2
	# oldStatus & 0x2		
	and	$t4, $t2, 0x1
	# oldStatus & 0x1		
	sll	$t5, $t2, 1
	# (oldStatus & 0x1) << 1		
	or	$s1, $t3, $t5
	# set A flag in newStatus		
	or	$s1, $s1, $s2
	# set D flag		
	sw	$s1, symTab+12($t8)
	# symTab[symIndex][2] = newStatus	
varNext:
	la	$s0, symACTS
	sll	$s1, $s1, 2
	add	$s0, $s0, $s1
	jr	$s0
varRealEnd:	
	jr	$ra
	
	
srchSymTab:
	li	$t3, 0
	# i = 0 in $t3				
	li	$t8, -1
srchStart:	
	bge	$t3, $t7, srchEnd
	# symTab index in $t7		
	lw	$t4, TOKEN			
	lw	$t5, symTab($t3)
	bne	$t4, $t5, update
	# match TOKEN with element in symTab		
	lw	$t4, TOKEN+4
	lw	$t5, symTab+4($t2)
	bne	$t4, $t5, update
	add	$t8, $zero, $t3
	# symIndex in $t8			
	j	srchEnd
update:
	addi	$t3, $t3, 16
	b	srchStart
srchEnd:
	jr	$ra
	
	
saveSymTab:
	sw	$s1, symTab+12($t7)
	# store newStatus in 4th word in symTab at $t7 entry	
	lw	$t3, TOKEN	
	sw	$t3, symTab($t7)
	# store the first word from TOKEN	
	lw	$t3, TOKEN+4		
	sw	$t3, symTab+4($t7)
	# store the second word from TOKEN into symTab	
	add	$t8, $zero, $t7
	# add symIndex		
	addi	$t7, $t7, 16
	# increment symTab index by 16 (1 entry is 4 words = 16 bytes)		
	jr	$ra
	
	
symACTS:
	b symACT0
	b symACT1
	b symACT2
	b symACT3
	b symACT4
	b symACT5
	
symACT0:
	lw	$t1, symTab+8($t8)
	# return previous VALUE	
	sw	$s4, symTab+8($t8)
	# store LOC in VALUE field of symTab	
	b	target
symACT1:
	lw	$t1, symTab+8($t8)
	# same as ACT0	
	sw	$s4, symTab+8($t8)
	b	target
symACT2:
	lw	$t1, symTab+8($t8)
	# return VALUE	
	b	target
symACT3:
	la	$a0, error
	# print "Double Definition Error" 	
	li	$v0, 4
	syscall
	li	$t1, -1
	# return -1		
	b	target
symACT4:
	sw	$s4, symTab+8($t8)
	# store LOC in VALUE	
	li	$t1, -1
	# return -1		
	b	target
symACT5:
	sw	$s4, symTab+8($t8)
	# store LOC in VALUE	
	li	$t1, 0
	# return 0		
	b	target
	
target:
	la	$s0, symACTS
	sll	$s1, $s1, 2
	add	$s0, $s0, $s1
	jr	$s0


####################### STATE ACTION ROUTINES #####################
##############################################
#
# ACT1:
#	$t5: Get next char
#	T = char type
#
##############################################
ACT1: 
	lb	$a0, inBuf($t5)
	# $a0: next char			
	jal	lin_search
	# $s0: T (char type)			
	addi	$t5, $t5, 1
	# $t5++			
	jr	$v1
	
###############################################
#
# ACT2:
#	save char to TOKEN for the first time
#	save char type as Token type
#	set remaining token space
#
##############################################
ACT2:
	li	$s3, 0
	# initialize index to TOKEN char 				
	sb	$a0, TOKEN($s3)
	# save 1st char to TOKEN			
	addi	$t0, $s0, 0x30
	# T in ASCII			
	sb	$t0, TOKEN+10($s3)
	# save T as Token type		
	li	$t0, '\n'
	sb	$t0, TOKEN+11($s3)
	# NULL to terminate an entry		
	addi	$s3, $s3, 1
	jr 	$v1
	
#############################################
#
# ACT3:
#	collect char to TOKEN
#	update remaining token space
#
#############################################
ACT3:
	bgt	$s3, 7, lenError
	# TOKEN length error		
	sb	$a0, TOKEN($s3)
	# save char to TOKEN			
	addi	$s3, $s3, 1
	# $s3: index to TOKEN			
	jr	$v1	
lenError:
	li	$s0, 7
	# T=7 for token length error				
	jr	$v1
					
#############################################
#
#  ACT4:
#	move TOKEN to tokArray
#
############################################
ACT4:
	lw	$t0, TOKEN($0)
	# get 1st word of TOKEN			
	sw	$t0, tokArray($a3)
	# save 1st word to tokArray		
	lw	$t0, TOKEN+4($0)
	# get 2nd word of TOKEN		
	sw	$t0, tokArray+4($a3)
	# save 2nd word to tokArray		
	lw	$t0, TOKEN+8($0)
	# get Token Type		
	sw	$t0, tokArray+8($a3)
	# save Token Type to tokArray		
	addi	$a3, $a3, 12
	# update index to tokArray			
	
	jal	clearTok
	# clear 3-word TOKEN			
	jr	$v1

############################################
#
#  RETURN:
#	End of the input string
#
############################################
RETURN:
	sw	$zero, tokArray($a3)
	# force NULL into tokArray		
	b	doSymb
	# leave the state table				


#############################################
#
#  ERROR:
#	Error statement and quit
#
############################################
ERROR:
	la	$a0, st_error
	# print error occurrence			
	li	$v0, 4
	syscall
	b	dump


############################### BOOK-KEEPING FUNCTIONS #########################
#############################################
#
#  clearTok:
#	clear 3-word TOKEN after copying it to tokArray
#
#############################################
clearTok:
	li	$t1, 0x20202020
	sw	$t1, TOKEN($0)
	sw	$t1, TOKEN+4($0)
	sw	$t1, TOKEN+8($0)
	jr	$ra
	
#############################################
#
#  printline:
#	Echo print input string
#
#############################################
printline:
	la	$a0, inBuf
	# input Buffer address			
	li	$v0,4
	syscall
	jr	$ra

#############################################
#
#  printTokArray:
#	print Token array header
#	print each token entry
#
#############################################
printTokArray:
	la	$a0, tableHead
	# table heading			
	li	$v0, 4
	syscall

	la	$a0, tokArray
	# print tokArray			
	li	$v0, 4
	syscall

	jr	$ra
	
printsymTab:
	la	$a0, symTab
	li	$v0, 4
	syscall
	

############################################
#
#  clearInBuf:
#	clear inbox
#
############################################
clearInBuf:
	li	$t0,0
loopInB:
	bge	$t0, 80, doneInB
	sw	$zero, inBuf($t0)
	# clear inBuf to 0x0		
	addi	$t0, $t0, 4
	b	loopInB
doneInB:
	jr	$ra
	
###########################################
#
# clearTokArray:
#	clear Token Array
#
###########################################
clearTokArray:
	li	$t0, 0
	li	$t1, 0x20202020
	# intialized with blanks			
loopCTok:
	bge	$t0, $a3, doneCTok
	sw	$t1, tokArray($t0)
	# clear		
	sw	$t1, tokArray+4($t0)
	#  3-word entry		
	sw	$t1, tokArray+8($t0)
	#  in tokArray		
	addi	$t0, $t0, 12
	b	loopCTok
doneCTok:
	jr	$ra
	

###################################################################
#
#  getline:
#	get input string into inbox
#
###################################################################
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


##################################################################
#
#  lin_search:
#	Linear search of Tabchar
#
#   	$a0: char key
#   	$s0: char type, T
#
#################################################################
lin_search:
	li	$t0,0
	# index to Tabchar				
	li	$s0, 7
	# return value, type T				
loopSrch:
	lb	$t1, Tabchar($t0)
	beq	$t1, 0x7F, charFail
	beq	$t1, $a0, charFound
	addi	$t0, $t0, 8
	b	loopSrch

charFound:
	lw	$s0, Tabchar+4($t0)
	# return char type		
charFail:
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
	.word ' ', 5
 	.word '#', 6
 	.word '$', 4 
	.word '(', 4
	.word ')', 4 
	.word '*', 3 
	.word '+', 3 
	.word ',', 4 
	.word '-', 3 
	.word '.', 4 
	.word '/', 3 

	.word '0', 1
	.word '1', 1 
	.word '2', 1 
	.word '3', 1 
	.word '4', 1 
	.word '5', 1 
	.word '6', 1 
	.word '7', 1 
	.word '8', 1 
	.word '9', 1 

	.word ':', 4 

	.word 'A', 2
	.word 'B', 2 
	.word 'C', 2 
	.word 'D', 2 
	.word 'E', 2 
	.word 'F', 2 
	.word 'G', 2 
	.word 'H', 2 
	.word 'I', 2 
	.word 'J', 2 
	.word 'K', 2
	.word 'L', 2 
	.word 'M', 2 
	.word 'N', 2 
	.word 'O', 2 
	.word 'P', 2 
	.word 'Q', 2 
	.word 'R', 2 
	.word 'S', 2 
	.word 'T', 2 
	.word 'U', 2
	.word 'V', 2 
	.word 'W', 2 
	.word 'X', 2 
	.word 'Y', 2
	.word 'Z', 2

	.word 'a', 2 
	.word 'b', 2 
	.word 'c', 2 
	.word 'd', 2 
	.word 'e', 2 
	.word 'f', 2 
	.word 'g', 2 
	.word 'h', 2 
	.word 'i', 2 
	.word 'j', 2 
	.word 'k', 2
	.word 'l', 2 
	.word 'm', 2 
	.word 'n', 2 
	.word 'o', 2 
	.word 'p', 2 
	.word 'q', 2 
	.word 'r', 2 
	.word 's', 2 
	.word 't', 2 
	.word 'u', 2
	.word 'v', 2 
	.word 'w', 2 
	.word 'x', 2 
	.word 'y', 2
	.word 'z', 2

	.word 0x7F, 0
