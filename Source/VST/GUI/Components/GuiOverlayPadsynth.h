#pragma once

#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "../../Utils/ContextMenus.h"
#include "../Sprites/buttons.h"

class GuiOverlayPadsynth : public GuiComponent
{
public:
	GuiButton* butGenerate;
	GuiButton* butClose;

	GuiLabel* labWaveType;

	GuiKnob* knobAmp;
	GuiKnob* knobBandwidth;
	GuiKnob* knobBandwidthScale;
	GuiKnob* knobFormantScale;

	GuiLabel* labKnob1;
	GuiLabel* labKnob2;
	GuiLabel* labKnob3;
	GuiLabel* labKnob4;

	WaveForm waveForm;

	GuiComponent* background;
	GuiOverlayPadsynth(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiOverlayPadsynth(void);
	void CallbackClicked(void* data, GEvent* evt);
};

