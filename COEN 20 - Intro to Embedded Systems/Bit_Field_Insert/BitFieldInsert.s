		.syntax	unified     //Nicholas Fong Coen 20 Lab 8 Lewis 11-11-15
		.arch	armv7-m
		.text
		.thumb_func
		.align	2

// ------------------------------------------------------------------------------------------
// uint32_t BitFieldInsert(uint32_t word, int lsb, int width, uint32_t value)
// ------------------------------------------------------------------------------------------

		.globl  BitFieldInsert
BitFieldInsert:

		// On entry: R0 = word, R1 = lsb, R2 = width, R3 = value, R4 = mask, R5 = extra variable
        PUSH {R4,R5}
        LDR R4,=1           //mask = 1
		ADD R5, R1, R2      //R5 = lsb+width
		LSL R4, R4, R5      //mask = 1<<(lsb+width)
		LDR R5,=1
		LSL R5, R5, R1      //R5 = 1<<lsb
		SUB R4, R4, R5      //mask = (1 << (lsb+width)) - (1 << lsb)
		BIC R0, R0, R4      //word &= ~mask

		LDR R4,=1
		LSL R4, R4, R2      //mask = 1<<width
		SUB R4, R4, #1      //mask = (1<<width) -1
		AND R3, R3, R4      //value &= mask

		LSL R3, R3, R1      //value << lsb
		ORR R0, R0, R3      //word | value<<lsb
        POP {R4,R5}
		BX      LR		            // return result in R0

		.end
