#include "GuiPanelOsc.h"


GuiPanelOsc::GuiPanelOsc(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	knobFinetune = new GuiKnob(0, 0, 7, 287, IDB_KNOBS_BI, true);
	knobPhase = new GuiKnob(0, 0, 52, 322, IDB_KNOBS_UNI, false);
	knobLevel = new GuiKnob(0, 0, 96, 288, IDB_KNOBS_UNI, false);
	subComponents->push(knobFinetune);
	subComponents->push(knobPhase);
	subComponents->push(knobLevel);
}


GuiPanelOsc::~GuiPanelOsc(void)
{
}
