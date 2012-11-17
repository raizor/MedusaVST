#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"


class GLImage
{
public:
	int imageAssetCode;
	GLuint textureId;
	GLint width;
	GLint height;
	GLenum eFormat;
		
	GLImage(int pngId);
	~GLImage(void);
	
	void bind();
};

