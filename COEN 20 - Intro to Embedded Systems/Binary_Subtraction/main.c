#include <stdio.h>
#include <stdint.h>
#include "library.h"

#define ENTRIES(a) (sizeof(a)/sizeof(a[0]))

extern void SubBinary(int a[8], int b[8], int c[8]) ;

int main(void)
	{
	static struct {int a[8], b[8], diff ; } testcase[] =
		{
		{{0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,1},0},
		{{1,1,1,1,1,1,1,1},{1,0,0,0,0,0,0,0},-2},
		{{1,0,1,0,1,0,1,0},{1,0,1,0,1,0,1,0},0},
		{{1,1,0,1,0,0,0,0},{0,1,1,0,1,1,1,1},21},
		{{1,0,1,0,1,0,1,0},{0,1,0,1,0,1,0,1},-85}
		} ;
	int k ;

	InitializeHardware(HEADER, PROJECT_NAME) ;

	for (;;)
		{
		for (k = 0; k < ENTRIES(testcase); k++)
			{
			int *a = testcase[k].a ;
			int *b = testcase[k].b ;
			int diff[8] ;
			uint32_t before, after, cycles ;

			printf(" Test Case %d: ", k+1) ;
			PrintBits(a) ;
			printf("-") ;
			PrintBits(b) ;
			printf("\n") ;

			printf("  Correct Diff: ") ;
			PrintByte(testcase[k].diff) ;
			printf("\n") ;

            before = GetClockCycleCount() ;
			SubBinary(a, b, diff) ;
            after  = GetClockCycleCount() ;
            cycles = after - before ;

			printf("     Your Diff: ") ;
			if (PrintBits(diff) != (uint8_t) testcase[k].diff) printf(" %s", ERROR_FLAG) ;
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
