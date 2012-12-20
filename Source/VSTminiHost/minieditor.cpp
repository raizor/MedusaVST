//-------------------------------------------------------------------------------------------------------
// VST Plug-Ins SDK
// Version 2.4		$Date: 2006/11/13 09:08:28 $
//
// Category     : VST 2.x SDK Samples
// Filename     : minieditor.cpp
// Created by   : Steinberg
// Description  : VST Mini Host Editor
//
// © 2006, Steinberg Media Technologies, All Rights Reserved
//-------------------------------------------------------------------------------------------------------

#include "pluginterfaces/vst2.x/aeffectx.h"

#include <windows.h>
#include <stdio.h>
#include "resources/resource.h"

//-------------------------------------------------------------------------------------------------------
struct MyDLGTEMPLATE: DLGTEMPLATE
{
	WORD ext[3];
	MyDLGTEMPLATE ()
	{
		memset (this, 0, sizeof (*this));
	};
};

static INT_PTR CALLBACK EditorProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
static AEffect* theEffect = 0;


//-------------------------------------------------------------------------------------------------------
bool checkEffectEditor (AEffect* effect)
{
	if ((effect->flags & effFlagsHasEditor) == 0)
	{
		printf ("This plug does not have an editor!\n");
		return false;
	}

	theEffect = effect;

	MyDLGTEMPLATE t;	
	t.style = WS_POPUPWINDOW|WS_DLGFRAME|DS_MODALFRAME|DS_CENTER;
	t.cx = 100;
	t.cy = 100;

	//DialogBox(GetModuleHandle (0), MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)EditorProc);
	DialogBoxIndirectParam (GetModuleHandle (0), &t, 0, (DLGPROC)EditorProc, (LPARAM)effect);
	//DialogBox(GetModuleHandle (0), MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)EditorProc, (LPARAM)effect);
	theEffect = 0;
	return true;
}

//-------------------------------------------------------------------------------------------------------
INT_PTR CALLBACK EditorProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	AEffect* effect = theEffect;

	switch(msg)
	{
		//-----------------------
		case WM_INITDIALOG :
		{
			SetWindowText (hwnd, "VST Editor");
			SetTimer (hwnd, 1, 20, 0);

			if (effect)
			{
				printf ("HOST> Open editor...\n");
				effect->dispatcher (effect, effEditOpen, 0, 0, hwnd, 0);

				printf ("HOST> Get editor rect..\n");
				ERect* eRect = 0;
				effect->dispatcher (effect, effEditGetRect, 0, 0, &eRect, 0);
				if (eRect)
				{
					int width = eRect->right - eRect->left;
					int height = eRect->bottom - eRect->top;
					if (width < 100)
						width = 100;
					if (height < 100)
						height = 100;

					RECT wRect;
					SetRect (&wRect, 0, 0, width, height);
					AdjustWindowRectEx (&wRect, GetWindowLong (hwnd, GWL_STYLE), FALSE, GetWindowLong (hwnd, GWL_EXSTYLE));
					width = wRect.right - wRect.left;
					height = wRect.bottom - wRect.top;

					SetWindowPos (hwnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE);
				}
			}
		}	break;

		//-----------------------
		case WM_TIMER : // 275//113
			if (effect)
				//effect->dispatcher (effect, effEditIdle, 0, 0, 0, 0);
			break;

		case WM_KEYDOWN:
			{
				DebugBreak();
				break;
			}

		case WM_CHAR:
			{
				DebugBreak();
				break;
			}

		//-----------------------
		case WM_CLOSE :
		{
			KillTimer (hwnd, 1);

			printf ("HOST> Close editor..\n");
			if (effect)
				effect->dispatcher (effect, effEditClose, 0, 0, 0, 0);

			EndDialog (hwnd, IDOK);
		}	break;
	}
	if (msg!=275)
	printf("i msg: %d\n", msg);
	return 0;
}

