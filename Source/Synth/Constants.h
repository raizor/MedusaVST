#pragma once

#include "ZynthTypes.h"
#include "Utils/PowerOfTwoTable.h"
#include "math.h"
	
// functionality switches
// use DirectSound? Otherwise WaveOut used - remember to link correct lib (dsound.lib or winmm.lib)!!
#define USE_DIRECT_SOUND 0

#define dsize 100000000

// data types
typedef int               sInt;
typedef unsigned int      sUInt;
typedef sInt              sBool;
typedef char              sChar;

typedef signed   char     sS8;
typedef signed   short    sS16;
typedef signed   long     sS32;
typedef signed   __int64  sS64;

typedef unsigned char     sU8;
typedef unsigned short    sU16;
typedef unsigned long     sU32;
typedef unsigned __int64  sU64;

typedef float             sF32;
typedef double            sF64;

// todo add multi channel (midi support)
#define Constants_NumMidiChannels  16 // number of midi channels
#define Constants_NumAudioChannels 2  // number of channels (2 stereo)
#define Constants_BytesPerSample sizeof(short)  // sizeof(short)  
#define Constants_BytesPerFloat sizeof(float)  // sizeof(short)  
#define Constants_BytesPerDouble sizeof(double)  // sizeof(short)  
#define Constants_BitsPerSample sizeof(short)*8
#define Constants_SamplesPerSec 44100  // samples per second
#define Constants_Nyquist Constants_SamplesPerSec/2  // samples per second
#define Constants_ClipLimitMax 32767  // audio clipping amplitude
#define Constants_ClipLimitMin -Constants_ClipLimitMax  // audio clipping amplitude
#define Constants_BlockAlign (Constants_NumAudioChannels * Constants_BytesPerSample) 
#define Constants_BytesPerSec (Constants_SamplesPerSec * Constants_BlockAlign)
#define Constants_BufferSizeInSamples 4410 
#define Constants_MixBufferSizeFloat Constants_BufferSizeInSamples 
#define Constants_MixBufferSizeBytes (Constants_MixBufferSizeFloat * Constants_NumAudioChannels * Constants_BytesPerSample) 
#define Constants_Pi  3.1415926535897932384
#define Constants_Pi2 Pi * 2
#define Constants_NoteCount 128  // The total number of notes.
#define Constants_NotesPerOctave 12  // The number of notes per octave.
#define Constants_A440NoteNumber 69  // The note number for the frequency 440Hz.
#define Constants_A440Frequency  440.0f // The frequency for the note A above middle C.
#define Constants_ParameterScaler 127  // For scaling generic parameter values.
#define Constants_MaxModulations 16 
#define Constants_ModValueInc 0.001f
#define Constants_TimeIncrement 1.0f / Constants_SamplesPerSec

// filters
#define fcdcoffset 3.814697265625e-6f // 2^-18

// GM.DLS
#define Constants_GmDlsInstrumentCount 235

// limits
#define Constants_Polyphony 16
#define Constants_MaxPatches 100
#define Constants_FrequencyMaxValueHz 12543.85366f
#define Constants_LfoFrequencyMaxValueHz 20.0f
#define Constants_PowerMaxValue 1.0f

#define Constants_NumOscillators    6
#define Constants_NumFilters        2
#define Constants_NumEnvelopes      6
#define Constants_NumLfoPerVoice    2
#define Constants_NumLfoAllVoices   4

// --------------------------------------------------------------------------
// Constants.
// --------------------------------------------------------------------------

// Natural constants
static const sF32 fclowest = 1.220703125e-4f; // 2^(-13) - clamp EGs to 0 below this (their nominal range is 0..128) 
static const sF32 fcpi_2  = 1.5707963267948966192313216916398f;
static const sF32 fcpi    = 3.1415926535897932384626433832795f;
static const sF32 fc1p5pi = 4.7123889803846898576939650749193f;
static const sF32 fc2pi   = 6.28318530717958647692528676655901f;
static const sF32 fc32bit = 2147483648.0f; // 2^31 (original code has (2^31)-1, but this ends up rounding up to 2^31 anyway)

// Synth constants
static const sF32 fcoscbase   = 261.6255653f; // Oscillator base freq
static const sF32 fcsrbase    = 44100.0f;     // Base sampling rate
static const sF32 fcboostfreq = 150.0f;       // Bass boost cut-off freq
static const sF32 fcframebase = 128.0f;       // size of a frame in samples
static const sF32 fcdcflt     = 126.0f;
static const sF32 fccfframe   = 11.0f;

static const sF32 fcfmmax     = 2.0f;
static const sF32 fcattackmul = -0.09375f; // -0.0859375
static const sF32 fcattackadd = 7.0f;
static const sF32 fcsusmul    = 0.0019375f;
static const sF32 fcgain      = 0.6f;
static const sF32 fcgainh     = 0.6f;
static const sF32 fcmdlfomul  = 1973915.49f;
static const sF32 fccpdfalloff = 0.9998f; // @@@BUG this should probably depend on sampling rate.


// Stuff that depends on the sample rate
extern sF32 SRfcsamplesperms;
extern sF32 SRfcobasefrq;
extern sF32 SRfclinfreq;
extern sF32 SRfcBoostCos, SRfcBoostSin;
extern sF32 SRfcdcfilter;

