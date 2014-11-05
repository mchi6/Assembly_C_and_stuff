; Do not add any comments beginning with @plugin

; Author: Dan Sun
; GtId: 902922711

.orig x3000
		LD 	R0, ARRAY_SIZE		; R0 - array_size
		LEA 	R1, ARRAY		; R1 - array address
			
		LD	R2, I			; R2 - i, initialize i

OUTER		ADD	R3, R0, #-1		; R3 - (i-n+1), calculate n-1
		NOT	R3, R3			; calculate -(n-1)
		ADD	R3, R3, #1		
		ADD	R3, R2, R3		; calculate i-(n-1)
		BRzp	OUTER_END		; if i >= n-1, exit the outer loop 
		ADD	R4, R2, #1		; R4 - j, initialize j
INNER		ADD	R3, R0, #0		; R3 - (j-n), reuse R3
		NOT	R3, R3			; calculate -n
		ADD	R3, R3, #1		
		ADD	R3, R4, R3		; calculate j-n
		BRzp	INNER_END		; if j >= n, exit the inner loop

BODY		ADD	R3, R1, R2		; R3 - address for a[i], reuse R3
		LDR	R5, R3, #0		; R5 - a[i]
		ADD	R3, R1, R4		; R3 - address for a[j], reuse R3
		LDR	R6, R3, #0		; R6 - a[j]
		ADD	R7, R6, #0		; R7 - a[i]-a[j]
		NOT	R7, R7			; calculate -a[j]
		ADD	R7, R7, #1		
		ADD	R7, R5, R7		; calculate a[i]-a[j]
		BRzp	BODY_END		; if a[i] >= a[j], exit the body

						; swap a[i] and a[j]
		AND	R7, R7, #0		; R7 - temp, reuse R7
		ADD	R7, R5, #0		; temp = a[i]
		ADD	R3, R1, R2		; R3 - address for a[i], reuse R3
		STR	R6, R3, #0		; a[i] = a[j]
		ADD	R3, R1, R4		; R3 - address for a[i], reuse R3
		STR	R7, R3, #0		; a[j] = temp

BODY_END	ADD	R4, R4, #1		; increment j
		BRnzp	INNER			; unconditionally go back to the inner loop

INNER_END	ADD	R2, R2, #1		; increment i
		BRnzp	OUTER			; unconditionally go back to the outer loop

OUTER_END

STOP		HALT				; Stop program

ARRAY_SIZE 	.fill 	5

ARRAY		.fill 	1
		.fill 	0
		.fill	4
		.fill 	2
		.fill	-1
I		.fill	0

.end
