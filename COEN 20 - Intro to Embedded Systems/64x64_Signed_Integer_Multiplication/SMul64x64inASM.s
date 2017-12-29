		.syntax	unified     //Nicholas Fong Lewis Coen 20 Lab 9 11/18/15
		.arch	armv7-m
		.text
		.thumb_func
		.align	2

// ------------------------------------------------------------------------------------------
// int64_t SMul64x64inASM(int64_t a, int64_t b)
// ------------------------------------------------------------------------------------------

		.globl  SMul64x64inASM
SMul64x64inASM:

	// The two parameters are passed to this function as follows:
	//
	// a<63..32> is in register R1; a<31..0> is in register R0
	// b<63..32> is in register R3; b<31..0> is in register R2
	//
	// Bits 63..32 of the product must be returned in register R1
	// Bits 31..0 of the product must be returned in register R0
	//
	// The value of all other registers must be preserved!

	// Insert your code here ...
        PUSH {R4}
        MUL R4, R1, R2        //Ahi * Blo       , Can use MUL since we throw away 32 MSB anyways
        MUL R1, R0, R3        //Alo * Bhi       , stored the results away in weird locations to use less registers
        ADD R3, R4, R1        //Add the 2 together
        UMULL R0, R1, R0, R2  //Alo * Blo
        ADD R1, R1, R3        //MSB Alo*Blo + LSB (Alo*Bhi+AhiBlo)
        POP {R4}
		BX	    LR		    	// Return to calling program.

        	.end
