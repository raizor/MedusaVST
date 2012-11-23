#include "GuiMainWindow.h"

GuiComponent* GuiMainWindow::hotComponent = NULL;
GuiComponent* GuiMainWindow::dragComponent = NULL;
GPoint* GuiMainWindow::dragPoint = NULL;
GPoint* GuiMainWindow::movePoint = NULL;

GuiMainWindow::GuiMainWindow(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{		
	panelNumber = 0;
	currentPatch = NULL;
	dragPoint = new GPoint(0,0);
	movePoint = new GPoint(0,0);

	// container panels for main gui
	panelOsc = new GuiPanelOsc( 460, 217, 0, 170, 0);
	panelFilter = new GuiPanelFilter(460, 217, 460, 170, 0);
	panelEg = new GuiPanelEg(460, 217, 0, 384, 0);
	panelLfo = new GuiPanelLfo(460, 217, 460, 384, 0); 
	panelModulations = new GuiPanelModulations(0, 0, 0, 596, 0); 
	panelMaster = new GuiComponent(0, 0, 640, 594); 

	keyboard = new GuiKeyboard(0, 0, 14, 634, IDB_KEYBOARD_OVERLAYS);

	AddSubComponent(panelOsc);
	AddSubComponent(panelEg);
	AddSubComponent(panelFilter);
	AddSubComponent(panelLfo);
	AddSubComponent(panelModulations);
	AddSubComponent(keyboard);
	/*
	subComponents->push(panelFilter);
	subComponents->push(panelEg);
	subComponents->push(panelLfo);
	subComponents->push(panelMod);
	subComponents->push(panelMaster);*/

	//subComponents->push(new GuiStackItem(0,0,0,0,IDB_PNG_ITEM_PANEL));
}

void GuiMainWindow::PatchChanged(Patch* patch)
{
	currentPatch = patch;
	/*
	int itemHeight = GLImageManager::instance->GetImageById(IDB_PNG_ITEM_PANEL)->height;
	int y = 0;
	for(int i=0; i<patch->numItems; i++)
	{
		Item* item = patch->items[i];
		subComponents->push(new GuiStackItem(0, 0, 0, y, IDB_PNG_ITEM_PANEL, item));
		y+=itemHeight;
	}*/
}

GuiMainWindow::~GuiMainWindow(void)
{
}

void GuiMainWindow::draw()
{
	//if (!dirty) return; // doesn't need drawing

	image->bind();

	glPushMatrix();

	glTranslatef(offsetX, offsetY, 0);

	//glColor4f(1,1,1,1);
	glBegin(GL_QUADS);

	float numPanels = 2.0f;
	float panelSize = 1.0f / numPanels;

	float x1 = panelSize*panelNumber;
	float x2 = x1 + panelSize;

	glTexCoord2f(x1,0);
	glVertex2i(0, 0);

	glTexCoord2f(x1,1);
	glVertex2i(0, 0+height);

	glTexCoord2f(x2,1);
	glVertex2i(0+width, 0+height);

	glTexCoord2f(x2,0);
	glVertex2i(0+width, 0);

	glEnd();


	// draw sub components last as they likely appear on top of this component
	for(int i=0; i<SubComponentCount(); i++)
	{
		GuiComponent* gc = GetComponent(i);
		gc->dirty = dirty; // mark children as dirty as we're dirty, dirty children!!
		gc->draw();
	}


	glPopMatrix();

	dirty = false;
}
