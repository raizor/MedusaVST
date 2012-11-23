#include "GuiPanelFilter.h"


GuiPanelFilter::GuiPanelFilter(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	knobCutoff1 = new GuiKnob(0, 0, 263, 70, IDB_KNOBS_BI, true);
	knobResonance1 = new GuiKnob(0, 0, 303, 38, IDB_KNOBS_BI, true);	
	knobPan1 = new GuiKnob(0, 0, 359, 38, IDB_KNOBS_BI, true);	
	knobLevel1 = new GuiKnob(0, 0, 400, 70, IDB_KNOBS_BI, true);
	
	knobCutoff2 = new GuiKnob(0, 0, 263, 130, IDB_KNOBS_BI, true);
	knobResonance2 = new GuiKnob(0, 0, 303, 164, IDB_KNOBS_BI, true);
	knobPan2 = new GuiKnob(0, 0, 359, 164, IDB_KNOBS_BI, true);
	knobLevel2 = new GuiKnob(0, 0, 400, 130, IDB_KNOBS_BI, true);

	AddSubComponent(knobCutoff1);
	AddSubComponent(knobResonance1);
	AddSubComponent(knobPan1);
	AddSubComponent(knobLevel1);

	AddSubComponent(knobCutoff2);
	AddSubComponent(knobResonance2);
	AddSubComponent(knobPan2);
	AddSubComponent(knobLevel2);

	butMode = new GuiButton(51, 49, 328, 100, IDB_BUTTONSTRIP, kSpritesButtons_But_filterMode_para, kSpritesButtons_But_filterMode_dual, kSpritesButtons_None);
	AddSubComponent(butMode);

	butLink = new GuiButton(28, 31, 233, 110, IDB_BUTTONSTRIP, kSpritesButtons_But_filterLink_off, kSpritesButtons_But_filterLink_on, kSpritesButtons_None);
	AddSubComponent(butLink);
}


GuiPanelFilter::~GuiPanelFilter(void)
{
}
