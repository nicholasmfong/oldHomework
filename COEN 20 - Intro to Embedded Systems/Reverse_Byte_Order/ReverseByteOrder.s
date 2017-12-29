		.syntax	unified         //Nicholas Fong Coen 20 Lab 10 Lewis
		.arch	armv7-m
		.text
		.thumb_func
		.align	2

// ------------------------------------------------------------------------------------------
// uint32_t ReverseByteOrder(uint32_t word)
// ------------------------------------------------------------------------------------------

		.globl  ReverseByteOrder
ReverseByteOrder:

		// On entry: R0 = word
		// Byte 0 is LSB, Byte 3 is MSB
		// Insert your code here

        LSL R1, R0, #24             // Puts Byte 0 into Byte 3
        ORR R1, R1, R0, LSR #24     //Puts Byte 3 into Byte 0
        AND R2, R0, 0x0000FF00      //Gets Byte 1 and Byte 1 only
        ORR R1, R1, R2, LSL #8      //Puts Byte 1 in Byte 2's spot
        AND R2, R0, 0x00FF0000      //Gets Byte 2 and Byte 2 only
        ORR R0, R1, R2, LSR #8      //Puts Byte 2 in Byte 3's spot
		BX	LR		                // Return result in R0

		.end
