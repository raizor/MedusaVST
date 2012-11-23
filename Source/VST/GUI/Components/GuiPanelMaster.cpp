#include "GuiPanelMaster.h"


GuiPanelMaster::GuiPanelMaster(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	butLimit = new GuiButton(32, 26, 236, 10, IDB_BUTTONSTRIP, kSpritesButtons_But_master_limit_off, kSpritesButtons_But_master_limit_on, kSpritesButtons_None);
	AddSubComponent(butLimit);
}


GuiPanelMaster::~GuiPanelMaster(void)
{
}
