#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "library.h"

extern uint32_t AbsValinASM(int32_t) ;

#define ENTRIES(a) (sizeof(a)/sizeof(a[0]))

// This shows how to compute absolute value without a branch
uint32_t AbsValinC(int32_t x)
	{
	uint32_t signext ;

	signext = (x >= 0) ? 0 : -1 ;	// You can do this with an ASR instruction

	return (x + signext) ^ signext ;
	}

int main(void)
	{
	static struct { int32_t arg ;} testcase[] =
		{
		{0},{+1000},{-1000},{0x7FFFFFFF},{0x80000001}
		} ;
	int k ;

	InitializeHardware(HEADER, PROJECT_NAME) ;

	for (;;)
		{
		for (k = 0; k < ENTRIES(testcase); k++)
			{
			uint32_t result, answer = AbsValinC(testcase[k].arg) ;
			uint32_t before, after, cycles ;

            before = GetClockCycleCount() ;
			result = AbsValinASM(testcase[k].arg) ;
            after  = GetClockCycleCount() ;
            cycles = after - before ;

			printf("   Test Case %d: abs(%ld)\n", k+1, testcase[k].arg) ;

			printf("Correct Result: %ld\n", answer) ;

			printf("   Your Result: %ld", result) ;
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
