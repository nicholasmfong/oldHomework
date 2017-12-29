#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "library.h"

extern uint32_t SqrtInASM(uint32_t) ;

#define ENTRIES(a) (sizeof(a)/sizeof(a[0]))

// Integer square root - adapted from Warren, "Hacker's Delight", Addison Wesley, 2003.
uint32_t SqrtInC(uint32_t x)
	{
	uint32_t m, y, b ;

	y = 0 ;
	m = 0x40000000 ;
	while (m != 0)	// repeats 16 times
		{
		b = y | m ;
		y = y >> 1 ;
		if (b <= x)
			{
			x = x - b ;
			y = y | m ;
			}
		m = m >> 2 ;
		}
	return y ;
	}

int main(void)
	{
	static struct { uint32_t squared ; } testcase[] =
		{
		{0*0},{1*1},{2*2},{1000*1000},{32767*32767}
		} ;
	int k ;

	InitializeHardware(HEADER, PROJECT_NAME) ;

	for (;;)
		{
		for (k = 0; k < ENTRIES(testcase); k++)
			{
			uint32_t result, answer = SqrtInC(testcase[k].squared) ;
			uint32_t before, after, cycles ;

            before = GetClockCycleCount() ;
			result = SqrtInASM(testcase[k].squared) ;
            after  = GetClockCycleCount() ;
            cycles = after - before ;

			printf("   Test Case %d: sqrt(%ld)\n", k+1, testcase[k].squared) ;

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
