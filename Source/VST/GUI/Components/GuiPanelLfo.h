#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelLfo : public GuiComponent
{
public:
	GuiKnob* knobOffset;
	GuiKnob* knobDelay;
	GuiKnob* knobFadeIn;

	GuiSlider* sliderFilter;
	
	GuiButton* butEnabled;

	GuiButton* butType;
	GuiButton* butTrans;
	GuiButton* butOctave;
	GuiButton* butMode;
	GuiButton* butMod;
	
	std::vector<GuiButton*> butsAv;
	std::vector<GuiButton*> butPv;

	GuiPanelLfo(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelLfo(void);
};

