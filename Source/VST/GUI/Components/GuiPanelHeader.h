#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "../../Utils/ContextMenus.h"

class GuiPanelHeader  : public GuiComponent
{
public:
	static GuiButton* butPatch;
	static GuiButton* butPatchFx;
	static GuiButton* butGlobalFx;
	static GuiButton* butDisk;
	static GuiButton* butExit;

	static GuiComponent* imgPatchNameBox;
	static GuiComponent* imgPatchNoBox;

	static GuiButton* butNextPatch;
	static GuiButton* butPrevPatch;

	static GuiLabel* labPatchName;
	static GuiLabel* labPatchNum;

	static GContextMenuEx* contextMenu;

	GuiPanelHeader(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelHeader(void);
	void GuiPanelHeader::HandlePatchChanged();
	void CallbackClicked(void* data, GEvent* evt);
	void GuiPanelHeader::CallbackEdited(void* data, GEvent* evt);
};

