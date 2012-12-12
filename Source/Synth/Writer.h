#pragma once

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <malloc.h>

enum WriterType
{
	WriterTypeFile,
	WriterTypeMem
};

class Writer
{
public:
	WriterType WriteType;
	FILE *fileHandle;
	unsigned char* memHandle;
	long memBufferOffset;
	Writer();
	Writer(FILE* fp);
	Writer::Writer(void* buffer);
	void Write(void* data, int size, int count);
	void Read(void* data, int size, int count);
	~Writer(void);
};

