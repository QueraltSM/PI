.data 0xffff0000

tcntrl: .space 4
tdata: 	.space 4
pcntrl: .space 4
pdata: 	.space 4
	
.data 0x10000000

pregunta:			.asciiz "0 - Programa principal\n1 - Mejora 1 : Contador de caracteres\n2 - Mejora 2 : Cronometro\n3 - Mejora 3 : Temporizador\n4 - Mejora 4 : Velocidad de mecanografia en 1 minuto\n5 - Mejora 5 : Trap inversor de cadena de texto\n6 - Mejora 6 : Sucesion Fibonacci\n\nIntroduza el numero del programa a ejecutar: "
errorInput:			.asciiz "\n\n-----------------------------------------------------------\n\nValor Introducido no es correcto. Vuelva a intentarlo.\n\n"

# Cadenas de texto del programa principal (Parte Básica)
x: 					.asciiz "En un lugar de la mancha de cuyo nombre...\n"
x1: 				.asciiz "[Pulsacion("
x2: 				.asciiz ") = "
x3: 				.asciiz " ]"
x4: 				.asciiz "\nHora local: "
x5: 				.asciiz ":"
x6: 				.asciiz "\nIntroduce hora: "
x7: 				.asciiz "\nIntroduce minutos: "
x8: 				.asciiz "\nIntroduce segundos: "
x9: 				.asciiz "ERROR. Escriba un numero entre 0-23\n"
x10: 				.asciiz "ERROR. Escriba un numero entre 0-59\n"
pPrincipalFrase:	.asciiz "\n\n- - - - - PROGRAMA PRINCIPAL : Parte básica - - - - -\n\n"

# Cadenas de texto de la mejora 1 (Contador de caracteres)
mejora1Frase:		.asciiz "\n\n- - - - - MEJORA 1: Contador de caracteres - - - - -\n\nPulse CTRL + S para parar. Introduzca un texto:\n\n"
fraseMejora1:		.asciiz "\n\nIntroduzca un caracter: "
resultMejora1:		.asciiz "\n\nSe repiten en total =  "

# Cadenas de texto de la mejora 2 (Cronometro)
mejora2Frase:		.asciiz "\n\n- - - - - MEJORA 2: Cronometro - - - - -\n\n"
fraseMejora2: 		.asciiz "Introduce CTRL + S para parar el cronometro\n"
tiempoMejora2: 		.asciiz "\n\nTiempo =  "

# Cadenas de texto de la mejora 3 (Temporizador)
mejora3Frase:		.asciiz "\n\n- - - - - MEJORA 3: Temporizador - - - - -\n\n"
fraseMejora3: 		.asciiz "Pulsa CTRL + S = Parar temporizador o CTRL + Q = Introducir un tiempo nuevo\n"
tiempo: 			.asciiz "\n\nTiempo =  "

# Cadenas de texto de la mejora 4 (Caracteres en 1 minuto)
mejora4Frase:		.asciiz "\n\n- - - - - MEJORA 4: Caracteres en 1 minuto - - - - -\n\nIntroduzca un texto:\n\n"
resultMejora4: 		.asciiz "\n\nLetras que eres capaz de escribir en 1 minuto =  "
#tiempoActualMejora4: .word 0

# Cadenas de texto de la mejora 5 (Trap inversor de cadenas de texto)
mejora5Frase:		.asciiz "\n\n- - - - - MEJORA 5: Trap inversor de cadena de texto - - - - -\n\n"
modo:				.asciiz "\nCTRL + N = Sucesion Fibonacci\nCTRL + P = Fibonacci Par\nCTRL + I = Fibonacci Impar\n\n"
espacio:			.asciiz " "

eleccion:			.word 0 # Eleccion del usuario del programa o mejora a ejecutar

# Variables de la mejora 1 y 3 (Programa Principal y Temporizador)
hour: 				.word 10
minutes: 			.word 20
seconds: 			.word 30
countPPrincipal: 	.word 0
reg: 				.space 4

# Variables de la mejora 1 (Contador de letras)
textoMejora1:		.space 120
countMejora1:		.word 0

