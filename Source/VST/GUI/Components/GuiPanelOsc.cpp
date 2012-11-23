#include "GuiPanelOsc.h"


GuiPanelOsc::GuiPanelOsc(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	knobFinetune = new GuiKnob(0, 0, 8, 118, IDB_KNOBS_BI, true);
	knobPhase = new GuiKnob(0, 0, 52, 152, IDB_KNOBS_UNI, false);
	knobLevel = new GuiKnob(0, 0, 96, 118, IDB_KNOBS_UNI, false);

	butStripOscs = new GuiButtonStrip(0, 0, 8, 287);

	AddSubComponent(knobFinetune);
	AddSubComponent(knobPhase);
	AddSubComponent(knobLevel);

	butEnabled = new GuiButton(26, 26, 62, 118, IDB_BUTTONSTRIP, kSpritesButtons_But_osc_power_off, kSpritesButtons_But_osc_power_on, kSpritesButtons_None);
	AddSubComponent(butEnabled);
	
	GuiButton* butOsc;
	butOsc = new GuiButton(26, 27, 102, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_1_off, kSpritesButtons_But_1_on, kSpritesButtons_None);
	butOscs.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 125, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_2_off, kSpritesButtons_But_2_on, kSpritesButtons_None);
	butOscs.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 148, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_3_off, kSpritesButtons_But_2_on, kSpritesButtons_None);
	butOscs.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 171, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_4_off, kSpritesButtons_But_2_on, kSpritesButtons_None);
	butOscs.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 194, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_5_off, kSpritesButtons_But_2_on, kSpritesButtons_None);
	butOscs.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 217, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_6_off, kSpritesButtons_But_2_on, kSpritesButtons_None);
	butOscs.push_back(butOsc);
	AddSubComponent(butOsc);

}


GuiPanelOsc::~GuiPanelOsc(void)
{
}
