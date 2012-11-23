#include "GLImage.h"
#include "GLHelpers.h"
#include "../Gui/Components/GuiImageManager.h"

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

void GuiImage::SetSpriteSheet(GSpriteCollection* sprites)
{
	if (sprites > 0)
	{
		this->spriteCollection = sprites;
		spriteCollection->imageWidth = width;
		spriteCollection->imageHeight = height;		
		spriteCollection->pixelSizeX = 1.0f/width;
		spriteCollection->pixelSizeY = 1.0f/height;
	}	
}