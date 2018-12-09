.data
	string_1: .asciiz "O factorial de n é: "
	string_0: .asciiz "Entre com o valor de n: "
	acc: .word 0
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
	la $a0, acc
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 1
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
	sw $v0, n
while_0:
	lw $a0, n
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 1
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sgt $a0, $t1, $a0
	sw $a0, 4($sp)
	addiu $sp, $sp, 4
	lw $t1, 0($sp)
	beqz $t1, while_out_0
	la $a0, acc
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	lw $a0, acc
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	lw $a0, n
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	mul $a0, $t1, $a0
	sw $a0, 4($sp)
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
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
	subu $a0, $t1, $a0
	sw $a0, 4($sp)
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
	j while_0
while_out_0:
	li $v0, 4
	la $a0, string_1
	syscall
	li $v0, 1
	lw $a0, acc
	syscall
	li $v0, 10
	syscall
