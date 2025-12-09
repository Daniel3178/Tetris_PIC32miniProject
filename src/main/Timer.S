
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw \reg,0($sp)
.endm

.macro	POP reg
	lw	 \reg,0($sp)
	addi	$sp,$sp,4
.endm

.data
.align 2
.global enable_interrupts
.global delay
.global memcpy
.text

enable_interrupts:
	ei

	jr $ra
	nop

delay: 
    move $t0, $a0   # t0 = arg
    li $t1, 0    # i = 0;
    lui $t2, 0x0043   # length = 0x00430000
    ori $t2, $t2, 0x0000
    j while
    nop

    while:
        slti $t3, $t0, 0     #set true if i < 0;
        bne $t3, $0, breakLoop  #if true, break
        nop
        addi $t0, $t0, -1
        j for
        nop
    
        for:
            beq $t1, $t2, end   #if i == length, end
            nop
            addi $t1, $t1, 1
            j for
            nop
        end:
            j while
            nop
    breakLoop:
        jr $ra
        nop
memcpy:
# check if aligned
    andi $t0,$a0,3
    andi $t1,$a1,3
    or $t0,$t0,$t1
    bne $t0,$zero,byteloop
    nop
#copy word by word
    wordloop:
        slti $t0,$a2,4 # check if fewer than 4 bytes
        bne $t0,$zero,byteloop
        nop
        lw $t0,0($a0) # load word
        sw $t0,0($a1) # store word
        addi $a0,$a0,4 # increment src pointer
        addi $a1,$a1,4 # increment dst pointer
        addi $a2,$a2,-4 # decrement counter
        j wordloop
        nop
# standard, byte by byte of the rest
    byteloop:
        beq $a2,$zero,done # branch if done
        lb $t0,0($a0) # load byte
        sb $t0,0($a1) # store byte
        addi $a0,$a0,1 # increment src pointer
        addi $a1,$a1,1 # increment dst pointer
        addi $a2,$a2,-1 # decrement counter
        j byteloop
        nop
    done:
        jr $ra
        nop