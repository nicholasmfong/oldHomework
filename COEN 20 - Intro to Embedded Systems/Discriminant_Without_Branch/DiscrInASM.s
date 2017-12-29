		.syntax	unified         //Nicholas Fong Lab 6 Coen 20 Lewis
		.arch	armv7-m
		.text
		.thumb_func
		.align	2

// ------------------------------------------------------------------------------------------
// int32_t DiscrInASM(int32_t a, int32_t b, int32_t c)
// ------------------------------------------------------------------------------------------

		.globl  DiscrInASM
DiscrInASM:

	// The first parameter (a) is passed to this function in R0.
	// The second parameter (b) is passed to this function in R1.
	// The third parameter (c) is passed to this function in R2.
	// The function should return the result in R0.

	// Registers R0 through R3 may be modified without
	// preserving their original content. However, the
	// value of all other registers must be preserved!

	// Insert your code here ...
        MUL R1, R1, R1  //turn b into b^2
        LSL R0, R0, #2  //multiplies a by 4
        MUL R0, R0, R2  //puts AC into R0
        SUB R0, R1, R0  //calculates the difference (b^2 - 4AC)
		BX	LR		            // return

		.end
