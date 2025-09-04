.section .data
_coded:
	.word 0x7FD37400, 0xC153C5EE
_key:
	.word 0x12345678, 0x9ABCDEF0, 0xFEDCBA98, 0x76543210

.section .text

.global tea_decrypt

tea_decrypt:
	la s0, _coded
	la s1, _key
	li s2, 0x9e3779b9 	    # Constante DELTA
	li s3, 32				# Rondas
	mul s4, s2, s3			# sum = DELTA * 32
	
	lw t0, 0(s0)			# v0 = v[0]
	lw t1, 4(s0)		    # v1 = v[1]
_loop:
	# Primera linea del loop
	lw t2, 8(s1)			# key[2]
	lw t3, 12(s1)			# key[3]
	slli t4, t0, 4
	add t4, t4, t2
	add t5, t0, s4
	srli t6, t0, 5
	add t6, t6, t3
	xor t4, t4, t5
	xor t4, t4, t6
	sub t1, t1, t4
	
	# Segunda linea del loop
	lw t2, 0(s1)			# key[0]
	lw t3, 4(s1)			# key[1]
	slli t4, t1, 4
	add t4, t4, t2
	add t5, t1, s4
	srli t6, t1, 5
	add t6, t6, t3
	xor t4, t4, t5
	xor t4, t4, t6
	sub t0, t0, t4
	
	# Tercera linea
	sub s4, s4, s2
	
	# Decremento del contador
	addi s3, s3, -1
	bgez s3, _loop
	
	# Guarda resultado
	sw t0, 0(s0)
	sw t1, 4(s0)
_end:
	j _end