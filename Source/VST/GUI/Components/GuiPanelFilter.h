#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelFilter : public GuiComponent
{
public:
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

	GuiPanelFilter(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelFilter(void);
};

