#include "GuiPanelMain.h"


GuiPanelMain::GuiPanelMain(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	panelNumber = kPanelPatch;
	panelPatch = new GuiComponent(width, height, 0, 0, 0);
	panelPatchFx = new GuiComponent(width, height, 0, 0, 0);
	panelPatchFx->enabled = false;
	panelGlobalFx = new GuiComponent(width, height, 0, 0, 0);
	panelGlobalFx->enabled = false;

	AddSubComponent(panelPatch);
	AddSubComponent(panelPatchFx);
	AddSubComponent(panelGlobalFx);
}


GuiPanelMain::~GuiPanelMain(void)
{
}


void GuiPanelMain::draw()
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
