#pragma once

const char* GetCurrentWorkingDirectory();
void SetCurrentWorkingDirectory(const char* path);

extern char g_pszStartDirectory[1024];
void SaveStartDirectory();