# Variables de la mejora 2 (Cronometro)
hourMejora2: 		.word 0
minutesMejora2: 	.word 0
secondsMejora2: 	.word 0

# Variables de la mejora 4 (Caracteres en 1 minuto)
countMejora4:		.word 0

# Variables de la mejora 6 (Sucesión de Fibonacci)
fibo:				.word 610 # Limite superior 
fibo1:				.word 0
fibo2:				.word 0

# Mejora 5 : Trap inversor de cadena de texto
.data 0x10001004
buffer:				.space 100
mejora6Frase:		.asciiz "\n\n- - - - - MEJORA 6: Sucesion de Fibonacci - - - - -\n\n"
trapMessage:		.asciiz " [TRAP EXCEPTION] "
salto:				.asciiz "\n"

.text 0x400000

main:
		li $v0,4 
		la $a0, pregunta
		syscall
		
		li $v0, 5
		syscall
		
		sw $v0, eleccion($0)
			
		beqz $v0, programaPrincipal
		addi $a0,$0,1
		beq $v0, $a0, mejora1
		addi $a0, $a0, 1
		beq $v0, $a0, mejora2
		addi $a0,$a0, 1
		beq $v0, $a0, mejora3
		addi $a0, $a0,1
		beq $v0, $a0, mejora4
		addi $a0, $a0, 1
		beq $v0, $a0, mejora5
		addi $a0, $a0, 1
		beq $v0, $a0, mejora6
		
		li $v0, 4
		la $a0, errorInput
		syscall
		
		j main   
		
fin:
		j fin 
		
# ReadCharacter(): Lee un carácter del teclado
# $a0: Carácter a leer	
ReadCharacter:
		lw $s4, tcntrl
		andi $s5,$s4,1
		beq $s5, $0, ReadCharacter
		lw $a0, tdata
		jr $31
	
# PrintCharacter(): Imprime un carácter en pantalla
# $a0: Carácter a imprimir	
PrintCharacter:
		lw $s4, pcntrl
		andi $s5,$s4,1
		beq $s5, $0, PrintCharacter
		sw $a0, pdata
		jr $31

# CaseIntr(): Detecta origen de la interrupción (teclado, timer u otros) y llama
# a la rutina de servicio que corresponda (KbdIntr o TimerIntr)	
CaseIntr: 
		mfc0 $t3,$13
		andi $t4,$t3,0x800 
    	bne $t4,$0, KbdIntr
		andi $t4, $t3, 0x8000 
		bne $t4, $0, TimerIntr

# KbdIntrEnable(): Subrutina de habilitación de interrupciones del teclado
KbdIntrEnable:
		mfc0 $t3,$12
		ori $t3,$t3,0x801 	
    	mtc0 $t3,$12		
    	lw $t1,tcntrl
    	ori $t1,$t1,2	
		sw $t1, tcntrl
		jr $31
 
# TimerIntrEnable(): Subrutina de habilitación de interrupciones del timer
TimerIntrEnable: 
		mtc0 $0,$9
		mfc0 $t3,$12
		ori $t3,$t3,0x8001 	
    	mtc0 $t3,$12	
		addi $t3,$0, 100 # Registro Compare, 1 segundo
		mtc0 $t3,$11		
		jr $31
		
		
		
# ---------------------------------------------------------------------------------------------------------------------------
# ----------------------------------------- PARTE BÁSICA ------------------------------------------------------------------------

				
programaPrincipal:
		jal KbdIntrEnable
		jal TimerIntrEnable
print:	
    	la $t6, x
		jal printPhrase
		j print
		
printPhrase:
    	sw $31, reg
loop:
		lb $a0, 0($t6)
		beq $0,$a0,endprintPhrase
		jal PrintCharacter
		addi $t6,$t6,1
		jal delay
		j loop

endprintPhrase:
		lw $31, reg
		jr $31

