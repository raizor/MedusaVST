#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class Adsr;

class GuiPanelEg : public GuiComponent
{
public:
	Adsr* itemAdsr;	
	GuiKnob* knobLevelAmount;
	GuiKnob* knobDelayTime;
	GuiKnob* knobStartLevel;
	GuiKnob* knobAttackTime;
	GuiKnob* knobDecayTime;
	GuiKnob* knobDecayLevel;
	GuiKnob* knobSustainTime;
	GuiKnob* knobSustainLevel;
	GuiKnob* knobReleaseTime;
	GuiKnob* knobReleaseLevel;

	GuiSlider* sliderFilter;
	
	GuiButton* butEnabled;

	GuiButton* butType;
	GuiButton* butTrans;
	GuiButton* butOctave;
	GuiButton* butMode;
	GuiButton* butMod;

	std::vector<GuiButton*> butEgs;

	GuiPanelEg(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelEg(void);

	void SetEg(Adsr* adsr);
};

