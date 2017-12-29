#include <stdio.h>
#include <stdint.h>
#include "library.h"

extern int64_t SMul64x64inASM(int64_t, int64_t) ;

#define ENTRIES(a) (sizeof(a)/sizeof(a[0]))

#define Lower32Bits(a)	((uint32_t *) &a)[0]
#define Upper32Bits(a)	((uint32_t *) &a)[1]

// Simulates the UMULL instruction: 32x32 --> 64
uint64_t UMULL(uint32_t a, uint32_t b)
	{
	return ((uint64_t) a) * ((uint64_t) b) ;
	}

// The only difference in signed vs. unsigned integer multiplication is
// in the most-significant half of the double-width product. Since we always
// discard those bits, the one routine below will work for either data type.

int64_t SMul64x64inC(int64_t a, int64_t b)
	{
	int64_t product, loXlo, loXhi, hiXlo ; ;

	// Compute three of four cross-products

	loXlo = UMULL(Lower32Bits(a), Lower32Bits(b)) ;
	hiXlo = UMULL(Lower32Bits(a), Upper32Bits(b)) ;
	loXhi = UMULL(Upper32Bits(a), Lower32Bits(b)) ;

	// Assemble the lower 64 bits of the 128-bit product

	product = loXlo ;
	Upper32Bits(product) += Lower32Bits(loXhi) ;
	Upper32Bits(product) += Lower32Bits(hiXlo) ;

	return product ;
	}

void PrintI64(int64_t n)
    {
    if (n < 0) { printf("-") ; n = -n ; }
    if (n >= 10) PrintI64(n / 10) ;
    printf("%d", (int) (n % 10)) ;
    }

int main(void)
	{
	static struct { int64_t multiplier, multiplicand ; } testcase[] =
 		{
 		// NOTE: The "LL" after each constant is to make it a 64-bit long long integer constant
		  {0LL,1LL},{1LL,0LL},{2LL,2LL},{-3LL,3LL},{3LL,-100000LL},{4LL,4294967296LL},{4294967296LL,-4LL}
       	} ;
	int k ;

	InitializeHardware(HEADER, PROJECT_NAME) ;

	for (;;)
		{
		for (k = 0; k < ENTRIES(testcase); k++)
			{
			int64_t mpier = testcase[k].multiplier ;
			int64_t mcand = testcase[k].multiplicand ;
			int64_t result, answer = SMul64x64inC(mpier, mcand) ;
			uint32_t before, after, cycles ;

            before = GetClockCycleCount() ;
			result = SMul64x64inASM(mpier, mcand) ;
            after  = GetClockCycleCount() ;
            cycles = after - before ;

			printf("   Test Case %d: ", k+1) ;
			PrintI64(mpier) ;
			printf(" x ") ;
			PrintI64(mcand) ;
			printf("\n") ;

			printf("Correct Result: ") ;
			PrintI64(answer) ;
			printf("\n") ;

			printf("   Your Result: ") ;
			PrintI64(result) ;
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
