#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class Osc;

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

	GuiLabel* labWaveType;
	GuiLabel* labTranspose;
	GuiLabel* labOctave;
	GuiLabel* labMode;
	GuiLabel* labModMode;
	
	std::vector<GuiButton*> butOscs;

	GuiButtonStrip* butStripOscs;
	
	GuiPanelOsc(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelOsc(void);
	virtual void SetStackItem(Osc* item);
};

