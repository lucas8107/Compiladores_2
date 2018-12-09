.data
	string_0: .asciiz " "
	n: .word 0
.text
	la $a0, n
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 0
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
while_0:
	lw $a0, n
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 20
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	slt $a0, $t1, $a0
	sw $a0, 4($sp)
	addiu $sp, $sp, 4
	lw $t1, 0($sp)
	beqz $t1, while_out_0
	lw $a0, n
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 2
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	div $a0, $t1, $a0
	mfhi $a0
	sw $a0, 4($sp)
	li $a0, 0
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	seq $a0, $a0, $t1
	sw $a0, 4($sp)
	addiu $sp, $sp, 4
	lw $t1, 0($sp)
	beqz $t1, if_end0
	li $v0, 4
	la $a0, string_0
	syscall
	li $v0, 1
	lw $a0, n
	syscall
if_end0:
	la $a0, n
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	lw $a0, n
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 1
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	addu $a0, $a0, $t1
	sw $a0, 4($sp)
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
	j while_0
while_out_0:
	li $v0, 10
	syscall
