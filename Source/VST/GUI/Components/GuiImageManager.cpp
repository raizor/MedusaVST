#include "GuiImageManager.h"

GuiImageManager* GuiImageManager::instance = 0;

void GuiImageManager::InitInstance()
{
	instance = new GuiImageManager();
}

GuiImageManager::GuiImageManager(void)
{
	glImages = new imageStack(1000);

	// add the images
	glImages->push(new GuiImage(IDB_PNG_PANEL_MAIN)); // main panel	
	glImages->push(new GuiImage(IDB_KNOBS_UNI)); // bi focus knobs
	glImages->push(new GuiImage(IDB_KNOBS_BI)); // bi knobs
	glImages->push(new GuiImage(IDB_PNG_KNOB_SURROUND)); // bi focus knobs
	glImages->push(new GuiImage(IDB_KEYBOARD_OVERLAYS)); // item panel
}

GuiImageManager::~GuiImageManager(void)
{
}

GuiImage* GuiImageManager::GetImageById(int id)
{
	for(int i=0; i<glImages->count; i++)
	{
		GuiImage* img = glImages->GetItem(i);
		if (img->imageAssetCode == id)
		{
			return img;
		}
	}
	return 0; // oops
}
