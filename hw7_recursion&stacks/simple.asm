.orig x3000
	LD R0, A		;Store A into R0
	LD R1, B		;Store B into R1
	ADD R2, R0, R1		;A+B, and store in R2
	AND R3, R0, R1		;A&B, and store in R3
	NOT R4, R0		;get -A, and store in R4
	ADD R4, R4, 1
	ADD R5, R0, R0		;get 2*A, and store in R5
	ADD R6, R1, R1		;get 3*B, and store in R6
	ADD R6, R5, R1
	ADD R6, R5, R6		;calculate 2*A+3*B, and store it in R6
	LD R7, FAR
	STR R2, R7, 0		;put A+B at address x5001
	STR R3, R7, 1
	STR R4, R7, 2
	STR R6, R7, 3
	
	HALT

	A	.FILL	157
	B	.FILL	257
	FAR	.FILL	x5001	

.end
