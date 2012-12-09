#include "FixedDelay.h"


FixedDelay::FixedDelay(void) 
{
}

void FixedDelay::Reset()
{
	zt_memset(buf, 0, sizeof(*buf)*len);
	pos = 0;
}

void FixedDelay::Init(sF32 *buf, sU32 len)
{
	this->buf = buf;
	this->len = len;
	Reset();
}


FixedDelay::~FixedDelay(void)
{
}
