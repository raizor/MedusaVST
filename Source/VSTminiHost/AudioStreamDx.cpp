#include "AudioStreamDx.h"
#include "Constants.h"
#include <string.h>

	AudioStreamDx::AudioStreamDx(int latencyMs)
	{
		latencyMs = latencyMs;
		oldPlayCursorPos = 0;
		updating = false;		
		InitializeCriticalSection(&cs);

		RenderBuffer = new SampleBufferShort(dsize);
		renderBufferOffset = 0;
		renderBufferSize = dsize;
		
		bufferSizeBytes = Constants_BlockAlign * Constants_SamplesPerSec * latencyMs / 1000;
		//bufferSizeBytes = Constants::MixBufferSizeBytes;

		if (DirectSoundCreate8(0, &device, 0) != DS_OK) 
		{
			DebugBreak();
			//throw EXCEPTION("Could not create device.");
		}
		if (device->SetCooperativeLevel(GetForegroundWindow(), DSSCL_PRIORITY) != DS_OK) 
		{
			DebugBreak();
			//throw EXCEPTION("Could not set device priority.");
		}
	
		WAVEFORMATEX bufferFormat =
		{			
			WAVE_FORMAT_PCM,
			Constants_NumAudioChannels,
			Constants_SamplesPerSec,
			Constants_BytesPerSec,
			Constants_BlockAlign,
			Constants_BitsPerSample,
			0
		};

		DSBUFFERDESC bufferDesc =
		{
			sizeof(DSBUFFERDESC),
			DSBCAPS_GLOBALFOCUS | DSBCAPS_GETCURRENTPOSITION2,
			bufferSizeBytes,
			0,
			&bufferFormat,
			0
		};
		if (device->CreateSoundBuffer(&bufferDesc, &buffer, 0) != DS_OK) 
		{
			DebugBreak();
			//throw EXCEPTION("Could not create secondary buffer.");
		}

		oldPlayCursorPos = 0;
		if (buffer->Play(0, 0, DSBPLAY_LOOPING) != DS_OK)
		{
			DebugBreak();
			//throw EXCEPTION("Could not start buffer playback.");
		}
	}

	extern void callProcessReplacing(short* buffer, int numSamples);

	void AudioStreamDx::Update()
	{
		EnterCriticalSection(&cs);
		if (updating)
		{
			DebugBreak();
		}
		updating = true;
		int playCursorPos;
		buffer->GetCurrentPosition((LPDWORD) &playCursorPos, 0);
		int bytesToRender = playCursorPos - oldPlayCursorPos;
		if (bytesToRender)
		{			
			if (bytesToRender < 0) bytesToRender += bufferSizeBytes;
			short *p1, *p2;
			int b1, b2;
			if (buffer->Lock(oldPlayCursorPos, bytesToRender, (LPVOID *) &p1, (LPDWORD) &b1, (LPVOID *) &p2, (LPDWORD) &b2, 0) != DS_OK)
			{
				DebugBreak();
				int xx =1;
			}

			//synth->Render(p1, b1 / sizeof(short));
			//Synth_RenderRouter(p1, b1 / sizeof(short));
			callProcessReplacing(p1, b1 / sizeof(short));

			if (b2 > 0) 
			{
				//Synth_RenderRouter(p2, b2 / sizeof(short));
				//synth->Render(p2, b2 / sizeof(short));
				callProcessReplacing(p2, b2 / sizeof(short));
			}
			if (buffer->Unlock(p1, b1, p2, b2) != DS_OK) 
			{
				DebugBreak();
				int xx =1;
			}
			oldPlayCursorPos = playCursorPos;			
		}
		updating = false;
		LeaveCriticalSection(&cs);
	}

	void AudioStreamDx::Free()
	{
		buffer->Stop();
		buffer->Release();
		device->Release();
	}