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
	GuiKnob* knobLevelAmount;

	GuiKnob* knobDelayTime;
	GuiKnob* knobStartLevel; // pitch eg only
	GuiKnob* knobAttackTime;
	GuiKnob* knobAttackLevel; // pitch only
	GuiKnob* knobDecayTime;
	GuiKnob* knobDecayLevel; // amp only
	GuiKnob* knobSustainTime; // amp only
	GuiKnob* knobSustainLevel; // amp only
	GuiKnob* knobReleaseTime;
	GuiKnob* knobReleaseLevel; // pitch eg only
	GuiComponent* panelOverlay;
	
	GuiSlider* sliderAmount;
	
	GuiButton* butEnabled;

	GuiButton* butType;
	GuiButton* butTrans;
	GuiButton* butOctave;
	GuiButton* butMode;
	GuiButton* butMod;


	GuiButton* butAmpEg;
	GuiButton* butPitchEg;
	std::vector<GuiButton*> butEgs;

	GuiPanelEg(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelEg(void);
	virtual void GuiPanelEg::SetStackItem(Adsr* item);
	void CallbackClicked(void* data, GEvent* evt);
};

