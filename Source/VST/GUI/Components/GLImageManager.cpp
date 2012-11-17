#include "GLImageManager.h"

GLImageManager* GLImageManager::instance = 0;

void GLImageManager::InitInstance()
{
	instance = new GLImageManager();
}

GLImageManager::GLImageManager(void)
{
	glImages = new imageStack(1000);

	// add the images
	glImages->push(new GLImage(IDB_PNG_MAIN)); // main panel
	glImages->push(new GLImage(IDB_PNG_ITEM_PANEL)); // item panel
}

GLImageManager::~GLImageManager(void)
{
}

GLImage* GLImageManager::GetImageById(int id)
{
	for(int i=0; i<glImages->count; i++)
	{
		GLImage* img = glImages->GetItem(i);
		if (img->imageAssetCode == id)
		{
			return img;
		}
	}
	return 0; // oops
}
