#pragma once

#include "../Constants.h"
#include <stdlib.h>
#include <string.h>

#define zt_pow pow
#define zt_powf powf

#define zt_fabs fabs

/*
__forceinline float zt_fabs(float v)
{
	float r;
	_asm fld  dword ptr [v]; 
	_asm fabs;  
	_asm fstp dword ptr [r]; 
	return r; 
}
*/

#define zt_memset memset

/*
__forceinline void zt_memset( void *dst, int val, int amount )
{
	_asm mov edi, dst
	_asm mov eax, val
	_asm mov ecx, amount
	_asm rep stosb
}*/

#define zt_memcpy memcpy

/*
__forceinline void zt_memcpy( void *dst, const void *ori, int amount )
{
	_asm mov edi, dst
	_asm mov esi, ori
	_asm mov ecx, amount
	_asm rep movsb
}
*/


static inline int FloatToInt(float x)
{
	unsigned e = (0x7F + 31) - ((* (unsigned*) &x & 0x7F800000) >> 23);
	unsigned m = 0x80000000 | (* (unsigned*) &x << 8);
	return int((m >> e) & -(e < 32));
}

// float from [0,1) into 0.32 unsigned fixed-point
// this loses a bit, but that's what V2 does.
static inline sU32 ftou32(sF32 v)
{
	return 2u * FloatToInt((v * fc32bit));
}

static inline sF32 bits2float(sU32 u)
{
	FloatBits x;
	x.u = u;
	return x.f;
}

// square
static inline sF32 sqr(sF32 x)
{
	return x*x;
}

static inline sF32 utof23(sU32 x)
{
	sF32 f = bits2float((x >> 9) | 0x3f800000); // 1 + x/(2^32)
	return f - 1.0f;
}

static inline sF32 calcfreq(sF32 x)
{
	return PowerOfTwoTable::instance->GetPower((x - 1.0f)*10.0f);
	//return powf(2.0f, (x - 1.0f)*10.0f);
}

static inline sF32 calcfreq2(sF32 x)
{
	return zt_powf(2.0f, (x - 1.0f)*fccfframe);
}

// float from [0,1) into 0.32 unsigned fixed-point
// this loses a bit, but that's what V2 does.
static inline sU32 ftosU32(sF32 v)
{
	return 2u * (sInt)(v * fc32bit);
}


static inline int clampi(int x, int min, int max)
{
	return (x < min) ? min : (x > max) ? max : x;
}

// linear interpolation between a and b using t.
static inline sF32 lerp(sF32 a, sF32 b, sF32 t)
{
	return a + t * (b-a);
}

/*
template<typename T>
static inline T clamp(T x, T min, T max)
{
	return (x < min) ? min : (x > max) ? max : x;
}*/

__forceinline float zt_clampMax(float v, float ceil)
{
	if (v<=ceil) return v;
	return ceil;
}

__forceinline float zt_clampfMixMax(float v, float floor, float ceil)
{
	if (v<=ceil && v>=floor) return v;
	if (v>ceil) return ceil;
	if (v<floor) return floor;
	return v;
}

__forceinline int zt_clampfMixMaxInt(int v, int floor, int ceil)
{
	if (v<=ceil && v>=floor) return v;
	if (v>ceil) return ceil;
	if (v<floor) return floor;
	return v;
}

__forceinline float msys_frand( int *seed )
{	
	unsigned int a;
	float res;
	seed[0] = seed[0] * 0x343FD + 0x269EC3;
	a = (((unsigned int)seed[0])>>9) | 0x3f800000;
	res = (*((float*)&a)) - 1.0f;
	return( res );
}

static short opc1 = 0x043f ;     // floor

#define msys_ifloorf floorf 

/*
__forceinline int msys_ifloorf( const float x )
{
	int res;
	short tmp;

	_asm fstcw   word  ptr [tmp]
	_asm fld     dword ptr [x]
	_asm fldcw   word  ptr [opc1]
	_asm fistp   dword ptr [res]
	_asm fldcw   word  ptr [tmp]

	return res;
}*/

/*
__forceinline float msys_powf( const float x, const float y )
{
	float res;

	_asm fld     dword ptr [y]
	_asm fld     dword ptr [x]
	_asm fyl2x
	_asm fld1
	_asm fld     st(1)
	_asm fprem
	_asm f2xm1
	_asm faddp   st(1), st(0)
	_asm fscale
	_asm fxch
	_asm fstp    st(0)
	_asm fstp    dword ptr [res];

	return res;
}*/
/*
__forceinline float msys_expf( const float x )
{
	float res;

	_asm fld     dword ptr [x]
	_asm fldl2e
	_asm fmulp   st(1), st(0)
	_asm fld1
	_asm fld     st(1)
	_asm fprem
	_asm f2xm1
	_asm faddp   st(1), st(0)
	_asm fscale
	_asm fxch    st(1)
	_asm fstp    st(0)
	_asm fstp    dword ptr [res]

	return res;
}*/

static inline float MIN(float a, float b)
{
	return a < b ? a : b;
}

static inline float MAX(float a, float b)
{
	return a > b ? a : b;
}

#define msys_cosf cosf

/*
__forceinline float msys_cosf( const float x)
{
	float r; _asm fld  dword ptr [x]; 
	_asm fcos; 
	_asm fstp dword ptr [r]; 
	return r; 
}
*/

#define msys_sinf sinf

/*
__forceinline float msys_sinf( const float x)
{ 
	float r; _asm fld  dword ptr [x]; 
	_asm fsin;  
	_asm fstp dword ptr [r]; 
	return r; 
}*/

__forceinline float RND_0_1()
{
	return (float)(rand()/(RAND_MAX+1.0f));
};

void *zynth_mallocAlloc( unsigned int amount );
void  zynth_mallocFree( void *ptr );
void *zynth_mallocRealloc( void* mem, unsigned int amount );
sU32 ReverseBits(sU32 p_nIndex, sU32 p_nBits);
sU32 numberOfBitsNeeded(sU32 p_nSamples);
bool isPowerOfTwo(sU32 p_nX);