KbdIntrProgramaPrincipal:
		addi $s1,$0,18  	# Ctrl + R : Pedimos tiempo nuevo 
		lw $s0, tdata
		beq $s1,$s0, introduceHour
		
		li $v0, 4		
		la $a0, x1
		syscall
		
		la $v0, countPPrincipal
		lw $a0, 0($v0)
		addi $a0, $a0, 1
		sw $a0, 0($v0)
		li $v0, 1
		syscall
	
		li $v0, 4
		la $a0, x2
		syscall
	
		lw $a0, tdata	
		jal PrintCharacter
		
		li $v0, 4
		la $a0, x3
		syscall
	
		j endKbdIntr

# KbdIntr(): Rutina de servicio del teclado
KbdIntr:
		addi $sp, $sp,-4 
		sw $31, 0($sp)
		addi $sp, $sp,-4 
		sw $s0, 0($sp)
		addi $sp, $sp,-4 
		sw $s1, 0($sp)
		addi $sp, $sp,-4 
		sw $s2, 0($sp)
	
		la $a0, eleccion($0)
		lw $v0,0($a0)
	
		beqz $v0, KbdIntrProgramaPrincipal
		addi $a0,$0,1
		beq $v0, $a0,KbdIntrMejora1
		addi $a0, $a0, 1
		beq $v0, $a0,KbdIntrMejora2
		addi $a0,$a0, 1
		beq $v0, $a0, KbdIntrMejora3
		addi $a0, $a0,1
		beq $v0, $a0, KbdIntrMejora4
		addi $a0, $a0, 1
		beq $v0, $a0, KbdIntrMejora5
		addi $a0, $a0, 1
		beq $v0, $a0, KbdIntrMejora6
	
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
		
introduceHour:
		li $v0, 4
		la $a0, x6
		syscall
		
		addi $s0,$0,23
		li $v0, 5
		syscall
			
		bgt $v0,$s0,notAnHour
		blt $v0,$0,notAnHour
		sw $v0,hour
		
introduceMinute:
		li $v0, 4
		la $a0, x7
		syscall
	
		addi $s0,$0,59
		li $v0, 5
		syscall
			
		bgt $v0,$s0,notAMinute
		blt $v0,$0,notAMinute
		sw $v0,minutes
		
introduceSecond:
		li $v0, 4
		la $a0, x8
		syscall
		
		li $v0, 5
		syscall
		
		bgt $v0,$s0,notASecond
		blt $v0,$0,notASecond
		sw $v0,seconds
		j endKbdIntr

notAnHour:
		li $v0, 4
		la $a0, x9
		syscall
		j introduceHour
	
notAMinute:
		li $v0, 4
		la $a0, x10
		syscall
		j introduceMinute
	
notASecond:
		li $v0, 4
		la $a0, x10
		syscall
		j introduceSecond
	
# TimerIntr(): Rutina de servicio del timer	
TimerIntrProgramaPrincipal: 

		addi $t7, $t7, 1 # Aumentamos contador hasta que llegue a 5
		
		addi $s1,$0,60
		addi $s2,$0,24	
		
		la $v0, seconds	
		lw $a0, 0($v0)		
		addi $a0, $a0, 1
		beq $a0, $s1, minutesUpdate
		sw $a0, 0($v0)
		j doneProgramaPrincipal

# TimerIntr(): Rutina de servicio del timer	
TimerIntr:	
		addi $sp, $sp,-4 
		sw $31, 0($sp)
		addi $sp, $sp,-4 
		sw $s1, 0($sp)
		addi $sp, $sp,-4 
		sw $s2, 0($sp)
	
		la $a0, eleccion($0)
		lw $v0,0($a0)
	
		beqz $v0, TimerIntrProgramaPrincipal
		addi $a0,$0,2
		beq $v0, $a0,TimerIntrMejora2
		addi $a0,$a0, 1
		beq $v0, $a0, TimerIntrMejora3
		addi $a0, $a0,1
		beq $v0, $a0, TimerIntrMejora4
	
		j endTimerIntr

minutesUpdate:		
		addi $a0, $0, 0
		sw $a0, 0($v0)
		la $v0, minutes
		lw $a0, 0($v0)
		addi $a0, $a0, 1
		beq $a0, $s1, hoursUpdate
		sw $a0, 0($v0)
		j doneProgramaPrincipal

