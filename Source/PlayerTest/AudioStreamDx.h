#pragma once

#include <dsound.h>
#include "Synth.h"
#include "Constants.h"
#include "Utils/ZynthTools.h"
#include "Utils/SampleBufferFloat.h"
#include "Utils/SampleBufferShort.h"

	typedef void (* RenderCallback)(short *buffer, int length, void *userData);

	class AudioStreamDx 
	{

	public:
		Synth* synth;
		int latencyMs;
		int bufferSizeBytes;
		LPDIRECTSOUND8 device;
		LPDIRECTSOUNDBUFFER buffer;
		int oldPlayCursorPos;
		bool updating;
		volatile HANDLE hThread;		
		CRITICAL_SECTION cs;

		SampleBufferShort* RenderBuffer;
		int renderBufferSize;
		int renderBufferOffset;


		AudioStreamDx(Synth* synth, int latencyMs);	// 100 ms
		void Free();
		void Update();
	};
