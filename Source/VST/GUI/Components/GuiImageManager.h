#pragma once
#include "../../includes.h"

class GuiImageManager
{
public:
	static GuiImageManager* instance;
	GuiImageManager(void);
	~GuiImageManager(void);
	GuiImage* GetImageById(int id);
	static void InitInstance();
private:
	imageStack* glImages;
};

