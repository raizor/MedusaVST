#include "GuiPanelHeader.h"
#include "GuiMainWindow.h"
#include "GuiPanelMain.h"

GuiButton* GuiPanelHeader::butPatch = 0;
GuiButton* GuiPanelHeader::butPatchFx = 0;
GuiButton* GuiPanelHeader::butGlobalFx = 0;


GuiPanelHeader::GuiPanelHeader(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	butPatch = new GuiButton(120, 28, 0, 139, IDB_BUTTONSTRIP, kSpritesButtons_But_patch, kSpritesButtons_But_patch_lit, kSpritesButtons_None);
	butPatch->buttonType = kButtonTypePage;
	butPatch->state = kButtonStateOn;
	butPatch->ClickedHandler = (FpClickedCallback)&GuiPanelHeader::CallbackClicked;
	AddSubComponent(butPatch);

	butPatchFx = new GuiButton(120, 28, 120, 139, IDB_BUTTONSTRIP, kSpritesButtons_But_patchFx, kSpritesButtons_But_patchFx_lit, kSpritesButtons_None);
	butPatchFx->buttonType = kButtonTypePage;
	butPatchFx->state = kButtonStateOff;
	butPatchFx->ClickedHandler = (FpClickedCallback)&GuiPanelHeader::CallbackClicked;
	AddSubComponent(butPatchFx);

	butGlobalFx = new GuiButton(120, 28, 240, 139, IDB_BUTTONSTRIP, kSpritesButtons_But_globalFx, kSpritesButtons_But_globalFx_lit, kSpritesButtons_None);
	butGlobalFx->buttonType = kButtonTypePage;
	butGlobalFx->state = kButtonStateOff;
	butGlobalFx->ClickedHandler = (FpClickedCallback)&GuiPanelHeader::CallbackClicked;
	AddSubComponent(butGlobalFx);
}


GuiPanelHeader::~GuiPanelHeader(void)
{
}


void GuiPanelHeader::CallbackClicked(void* data, GEvent* evt)
{
	GuiPanelHeader::butPatch->state = data == GuiPanelHeader::butPatch ? kButtonStateOn : kButtonStateOff;
	GuiPanelHeader::butPatchFx->state = data == GuiPanelHeader::butPatchFx ? kButtonStateOn : kButtonStateOff;
	GuiPanelHeader::butGlobalFx->state = data == GuiPanelHeader::butGlobalFx ? kButtonStateOn : kButtonStateOff;

	if (GuiPanelHeader::butPatch->state == kButtonStateOn)
	{
		GuiMainWindow::panelMain->panelNumber = kPanelPatch;
		GuiMainWindow::panelMain->panelPatch->enabled = true;
		GuiMainWindow::panelMain->panelPatchFx->enabled = false;
		GuiMainWindow::panelMain->panelGlobalFx->enabled = false;
	}

	if (GuiPanelHeader::butPatchFx->state == kButtonStateOn)
	{
		GuiMainWindow::panelMain->panelNumber = kPanelPatchFx;
		GuiMainWindow::panelMain->panelPatch->enabled = false;
		GuiMainWindow::panelMain->panelPatchFx->enabled = true;
		GuiMainWindow::panelMain->panelGlobalFx->enabled = false;
	}

	if (GuiPanelHeader::butGlobalFx->state == kButtonStateOn)
	{
		GuiMainWindow::panelMain->panelNumber = KPanelGlobalFx;
		GuiMainWindow::panelMain->panelPatch->enabled = false;
		GuiMainWindow::panelMain->panelPatchFx->enabled = false;
		GuiMainWindow::panelMain->panelGlobalFx->enabled = true;
	}

	/*
	char msg[100];
	for (int i=0; i<GuiMainWindow::panelOsc->butOscs.size(); i++)
	{
		if (data == GuiMainWindow::panelOsc->butOscs[i])
		{
			sprintf(&msg[0], "osc %d", i);
			DebugPrintLine(msg);
			Osc* osc = (Osc*)PatchList::list->CurrentPatch->items[NUMBER_START_OSC+i];
			GuiMainWindow::panelOsc->SetStackItem(osc);
			return;
		}

		if (data == GuiMainWindow::panelOsc->butEnabled)
		{
			DebugPrintLine("EN");
			return;
		}		
	}*/

}
