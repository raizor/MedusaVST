#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"


class GuiImage
{
public:
	int imageAssetCode;
	GLuint textureId;
	GLint width;
	GLint height;
	GLenum eFormat;
		
	GuiImage(int pngId);
	~GuiImage(void);
	
	void bind();
};

