#pragma once

#include "../../ItemProcessor.h"

class FixedDelay
{
public:
	FixedDelay(void);
	~FixedDelay(void);

	sU32 pos, len;
	sF32 *buf;

	void FixedDelay::Reset();
	void FixedDelay::Init(sF32 *buf, sU32 len);

	inline sF32 FixedDelay::Fetch() const
	{
		return buf[pos];
	}

	inline void FixedDelay::Feed(sF32 v)
	{
		buf[pos] = v;
		if (++pos == len)
			pos = 0;
	}
};

