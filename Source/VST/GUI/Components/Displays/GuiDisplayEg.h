#pragma once
#include "../GuiComponent.h"
#include "../GuiKnob.h"
#include "../GuiSlider.h"
#include "../GuiButton.h"
#include "../GuiLabel.h"

class Adsr;

class GuiDisplayEg : public GuiComponent
{
public:
	Adsr* eg;
	
	GuiDisplayEg(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiDisplayEg(void);
	virtual void draw();
	void SetEg(Adsr* eg);

	
};

