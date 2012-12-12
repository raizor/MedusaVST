#include "filedialog.h"
#include "directories.h"
#include <windows.h>		// Header File For Windows

char fileDialogResult[256];

char* DialogResult()
{
	return &fileDialogResult[0];
}

int SpawnSaveFileDialog()
{
	OPENFILENAMEA opf;
	opf.hwndOwner = 0;
	opf.lpstrFilter = "\0\0";
	opf.lpstrCustomFilter = 0;
	opf.nMaxCustFilter = 0L;
	opf.nFilterIndex = 1L;
	opf.lpstrFile = fileDialogResult;
	opf.lpstrFile[0] = '\0';
	opf.nMaxFile = 256;
	opf.lpstrFileTitle = 0;
	opf.nMaxFileTitle=50;
	opf.lpstrInitialDir = GetCurrentWorkingDirectory();
	opf.lpstrTitle = "Save File";
	opf.nFileOffset = 0;
	opf.nFileExtension = 0;
	opf.lpstrDefExt = "";
	opf.lpfnHook = NULL;
	opf.lCustData = 0;
	opf.Flags = (OFN_OVERWRITEPROMPT) & ~OFN_ALLOWMULTISELECT;
	opf.lStructSize = sizeof(OPENFILENAME);

	if(GetSaveFileNameA(&opf))
	{
		return kDialogFileChosen;
	}
	return kDialogCanceled;
}

int SpawnLoadFileDialog()
{
	OPENFILENAMEA opf;
	opf.hwndOwner = 0;
	opf.lpstrFilter = "\0\0";
	opf.lpstrCustomFilter = 0;
	opf.nMaxCustFilter = 0L;
	opf.nFilterIndex = 1L;
	opf.lpstrFile = fileDialogResult;
	opf.lpstrFile[0] = '\0';
	opf.nMaxFile = 256;
	opf.lpstrFileTitle = 0;
	opf.nMaxFileTitle=50;
	opf.lpstrInitialDir = GetCurrentWorkingDirectory();
	opf.lpstrTitle = "Open File";
	opf.nFileOffset = 0;
	opf.nFileExtension = 0;
	opf.lpstrDefExt = "*.*";
	opf.lpfnHook = NULL;
	opf.lCustData = 0;
	opf.Flags = (OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT) & ~OFN_ALLOWMULTISELECT;
	opf.lStructSize = sizeof(OPENFILENAME);

	if(GetOpenFileNameA(&opf))
	{
		return kDialogFileChosen;
	}
	return kDialogCanceled;
}
