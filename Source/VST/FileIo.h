#pragma once

#include <stdio.h>

class Writer;
class Item;
class Patch;
enum ParamType;
enum StackItemType;

class ZynthIo
{
public:
	static void LoadBank(FILE* fp, Writer *writer, bool useFile);
	static void LoadBankFromFile(char* loadPath);	
	static void LoadBankFromMem(unsigned char* mem);

	static int SaveBank(FILE* fp, Writer *writer, bool useFile);
	static void SaveBankToFile(char* savePath);
	static int SaveBankToMem(unsigned char* mem);
	static void read(void* data, int size, int count, FILE *fp, Writer* writer, bool useFile);
	static void write(void* data, int size, int count, FILE *fp, Writer* writer, bool useFile);
	static void WriteBool(bool val, FILE *fp, Writer* writer, bool useFile);
	static void WriteInt(int val, FILE *fp, Writer* writer, bool useFile);
	static bool ReadBool(FILE *fp, Writer* writer, bool useFile);
	static float ReadFloat(FILE *fp, Writer* writer, bool useFile);
	static int ReadInt(FILE *fp, Writer* writer, bool useFile);
	static void SaveParam(void* item, ParamType paramType, FILE *fp, Writer* writer, bool useFile);
	static void SaveParams(Item* item, FILE *fp, Writer* writer, bool useFile);
	static void LoadParams(Item* item, FILE *fp, Writer* writer, bool useFile);
	static void LoadParam(void* item, ParamType paramType, FILE *fp, Writer* writer, bool useFile);
};

