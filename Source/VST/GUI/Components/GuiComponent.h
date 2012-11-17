#pragma once

#include "../../includes.h"
#include "GLImageManager.h"

class GuiComponent
{
public:
	int width, height;
	int offsetX, offsetY;
	bool dirty;
	GLImage* image;
	objectStack* subComponents;
	GuiComponent(int width, int height, int offsetX, int offsetY, int imageId = 0);
	bool SetImage(int imageId);
	~GuiComponent(void);

	virtual void draw();
	void AddComponent(GuiComponent* component);
};

