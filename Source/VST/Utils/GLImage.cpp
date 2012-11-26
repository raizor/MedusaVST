#include "GLImage.h"
#include "GLHelpers.h"
#include "../Gui/Components/GuiImageManager.h"

GuiImage::GuiImage(int pngId)
{
	GlHelpers::GetTexture(pngId, &textureId, &width, &height);
	this->imageAssetCode = pngId;
	this->spriteCollection = 0;

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

bool GuiImage::HasSprites()
{
	return this->spriteCollection != 0;
}

void GuiImage::drawSprite(GSprite* sprite, int x, int y)
{
	float pixSizeX = sprite->spriteCollection->pixelSizeX; 
	float pixSizeY = sprite->spriteCollection->pixelSizeY;

	float x1 = pixSizeX * sprite->posX;
	float y1 = pixSizeY * sprite->posY;

	float x2 = x1 + (sprite->width*pixSizeX);
	float y2 = y1 + (sprite->height*pixSizeY);

	glTexCoord2f(x1,y1);
	glVertex2i(x,y);

	glTexCoord2f(x1,y2);
	glVertex2i(x, y+sprite->height);

	glTexCoord2f(x2,y2);
	glVertex2i(x+sprite->width, y+sprite->height);

	glTexCoord2f(x2,y1);
	glVertex2i(x+sprite->width, y);
}