; DO NOT ADD ANY LINES THAT BEGIN WITH @plugin OR YOU RISK GETTING A ZERO FOR THIS PART.

; Author: Dan Sun
; Gtid: 902922711

.orig x3000
		LD R0, A				; Load the value of a into R0
		LD R1, B				; Load the value of b into R1
		BRz IF					; if b = 0
		AND R2, R2, #0				; R2 - quotient
		
LOOP		NOT R3, R1				; comparing a and b
		ADD R3, R3, #1				; by adding a and -b
		ADD R3, R0, R3				; and store the a-b into R3
		BRn DONE				; if a < b, exit the while loop
		ADD R2, R2, #1				; increment R2 by 1
		AND R0, R0, #0				; a = a - b
		ADD R0, R0, R3				; by transferring value from R3 (a-b) to R0 (a)
		BRzp LOOP

DONE		ST R2, QUOTIENT				; store R2 into QUOTIENT
		ST R0, REMAINDER			; store R0 into REMAINDER

					
IF		ADD R2, R2, #-1				; quotient = -1

		HALT					; Stop program x300F

		A .fill 16				; Initialize U x3012
		B .fill 12				; Initialize V x3013
		QUOTIENT .blkw 1			; Store your quotient here
		REMAINDER .blkw 1			; Store your remainder here
.end

