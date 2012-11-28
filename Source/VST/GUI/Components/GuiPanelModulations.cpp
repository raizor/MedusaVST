#include "GuiPanelModulations.h"

GuiPanelModulations::GuiPanelModulations(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	butNums= new GuiButton(54, 27, 575, 10, IDB_BUTTONSTRIP, kSpritesButtons_But_mod_1_8, kSpritesButtons_But_mod_9_16, kSpritesButtons_None);
	AddSubComponent(butNums);
}


GuiPanelModulations::~GuiPanelModulations(void)
{
}
