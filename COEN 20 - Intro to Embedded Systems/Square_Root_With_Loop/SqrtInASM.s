		.syntax unified     //Nicholas Fong COEN 20 Lab 7 Lewis 11-4-15
		.arch	armv7-m
		.text
		.thumb_func
		.align	2

// ------------------------------------------------------------------------------------------
// uint32_t SqrtInASM(uint32_t x)
// ------------------------------------------------------------------------------------------
//  R0 = x, R1 = low, R2 = mid, R3 = high, R4 = mid^2
//  solving using binary search
		.globl  SqrtInASM
SqrtInASM:
        PUSH {R4}       //need an extra register
        LDR R1, =0      //load the smallest number
        LDR R3, =1      //load the biggest number possible
        LSL R3, R3, #16
Top:    ADD R2, R1, R3  //sets R2 as the midpoint between R1 and R3
        LSR R2, R2, #1  //Part of above comment
        MUL R4, R2, R2  //squares R2 to test answer
        CMP R4, R0
        BLT Less
        BGT Greater
        MOV R0, R2      //Put the answer in R0
        POP {R4}        //Put R4 back to what it was
		BX      LR

Less:
        MOV R1, R2      //set low <- mid
        B Top
Greater:
        MOV R3, R2      //set high <- mid
        B Top

	        .end
