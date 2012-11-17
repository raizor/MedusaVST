#include "SampleBufferFloat.h"
#include "../Constants.h"
#include "../Utils/ZynthTools.h"

	SampleBufferFloat::SampleBufferFloat(long size)
	{
		Size = size;
		SizeInBytes = size*Constants_BytesPerFloat*2;
		Buffer = new StereoSample[size];
	}

	void SampleBufferFloat::Clear()
	{
		zt_memset(Buffer , 0, SizeInBytes);
	}

	void SampleBufferFloat::ClearRange(int numSamples)
	{
		if (Constants::instance->BufferOffset+numSamples > Size-2)
		{
			// out of bounds of edge of buffer
			for(int i=0; i<Constants_NumAudioChannels; i++)
			{				
				for(int j=0; j<numSamples; j++)
				{
					int inc = Constants::instance->BufferOffset+j;
					inc = inc % Size;
					Buffer[inc].ch[i] = 0;
				}
				/*
				int amtFloats = Size-(Constants::BufferOffset);
				int remainderFloats = numSamples-amtFloats;
				zt_memset(Buffer[i]+Constants::BufferOffset , 0, amtFloats << 2); // <<2 because float is 4 bytes
				zt_memset(Buffer[i] , 0, remainderFloats << 2);*/
			}
		}else{
			zt_memset(Buffer+Constants::instance->BufferOffset , 0, (numSamples*2) << 2);
		}
		// TODO: BUG IS HERE! - FIX LATER, above method is slow and should use memset;
		/*
		if (Constants::BufferOffset+numSamples > Size-1)
		{
			// out of bounds of edge of buffer
			for(int i=0; i<Constants::NumAudioChannels; i++)
			{
				int amtFloats = Size-(Constants::BufferOffset);
				int remainderFloats = numSamples-amtFloats;
				zt_memset(Buffer[i]+Constants::BufferOffset , 0, amtFloats << 2);
				zt_memset(Buffer[i] , 0, remainderFloats << 2);
			}
		}else{
			for(int i=0; i<Constants::NumAudioChannels; i++)
			{
				zt_memset(Buffer[i]+Constants::BufferOffset , 0, numSamples << 2);
			}
		}*/

	}

	// todo: remove amp buffer??
	void SampleBufferFloat::MixIn(SampleBufferFloat* bufferIn, SampleBufferFloat* ampBuffer, int numSamples)
	{
		bool haveAmp = ampBuffer != 0;
		for(int i=0; i<Constants_NumAudioChannels; i++)
		{
			for (int j = Constants::instance->BufferOffset; j < Constants::instance->BufferOffset+numSamples; j++)
			{			
				int idx = j%Constants_MixBufferSizeFloat;
				float val = bufferIn->Buffer[idx].ch[i];
				
				float amp = haveAmp ? ampBuffer->Buffer[idx].ch[i] : 1.0f; 
				//buffer->Buffer[i][idx] += val * Constants_MasterVolume * amp;				
				Buffer[idx].ch[i] += val;
			}
		}
		int xxx=1;

	}

	void SampleBufferFloat::AddClippedValue(int channel, int sampleNo, float val)
	{
		if (Buffer[sampleNo].ch[channel] + val <= 1.0f)
		{
			Buffer[sampleNo].ch[channel] += val;
		}else
		{
			Buffer[sampleNo].ch[channel] = 1.0f;
		}
	}

	void SampleBufferFloat::CopyToByteBuffer(SampleBufferShort* bufferTo)
	{
		for (int i = 0; i < Size; i++)
		{
			for (int c = 0; c < Constants_NumAudioChannels; c++)
			{
				// First clamp the value to the [-1.0..1.0] range
				double floatSample = zt_clampfMixMax(Buffer[i].ch[c], -1.0f, 1.0f);

				// Convert it to the 16 bit [short.MinValue..short.MaxValue] range
				short shortSample = (short)(floatSample >= 0.0f ? floatSample * Constants_ClipLimitMax : floatSample * Constants_ClipLimitMin * -1);

				// Calculate the right index based on the PCM format of interleaved samples per channel [L-R-L-R]
				int index = i * Constants_NumAudioChannels * Constants_BytesPerSample + c;

				bufferTo->Buffer[index] = shortSample;

				// Store the 16 bit sample as two consecutive 8 bit values in the buffer with regard to endian-ness
				//if (!BitConverter.IsLittleEndian)
				//{
					///buffer.Buffer[index] = (unsigned char)(shortSample >> 8);
					//buffer.Buffer[index + 1] = (unsigned char)shortSample;
				//}
				//else
				//{
				//	buffer.Buffer[index] = (byte)shortSample;
				//	buffer.Buffer[index + 1] = (byte)(shortSample >> 8);
				//}
			}
		}
	}
