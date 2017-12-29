#include <stdio.h>
#include <stdint.h>
#include "library.h"

#define ENTRIES(a) (sizeof(a)/sizeof(a[0]))

extern uint32_t ReverseByteOrder(uint32_t) ;

// This function simulates the REV instruction ...
uint32_t REV(uint32_t word)
	{
	uint32_t result ;
	int byte ;

	result = 0 ;
	for (byte = 0; byte <= 3; byte++)
		{
		((uint8_t *) &result)[3 - byte] = ((uint8_t *) &word)[byte] ;
		}
	return result ;
	}

int main(void)
    {
	static uint32_t testcase[] =
		{
		0x12345678,	0x0000FFFF,	0x00FF00FF
		} ;

	InitializeHardware(HEADER, PROJECT_NAME) ;

	for (;;)
		{
		int k ;

		for (k = 0; k < ENTRIES(testcase); k++)
			{
			uint32_t word = testcase[k] ;
			uint32_t result, answer = REV(word) ;
			uint32_t before, after, cycles ;

            before = GetClockCycleCount() ;
			result = ReverseByteOrder(word) ;
            after  = GetClockCycleCount() ;
            cycles = after - before ;

			printf("   Test Case %d: %08X (hex)\n", k+1, (unsigned) word) ;

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
