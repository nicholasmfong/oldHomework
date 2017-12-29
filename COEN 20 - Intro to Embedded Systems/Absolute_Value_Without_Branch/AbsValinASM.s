		.syntax	unified         //Nicholas Fong Lab 6 Coen 20 Lewis
		.arch	armv7-m
		.text
		.thumb_func
		.align	2

// ------------------------------------------------------------------------------------------
// uint32_t AbsValinASM(int32_t x)
// ------------------------------------------------------------------------------------------

		.globl  AbsValinASM
AbsValinASM:

	// The first parameter (x) is passed to this function in R0.
	// The function should return the result in R0.

	// Registers R0 through R3 may be modified without
	// preserving their original content. However, the
	// value of all other registers must be preserved!

	// Insert your code here ...
        ASR R1, R0, #31 //put the MSB of R0 into R1
        EOR R0, R1, R0  //if R0 is negative, flip the sign since R1 should be all 1s
        LSR R1, R1, #31 //sets R1 as either 1 or 0
        ADD R0, R1, R0  //Add R1 to R0 (add 1 if R0 started out negative)
		BX	LR		            // return

		.end