hoursUpdate:		
		addi $a0, $0, 0
		sw $a0, 0($v0)
		la $v0, hour
		lw $a0, 0($v0)
		addi $a0, $a0, 1
		beq $a0, $s2, reset
		sw $a0, 0($v0)
		j doneProgramaPrincipal
		
reset:			
		addi $a0, $0, 0
		sw $a0, 0($v0)
	
# $t7: Contador de veces que se produce una interrupcion del timer
# Utilidad: A cada 5 veces que interrumpa en timer (alrededor de 5 segundos)
# Se imprimirá la cadena x4 (Hora Local)

doneProgramaPrincipal:
		addi $t2, $0, 5
		beq $t7, $t2, mostrar # Han pasado aproximadamente 5 segundos
		jal endTimerIntr
		jr $31
	
mostrar:
		addi $t7,$0,0 # Restauramos contador
	
		li $v0, 4		
		la $a0, x4
		syscall
		
		la $v0, hour
		lw $a0, 0($v0)
		li $v0, 1
		syscall
	
		li $v0, 4
		la $a0, x5
		syscall
	
		la $v0, minutes
		lw $a0, 0($v0)
		li $v0, 1
		syscall
		
		li $v0, 4
		la $a0, x5
		syscall

		la $v0, seconds
		lw $a0, 0($v0)
		li $v0, 1
		syscall
		
		li $a0,0x0d # Retorno de carro
		jal PrintCharacter

endTimerIntr:
		mtc0 $0,$9 # Restore de Count ($9)
		lw $s2, 0($sp)
		addi $sp, $sp,4
		lw $s1, 0($sp)
		addi $sp, $sp,4
		lw $31, 0($sp)
		addi $sp, $sp,4
		jr $31
	
# Delay(): Temporizador (0.5 seg aproximadamente)
delay:
    	li $s2,0
		li $s3,25000
		
bucle_delay:
	
		beq $s2,$s3,finDelay
		addi $s2,$s2,1
		j bucle_delay
finDelay:	
		jr $31
	
# ---------------------------------------------------------------------------------------------------------------------------
# ------------------ MEJORA 1 : Contador de caracteres ----------------------------------------------------------------------

mejora1:
		li $v0, 4
		la $a0, mejora1Frase
		syscall 
	
		jal KbdIntrEnable
		j fin

KbdIntrMejora1:
		addi $s1,$0,19  	# Ctrl + S = Stop : Paramos de introducir texto 
		lw $s0, tdata
		beq $s1,$s0, askLetter
		lw $a0, tdata
		jal PrintCharacterMejora1
	
		j endKbdIntr
	
PrintCharacterMejora1:
		lw $s4, pcntrl
		andi $s5,$s4,1
		beq $s5, $0, PrintCharacterMejora1
		sw $a0, pdata
		sw $a0, textoMejora1($t7)	# Almacenamos en memoria el caracter introducido
		lw $t5, textoMejora1($t7)   # $t5: contiene la última letra introducida
		addi $t7, $t7, 4
		jr $31

askLetter:
		li $v0, 4
		la $a0, fraseMejora1
		syscall
	
		jal ReadCharacter
		jal PrintCharacterMejora1
	
trataFrase:
		la $s6, textoMejora1
	
bucle:
		lw $t4, 0($s6)
		beqz $t4,finTrataFrase
	
		bne $t4, $t5, seguir
	
		la $v0, countMejora1 # Aumentamos contador de caracteres introducidos
		lw $a0, 0($v0)
		addi $a0, $a0, 1
		sw $a0, 0($v0)
	
seguir:
		addi $s6,$s6, 4
		j bucle

finTrataFrase:
		li $v0, 4
		la $a0, resultMejora1
		syscall 
	
	# Disminuimos 1 porque el último caracter introducido ha sido almacenada en memoria también
		la $v0, countMejora1
		lw $a0, 0($v0)
	
		beqz $a0, noResta # No restaremos si no se encuentra el caracter
		addi $a0, $a0, -1
	
noResta:
		sw $a0, 0($v0)
		li $v0, 1
		syscall

		j fin
	
# ---------------------------------------------------------------------------------------------------------------------------
# -------------- MEJORA 2 : Cronometro --------------------------------------------------------------------------------------
		
