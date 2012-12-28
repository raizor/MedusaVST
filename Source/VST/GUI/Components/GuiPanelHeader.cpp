#include "GuiPanelHeader.h"
#include "GuiMainWindow.h"
#include "GuiPanelMain.h"
#include "Utils/Patch.h"
#include "Utils/VoicePool.h"
#include "../../Utils/filedialog.h"
#include "../../fileio.h"


GuiButton* GuiPanelHeader::butPatch = 0;
GuiButton* GuiPanelHeader::butPatchFx = 0;
GuiButton* GuiPanelHeader::butGlobalFx = 0;
GuiButton* GuiPanelHeader::butExit = 0;
GuiButton* GuiPanelHeader::butDisk = 0;

GuiButton* GuiPanelHeader::butPrevPatch = 0;
GuiButton* GuiPanelHeader::butNextPatch = 0;
GuiComponent* GuiPanelHeader::imgPatchNameBox = 0;
GuiComponent* GuiPanelHeader::imgPatchNoBox = 0;
GuiLabel* GuiPanelHeader::labPatchName = 0;
GuiLabel* GuiPanelHeader::labPatchNum = 0;

GContextMenuEx* GuiPanelHeader::contextMenu = 0;

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

	butDisk = new GuiButton(36, 36, 2, 2, IDB_BUTTONSTRIP, kSpritesButtons_SaveDisk, kSpritesButtons_SaveDisk, kSpritesButtons_None);
	butDisk->buttonType = kButtonTypeDisk;
	butDisk->state = kButtonStateOff;
	butDisk->ClickedHandler = (FpClickedCallback)&GuiPanelHeader::CallbackClicked;
	AddSubComponent(butDisk);

	butExit = new GuiButton(36, 36, 880, 2, IDB_BUTTONSTRIP, kSpritesButtons_Exit, kSpritesButtons_Exit, kSpritesButtons_None);
	butExit->buttonType = kButtonTypeExit;
	butExit->state = kButtonStateOff;
	butExit->ClickedHandler = (FpClickedCallback)&GuiPanelHeader::CallbackClicked;
	AddSubComponent(butExit);

	imgPatchNameBox = new GuiComponent(0, 0, 368, 142, IDB_BUTTONSTRIP, kSpritesButtons_Box_patchName);
	AddSubComponent(imgPatchNameBox);

	imgPatchNoBox = new GuiComponent(0, 0, 750, 142, IDB_BUTTONSTRIP, kSpritesButtons_Box_patchNum);
	AddSubComponent(imgPatchNoBox);

	labPatchName = new GuiLabel(100, 20, 374, 146, "hello", false, kGuiLabelSizeSmall);
	labPatchName->ClickedHandler = (FpClickedCallback)&GuiPanelHeader::CallbackClicked;
	labPatchName->EditedHandler = (FpClickedCallback)&GuiPanelHeader::CallbackEdited;
	AddSubComponent(labPatchName);

	labPatchNum = new GuiLabel(100, 20, 735, 146, "1 / 100", true, kGuiLabelSizeSmall);
	AddSubComponent(labPatchNum);

	butPrevPatch = new GuiButton(36, 36, 710, 137, IDB_BUTTONSTRIP, kSpritesButtons_But_left, kSpritesButtons_But_left, kSpritesButtons_None);
	butPrevPatch->buttonType = kButtonTypeNav;
	butPrevPatch->state = kButtonStateOff;
	butPrevPatch->ClickedHandler = (FpClickedCallback)&GuiPanelHeader::CallbackClicked;
	AddSubComponent(butPrevPatch);

	butNextPatch = new GuiButton(36, 36, 825, 137, IDB_BUTTONSTRIP, kSpritesButtons_But_right, kSpritesButtons_But_right, kSpritesButtons_None);
	butNextPatch->buttonType = kButtonTypeNav;
	butNextPatch->state = kButtonStateOff;
	butNextPatch->ClickedHandler = (FpClickedCallback)&GuiPanelHeader::CallbackClicked;
	AddSubComponent(butNextPatch);
}


GuiPanelHeader::~GuiPanelHeader(void)
{
}

void GuiPanelHeader::HandlePatchChanged()
{
	GuiMainWindow::panelOsc->SetStackItem((Osc*)PatchList::list->CurrentPatch->items[NUMBER_START_OSC]);
	GuiMainWindow::panelEg->SetStackItem((Adsr*)PatchList::list->CurrentPatch->egAmp);
	GuiMainWindow::panelFilter->SetStackItem((SimpleFilter*)PatchList::list->CurrentPatch->items[NUMBER_START_FILTER], (SimpleFilter*)PatchList::list->CurrentPatch->items[NUMBER_START_FILTER+1]);
	GuiMainWindow::panelModMatrix->UpdateGrid();
	char* patchName = new char[50];
	sprintf(patchName, PatchList::list->CurrentPatch->name);
	labPatchName->SetText(patchName);
}


void GuiPanelHeader::CallbackEdited(void* data, GEvent* evt)
{
	sprintf(PatchList::list->CurrentPatch->name, labPatchName->text);
}

void GuiPanelHeader::CallbackClicked(void* data, GEvent* evt)
{
	if (data == labPatchName)
	{
		GuiMainWindow::panelHeader->labPatchName->isEditing = true;
		GuiMainWindow::editingComponent = GuiMainWindow::panelHeader->labPatchName;
	}

	if (data == butNextPatch)
	{
		int num = PatchList::list->CurrentPatch->number+1 < 99 ? PatchList::list->CurrentPatch->number+1 : PatchList::list->CurrentPatch->number;
		PatchList::list->CurrentPatch = PatchList::list->patches[num];
		HandlePatchChanged();
		char* txt = new char[10];
		sprintf(txt, "%d / 100", num+1);
		labPatchNum->SetText(txt);
		//CurrentPatch = PatchList::list->CurrentPatch;
		//PatchList::list->CurrentPatch = PatchList::list->patches[PatchList::list->CurrentPatch->number++];
	}else if (data == butPrevPatch)
	{
		int num = PatchList::list->CurrentPatch->number-1 > -1 ? PatchList::list->CurrentPatch->number-1: PatchList::list->CurrentPatch->number;
		PatchList::list->CurrentPatch = PatchList::list->patches[num];
		HandlePatchChanged();
		char* txt = new char[10];
		sprintf(txt, "%d / 100", num+1);
		labPatchNum->SetText(txt);
	}else if (data == butExit)
	{
		VoicePool::Pool->StopAllVoices();
	
	}else if (data == butDisk)
	{
		contextMenu = new GContextMenuEx();
		int id = 1000;
		int idLoadBank = id++;
		int idSaveBank = id++;
		int idResetBank = id++;

		GContextMenuEx* menuItem = new GContextMenuEx();
		contextMenu->AddMenu(menuItem, "Bank");

		menuItem->AddItem(idLoadBank, "Load Bank");
		menuItem->AddItem(idSaveBank, "Save Bank");
		menuItem->AddItem(idResetBank, "Reset Bank");

		GPoint gp;
		gp.x = 0;
		gp.y = 0;
		int selectedId = contextMenu->SelectAt(evt->pos);
		if (selectedId == idLoadBank)
		{
			int res = SpawnLoadFileDialog();
			if (res == kDialogFileChosen)
			{
				ZynthIo::LoadBankFromFile(DialogResult());
				HandlePatchChanged();
			}
		}

		if (selectedId == idSaveBank)
		{
			int res = SpawnSaveFileDialog();
			if (res == kDialogFileChosen)
			{
				ZynthIo::SaveBankToFile(DialogResult());
			}
		}
	}else{
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

}
