#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "library.h"

extern uint32_t BitFieldInsert(uint32_t word, int lsb, int width, uint32_t value) ;

#define ENTRIES(a) (sizeof(a)/sizeof(a[0]))

//This function simulates the BFC instruction
uint32_t BFI(uint32_t word, int lsb, int width, uint32_t value)
	{
	uint32_t mask ;

	// replace bit-field with zeroes
	mask = (1 << (lsb+width)) - (1 << lsb) ;
	word &= ~mask ;

	// limit width of value to insert
	mask = (1 << width) - 1 ;
	value &= mask ;

	// insert new value into bit-field
	return word | (value << lsb) ;
	}

int main(void)
	{
	static struct
		{
		uint32_t	word ;
		int			lsb ;
		int			width ;
		uint32_t	value ;
		} testcase[] =
		{
		{0xFFFFFFFF,  5, 7,  0},
		{0x00000000, 22, 5, -1}
		} ;
	int k ;

	InitializeHardware(HEADER, PROJECT_NAME) ;

	for (;;)
		{
		for (k = 0; k < ENTRIES(testcase); k++)
			{
			uint32_t	word	= testcase[k].word ;
			int			lsb		= testcase[k].lsb ;
			int			width	= testcase[k].width ;
			uint32_t	value	= testcase[k].value ;
			uint32_t	result, answer	= BFI(word, lsb, width, value) ;
			uint32_t    before, after, cycles ;

            before = GetClockCycleCount() ;
			result = BitFieldInsert(word, lsb, width, value) ;
            after  = GetClockCycleCount() ;
            cycles = after - before ;

			printf("   Test Case %d: %08X,%d,%d,%d\n", k+1,
				(unsigned) word, lsb, width, (int) value) ;

			printf("Correct Result: %08X\n", (unsigned) answer) ;

			printf("   Your Result: %08X", (unsigned) result) ;
			if (result != answer) printf(" %s", ERROR_FLAG) ;
			printf("\n") ;

			printf("  Clock Cycles: %lu\n\n", cycles) ;

			WaitForPushButton() ;
			}

		printf("Press button to start over.\n") ;
		WaitForPushButton() ;
		ClearDisplay() ;
		}
	}
