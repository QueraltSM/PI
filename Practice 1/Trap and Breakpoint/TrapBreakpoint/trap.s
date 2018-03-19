.data 0xffff0000

tcntrl: .space 4
tdata: 	.space 4
pcntrl: .space 4
pdata: 	.space 4
	
.data 0x10000000

trapMessage:	.asciiz "[TrapException!!]"

.text 0x400000


main:
		jal KbdIntrEnable
		jal ReadCharacter
		
fin:
	j fin 
	
ReadCharacter:
	lw $s4, tcntrl
	andi $s5,$s4,1
	beq $s5, $0, ReadCharacter
	lw $a0, tdata
	jr $31


PrintCharacter:
	lw $s4, pcntrl
	andi $s5,$s4,1
	beq $s5, $0, PrintCharacter
	sw $a0, pdata
	jr $31

		
KbdIntrEnable:
		mfc0 $t3,$12
		ori $t3,$t3,0x801 	
    	mtc0 $t3,$12		
    	lw $t1,tcntrl
    	ori $t1,$t1,2
		sw $t1, tcntrl
		jr $31
 
TrapException:
		
		li $v0, 4
		la $a0, trapMessage
		syscall
		
		j endKbdIntr
		
		
generateTrapException:
		teq $0, $0
		jr $31
		
	

KbdIntr:
	addi $sp, $sp,-4 
	sw $31, 0($sp)
	addi $sp, $sp,-4 
	sw $s0, 0($sp)
	addi $sp, $sp,-4 
	sw $s1, 0($sp)
	addi $sp, $sp,-4 
	sw $s2, 0($sp)
		
	addi $s1,$0,19  	
	lw $s0, tdata
		
	beq $s1, $s0, generateTrapException

	lw $a0, tdata	
	jal PrintCharacter

endKbdIntr:
	
	lw $s2, 0($sp)
	addi $sp, $sp,4
	lw $s1, 0($sp)
	addi $sp, $sp,4
	lw $s0, 0($sp)
	addi $sp, $sp,4
	lw $31, 0($sp)
	addi $sp, $sp,4
	jr $31