extern sInt SRcFrameSize;
extern sF32 SRfciframe;

void Constants_Init();

enum StackItemType
{
	kStackItemTypeWfOsc = 0,
	kStackItemTypeSimpleFilter = 1,
	kStackItemTypeEnvAdsr = 2,
	kStackItemTypeLfoAllVoices = 3,
	kStackItemTypeMixer = 4,
	kStackItemTypeAmpEg = 5,
	kStackItemTypePitchEg = 6,
	kStackItemTypeLfoPerVoice = 7,
	kStackItemTypePitchBender = 8,
	kStackItemTypeDistortion = 9,
	kStackItemTypeModDelay = 20,
	kStackItemTypeGlobalReverb = 21,
	kStackItemTypeCompressor = 22,
	kStackItemTypeBoost = 23,
	kStackItemTypePatchSettings = 24
};

enum LfoType
{
	LfoTypeAllVoices = 3,
	LfoTypePerVoice  =7
};

enum OscMode
{
	kOscModeNormalSync = 0,
	kOscModInvertedSync = 1,
	kOscModeNormalFree = 2,
	kOscModeInvertedFree = 3,
	kOscModeFixedSync = 4,
	kOscModeFixedFree = 5
};

enum OscModMode
{
	kOscModModeAdd = 0,
	kOscModModeRing = 1,
	kOscModModeSync = 2,
	kOscModModePM = 3,
	kOscModModeFM = 4
};

enum EgType
{
	kEgTypeStandard = 0,
	kEgTypeAmp  = 1,
	kEgTypePitch  =2,
};

enum FilterMode
{
	kFilterModeParallel = 1,
	kFilterModeDual = 2
};

enum FilterType
{
	kFilterTypeOff = -1,
	kFilterTypeLowPass = 0,
	kFilterTypeHighPass = 1,
	kFilterTypeBandPass = 2,
	kFilterTypeNotch = 3,
	kFilterTypeAll = 4,
	kFilterTypeMoogLow = 5,
	kFilterTypeMoogHigh = 6
};

enum BufferAction
{
	kBufferActionReplace = 0,
	kBufferActionMultiply = 1
};

enum WaveForm
{
	kWaveFormOff = -1,
	kWaveFormSin = 0,
	kWaveFormSquare = 1,
	kWaveFormSaw = 2,
	kWaveFormTriangle = 3,
	kWaveFormNoise = 4,	
	kWaveFormPadSynthChoir = 5,
	kWaveFormPadSynthEnsemble = 6,
	kWaveFormPadSynthExtended = 7,
	kWaveFormCustom = 25,
	
};

enum VoiceState
{
	kVoiceStateOff = 0,
	kVoiceStateOn = 1,
	kVoiceStateStopping = 2
};

enum NoteState
{
	kNoteStateOn = 0,
	kNoteStateOff = 1
};

enum Polarity
{
	kPolarityPositive = 0,
	kPolarityNegative = 1,
	kPolarityBoth = 2
}; 

enum PadSynthType
{
	kPadSynthTypeChoir = 0,
	kPadSynthTypeEnsemble = 1,
	kPadSynthTypeExtended = 2
};

struct FloatStereoSample
{
	float l;
	float r;
};

struct ShortStereoSample
{
	short l;
	short r;
};

enum ParamValueTypeFloat
{
	kParamValueTypeTime = 1,
	kParamValueTypeZeroToOneUni = 2,
	kParamValueTypeZeroToOneBi = 3,
	kParamValueTypeCents = 4,
	kParamValueTypeIntUni = 5,
	kParamValueTypeIntBi = 6,
	kParamValueTypePan = 7
};

// modulation
enum ModulationCurve
{
	kModulationCurveAddBipolarPlus = 0,
	kModulationCurveAddBipolarMinus = 1,
	kkModulationCurveAddUnipolarPlus = 2,
	kModulationCurveAddUnipolarMinus = 3,
	kModulationCurveMultBipolarPlus = 4,
	kModulationCurveMultBipolarMinus = 5,
	kModulationCurveMultUnipolarPlus = 6,
	kModulationCurveMultUnipolarMinus = 7
};

enum PlayerEventType
{
	kPlayerEventTypeNoteOn = 0,
	kPlayerEventTypeNoteOff,
	kPlayerEventTypeProgramChange
};

enum EgStage
{
	kStageNone = 0,
	kStageDelay,
	kStageAttack,
	kStageDecay,
	kStageSustain,
	kStageRelease
};



#define FILTERTYPE V2Filter
#define FILTER_INIT V2Filter_Init

// Float bitcasts. Union-based type punning to maximize compiler compatibility.
union FloatBits
{
	sF32 f;
	sU32 u;
};


union StereoSample
{
	struct
	{
		sF32 l, r;
	};
	sF32 ch[2];
};

class Constants
{
public:
	static Constants* instance;
	long RenderTime;
	float MasterVolume;
	int CurrentPatchNumber[Constants_NumMidiChannels];
	int CurrentPatchNumberEditor;
	int BufferOffset; // offset into float buffers for current dsound mix pos, offset is in floats

	Constants();
	~Constants();
	void CalcNewSampleRate(sInt samplerate);
};