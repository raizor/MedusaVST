#pragma once
#include "../../includes.h"

class GuiImageManager
{
public:
	GuiImageManager(void);
	~GuiImageManager(void);
	GuiImage* GetImageById(int id);
	static GuiImageManager* instance;
	static void InitInstance();
private:
	imageStack* glImages;
};

