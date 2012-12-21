#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class SimpleFilter;

class ContextMenuEx;
class GContextMenuEx;

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
	GuiButton* butLabFilter1Type;

	GuiLabel* labFilter1Limiter;
	GuiButton* butLabFilter1Limiter;

	GuiLabel* labFilter1ResoBoost;
	GuiButton* butLabFilter1ResoBoost;


	GuiLabel* labFilter2Type;
	GuiButton* butLabFilter2Type;

	GuiLabel* labFilter2Limiter;
	GuiButton* butLabFilter2Limiter;

	GuiLabel* labFilter2ResoBoost;
	GuiButton* butLabFilter2ResoBoost;

	GuiLabel* labKnob1;
	GuiLabel* labKnob2a;
	GuiLabel* labKnob2b;
	GuiLabel* labKnob3a;
	GuiLabel* labKnob3b;
	GuiLabel* labKnob4;

	GContextMenuEx* menuMenu;

	GuiPanelFilter(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelFilter(void);
	virtual void SetStackItem(SimpleFilter* item1, SimpleFilter* item2);
	void CallbackClicked(void* data, GEvent* evt);
	char* FilterTypeToString(int val);
};

