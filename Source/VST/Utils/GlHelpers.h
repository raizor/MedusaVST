#pragma once

#include "../../includes.h"

class GlHelpers
{
public:
	GlHelpers(void);
	~GlHelpers(void);
	static void ViewOrthagnonal(GLdouble width, GLdouble height);
	static void ViewPerspective();

	static GLbyte* LoadPNG(int resourceId, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);
	static bool GetTexture(int resourceId, GLuint* textureId, GLint* width, GLint* height);
};

