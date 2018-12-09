.data
	string_1: .asciiz "It works\n"
	string_0: .asciiz "If wont execute\n"
	x: .word 0
.text
	la $a0, x
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 2
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
	li $v0, 4
	la $a0, string_0
	syscall
	lw $a0, x
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 4
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sge $a0, $t1, $a0
	sw $a0, 4($sp)
	addiu $sp, $sp, 4
	lw $t1, 0($sp)
	beqz $t1, if_end0
	li $v0, 4
	la $a0, string_1
	syscall
if_end0:
	li $v0, 10
	syscall