mejora2:
		li $v0, 4
		la $a0, mejora2Frase
		syscall 
	
		li $v0,4
		la $a0, fraseMejora2
		syscall 
		
		jal KbdIntrEnable
		jal TimerIntrEnable
	
		j fin 
				
KbdIntrMejora2:
		addi $s1,$0,19  	#Ctrl + S = Stop : Paramos el cronómetro
		lw $s0, tdata
		beq $s1,$s0, fin
		lw $a0, tdata
		jal PrintCharacter
	
		j endKbdIntr
	
TimerIntrMejora2: 	
		addi $sp, $sp,-4 
		sw $31, 0($sp)
		addi $sp, $sp,-4 
		sw $s1, 0($sp)
		addi $sp, $sp,-4 
		sw $s2, 0($sp)
		
		addi $s1,$0,60
		addi $s2,$0,24
			
		la $v0, secondsMejora2
		lw $a0, 0($v0)		
		addi $a0, $a0, 1
		beq $a0, $s1, minutesUpdateMejora2 # Si hemos llegado al segundo 60, actualizamos variable
		sw $a0, 0($v0)
		j doneMejora2

minutesUpdateMejora2:		
		addi $a0, $0, 0 # Ponemos a 0 la variable seconds 
		sw $a0, 0($v0)
		la $v0, minutesMejora2
		lw $a0, 0($v0)
		addi $a0, $a0, 1
		beq $a0, $s1, hoursUpdateMejora2 # Si hemos llegado al minuto 60, actualizamos variable
		sw $a0, 0($v0)
		j doneMejora2

hoursUpdateMejora2:		
		addi $a0, $0, 0 # Ponemos a 0 la variable minutes
		sw $a0, 0($v0)
		la $v0, hourMejora2
		lw $a0, 0($v0)
		addi $a0, $a0, 1
		beq $a0, $s2, resetMejora2 # Si llegamos a la hora 24, actualizamos variable
		sw $a0, 0($v0)
		j doneMejora2

resetMejora2:			
		addi $a0, $0, 0 # Ponemos a 0 la variable hour
		sw $a0, 0($v0)
	
doneMejora2:
		li $v0, 4		
		la $a0, tiempoMejora2
		syscall
		
		la $v0, hourMejora2
		lw $a0, 0($v0)
		li $v0, 1
		syscall
	
		li $v0, 4
		la $a0, x5
		syscall
	
		la $v0, minutesMejora2
		lw $a0, 0($v0)
		li $v0, 1
		syscall
		
		li $v0, 4
		la $a0, x5
		syscall
	
		la $v0, secondsMejora2
		lw $a0, 0($v0)
		li $v0, 1
		syscall
				
		addi $t3,$0,0
		mtc0 $t3,$9
		li $a0,0x0d
		jal PrintCharacter
	
		lw $s2, 0($sp)
		addi $sp, $sp,4
		lw $s1, 0($sp)
		addi $sp, $sp,4
		lw $31, 0($sp)
		addi $sp, $sp,4
	
		j endTimerIntr
	
# ---------------------------------------------------------------------------------------------------------------------------
# ------------- MEJORA 3 : Temporizador -------------------------------------------------------------------------------------
	
mejora3:
		li $v0, 4
		la $a0, mejora3Frase
		syscall 
		
		li $v0,4
		la $a0, fraseMejora3
		syscall 
		
    	jal KbdIntrEnable
		jal TimerIntrEnable
	
		j fin 
			
KbdIntrMejora3:
		addi $s2, $0, 17 	# Ctrl + Q = Question : Preguntamos por un tiempo nuevo
		addi $s1,$0,19  	# Ctrl + S = Stop : Paramos el temporizador
		lw $s0, tdata
		
		beq $s1,$s0, fin		
		beq $s2, $s0, getTime 	
		
		lw $a0, tdata
		jal PrintCharacter
		
		j endKbdIntr
	
