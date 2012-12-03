#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class SimpleFilter;

class GuiPanelFilter : public GuiComponent
{
public:
	LinkedSynthItem* synthItem2; 
	GuiKnob* knobCutoff1;
	GuiKnob* knobCutoff2;

	GuiKnob* knobResonance1;
	GuiKnob* knobResonance2;

	GuiKnob* knobPan1;
	GuiKnob* knobPan2;

	GuiKnob* knobLevel1;
	GuiKnob* knobLevel2;
	
	GuiSlider* sliderFilter;
	
	GuiButton* butEnabled;
	
	GuiButton* butMode; // parallel/dual
	GuiButton* butLink; // parallel/dual

	GuiLabel* labFilter1Type;
	GuiLabel* labFilter1Limiter;
	GuiLabel* labFilter1ResoBoost;

	GuiLabel* labFilter2Type;
	GuiLabel* labFilter2Limiter;
	GuiLabel* labFilter2ResoBoost;

	GuiPanelFilter(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelFilter(void);
	virtual void SetStackItem(SimpleFilter* item1, SimpleFilter* item2);
	void CallbackClicked(void* data, GEvent* evt);
	char* FilterTypeToString(int val);
};

