#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "Displays/GuiDisplayWave.h"

class Osc;

class GuiPanelOsc : public GuiComponent
{
public:
	char waveTableName [100];

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

	GuiButton* butLabWaveType;
	GuiButton* butLabTranspose;
	GuiButton* butLabOctave;
	GuiButton* butLabMode;
	GuiButton* butLabModMode;

	GuiLabel* labWaveType;
	GuiLabel* labTranspose;
	GuiLabel* labOctave;
	GuiLabel* labMode;
	GuiLabel* labModMode;
	
	GuiDisplayWave* displayWave;

	std::vector<GuiButton*> butOscs;

	GuiButtonStrip* butStripOscs;
	
	GuiPanelOsc(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelOsc(void);
	virtual void SetStackItem(Osc* item);
	void CallbackClicked(void* data, GEvent* evt);
	char* OscModModeToString(int val);
	char* OscModeToString(int val);
	void GuiPanelOsc::SetWaveformName(Osc* osc);
};

