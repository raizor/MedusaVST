#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelMaster : public GuiComponent
{
public:
	GuiLabel* labPolyphony;
	GuiLabel* labTranspose;
	GuiLabel* labVoices;
	GuiLabel* labTune;

	GuiLabel* labParamName;
	GuiLabel* labParamValue;

	GuiButton* butLimit;
	GuiPanelMaster(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelMaster(void);

	void SetParamName(char* text);
	void SetParamValue(char* text);
	void SetPolyphony(char* text);
	void SetTranspose(char* text);
	void SetVoices(char* text);
	void SetTune(char* text);
};

