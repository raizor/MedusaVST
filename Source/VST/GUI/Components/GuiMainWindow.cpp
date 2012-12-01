#include "GuiMainWindow.h"
#include "../Text/TextWriter.h"
#include "GuiPanelMaster.h"

GuiComponent* GuiMainWindow::hotComponent = NULL;
GuiComponent* GuiMainWindow::dragComponent = NULL;
GPoint* GuiMainWindow::dragPoint = NULL;
GPoint* GuiMainWindow::movePoint = NULL;
int GuiMainWindow::currentOscNumber = 0;
int GuiMainWindow::currentEgNumber = 0;
int GuiMainWindow::currentLfoNumber = 0;
GuiPanelMaster* GuiMainWindow::panelMaster = 0;
GuiPanelOsc* GuiMainWindow::panelOsc = 0;
GuiPanelEg* GuiMainWindow::panelEg = 0;
GuiPanelLfo* GuiMainWindow::panelLfo = 0;
GuiModMatrix* GuiMainWindow::panelModMatrix = 0;
//GuiPanelModulations* GuiMainWindow::panelModulations = 0;
GuiPanelFilter* GuiMainWindow::panelFilter = 0;
void* GuiMainWindow::hWindow = 0;
GuiKeyboard* GuiMainWindow::keyboard = 0;
char GuiMainWindow::labelText[100];

GuiMainWindow::GuiMainWindow(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{		
	panelNumber = 0;
	currentPatch = NULL;
	dragPoint = new GPoint(0,0);
	movePoint = new GPoint(0,0);

	currentOscNumber = 0;
	currentEgNumber = NUMBER_EG_AMP;
	currentLfoNumber = 0;

	// container panels for main gui
	panelOsc = new GuiPanelOsc( 460, 217, 0, 170, 0);
	panelFilter = new GuiPanelFilter(460, 217, 460, 170, 0);
	panelEg = new GuiPanelEg(460, 217, 0, 384, 0);
	panelLfo = new GuiPanelLfo(460, 217, 460, 384, 0); 
	//panelModulations = new GuiPanelModulations(630, 205, 0, 594, 0); 
	panelMaster = new GuiPanelMaster(279, 202, 640, 594, 0); 
	panelModMatrix = new GuiModMatrix(635, 205, 0, 597, 0); 

	keyboard = new GuiKeyboard(858, 58, 13, 801, IDB_KEYBOARD_OVERLAYS);

	//surface = new GSurface(400, 400);
	

	AddSubComponent(panelOsc);
	AddSubComponent(panelEg);
	AddSubComponent(panelFilter);
	AddSubComponent(panelLfo);
	AddSubComponent(panelMaster);	
	AddSubComponent(keyboard);
	AddSubComponent(panelModMatrix);
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

	glDisable(GL_TEXTURE_2D);
	//GPoint* gp = new GPoint(0,0);
	//GColor* gc = new GColor(0, 0, 0);
	//FontManager::manager->DrawText(kFontFaceLucidaGrande, "HELLO THIS IS A BUNCH OF TEXT FOR YOU TO LOOK AT", *gp, *gc, 20.0, 0);
	glEnable(GL_TEXTURE_2D);

	glEnd();


	// draw sub components last as they likely appear on top of this component
	for(int i=0; i<SubComponentCount(); i++)
	{
		GuiComponent* gc = GetComponent(i);
		gc->dirty = dirty; // mark children as dirty as we're dirty, dirty children!!
		gc->draw();
	}

	//TextWriter::writer->Lucida->SetColor(250,250,55,254);
	//TextWriter::writer->Lucida->PrintCenter(240,"This is another font.");


	glPopMatrix();

	dirty = false;
}
