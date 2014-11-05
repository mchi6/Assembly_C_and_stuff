; Name: Dan Sun


; Main
; Do not edit this function!

.orig x3000

	LD R6, STACK	; Initialize the stack

	LEA R0, STRING	; R0 = &str[0]
	ADD R1, R0, 0

SL_LOOP	LDR R2, R1, 0	; \ R1 = strlen(str)
	BRz SL_END	; |
	ADD R1, R1, 1	; |
	BR SL_LOOP	; |
SL_END	NOT R2, R0	; |
	ADD R2, R2, 1	; |
	ADD R1, R1, R2	; /

	ADD R6, R6, -2	; \ R0 = eval(str, len)
	STR R0, R6, 0	; |
	STR R1, R6, 1	; |
	LD R2, EVALPTR	; |
	JSRR R2		; |
	LDR R0, R6, 0	; |
	ADD R6, R6, 3	; /

	ST R0, ANS
	HALT

STACK	.fill xf000
ANS	.fill -1
EVALPTR	.fill EVAL
STRING	.stringz "9+8+7+6*5+4+3+2+1"
	.blkw 200

EVAL
	ADD R6, R6, -4		; Build a new stack frame
	STR R7, R6, 2		; Store return address
	STR R5, R6, 1		; Store old FP
	ADD R5, R6, 0		; New FP

	ADD R6, R6, -2		; Leave room for 3 local variables (right R6-0, left R6-1, i R6-2)
	;; End of stack initialization
	
	AND R2, R2, 0		; Initialize i
	STR R2, R5, 0		; Save i
ADDI
	LDR R1, R5, 5		; Get len
	NOT R1, R1		; Calculate i-len
	ADD R1, R1, 1
	LDR R2, R5, 0		; Get i
	ADD R1, R1, R2
	BRzp ADDI_END 		; if i >= len, exit the loop
	
IF1
	LDR R0, R5, 4		; Get str
	LDR R2, R5, 0		; Get i
	ADD R0, R0, R2		; Calculate str+i
	LDR R0, R0, 0		; Get *(str+i)
	ADD R0, R0, -15		; Get *(str+i)-'+'
	ADD R0, R0, -15
	ADD R0, R0, -13
	BRnp IF1_END		; if *(str + i) != '+', go to IF1_END

LEFT1
	ADD R6, R6, -2		; Store str and i
	LDR R0, R5, 4		; Get str (R0)
	LDR R2, R5, 0		; Get i (R1)
	STR R0, R6, 0		; Store str
	STR R2, R6, 1		; Store i
	JSR EVAL
	LDR R0, R6, 0		; Save left result
	LDR R5, R5, 1		; Restore R5
	STR R0, R5, -2		; Store left
	ADD R6, R6, -5		; Restore the position of R6, but not R5
	
RIGHT1
	ADD R6, R6, -2		; Store str+i+1 and len-i-1
	LDR R0, R5, 4		; Get str
	LDR R1, R5, 5		; Get len
	LDR R2, R5, 0		; Get i
	ADD R2, R2, 1		; Calculate i+1
	ADD R0, R0, R2		; Calculate str+i+1 (R0)
	NOT R2, R2		; Calculate len-i-1 (R1)
	ADD R2, R2, 1
	ADD R1, R1, R2
	STR R0, R6, 0		; Store str+i+1
	STR R1, R6, 1		; Store len-i-1
	JSR EVAL
	LDR R0, R6, 0		; Save right result
	LDR R5, R5, 1		; Restore R5
	STR R0, R5, -1		; Store right
	
SUM	LDR R0, R5, -2		; Save left
	LDR R1, R5, -1		; Save right
	ADD R0, R0, R1		; left+right
	BR RETURN
IF1_END	
	LDR R2, R5, 0		; Get i
	ADD R2, R2, 1		; increment i
	STR R2, R5, 0		; Store incremented i
	BR ADDI
ADDI_END
	AND R2, R2, 0		; Initialize i
	STR R2, R5, 0		; Save i

MULTI
	LDR R1, R5, 5		; Get len
	NOT R1, R1		; Calculate i-len
	ADD R1, R1, 1
	LDR R2, R5, 0		; Get i
	ADD R1, R1, R2
	BRzp MULTI_END 		; if i >= len, exit the loop
	
IF2
	LDR R0, R5, 4		; Get str
	LDR R2, R5, 0		; Get i
	ADD R0, R0, R2		; Calculate str+i
	LDR R0, R0, 0		; Get *(str+i)
	ADD R0, R0, -15		; Get *(str+i)-'+'
	ADD R0, R0, -15
	ADD R0, R0, -12
	BRnp IF2_END		; if *(str + i) != '+', go to IF2_END

LEFT2
	ADD R6, R6, -2		; Store str and i
	LDR R0, R5, 4		; Get str (R0)
	LDR R2, R5, 0		; Get i (R1)
	STR R0, R6, 0		; Store str
	STR R2, R6, 1		; Store i
	JSR EVAL
	LDR R0, R6, 0		; Save left result
	LDR R5, R5, 1		; Restore R5
	STR R0, R5, -2		; Store left
	ADD R6, R6, -5		; Restore the position of R6, but not R5
	
RIGHT2
	ADD R6, R6, -2		; Store str+i+1 and len-i-1
	LDR R0, R5, 4		; Get str
	LDR R1, R5, 5		; Get len
	LDR R2, R5, 0		; Get i
	ADD R2, R2, 1		; Calculate i+1
	ADD R0, R0, R2		; Calculate str+i+1 (R0)
	NOT R2, R2		; Calculate len-i-1 (R1)
	ADD R2, R2, 1
	ADD R1, R1, R2
	STR R0, R6, 0		; Store str+i+1
	STR R1, R6, 1		; Store len-i-1
	JSR EVAL
	LDR R0, R6, 0		; Save right result
	LDR R5, R5, 1		; Restore R5
	STR R0, R5, -1		; Store right
	
	LDR R0, R5, -2		; Save left
	LDR R1, R5, -1		; Save right
	AND R2, R2, 0		; Initialize j
	AND R4, R4, 0		; Initialize sum
MUT	NOT R3, R1		; Calculate j-right
	ADD R3, R3, 1
	ADD R3, R3, R2
	BRzp MUT_END		; if j>=right, exit the while loop
	ADD R4, R4, R0		; sum+=left
	ADD R2, R2, 1		; Increment j
	BR MUT
MUT_END
	ADD R0, R4, 0		; R0=left*right
	BR RETURN
IF2_END	
	LDR R2, R5, 0		; Get i
	ADD R2, R2, 1		; increment i
	STR R2, R5, 0		; Store incremented i
	BR MULTI
MULTI_END
	LDR R0, R5, 4		; Get str
	LDR R0, R0, 0		; Get *str
	ADD R0, R0, -15		; Calculate *str-'0'
	ADD R0, R0, -15
	ADD R0, R0, -15
	ADD R0, R0, -3

RETURN 
	STR R0, R5, 3		; Store RV
	LDR R7, R5, 2		; Restore RA
	ADD R6, R5, 3		; Point SP at RV
	RET
.end
