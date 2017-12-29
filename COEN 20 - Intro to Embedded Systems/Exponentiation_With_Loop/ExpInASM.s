		.syntax unified         //Nicholas Fong Coen 20 Lab 7 Lewis 11-4-15
		.arch	armv7-m
		.text
		.thumb_func
		.align	2

// ------------------------------------------------------------------------------------------
// int32_t ExpInASM(int32_t x, uint32_t n)  x^n
// ------------------------------------------------------------------------------------------
//      R0 = x, R1 = n, R2 = counter, R3 = Solution
		.globl  ExpInASM
ExpInASM:

        LDR R2, =0          //counter up to n
        LDR R3, =1          //solution
    Top:
        CMP R2, R1
        BGE End
        MUL R3, R0          //Multiplies
        ADD R2, R2, #1      //Adds 1 to the counter
        B   Top
    End:
        MOV R0, R3
		BX      LR

     		.end
