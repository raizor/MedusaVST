#include "Writer.h"

#define MEM_BUFFER_SIZE 5*1024*1204

// file writer
Writer::Writer(FILE* fp)
{
	WriteType = WriterTypeFile;
	fileHandle = fp;
}

// mem writer
Writer::Writer()
{
	WriteType = WriterTypeFile;
	memBufferOffset = 0;
	memHandle = (unsigned char*)malloc(MEM_BUFFER_SIZE); // 5 meg buffer
	memset(memHandle, 0, MEM_BUFFER_SIZE);
}

// mem writer
Writer::Writer(void* buffer)
{
	WriteType = WriterTypeFile;
	memBufferOffset = 0;
	memHandle = (unsigned char*)buffer; // 5 meg buffer
	//memset(memHandle, 0, MEM_BUFFER_SIZE);
	//memcpy(memHandle, buffer, MEM_BUFFER_SIZE);
}

void Writer::Write(void* data, int size, int count)
{
	unsigned char* p = (unsigned char*) data;
	for(int i=0; i<count*size; i++)
	{
		memHandle[memBufferOffset++] = p[i];
	}
	//Write();
}

void Writer::Read(void* data, int size, int count)
{
	unsigned char* p = (unsigned char*) data;
	for(int i=0; i<count*size; i++)
	{
		p[i] = memHandle[memBufferOffset++];
	}
	//Write();
}

Writer::~Writer(void)
{
}