doneMejora3:
		li $v0, 4		
		la $a0, tiempo
		syscall
		
		la $v0, hour
		lw $a0, 0($v0)
		li $v0, 1
		syscall
	
		li $v0, 4
		la $a0, x5
		syscall
	
		la $v0, minutes
		lw $a0, 0($v0)
		li $v0, 1
		syscall
		
		li $v0, 4
		la $a0, x5
		syscall
	
		la $v0, seconds
		lw $a0, 0($v0)
		li $v0, 1
		syscall
			
		# Restore de Count ($9) 
		addi $t3,$0,0
		mtc0 $t3,$9
		
		li $a0,0x0d 
		jal PrintCharacter
	
		j endTimerIntr
	
	
TimerIntrMejora3:
		jal checkTime # Comprobamos si el tiempo actual es 0:0:0
	
		la $v0, seconds	
		lw $a0, 0($v0)
		beqz $a0, minutesUpdateMejora3
		addi $a0, $a0, -1 
		sw $a0, 0($v0)
	
		j doneMejora3

minutesUpdateMejora3:		
		addi $a0, $0, 59 # Sumamos 59 a los segundos
		sw $a0, 0($v0)
		la $v0, minutes
		lw $a0, 0($v0)
		beqz $a0, hoursUpdateMejora3
		addi $a0, $a0, -1
		sw $a0, 0($v0)
		j doneMejora3

hoursUpdateMejora3:		
		addi $a0, $0, 59 # Sumamos 59 al minutero
		sw $a0, 0($v0)
		la $v0, hour
		lw $a0, 0($v0)
		addi $a0, $a0, -1
		sw $a0, 0($v0)
	
		j endTimerIntr

getTime:
		li $v0, 4
		la $a0, x6
		syscall
		
		addi $s0,$0,23
		li $v0, 5
		syscall
		
		addi $s0,$0,23
		li $v0, 5
		syscall
		
		bgt $v0,$s0,notAnHour
		blt $v0,$0,notAnHour
		sw $v0,hour
		
		j introduceMinute
	
# checkTime : Comprueba si hemos llegado a las 0:0:0
checkTime:
		la $v0, seconds	
		lw $a0, 0($v0)	
		bnez $a0, salir
    
		la $v0, minutes	
		lw $a0, 0($v0)	
		bnez $a0, salir
	
		la $v0, hour	
		lw $a0, 0($v0)	
		bnez $a0, salir
	
		j fin
	
salir:
		jr $31
	
# ---------------------------------------------------------------------------------------------------------------------------
# ----------- MEJORA 4 : Velocidad de mecanografía --------------------------------------------------------------------------

TimerIntrEnableMejora4:
		mtc0 $0,$9 # Inicializamos Count Register
		mfc0 $t3,$12
		ori $t3,$t3,0x8001 	
    	mtc0 $t3,$12 		
		addi $t3,$0, 6000 # Teoricamente equivale a 1 minuto
		mtc0 $t3,$11 
		jr $31 
		
mejora4:
		li $v0, 4
		la $a0, mejora4Frase
		syscall 
	
    	jal KbdIntrEnable 
		jal TimerIntrEnableMejora4
	
		j fin 
		
		
KbdIntrMejora4:
		# Aumentamos en 1 el contador de letras
		la $v0, countMejora4
		lw $a0, 0($v0)
		addi $a0, $a0, 1
		sw $a0, 0($v0)

		lw $a0, tdata
		jal PrintCharacter
	
		j endKbdIntr
	
TimerIntrMejora4:
		jal obtenerResultado # Imprimimos resultado 
		j endTimerIntr
	
obtenerResultado:
		li $v0, 4
		la $a0, resultMejora4
		syscall
		
		la $v0, countMejora4
		lw $a0, 0($v0)
		li $v0, 1
		syscall
	
		j fin
	
# ---------------------------------------------------------------------------------------------------------------------------
# -------------- MEJORA 5 : Trap inversor de cadena de texto ----------------------------------------------------------------
	
mejora5:
		li $v0, 4
		la $a0, mejora5Frase
		syscall 
	
		la $t6, 0x10001000
		
		jal KbdIntrEnable
		jal ReadCharacter
		jal KbdIntrEnable
		
		j fin

PrintCharacterMejora5:
		lw $s4, pcntrl
		andi $s5,$s4,1
		beq $s5, $0, PrintCharacter
		sw $a0, pdata
				
		sw $a0, buffer($t7)
		addi $t7, $t7, 4
	
		jr $31
	
