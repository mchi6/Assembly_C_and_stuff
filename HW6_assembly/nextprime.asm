; Author: Dan Sun
; GtId: 902922711

.orig x3000
	LD		R0, K				; R0 - k
	LD		R1, FOUND			; R1 - found

WHILE	BRp		DONE				; if found = 1, exit the loop
	ADD		R0, R0, #1			; increment k
	ST		R0, K				; store incremented R0 into K
	LD		R3, I				; R3 - i
	ST		R3, I2
	LD		R2, ISPRIME			; R2 - isprime
	ST		R2, ISPRIME2
FOR	BRz		FOREND				; if isPrime = 0, exit for loop
	AND		R4, R4, #0			; R4 - k-2*i
	ADD 		R4, R3, R3			; compute 2*i
	NOT		R4, R4				; compute -2*i
	ADD		R4, R4, #1			
	ADD		R4, R0, R4			; compute k-2*i
	BRnz		FOREND				; if k-2*i <= 0, exit for loop
	LD		R5, I2				; R5 - k-i (first time)
	NOT		R5, R5				; compute -i
	ADD		R5, R5, #1
	ADD		R5, R5, R0			; compute k-i
MOD	BRn		MODEND				; if k < i, exit MOD
	ADD		R2, R5, #0			; R2 - k-=i		
	LD		R5, I2				; R5 - k-i (later times)
	NOT		R5, R5				; compute -i
	ADD		R5, R5, #1			
	ADD		R5, R5, R2			; compute k-i
	BRnzp		MOD
MODEND	ADD		R3, R3, #1			; increment i
	ST		R3, I2	
	ST		R2, ISPRIME2			; isPrime = k % i
	LD		R2, ISPRIME2
	BRnzp		FOR		
FOREND	LD		R1, ISPRIME2			; found = isPrime
	ST		R1, FOUND
	BRnzp		WHILE
DONE	ST		R0, NEXTPRIME			; store R0 into NEXTPRIME
	HALT

	K		.fill	5			; K
	I		.fill	2			; I
	ISPRIME		.fill	1			; ISPRIME
	FOUND		.fill	0			; FOUND
	NEXTPRIME	.blkw 	1			; NEXTPRIME
	I2		.blkw	1			; temp for i
	ISPRIME2	.blkw	1			; temp for isPrime

.end
