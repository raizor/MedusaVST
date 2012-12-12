#ifndef __GFILEDIALOG__
#define __GFILEDIALOG__

extern char fileDialogResult[256];

enum
{
	kDialogFileChosen,
	kDialogCanceled,
	kDialogError
};

int SpawnLoadFileDialog();
int SpawnSaveFileDialog();

char* DialogResult();

#endif //__GFILEDIALOG__
