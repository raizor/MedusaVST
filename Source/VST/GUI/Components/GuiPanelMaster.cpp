#include "GuiPanelMaster.h"


GuiPanelMaster::GuiPanelMaster(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	butLimit = new GuiButton(32, 26, 236, 10, IDB_BUTTONSTRIP, kSpritesButtons_But_master_limit_off, kSpritesButtons_But_master_limit_on, kSpritesButtons_None);
	AddSubComponent(butLimit);

	// labels
	labPolyphony = new GuiLabel(80, 20, 20, 150, "0", true);
	AddSubComponent(labPolyphony);
	
	labTranspose = new GuiLabel(80, 20, 112, 150, "0", true);
	AddSubComponent(labTranspose);

	labVoices = new GuiLabel(80, 20, 20, 182, "0", true);
	AddSubComponent(labVoices);

	labTune = new GuiLabel(80, 20, 112, 182, "0", true);
	AddSubComponent(labTune);

	labParamName = new GuiLabel(80, 20, 63, 60, "OSC TYPE", true, kGuiLabelSizeLarge);
	AddSubComponent(labParamName); 

	labParamValue = new GuiLabel(80, 20, 63, 99, "Sine", true, kGuiLabelSizeLarge);
	AddSubComponent(labParamValue); 
}


GuiPanelMaster::~GuiPanelMaster(void)
{
}

void GuiPanelMaster::SetParamName(char* text)
{
	sprintf(labParamName->text, text);
}

void GuiPanelMaster::SetParamValue(char* text)
{
	sprintf(labParamValue->text, text);
}
void GuiPanelMaster::SetPolyphony(char* text)
{
	sprintf(labPolyphony->text, text);
}
void GuiPanelMaster::SetTranspose(char* text)
{
	sprintf(labTranspose->text, text);
}
void GuiPanelMaster::SetVoices(char* text)
{
	sprintf(labVoices->text, text);
}
void GuiPanelMaster::SetTune(char* text)
{
	sprintf(labTune->text, text);
}