TrapException:
		
		li $v0, 4
		la $a0, trapMessage
		syscall
		
inversa:
		lw $a0, buffer($t7)
		
		lw $s4, pcntrl
		andi $s5,$s4,1
		beq $s5, $0, inversa
		sw $a0, pdata
		
		sw $0, buffer($t7) # Vaciamos esta posicion del buffer tras imprimir el caracter
		addi $t7, $t7, -4
		
		la $t5, buffer($t7)
		
		bne $t6, $t5, inversa
		
		la $a0, salto
		li $v0, 4
		syscall
	
		add $t7, $0, $0 # Restore de la variable posicion 
	
		j endKbdIntr
	
generarTrapException:
		teq $0, $0
		jr $31
		
KbdIntrMejora5:
		addi $sp, $sp,-4 
		sw $31, 0($sp)
		addi $sp, $sp,-4 
		sw $s0, 0($sp)
		addi $sp, $sp,-4 
		sw $s1, 0($sp)
		addi $sp, $sp,-4 
		sw $s2, 0($sp)
		
		addi $s1,$0,20  	#Ctrl + T
		lw $s0, tdata
		
		beq $s1, $s0, generarTrapException

		lw $a0, tdata	
		jal PrintCharacterMejora5

		j endKbdIntr
	
# ---------------------------------------------------------------------------------------------------------------------------
# ----------- MEJORA 6 : Sucesión de Fibonacci ------------------------------------------------------------------------------

mejora6:
		li $v0, 4
		la $a0, mejora6Frase
		syscall 
	
		li $t2, 2 
		
		sw $0, fibo1($0)
		addi $a0, $0, 1
		sw $a0, fibo2($0)
		
		li $v0, 4
		la $a0, modo 
		syscall 
		
		jal KbdIntrEnable

		j fin 
	
imprime: # Imprime el número 'x' de la sucesión de Fibonacci
		lw $a0, fibo2($0)
		li $v0, 1
		syscall
	
		li $v0, 4
		la $a0, espacio
		syscall 
	
		j bucle_fibo
 	
	
bucle_fibo: # Bucle que calcula la sucesión de Fibonacci

		lw $t4, fibo($0)
		lw $t5, fibo1($0)
		lw $t6, fibo2($0)
		add $t7, $t5, $t6
		bge $t7, $t4, fin # Si la suma es superior que el límite terminamos la impresión de la sucesión
		
		sw $t6, fibo1($0)
		sw $t7, fibo2($0)
	
		jr $31

		
# Si imprimimos Fibonacci en modo 'normal', se imprime hasta el numero	
# anterior del límite superior impuesto
			
fiboNormal: 
		jal bucle_fibo
		j imprime 

# fiboPar() : comprueba si el resto de la división del número 'x' 
# de la sucesión entre 2 es 0, por tanto 'x' es par.
	
fiboPar:
		jal bucle_fibo
	
		div $t7, $t2
		mfhi $a0
	
		bnez $a0, bucle_fibo
		j imprime 
	
# fiboImpar() : comprueba si el resto de la división del número 'x' 
# de la sucesión entre 2 es distinto de 0, por tanto 'x' es impar.

fiboImpar:
		jal bucle_fibo
	
		div $t7, $t2
		mfhi $a0
	
		beqz $a0, bucle_fibo
		j imprime 

KbdIntrMejora6:
		addi $sp, $sp,-4 
		sw $31, 0($sp)
		addi $sp, $sp,-4 
		sw $s0, 0($sp)
		addi $sp, $sp,-4 
		sw $s1, 0($sp)
		
		lw $s0, tdata	
		
		addi $s1, $0,14  	# Sucesion Fibonacci Normal 	
		beq $s1,$s0, fiboNormal
		
		addi $s1,$0,16  	# Sucesion Fibonacci Par 
		beq $s1,$s0, fiboPar
		
		addi $s1,$0,9  	# Sucesion Fibonacci Impar 
		beq $s1,$s0, fiboImpar
		
		j endKbdIntr