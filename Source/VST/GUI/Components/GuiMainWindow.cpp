#include "GuiMainWindow.h"
#include "GuiStackItem.h"

GuiMainWindow::GuiMainWindow(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{		
	currentPatch = NULL;
	//subComponents->push(new GuiStackItem(0,0,0,0,IDB_PNG_ITEM_PANEL));
}

void GuiMainWindow::PatchChanged(Patch* patch)
{
	currentPatch = patch;
	int itemHeight = GLImageManager::instance->GetImageById(IDB_PNG_ITEM_PANEL)->height;
	int y = 0;
	for(int i=0; i<patch->numItems; i++)
	{
		subComponents->push(new GuiStackItem(0, 0, 0, y, IDB_PNG_ITEM_PANEL));
		y+=itemHeight;
	}
}

GuiMainWindow::~GuiMainWindow(void)
{
}