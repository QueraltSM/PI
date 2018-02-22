.data 0xffff0000

tcntrl: .space 4
tdata: 	.space 4
pcntrl: .space 4
pdata: 	.space 4
	
.data 0x10000000

texto:	.space 120 # 30 letras 

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
 
BreakPoint:
	lw $a0, texto($s6)
	beqz $a0, finTrataFrase
	jal PrintCharacter
	
seguir:
	addi $s6,$s6, 4
	j BreakPoint

finTrataFrase:
		
		add $t7, $0, $0
		add $s6, $0, $0

		j endKbdIntr
		
		
generarBreakpoint:
		break 5;
		jr $31
		
	
almacenarBuffer:
	lw $a0, tdata
	sw $a0, texto($t7) 
	addi $t7, $t7, 4
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
		
	addi $s1,$0,20  	
	lw $s0, tdata
		
	beq $s1, $s0, generarBreakpoint
	jal almacenarBuffer
	

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
