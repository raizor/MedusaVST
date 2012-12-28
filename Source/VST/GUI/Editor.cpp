//	ExampleEditor.cpp - Simple OpenGL editor window.
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

#include "Editor.h"
#include "../../includes.h"
#include "Components/GuiImageManager.h"
#include "Components/GuiLabel.h"
//#include "Text/FontManager.h"
#include "Utils/VoicePool.h"

// init statics
int Editor::_winWidth = 0;
int Editor::_winHeight = 0;
bool Editor::_initDone = false;
GuiMainWindow* Editor::_mainWindow = NULL;

//----------------------------------------------------------------------------
Editor::Editor(AudioEffect *effect):
VSTGLEditor(effect, Antialias4x),
Timer(30), //30ms == ~30fps?
thing(0.0f)
{
	currentPatch = NULL;
	//Set the opengl context's size - This must be called here!
	_winWidth = 920;
	_winHeight = 863;
	setRect(0, 0, _winWidth, _winHeight);
}

//----------------------------------------------------------------------------
Editor::~Editor()
{
	
}

void Editor::PatchChanged(Patch* patch)
{
	//PatchList::list->patches[0];
	_mainWindow->PatchChanged(patch);
}

//----------------------------------------------------------------------------
void Editor::guiOpen()
{

	//Setup OpenGL stuff.
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glViewport(0, 0, getWidth(), getHeight());

    //Set viewing projection.
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,
				   (GLfloat)getWidth()/(GLfloat)getHeight(),
				   0.1f,
				   100.0f);

    //Position viewer.
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0f);

	glEnable(GL_TEXTURE_2D);
	if (!_initDone)
	{	
		// Setup font manager
		//if (!g_pFontManager)	

		GuiImageManager::InitInstance();
		GuiImageManager::instance->GetImageById(IDB_BUTTONSTRIP)->SetSpriteSheet(new SpritesButtonsSprites());
		_mainWindow = new GuiMainWindow(920, 863, 0, 0, IDB_PNG_PANEL_MAIN);
		_mainWindow->hWindow = systemWindow;
		int* ii = new int();
		delete(ii);
		TextWriter::writer = new TextWriter();

		//MessageBoxEx(NULL, "", "", NULL, NULL);
		//_initDone = true;
	}
	PatchList::list->CurrentPatch = PatchList::list->patches[0];
	_mainWindow->PatchChanged(PatchList::list->CurrentPatch);

	//Start timer to constantly update gui.
	start();
}

//----------------------------------------------------------------------------
void Editor::guiClose()
{
	//Stop the timer.
	stop();
}

//----------------------------------------------------------------------------
void Editor::draw()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glViewport(0, 0, _winWidth, _winHeight); // change viewport to match screen size
	GlHelpers::ViewOrthagnonal(_winWidth, _winHeight);
	glDisable(GL_DEPTH_TEST);
	_mainWindow->draw();
	glEnable(GL_DEPTH_TEST);

	GlHelpers::ViewPerspective();
	
}

void Editor::onGLKeyDown(const VstKeyCode& key)
{
	if (GuiMainWindow::editingComponent != NULL)
	{
		GuiLabel* lab = (GuiLabel*)GuiMainWindow::editingComponent;

		GEvent* evt = new GEvent();
		evt->type = kGEventKeyDown;
		evt->key[0] = key.character;
		evt->key[1] = key.virt;
		_mainWindow->HandleEvent(evt);

		/*
		char* txt = new char[255];
		if (key.virt == VKEY_BACK || key.virt == VKEY_DELETE)
		{
			int len = strlen(lab->text);
			lab->text[len-1] = 0;
			//sprintf(txt, "%s%c", lab->text, key.character);		
		}else{
			sprintf(txt, "%s%c", lab->text, key.character);		
			lab->SetText(txt);
		}

		GEvent* evt = new GEvent();
		evt->type = kGEventKeyDown;
		evt->key[0] = key.character;
		evt->key[1] = key.virt;
		_mainWindow->HandleEvent(evt);
		*/
		/*
		if (lab->EditedHandler != NULL)
		{
			(lab->*EditedHandler)(this, 0);
		}*/
		//delete(txt);

		//lab->Edited(new GEvent());
	}
	/*
	int midiNumber = 70;
	Patch* p = PatchList::list->CurrentPatch = PatchList::list->patches[0];
	VoicePool::Pool->GetVoiceAndPlayNote(0, midiNumber, p);*/
}

void Editor::onGLKeyUp(const VstKeyCode& key)
{
	/*
	int midiNumber = 70;
	Patch* p = PatchList::list->CurrentPatch = PatchList::list->patches[0];
	VoicePool::Pool->GetVoiceAndPlayNote(0, midiNumber, p);*/
}

void Editor::onMouseMove(int x, int y)
{
	GEvent* evt = new GEvent();
	evt->pos.x = x;
	evt->pos.y = y;
	evt->type = kGEventMouseMoved;
	_mainWindow->HandleEvent(evt);
}

void Editor::onMouseDown(int button, int x, int y)
{
	GEvent* evt = new GEvent();
	evt->pos.x = x;
	evt->pos.y = y;
	evt->type = kGEventMouseDown;
	evt->button = (GEventMouseButton)button;
	_mainWindow->HandleEvent(evt);
}

void Editor::onMouseUp(int button, int x, int y)
{
	GEvent* evt = new GEvent();
	evt->pos.x = x;
	evt->pos.y = y;
	evt->type = kGEventMouseUp;
	evt->button = (GEventMouseButton)button;
	_mainWindow->HandleEvent(evt);
}

//----------------------------------------------------------------------------
void Editor::timerCallback()
{
	refreshGraphics();
}
