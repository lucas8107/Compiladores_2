.data
	string_2: .asciiz "\n"
	string_1: .asciiz "A resposta é: "
	aux: .word 0
	string_0: .asciiz "Entre com o indice: "
	target: .word 0
	b: .word 0
	a: .word 0
.text
	la $a0, a
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 1
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
	la $a0, b
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 1
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
	la $a0, target
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
	sw $v0, target
	la $a0, target
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	lw $a0, target
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 2
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	subu $a0, $t1, $a0
	sw $a0, 4($sp)
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
	la $a0, aux
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 0
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
while_0:
	lw $a0, target
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	li $a0, 0
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sgt $a0, $t1, $a0
	sw $a0, 4($sp)
	addiu $sp, $sp, 4
	lw $t1, 0($sp)
	beqz $t1, while_out_0
	la $a0, aux
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	lw $a0, a
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	lw $a0, b
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	addu $a0, $a0, $t1
	sw $a0, 4($sp)
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
	la $a0, a
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	lw $a0, b
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
	la $a0, b
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	lw $a0, aux
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	addiu $sp, $sp, 4
	lw $t1, 4($sp)
	sw $a0, ($t1)
	la $a0, target
	sw $a0, 0($sp)
	addiu $sp, $sp, -4
	lw $a0, target
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
	lw $a0, b
	syscall
	li $v0, 4
	la $a0, string_2
	syscall
	li $v0, 10
	syscall
