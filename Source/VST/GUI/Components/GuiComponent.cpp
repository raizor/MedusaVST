#include "GuiComponent.h"

GuiComponent::GuiComponent(int width, int height, int offsetX, int offsetY, int imageId)
{
	dirty = true;
	this->width = width;
	this->height = height;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	subComponents = new objectStack(1000);
	if (imageId !=0)
	{
		image = GLImageManager::instance->GetImageById(imageId);
		if (width == 0) this->width = image->width;
		if (height == 0) this->height = image->height;
		int xx = 1;
	}
}


GuiComponent::~GuiComponent(void)
{
}

bool GuiComponent::SetImage(int imageId)
{
	image = GLImageManager::instance->GetImageById(imageId);
	return image > 0;
}

void GuiComponent::draw()
{
	//if (!dirty) return; // doesn't need drawing

	image->bind();
	//glColor4f(1,1,1,1);
	glBegin(GL_QUADS);

	glTexCoord2f(0,0);
	glVertex2i(offsetX,offsetY);

	glTexCoord2f(0,1);
	glVertex2i(offsetX,offsetY+height);

	glTexCoord2f(1,1);
	glVertex2i(offsetX+width,offsetY+height);

	glTexCoord2f(1,0);
	glVertex2i(offsetX+width,offsetY);

	glEnd();

	// draw sub components last as they likely appear on top of this component
	for(int i=0; i<subComponents->count; i++)
	{
		GuiComponent* gc = (GuiComponent*)subComponents->items[i];
		gc->dirty = dirty; // mark children as dirty as we're dirty, dirty children!!
		gc->draw();
	}

	dirty = false;

}

void GuiComponent::AddComponent(GuiComponent* component)
{
	subComponents->push(component);
}
