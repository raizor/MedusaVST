#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"
#include "Types.h"

class GuiImage
{
public:
	int imageAssetCode;
	GSpriteCollection* spriteCollection;
	GLuint textureId;
	GLint width;
	GLint height;
	GLenum eFormat;
		
	GuiImage(int pngId);
	~GuiImage(void);
	void SetSpriteSheet(GSpriteCollection* sprites);
	
	void bind();
};

