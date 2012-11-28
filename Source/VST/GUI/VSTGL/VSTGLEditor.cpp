//	VSTGLEditor.cpp - Editor window for a VST plugin using OpenGL to handle
//					  all the drawing.
//	---------------------------------------------------------------------------
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
//	---------------------------------------------------------------------------

#include "VSTGLEditor.h"
#include "public.sdk/source/vst2.x/audioeffect.h"
#include "../../includes.h"
#include <cstdio>

#ifdef WIN32
//This is the instance of the application, set in the main source file.
extern void* hInstance;

RECT rc;

//Used to check/setup Vertical Sync.
typedef void (APIENTRY *PFNWGLEXTSWAPCONTROLPROC) (int);
typedef int (*PFNWGLEXTGETSWAPINTERVALPROC) (void);

//Used to check/setup Antialiasing.
typedef BOOL (WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
#endif

//-----------------------------------------------------------------------------
VSTGLEditor::VSTGLEditor(AudioEffect *effect, WindowFlags flags):
AEffEditor(effect),
useVSync(false),
antialiasing(0)
{
	char tempstr[32];
	effect->setEditor(this);

	_rect.left = 0;
	_rect.top = 0;
	_rect.right = 0;
	_rect.bottom = 0;

	if((flags&WaitForVerticalSync) == WaitForVerticalSync)
		useVSync = true;
	if((flags&Antialias6x) == Antialias6x)
		antialiasing = 2;
	else if((flags&Antialias4x) == Antialias4x)
		antialiasing = 4;
	else if((flags&Antialias2x) == Antialias2x)
		antialiasing = 6;
	
	dc = 0;
	glRenderingContext = 0;

	//Register window class.
	WNDCLASSEX winClass;

	//most of this stuff is copied from VSTGUI
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	winClass.lpfnWndProc = GLWndProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = static_cast<HINSTANCE>(hInstance);
	winClass.hIcon = 0;
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winClass.lpszMenuName = 0;
	//sprintf(tempstr, "VSTGLWindow%08x", static_cast<HINSTANCE>(hInstance));
	sprintf(tempstr, "VSTGLWindow%08x", reinterpret_cast<int>(this));
	winClass.lpszClassName = tempstr;
	winClass.hIconSm = NULL;

	//Register the window class (this is unregistered in the VSTGLEditor
	//destructor).
	RegisterClassEx(&winClass);
}

//-----------------------------------------------------------------------------
VSTGLEditor::~VSTGLEditor()
{
#ifdef WIN32
	char tempstr[32];

	//sprintf(tempstr, "VSTGLWindow%08x", static_cast<HINSTANCE>(hInstance));
	sprintf(tempstr, "VSTGLWindow%08x", reinterpret_cast<int>(this));
	//unregisters the window class
	UnregisterClass(tempstr, static_cast<HINSTANCE>(hInstance));
#elif MACX
	//Unregister our HIView object.
	UnregisterToolboxObjectClass((ToolboxObjectClassRef)controlSpec.u.classRef);
#endif
}

//-----------------------------------------------------------------------------
bool VSTGLEditor::open(void *ptr)
{
	AEffEditor::open(ptr);
	createWindow();

	int tempint;
	dc = GetDC(tempHWnd);

	//Have to set the pixel format first...
	pixelformat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelformat.nVersion = 1;
    pixelformat.dwFlags = PFD_DRAW_TO_WINDOW |
						  PFD_SUPPORT_OPENGL |
						  PFD_DOUBLEBUFFER;
    pixelformat.iPixelType = PFD_TYPE_RGBA;
    pixelformat.cColorBits = 32;
    pixelformat.cRedBits = 0;
    pixelformat.cRedShift = 0;
    pixelformat.cGreenBits = 0;
    pixelformat.cGreenShift = 0;
    pixelformat.cBlueBits = 0;
    pixelformat.cBlueShift = 0;
    pixelformat.cAlphaBits = 0;
    pixelformat.cAlphaShift = 0;
    pixelformat.cAccumBits = 0;
    pixelformat.cAccumRedBits = 0;
    pixelformat.cAccumGreenBits = 0;
    pixelformat.cAccumBlueBits = 0;
    pixelformat.cAccumAlphaBits = 0;
    pixelformat.cDepthBits = 32;
    pixelformat.cStencilBits = 0;
    pixelformat.cAuxBuffers = 0;
    pixelformat.iLayerType = PFD_MAIN_PLANE;
    pixelformat.bReserved = 0;
    pixelformat.dwLayerMask = 0;
    pixelformat.dwVisibleMask = 0;
    pixelformat.dwDamageMask = 0;
	tempint = ChoosePixelFormat(dc, &pixelformat);
	SetPixelFormat(dc, tempint, &pixelformat);

	glRenderingContext = wglCreateContext(dc);
	wglMakeCurrent(dc, glRenderingContext);
	//If one of the antialiasing options was specified in the constructor,
	//try to switch it on.
	if(antialiasing)
		setupAntialiasing();
	//If WaitForVerticalSync was specified in the constructor, try to switch
	//it on.
	if(useVSync)
		setupVSync();
	guiOpen();
	
	return true;
}

//-----------------------------------------------------------------------------
void VSTGLEditor::close()
{
	setupContext();
	guiClose();
	swapBuffers();

#ifdef WIN32
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(glRenderingContext);
	ReleaseDC(tempHWnd, dc);
	DestroyWindow(tempHWnd);
#elif MACX
	aglSetCurrentContext(NULL);
	aglSetDrawable(context, NULL);
	if(context)
	{
		aglDestroyContext(context);
		context = NULL;
	}
	if(pixels)
	{
		aglDestroyPixelFormat(pixels);
		pixels = NULL;
	}

	HIViewRemoveFromSuperview(controlRef);

	if(controlRef)
		DisposeControl(controlRef);
#endif
}

//-----------------------------------------------------------------------------
void VSTGLEditor::refreshGraphics()
{
	setupContext();
	draw();
	swapBuffers();
}

#ifdef MACX
//-----------------------------------------------------------------------------
void VSTGLEditor::updateBounds(int x, int y)
{
	int tempHeight;
	Rect tempRect2;
	HIRect tempRect;

	//Get the new bounds of our dummy HIView.
	HIViewGetFrame(controlRef, &tempRect);

	//Invert tempRect's y-axis (honestly, who designed this API!).
	GetWindowBounds(window, kWindowContentRgn, &tempRect2);
	tempHeight = (tempRect2.bottom-tempRect2.top);
	tempRect.origin.y = tempHeight - tempRect.origin.y - tempRect.size.height;

	boundsX = (int)tempRect.origin.x;
	boundsY = (int)tempRect.origin.y;
}
#endif

//-----------------------------------------------------------------------------
//This is only necessary in Windows (and only really for Tracktion) - the
//window will have already been constructed for us on OS X.
void VSTGLEditor::createWindow()
{
#ifdef WIN32
	char tempstr[32];
	HWND parentHWnd = static_cast<HWND>(systemWindow);

	int winWidth = (_rect.right-_rect.left);
	int winHeight = (_rect.bottom-_rect.top);

	//sprintf(tempstr, "VSTGLWindow%08x", static_cast<HINSTANCE>(hInstance));
	sprintf(tempstr, "VSTGLWindow%08x", reinterpret_cast<int>(this));
	tempHWnd = CreateWindowEx(0,					//extended window style
							  tempstr,				//pointer to registered class name
							  "VSTGLEditor",		//pointer to window name
							  WS_CHILD|
							  WS_VISIBLE,			//window style
							  0,					//horizontal position of window
							  0,					//vertical position of window
							  winWidth,//window width
							  winHeight,//window height
							  parentHWnd,			//handle to parent or owner window
							  NULL,					//handle to menu, or child-window identifier
							  (HINSTANCE)hInstance,	//handle to application instance
							  NULL);				//pointer to window-creation data

	/* Variables */
	
	/* If Parent Window Is Set As Null, Get The Desktop Window */
	if(parentHWnd == NULL)
	{

		parentHWnd = GetDesktopWindow();

	}

	/* Get Parent Client Area Measurements */
	GetClientRect(parentHWnd, &rc);

	/* Center The Window */
	MoveWindow(
		parentHWnd,
		winWidth / 2,
		0,
		winWidth,
		winHeight,
		TRUE
		);

	//This is so we can send messages to this object from the message loop.
	SetWindowLong(tempHWnd, GWL_USERDATA, (long)this);
#endif
}

//-----------------------------------------------------------------------------
void VSTGLEditor::setupVSync()
{
#ifdef WIN32
	unsigned char *extensions;
	PFNWGLEXTSWAPCONTROLPROC wglSwapIntervalEXT = NULL;

	//Check the graphics card's extensions.
	extensions = const_cast<unsigned char *>(glGetString(GL_EXTENSIONS));
  
	//Check if extensions contains the vertical sync string.
	if(strstr(reinterpret_cast<char *>(extensions),"WGL_EXT_swap_control"))
	{
		//Get the address of the relevant functions.
		wglSwapIntervalEXT = reinterpret_cast<PFNWGLEXTSWAPCONTROLPROC>(wglGetProcAddress("wglSwapIntervalEXT"));

		//Turn it on.
		if(wglSwapIntervalEXT)
			wglSwapIntervalEXT(1);
	}
#elif MACX
	GLint swap = 1;

	//Some things are so much easier on OSX...
	aglSetInteger(context, AGL_SWAP_INTERVAL, &swap);
#endif
}

//-----------------------------------------------------------------------------
void VSTGLEditor::setupAntialiasing()
{
#ifdef WIN32
	unsigned char *extensions;
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
	int pixelFormat;
	UINT numFormats;
	float fAttributes[] = {0,0};

	//Check the graphics card's extensions.
	extensions = const_cast<unsigned char *>(glGetString(GL_EXTENSIONS));
  
	//Check if extensions contains the multisample string.
	if(strstr(reinterpret_cast<char *>(extensions),"GL_ARB_multisample"))
	{
		//Get the address of the relevant functions.
		wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");

		if(wglChoosePixelFormatARB)
		{
			int iAttributes[] = {
				WGL_DRAW_TO_WINDOW_ARB,GL_TRUE,
				WGL_SUPPORT_OPENGL_ARB,GL_TRUE,
				WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB,
				WGL_COLOR_BITS_ARB,24,
				WGL_ALPHA_BITS_ARB,8,
				WGL_DEPTH_BITS_ARB,16,
				WGL_STENCIL_BITS_ARB,0,
				WGL_DOUBLE_BUFFER_ARB,GL_TRUE,
				WGL_SAMPLE_BUFFERS_ARB,GL_TRUE,
				WGL_SAMPLES_ARB, antialiasing,
				0,0};

			//Try and get the correct pixel format.
			if(wglChoosePixelFormatARB(dc,
									   iAttributes,
									   fAttributes,
									   1,
									   &pixelFormat,
									   &numFormats))
			{
				if(numFormats > 0)
				{
					//Destroy the current window.
					wglMakeCurrent(NULL, NULL);
					wglDeleteContext(glRenderingContext);
					ReleaseDC(tempHWnd, dc);
					DestroyWindow(tempHWnd);

					//Create a new one with the correct pixel format.
					createWindow();
					dc = GetDC(tempHWnd);
					SetPixelFormat(dc, pixelFormat, &pixelformat);
					glRenderingContext = wglCreateContext(dc);
					wglMakeCurrent(dc, glRenderingContext);
				}
			}
		}
	}
#endif
}

//-----------------------------------------------------------------------------
void VSTGLEditor::setupContext()
{
#ifdef WIN32
	wglMakeCurrent(dc, glRenderingContext);
#elif MACX
	GLint tempBounds[4];

    tempBounds[0] = boundsX;
    tempBounds[1] = boundsY;
	tempBounds[2] = (_rect.right-_rect.left);
    tempBounds[3] = (_rect.bottom-_rect.top);

	//Move the port to the correct offset.
	aglSetInteger(context, AGL_BUFFER_RECT, tempBounds);
    aglEnable(context, AGL_BUFFER_RECT);

	//Also necessary for Bidule.
	aglSetCurrentContext(context);
#endif
}

//-----------------------------------------------------------------------------
void VSTGLEditor::swapBuffers()
{
#ifdef WIN32
	SwapBuffers(dc);
#elif MACX
	aglSwapBuffers(context);
#endif
}

//-----------------------------------------------------------------------------
void VSTGLEditor::setRect(int x, int y, int width, int height)
{
	_rect.left = x;
	_rect.top = y;
	_rect.right = x+width;
	_rect.bottom = y+height;
}

//-----------------------------------------------------------------------------
#ifdef WIN32

//Don't know why MSVC doesn't seem to recognise WM_MOUSEWHEEL for me...
//(this probably won't work)
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#endif

LONG WINAPI VSTGLEditor::GLWndProc(HWND hwnd,
								   UINT message,
								   WPARAM wParam,
								   LPARAM lParam)
{
	VstKeyCode tempkey;
	VSTGLEditor *ed = reinterpret_cast<VSTGLEditor *>(GetWindowLong(hwnd, GWL_USERDATA));

	/*
	int modifiers = 0;
	if (GetKeyState (VK_CONTROL) < 0)
		modifiers |= kGEventModifierControl;
	if (GetKeyState (VK_SHIFT) < 0)
		modifiers |= kGEventModifierShift;
	// added to achieve information from the ALT button
	if (GetKeyState (VK_MENU) < 0)
		modifiers |= kGEventModifierAlt;
	*/
	switch(message)
	{
		case WM_LBUTTONDOWN:
			if(ed)
			{
				SetCapture(hwnd);
				ed->onMouseDown(1,
								(int)(short)LOWORD(lParam),
								(int)(short)HIWORD(lParam));
			}
			break;
		case WM_MBUTTONDOWN:
			if(ed)
			{
				SetCapture(hwnd);
				ed->onMouseDown(3,
								(int)(short)LOWORD(lParam),
								(int)(short)HIWORD(lParam));
			}
			break;
		case WM_RBUTTONDOWN:
			if(ed)
			{
				SetCapture(hwnd);
				ed->onMouseDown(2,
								(int)(short)LOWORD(lParam),
								(int)(short)HIWORD(lParam));
			}
			break;
		case WM_LBUTTONUP:
			if(ed)
			{
				ReleaseCapture();
				ed->onMouseUp(1,
							  (int)(short)LOWORD(lParam),
							  (int)(short)HIWORD(lParam));
			}
			break;
		case WM_MBUTTONUP:
			if(ed)
			{
				ReleaseCapture();
				ed->onMouseUp(3,
							  (int)(short)LOWORD(lParam),
							  (int)(short)HIWORD(lParam));
			}
			break;
		case WM_RBUTTONUP:
			if(ed)
			{
				ReleaseCapture();
				ed->onMouseUp(2,
							  (int)(short)LOWORD(lParam),
							  (int)(short)HIWORD(lParam));
			}
			break;
		case WM_MOUSEMOVE:
			if(ed)
			{
				ed->onMouseMove((int)(short)LOWORD(lParam),
								(int)(short)HIWORD(lParam));
			}
			break;
		case WM_MOUSEWHEEL:
			if(ed)
				ed->onMouseWheel(HIWORD(wParam),
								 (int)(short)LOWORD(lParam),
								 (int)(short)HIWORD(lParam));
			break;
		case WM_KEYDOWN:
			if(ed)
			{
				//This could be improved?
				tempkey.character = wParam;
				ed->onGLKeyDown(tempkey);
			}
			break;
		case WM_KEYUP:
			if(ed)
			{
				tempkey.character = wParam;
				ed->onGLKeyUp(tempkey);
			}
			break;
		case WM_PAINT:
			if(ed)
				ed->idle();
			break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
#endif

//-----------------------------------------------------------------------------
#ifdef MACX
pascal OSStatus VSTGLEditor::macEventHandler(EventHandlerCallRef handler,
											 EventRef event,
											 void *userData)
{
	int width;
	int height;
	int tempHeight;
	Rect tempRect;
	int actualButton;
	EventMouseButton button;
	HIPoint location;
	EventMouseWheelAxis wheelAxis;
	SInt32 wheelDelta;
	UInt32 key;
	VstKeyCode tempKey;
	WindowRef win;
	Rect titleBounds;

	OSStatus result = eventNotHandledErr;
	VSTGLEditor *ed = static_cast<VSTGLEditor *>(userData);
	UInt32 eventClass = GetEventClass(event);
	UInt32 eventType = GetEventKind(event);

	if(ed)
	{
		if(eventClass == kEventClassMouse)
		{
			switch(eventType)
			{
				case kEventMouseDown:
					GetEventParameter(event,
									 kEventParamMouseButton,
									 typeMouseButton,
									 NULL,
									 sizeof(EventMouseButton),
									 NULL,
									 &button);
					GetEventParameter(event,
									 kEventParamWindowMouseLocation,
									 typeHIPoint,
									 NULL,
									 sizeof(HIPoint),
									 NULL,
									 &location);
					switch(button)
					{
						case kEventMouseButtonPrimary:
							actualButton = 1;
							break;
						case kEventMouseButtonSecondary:
							actualButton = 2;
							break;
						case kEventMouseButtonTertiary:
							actualButton = 3;
							break;
						default:
							actualButton = -1;
					}

					//Make sure we're not picking up a mouse click on the
					//title bar.
					win = ed->getWindowRef();
					GetWindowBounds(win, kWindowTitleBarRgn, &titleBounds);
					location.y -= (titleBounds.bottom - titleBounds.top);
					if(location.y > -1)
					{
						if(actualButton != -1)
							ed->onMouseDown(actualButton,
											static_cast<int>(location.x),
											static_cast<int>(location.y));
					}
					else
					{
						//So we can still click on the title bar.
						CallNextEventHandler(handler, event);
					}
					result = noErr;
					break;
				case kEventMouseUp:
					GetEventParameter(event,
									  kEventParamMouseButton,
									  typeMouseButton,
									  NULL,
									  sizeof(EventMouseButton),
									  NULL,
									  &button);
					GetEventParameter(event,
									  kEventParamWindowMouseLocation,
									  typeHIPoint,
									  NULL,
									  sizeof(HIPoint),
									  NULL,
									  &location);
					switch(button)
					{
						case kEventMouseButtonPrimary:
							actualButton = 1;
							break;
						case kEventMouseButtonSecondary:
							actualButton = 2;
							break;
						case kEventMouseButtonTertiary:
							actualButton = 3;
							break;
						default:
							actualButton = -1;
					}

					//Make sure we're not picking up a mouse click on the
					//title bar.
					win = ed->getWindowRef();
					GetWindowBounds(win, kWindowTitleBarRgn, &titleBounds);
					location.y -= (titleBounds.bottom - titleBounds.top);
					if(location.y > -1)
					{
						
						if(actualButton != -1)
						{
							ed->onMouseUp(actualButton,
										  static_cast<int>(location.x),
										  static_cast<int>(location.y));
						}
					}
					else
					{
						//So we can still click on the title bar.
						CallNextEventHandler(handler, event);
					}
					result = noErr;
					break;
				case kEventMouseMoved:
					width = ed->getWidth();
					height = ed->getHeight();

					GetEventParameter(event,
									  kEventParamWindowMouseLocation,
									  typeHIPoint,
									  NULL,
									  sizeof(HIPoint),
									  NULL,
									  &location);

					//Make sure we're not picking up a mouse click on the
					//title bar.
					win = ed->getWindowRef();
					GetWindowBounds(win, kWindowContentRgn, &tempRect);
					GetWindowBounds(win, kWindowTitleBarRgn, &titleBounds);
					location.y -= (titleBounds.bottom - titleBounds.top);
					if(location.y > -1)
					{
						tempHeight = (tempRect.bottom-tempRect.top);
						location.y -= tempHeight - ed->getBoundsY() - ed->getHeight();
						if(location.y < height)
						{
							location.x -= ed->getBoundsX();
							if((location.x > -1) && (location.x < width))
							{
								ed->onMouseMove(static_cast<int>(location.x),
												static_cast<int>(location.y));
							}
						}
					}
					result = noErr;
					break;
				//We handle dragging as well as moving events, because OS X
				//makes a specific distinction between them, whereas I
				//prefer to use the mouseUp and mouseDown events to tell
				//whether I'm supposed to be dragging...
				case kEventMouseDragged:
					width = ed->getWidth();
					height = ed->getHeight();

					GetEventParameter(event,
									  kEventParamWindowMouseLocation,
									  typeHIPoint,
									  NULL,
									  sizeof(HIPoint),
									  NULL,
									  &location);

					//Make sure we're not picking up a mouse click on the
					//title bar.
					win = ed->getWindowRef();
					GetWindowBounds(win, kWindowContentRgn, &tempRect);
					GetWindowBounds(win, kWindowTitleBarRgn, &titleBounds);
					location.y -= (titleBounds.bottom - titleBounds.top);
					if(location.y > -1)
					{
						tempHeight = (tempRect.bottom-tempRect.top);
						location.y -= tempHeight - ed->getBoundsY() - ed->getHeight();
						if(location.y < height)
						{
							location.x -= ed->getBoundsX();
							if((location.x > -1) && (location.x < width))
							{
								ed->onMouseMove(static_cast<int>(location.x),
												static_cast<int>(location.y));
							}
						}
					}
					result = noErr;
					break;
				case kEventMouseWheelMoved:
					GetEventParameter(event,
									  kEventParamMouseWheelAxis,
									  typeMouseWheelAxis,
									  NULL,
									  sizeof(EventMouseWheelAxis),
									  NULL,
									  &wheelAxis);
					GetEventParameter(event,
									  kEventParamMouseWheelDelta,
									  typeLongInteger,
									  NULL,
									  sizeof(SInt32),
									  NULL,
									  &wheelDelta);
					GetEventParameter(event,
									  kEventParamWindowMouseLocation,
									  typeHIPoint,
									  NULL,
									  sizeof(HIPoint),
									  NULL,
									  &location);

					//Make sure we're not picking up a mouse click on the
					//title bar.
					win = ed->getWindowRef();
					GetWindowBounds(win, kWindowTitleBarRgn, &titleBounds);
					location.y -= (titleBounds.bottom - titleBounds.top);
					if(location.y > -1)
					{
						if(wheelAxis == kEventMouseWheelAxisY)
						{
							ed->onMouseWheel(static_cast<int>(wheelDelta),
											 static_cast<int>(location.x),
											 static_cast<int>(location.y));
						}
					}
					result = noErr;
					break;
			}
		}
		else if(eventClass == kEventClassKeyboard)
		{
			switch(eventType)
			{
				case kEventRawKeyDown:
					GetEventParameter(event,
									  kEventParamKeyCode,
									  typeUInt32,
									  NULL,
									  sizeof(UInt32),
									  NULL,
									  &key);
					tempKey.character = key;
					ed->onGLKeyDown(tempKey);
					result = noErr;
					break;
				case kEventRawKeyUp:
					GetEventParameter(event,
									  kEventParamKeyCode,
									  typeUInt32,
									  NULL,
									  sizeof(UInt32),
									  NULL,
									  &key);
					tempKey.character = key;
					ed->onGLKeyUp(tempKey);
					result = noErr;
					break;
			}
		}
		else if((eventClass == kEventClassControl)||(eventClass == kEventClassWindow))
		{
			switch(eventType)
			{
				case kEventWindowBoundsChanged:
				case kEventControlBoundsChanged:
					Rect tempRect;
					OSStatus err;
					err = GetEventParameter(event,
									  kEventParamCurrentBounds, 
									  typeQDRectangle,
									  NULL,
									  sizeof(Rect),
									  NULL,
									  &tempRect);
					if(err == noErr)
						ed->updateBounds(tempRect.left, tempRect.top);
					else
						ed->updateBounds(0, 0);
					result = noErr;
					break;
				case kEventControlHitTest:
					{
						ControlPartCode part = 127;
						SetEventParameter(event, kEventParamControlPart, typeControlPartCode, sizeof(part), &part);
					}
					result = noErr;
					break;
				case kEventControlClick:
					GetEventParameter(event,
									 kEventParamMouseButton,
									 typeMouseButton,
									 NULL,
									 sizeof(EventMouseButton),
									 NULL,
									 &button);
					GetEventParameter(event,
									 kEventParamWindowMouseLocation,
									 typeHIPoint,
									 NULL,
									 sizeof(HIPoint),
									 NULL,
									 &location);
					switch(button)
					{
						case kEventMouseButtonPrimary:
							actualButton = 1;
							break;
						case kEventMouseButtonSecondary:
							actualButton = 2;
							break;
						case kEventMouseButtonTertiary:
							actualButton = 3;
							break;
						default:
							actualButton = -1;
					}

					//Make sure we're not picking up a mouse click on the
					//title bar.
					if(actualButton != -1)
					{
						ed->onMouseDown(actualButton,
										static_cast<int>(location.x),
										static_cast<int>(location.y));
					}
					result = noErr;
					break;
				case kEventControlContextualMenuClick:
					GetEventParameter(event,
									 kEventParamMouseButton,
									 typeMouseButton,
									 NULL,
									 sizeof(EventMouseButton),
									 NULL,
									 &button);
					GetEventParameter(event,
									 kEventParamWindowMouseLocation,
									 typeHIPoint,
									 NULL,
									 sizeof(HIPoint),
									 NULL,
									 &location);
					switch(button)
					{
						case kEventMouseButtonPrimary:
							actualButton = 1;
							break;
						case kEventMouseButtonSecondary:
							actualButton = 2;
							break;
						case kEventMouseButtonTertiary:
							actualButton = 3;
							break;
						default:
							actualButton = -1;
					}

					//Make sure we're not picking up a mouse click on the
					//title bar.
					if(actualButton != -1)
					{
						ed->onMouseDown(actualButton,
										static_cast<int>(location.x),
										static_cast<int>(location.y));
					}
					result = noErr;
					break;
				case kEventControlTrack:
					result = noErr;
					break;
				case kEventControlHiliteChanged:
					result = noErr;
					break;
				case kEventControlDraw:
					result = noErr;
					break;
				default:
					CallNextEventHandler(handler, event);
			}
		}
	}

	return result;
}

#endif
