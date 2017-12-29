#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "library.h"

extern int32_t ExpInASM(int32_t x, uint32_t n) ;

#define ENTRIES(a) (sizeof(a)/sizeof(a[0]))

// Integer exponentiation - adapted from Warren, "Hacker's Delight", Addison Wesley, 2003.
int32_t ExpInC(int32_t x, int32_t n)
	{
	int32_t p, y ;

	y = 1 ;
	p = x ;
	while (1)
		{
		if ((n & 1) != 0) y = p * y ;
		n = n >> 1 ;
		if (n == 0) break ;
		p = p * p ;
		}
	return y ;
	}

int main(void)
	{
	static struct { int32_t base; uint32_t exponent; } testcase[] =
 		{
		{0,0},{2,0},{2,1},{-2,1},{2,3},{-2,3}
		} ;
	int k ;

	InitializeHardware(HEADER, PROJECT_NAME) ;

	for (;;)
		{
		for (k = 0; k < ENTRIES(testcase); k++)
			{
			int base = testcase[k].base ;
			int exponent = testcase[k].exponent ;
			int32_t result, answer = ExpInC(base, exponent) ;
			uint32_t before, after, cycles ;

            before = GetClockCycleCount() ;
			result = ExpInASM(base, exponent) ;
            after  = GetClockCycleCount() ;
            cycles = after - before ;

			printf("   Test Case %d: iexp(%d,%d)\n", k+1, base, exponent) ;

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
