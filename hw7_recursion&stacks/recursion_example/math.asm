.orig x3000
	LD R6, STACK	; Initialize the stack
	LD R0, X
	STR R0, R6, 0	; Put first parameter on stack
	LD R1, MATHPTR	;
	JSRR R1			; Start recursive call
	LDR R0, R6, 0	;
	ADD R6, R6, 1	;

	ST R0, ANS
	HALT

STACK	.fill xf000
ANS	.fill -1
MATHPTR	.fill MATH
X .fill 10
	.blkw 200

MATH               
	ADD R6, R6, -4	; allocate space for new frame
	STR R5, R6, 1	; store old frame pointer
	ADD R5, R6, 0	; R5 -> first local variable
	STR R7, R5, 2 	; store return address

	AND R0, R0, 0	; R0 = 0
	STR R0, R5, 0	; i = 0

	LDR R1, R5, 4	; R1 = x
	BRZ BASE
	ADD R1, R1, -1	; R1 = x-1
	ADD R6, R6, -1 	; start a new frame
	STR R1, R6, 0	; put x-1, the first parameter, on stack
	JSR MATH
	LDR R0, R6, 0	; R0 = sum(x-1)
	STR R0, R5, 0	; i = sum(x-1)
	ADD R0, R0, R0	; R0 = 2i
	BR RETURN

BASE
	AND R0, R0, 0	;
	ADD R0, R0, 1 	; ready to return 1

RETURN
	STR R0, R5, 3	; save return value
	LDR R7, R5, 2 	; restore return address
	ADD R6, R5, 3	; R6 -> return value
	LDR R5, R5, 1	; restore R5
	RET
.end
