// PlayerTest.cpp : Defines the entry point for the console application.
//

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Synth.h"
#include <mmeapi.h>
#include "AudioStreamDx.h"

static HANDLE stdout;
static AudioStreamDx *audioStreamDx;	
static HANDLE threadHandle;
static Synth* _synth;

void print(const char *bla)
{
	unsigned long bw;
	int len=-1;
	while (bla[++len]);
	WriteFile(stdout,bla,len,&bw,0);
}

void RenderAudio( void *arg ) 
{
	while (true)
	{
		audioStreamDx->Update();
		Sleep(1);
	}
}

void entrypoint( void )
{
	stdout=GetStdHandle(STD_OUTPUT_HANDLE);
	_synth = new Synth();
	audioStreamDx = new AudioStreamDx(_synth, 100);
	print("raizor's tiny synth test #1...");

	threadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RenderAudio, 0, 0, 0);
	SetThreadPriority(threadHandle, THREAD_PRIORITY_ABOVE_NORMAL);

	while (GetAsyncKeyState(VK_ESCAPE)>=0 && GetAsyncKeyState(VK_SPACE)>=0)
	{
		Sleep(10);
	}
	ExitProcess(0);
}

