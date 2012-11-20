#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelOsc : public GuiComponent
{
public:
	GuiKnob* knobFinetune;
	GuiKnob* knobPhase;
	GuiKnob* knobLevel;
	GuiKnob* knob;

	GuiSlider* sliderFilter;
	
	GuiButton* butEnabled;

	GuiButton* butType;
	GuiButton* butTrans;
	GuiButton* butOctave;
	GuiButton* butMode;
	GuiButton* butMod;
	
	GuiButton** butOscs;

	GuiPanelOsc(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelOsc(void);
};

