#include "GuiMainWindow.h"
#include "../Text/TextWriter.h"
#include "GuiPanelMaster.h"

GuiComponent* GuiMainWindow::hotComponent = NULL;
GuiComponent* GuiMainWindow::dragComponent = NULL;
GPoint* GuiMainWindow::dragPoint = NULL;
GPoint* GuiMainWindow::movePoint = NULL;
int GuiMainWindow::currentOscNumber = 0;
int GuiMainWindow::currentEgNumber = 0;
int GuiMainWindow::currentLfoAvNumber = 0;
int GuiMainWindow::currentLfoPvNumber = 0;
GuiPanelMain* GuiMainWindow::panelMain = 0;
GuiPanelMaster* GuiMainWindow::panelMaster = 0;
GuiPanelHeader* GuiMainWindow::panelHeader = 0;
GuiPanelOsc* GuiMainWindow::panelOsc = 0;
GuiPanelEg* GuiMainWindow::panelEg = 0;
GuiPanelLfo* GuiMainWindow::panelLfo = 0;
GuiModMatrix* GuiMainWindow::panelModMatrix = 0;
//GuiPanelModulations* GuiMainWindow::panelModulations = 0;
GuiPanelFilter* GuiMainWindow::panelFilter = 0;
void* GuiMainWindow::hWindow = 0;
GuiKeyboard* GuiMainWindow::keyboard = 0;
char GuiMainWindow::labelText[100];

GuiMainWindow::GuiMainWindow(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, 0)
{		
	currentPatch = NULL;
	dragPoint = new GPoint(0,0);
	movePoint = new GPoint(0,0);

	currentOscNumber = 0;
	currentEgNumber = NUMBER_EG_AMP;
	currentLfoAvNumber = 0;
	currentLfoPvNumber = 0;

	panelHeader = new GuiPanelHeader(921, 167, 0, 0, IDB_PNG_HEADER);
	panelHeader->drawOverlay = false;
	panelMain = new GuiPanelMain(920, 696, 0, 167, imageId);
	panelMain->drawOverlay = false;

	// container panels for main gui
	panelOsc = new GuiPanelOsc( 460, 217, 0, 0, 0);
	panelFilter = new GuiPanelFilter(460, 217, 460, 0, 0);
	panelEg = new GuiPanelEg(460, 217, 0, 384-167, 0);
	panelLfo = new GuiPanelLfo(460, 217, 460, 384-167, 0); 
	panelModMatrix = new GuiModMatrix(635, 205, 0, 597-167, 0); 
	
	// patch fx
	panelPatchGlobal = new GuiPanelPatchGlobal(389, 209, 525, 5, 0);
	panelDistortion = new GuiPanelDistortion(288, 209, 6, 6, 0);
	panelCompression = new GuiPanelCompression(288, 205, 5, 220, 0);
	panelFxRoutingPatch = new GuiPanelFxRouting(219, 419, 299, 6, 0);

	// global fx
	panelGlobalDelay = new GuiPanelGlobalDelay(389, 205, 524, 220, 0);
	panelGlobalReverb = new GuiPanelGlobalReverb(288, 204, 6, 431, 0);
	panelGlobalEq = new GuiPanelGlobalEq(334, 204, 299, 430, 0);
	panelGlobalModulation = new GuiPanelGlobalModulation(389, 209, 524, 6, 0);
	panelFxRoutingGlobal = new GuiPanelFxRouting(219, 419, 299, 6, 0);

	keyboard = new GuiKeyboard(858, 58, 13, 801, IDB_KEYBOARD_OVERLAYS);

	//surface = new GSurface(400, 400);
	
	// patch 
	panelMain->panelPatch->AddSubComponent(panelOsc);
	panelMain->panelPatch->AddSubComponent(panelEg);
	panelMain->panelPatch->AddSubComponent(panelFilter);
	panelMain->panelPatch->AddSubComponent(panelLfo);	
	panelMain->panelPatch->AddSubComponent(panelModMatrix);
	panelMain->panelPatch->drawOverlay = false;
	
	// patch fx
	panelMain->panelPatchFx->AddSubComponent(panelPatchGlobal);
	panelMain->panelPatchFx->AddSubComponent(panelDistortion);
	panelMain->panelPatchFx->AddSubComponent(panelCompression);
	panelMain->panelPatchFx->AddSubComponent(panelFxRoutingPatch);
	panelMain->panelPatchFx->drawOverlay = false;

	// global fx
	panelMain->panelGlobalFx->AddSubComponent(panelGlobalDelay);
	panelMain->panelGlobalFx->AddSubComponent(panelGlobalReverb);
	panelMain->panelGlobalFx->AddSubComponent(panelGlobalEq);
	panelMain->panelGlobalFx->AddSubComponent(panelGlobalModulation);
	panelMain->panelGlobalFx->AddSubComponent(panelFxRoutingGlobal);
	panelMain->panelGlobalFx->drawOverlay = false;

	AddSubComponent(panelHeader);
	AddSubComponent(panelMain);
	AddSubComponent(keyboard);

	panelMaster = new GuiPanelMaster(279, 202, 640, 595, 0); 
	AddSubComponent(panelMaster);	


	panelOsc->SetStackItem((Osc*)PatchList::list->CurrentPatch->items[NUMBER_START_OSC]);
	panelEg->SetStackItem((Adsr*)PatchList::list->CurrentPatch->egAmp);
	panelLfo->SetStackItem((Lfo*)PatchList::list->CurrentPatch->items[NUMBER_START_LFO_AV]);
	panelGlobalDelay->SetStackItem();
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

/*
void GuiMainWindow::draw()
{
	//if (!dirty) return; // doesn't need drawing

	image->bind();

	glPushMatrix();

	glTranslatef(offsetX, offsetY, 0);

	//glColor4f(1,1,1,1);
	glBegin(GL_QUADS);

	float numPanels = 3.0f;
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
*/