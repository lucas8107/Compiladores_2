.data
	string_2: .asciiz "X é maior que 3 e menor que 10\n"
	string_1: .asciiz "X é menor ou igual a 3 ou maior ou igual a 10"
	string_0: .asciiz "Entre com o x: "
	x: .word 0
.text
	la $a0, x
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 0
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
	li $v0, 4
	la $a0, string_0
	syscall
	li $v0, 5
	syscall
	sw $v0, x
	lw $a0, x
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 3
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sle $a0, $t1, $a0
	sw $a0, 4($sp)
	lw $a0, x
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 10
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sge $a0, $t1, $a0
	sw $a0, 4($sp)
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sne $t1, $t1, $zero
	sne $a0, $a0, $zero
	or $a0, $a0, $t1
	sw $a0, 4($sp)
	addiu $sp, $sp, 4
	lw $t1, 0($sp)
	beqz $t1, else_init0
	li $v0, 4
	la $a0, string_1
	syscall
	j else_end0
else_init0:
	li $v0, 4
	la $a0, string_2
	syscall
else_end0:
	li $v0, 10
	syscall
