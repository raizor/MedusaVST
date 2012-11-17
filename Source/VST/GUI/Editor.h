//	ExampleEditor.h - Simple OpenGL editor window.
//	--------------------------------------------------------------------------
//	Copyright (c) 2005-2006 Niall Moody
//	
//	Permission is hereby granted, free of charge, to any person obtaining a
//	copy of this software and associated documentation files (the "Software"),
//	to deal in the Software without restriction, including without limitation
//	the rights to use, copy, modify, merge, publish, distribute, sublicense,
//	and/or sell copies of the Software, and to permit persons to whom the
//	Software is furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//	DEALINGS IN THE SOFTWARE.
//	--------------------------------------------------------------------------

#ifndef EDITOR_H_
#define EDITOR_H_

#include "VSTGL/VSTGLEditor.h"
#include "VSTGL/VSTGLTimer.h"
#include "Synth.h"
#include "Components/GuiMainWindow.h"
#include <iostream>

///	Simple VSTGL example.
class Editor : public VSTGLEditor,
					  public Timer
{
public:
	Patch* currentPatch;
	GuiMainWindow* _mainWindow;
	static int _winWidth, _winHeight;
		
	///	Constructor.
	Editor(AudioEffect *effect);
	///	Destructor.
	~Editor();

	///	Called when the Gui's window is opened.
	void guiOpen();
	///	Called when the Gui's window is closed.
	void guiClose();

	///	Draws a spinning pyramid.
	void draw();

	void PatchChanged(Patch* patch);

	///	Called repeatedly, to update the graphics.
	void timerCallback();
  private:
	///	Variable used to rotate the pyramid.
	float thing;
};

#endif
