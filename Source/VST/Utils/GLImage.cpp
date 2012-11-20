#include "GLImage.h"
#include "GLHelpers.h"

GuiImage::GuiImage(int pngId)
{
	GlHelpers::GetTexture(pngId, &textureId, &width, &height);
	this->imageAssetCode = pngId;
}


GuiImage::~GuiImage(void)
{
}

void GuiImage::bind()
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}
