#include <stdio.h>
#include <stdint.h>
#include "library.h"

#define ENTRIES(a) (sizeof(a)/sizeof(a[0]))

extern void AddBinary(int a[8], int b[8], int c[8]) ;

int main(void)
	{
	static struct {int a[8], b[8], sum ; } testcase[] =
		{
		{{0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,1},0},
		{{1,1,1,1,1,1,1,1},{1,0,0,0,0,0,0,0},0},
		{{1,0,1,0,1,0,1,0},{1,0,1,0,1,0,1,0},-86},
		{{1,1,0,1,0,0,0,0},{0,1,1,0,1,1,1,1},1},
		{{1,0,1,0,1,0,1,0},{0,1,0,1,0,1,0,1},-1}
		} ;
	int k ;

	InitializeHardware(HEADER, PROJECT_NAME) ;

	for (;;)
		{
		for (k = 0; k < ENTRIES(testcase); k++)
			{
			int *a = testcase[k].a ;
			int *b = testcase[k].b ;
			int sum[8] ;
			uint32_t before, after, cycles ;

			printf(" Test Case %d: ", k+1) ;
			PrintBits(a) ;
			printf("+") ;
			PrintBits(b) ;
			printf("\n") ;

			printf("   Correct Sum: ") ;
			PrintByte(testcase[k].sum) ;
			printf("\n") ;

            before = GetClockCycleCount() ;
			AddBinary(a, b, sum) ;
            after  = GetClockCycleCount() ;
            cycles = after - before ;

			printf("      Your Sum: ") ;
			if (PrintBits(sum) != (uint8_t) testcase[k].sum) printf(" %s", ERROR_FLAG) ;
			printf("\n") ;
			printf("  Clock Cycles: %lu\n", cycles) ;

			printf("\n") ;

			WaitForPushButton() ;
			}

		printf("Press button to start over.\n") ;
		WaitForPushButton() ;
		ClearDisplay() ;
		}
	}
