#include "ZynthTools.h"
#include <windows.h>

void *zynth_mallocAlloc( unsigned int amount )
{
	//void* ret = HeapAlloc(GetProcessHeap, HEAP_ZERO_MEMORY, amount);
	//return ret;
	return( GlobalAlloc( GMEM_ZEROINIT, amount ) );
}

void zynth_mallocFree( void *ptr )
{
	//HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, ptr);
	GlobalFree( ptr );
}

void *msys_mallocRealloc( void* mem, unsigned int amount )
{
	if (mem == NULL)
	{
		return zynth_mallocAlloc(amount);
	}
	return GlobalReAlloc(mem, amount, GMEM_MOVEABLE);
}

sU32 ReverseBits(sU32 p_nIndex, sU32 p_nBits)
{
	sU32 i, rev;
	for (i = rev = 0; i < p_nBits; i++)
	{
		rev = (rev << 1) | (p_nIndex & 1);
		p_nIndex >>= 1;
	}
	return rev;
}

sU32 numberOfBitsNeeded(sU32 p_nSamples)
{
	int i;
	if (p_nSamples < 2)
		return 0;

	for (i = 0; ; i++)
		if ((p_nSamples & (1 << i)) != 0) return (sU32)i;
}

bool isPowerOfTwo(sU32 p_nX)
{
	if (p_nX < 2) return false;

	if ((p_nX & (p_nX - 1)) == 0)
		return true;
	else
		return false;
}