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
	panelOsc = new GuiPanelOsc(0,0,0,0,0);
	panelFilter = new GuiComponent(0,0,0,0);
	panelEg = new GuiComponent(0,0,0,0);
	panelLfo = new GuiComponent(0,0,0,0); 
	panelMod = new GuiComponent(0,0,0,0); 
	panelMaster = new GuiComponent(0,0,0,0); 

	keyboard = new GuiKeyboard(0, 0, 14, 634, IDB_KEYBOARD_OVERLAYS);

	subComponents->push(panelOsc);
	subComponents->push(keyboard);
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
	//glColor4f(1,1,1,1);
	glBegin(GL_QUADS);

	float numPanels = 2.0f;
	float panelSize = 1.0f / numPanels;

	float x1 = panelSize*panelNumber;
	float x2 = x1 + panelSize;

	glTexCoord2f(x1,0);
	glVertex2i(offsetX,offsetY);

	glTexCoord2f(x1,1);
	glVertex2i(offsetX,offsetY+height);

	glTexCoord2f(x2,1);
	glVertex2i(offsetX+width,offsetY+height);

	glTexCoord2f(x2,0);
	glVertex2i(offsetX+width,offsetY);

	glEnd();

	// draw sub components last as they likely appear on top of this component
	for(int i=0; i<subComponents->count; i++)
	{
		GuiComponent* gc = (GuiComponent*)subComponents->items[i];
		gc->dirty = dirty; // mark children as dirty as we're dirty, dirty children!!
		gc->draw();
	}

	dirty = false;
}
