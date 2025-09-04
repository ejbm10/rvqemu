.section .text

.globl tea_encrypt

tea_encrypt:
	li s2, 0x9e3779b9 	    # Constante DELTA
	li s3, 32				# Rondas
	li s4, 0				# sum = 0
	
	lw t0, 0(a0)			# v0 = v[0]
	lw t1, 4(a0)		    # v1 = v[1]
    
_loop:
	# Primera linea del loop
	add s4, s4, s2
	
	lw t2, 0(a1)			# key[0]
	lw t3, 4(a1)			# key[1]
	# Segunda linea del loop
	slli t4, t1, 4
	add t4, t4, t2
	add t5, t1, s4
	srli t6, t1, 5
	add t6, t6, t3
	xor t4, t4, t5
	xor t4, t4, t6
	add t0, t0, t4
	
	lw t2, 8(a1)			# key[2]
	lw t3, 12(a1)			# key[3]
	# Tercera linea del loop
	slli t4, t0, 4
	add t4, t4, t2
	add t5, t0, s4
	srli t6, t0, 5
	add t6, t6, t3
	xor t4, t4, t5
	xor t4, t4, t6
	add t1, t1, t4
	
	# Decremento del contador
	addi s3, s3, -1
	bnez s3, _loop

_finish:
	# Guarda resultado
	sw t0, 0(a0)
	sw t1, 4(a0)
    ret