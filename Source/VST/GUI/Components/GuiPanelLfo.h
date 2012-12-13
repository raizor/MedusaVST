#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "Displays/GuiDisplayWave.h"

class Lfo;

class GuiPanelLfo : public GuiComponent
{
public:
	GuiKnob* knobOffset;
	GuiKnob* knobDelay;
	GuiKnob* knobFadeIn;

	GuiSlider* sliderMorph;
	GuiSlider* sliderSpeed;
	GuiSlider* sliderAmount;
	
	GuiButton* butEnabled;

	GuiButton* butType;
	GuiButton* butTrans;
	GuiButton* butOctave;
	GuiButton* butMode;
	GuiButton* butMod;
	
	std::vector<GuiButton*> butsAv;
	std::vector<GuiButton*> butPv;

	GuiDisplayWave* displayWave;

	GuiLabel* labWaveType1;
	GuiLabel* labWaveType2;

	GuiPanelLfo(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelLfo(void);
	void GuiPanelLfo::SetWaveformName(Lfo* osc);
	virtual void SetStackItem(Lfo* item);
	void CallbackClicked(void* data, GEvent* evt);
};

