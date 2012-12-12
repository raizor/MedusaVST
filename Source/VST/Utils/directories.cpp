#include "directories.h"
#include <windows.h>		// Header File For Windows

// Dialogs change the current path, so this will only work correctly the first time
char buffer[1024];

const char* GetCurrentWorkingDirectory()
{
	GetCurrentDirectoryA(1024, buffer);

	return buffer;
}

void SetCurrentWorkingDirectory(const char* path)
{
	SetCurrentDirectoryA(path);
}

char g_pszStartDirectory[1024];

void SaveStartDirectory()
{
	const char* path = GetCurrentWorkingDirectory();
	strcpy(g_pszStartDirectory, path);
}

