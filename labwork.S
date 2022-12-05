  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
.global delay
.global time2string
.global enable_interrupt
.set noat

hexasc:
      
     la    $t3, ($a0)
     
      slti    $t5,$a0,10
      beq    $t5,$0,false
      nop
      addi    $v0,$t3,48
      
      jr    $ra
      nop
  false:
      addi    $v0,$t3,55
      jr    $ra
      nop
      
  delay:
    li    $t0,1000            #time in ms to delay
    li    $t1,0             #i from the c example
    li    $t2,3800        #easily changed constant
    j    whileLoop
    
whileLoop:
    sub     $t0,$t0,1
    slti     $t5,$t0,0
    bne    $t5,$0,whileDone
    
    
    li    $t1,0
    slt     $t6,$t1,$t2    #change here to change for loop iteration count
    bne     $t6,$0,forLoop
    j    whileLoop
    
forLoop:
    slt     $t6,$t1,$t2    #change here to change for loop iteration count
    beq     $t6,$0,whileLoop
    addi    $t1,$t1,1
    j     forLoop
    
whileDone:
jr     $ra
nop
          
  time2string:
  PUSH $ra
  PUSH $a0
  
  sll $t4,$a1,0x10
  PUSH $a1
  srl $a0,$t4,0x1c #first number (read left ro tight)
  jal hexasc
  nop
  POP $a1
  PUSH        $v0
  
  
  sll $t4,$a1,0x14
  PUSH $a1
  srl $a0,$t4,0x1c #second number (read left ro tight)
  jal hexasc
  nop
  POP $a1
  PUSH        $v0
 
  
  sll $t4,$a1,0x18
  PUSH $a1
  srl $a0,$t4,0x1c #first number (read left ro tight)
  jal hexasc
  nop
  POP $a1
  PUSH $v0

  
  sll $t4,$a1,0x1c
  PUSH $a1
  srl $a0,$t4,0x1c #first number (read left ro tight)
  jal hexasc
  nop
  POP $a1
  PUSH $v0

 
  POP $t0
  POP $t1
  POP $t2
  POP $t3
  POP $a0

  li    $t4,0x3a #:
  li    $t5,0x00 #null
 
  sb  $t3,0($a0)
  sb  $t2,1($a0)
  
  sb  $t4,2($a0)
  
  sb  $t1,3($a0)
  sb  $t0,4($a0)
  
  sb  $t5,5($a0)
   
 
  POP $ra
  
  jr    $ra
  nop

enable_interrupt:
    ei
jr    $ra
