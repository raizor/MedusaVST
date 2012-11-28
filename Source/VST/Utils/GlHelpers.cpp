#include "GlHelpers.h"
#include "loaders/stb_image.h"

extern void* hInstance;

GlHelpers::GlHelpers(void)
{
}


GlHelpers::~GlHelpers(void)
{
}

void GlHelpers::ViewOrthagnonal(GLdouble width, GLdouble height)
{
	glMatrixMode(GL_PROJECTION);                    // Select Projection
	glPushMatrix();                         // Push The Matrix
	glLoadIdentity();                       // Reset The Matrix
	glOrtho( 0, width , height , 0, -1, 1 );             // Select Ortho Mode (ie.640x480)
	glMatrixMode(GL_MODELVIEW);                 // Select Modelview Matrix
	glPushMatrix();                         // Push The Matrix
	glLoadIdentity();                       // Reset The Matrix
}

void GlHelpers::ViewPerspective()
{
	glMatrixMode( GL_PROJECTION );                  // Select Projection
	glPopMatrix();                          // Pop The Matrix
	glMatrixMode( GL_MODELVIEW );                   // Select Modelview
	glPopMatrix();                          // Pop The Matrix
}

GLbyte* GlHelpers::LoadPNG(int resourceId, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	HRSRC		rec;
	HGLOBAL		handle;

	LPCSTR lpResourceId = MAKEINTRESOURCE(resourceId);
	
	rec = FindResource((HMODULE)hInstance, lpResourceId, "PNG");
	handle = LoadResource((HMODULE)hInstance, rec);

	void* data = LockResource(handle);
	int size = SizeofResource((HMODULE)hInstance, rec);

	//stbi_load_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp, int req_comp)';
	int req_comp = 4;
	GLbyte* pixels = (GLbyte*)stbi_load_from_memory((unsigned char*)data, size, iWidth, iHeight, iComponents, req_comp);

	// TODO: invert Y

	*eFormat = GL_RGBA;
	*iComponents = GL_RGBA8;

	return pixels;
}

bool GlHelpers::GetTexture(int resourceId, GLuint* textureId, GLint* width, GLint* height, bool genMipmaps, int minFilter, int magFilter, int wrapS, int wrapT)
{
	GLint icomps;
	GLenum eFormat;
	GLbyte *pixels = LoadPNG(resourceId, width, height, &icomps, &eFormat );
	glGenTextures(1, textureId);
	glBindTexture(GL_TEXTURE_2D, *textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, icomps, *width, *height, 0, eFormat, GL_UNSIGNED_BYTE, pixels );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering

	free(pixels);

	/*
	GLint icomps;
	GLenum eFormat;
	GLbyte *pixels = LoadPNG(resourceId, width, height, &icomps, &eFormat );
	glGenTextures(1, textureId);
	glBindTexture(GL_TEXTURE_2D, *textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, icomps, *width, *height, 0, eFormat, GL_UNSIGNED_BYTE, pixels );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, minFilter); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, magFilter); // Linear Filtering
	if (genMipmaps)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); 
	}else{
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE); 
	}

	free(pixels);*/




	return true;
}
