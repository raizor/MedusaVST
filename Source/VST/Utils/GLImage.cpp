#include "GLImage.h"
#include "GLHelpers.h"

GLImage::GLImage(int pngId)
{
	GlHelpers::GetTexture(pngId, &textureId, &width, &height);
	this->imageAssetCode = pngId;
}


GLImage::~GLImage(void)
{
}

void GLImage::bind()
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}
