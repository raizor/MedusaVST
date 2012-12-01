#include "GuiModMatrix.h"
#include "GuiMainWindow.h"

GuiModMatrix::GuiModMatrix(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	int lineSpacing = 18;
	int textStartY = 55;
	int textStartX = 35;

	// source
	for(int i=0; i<8; i++)
	{
		GuiLabel* lab = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*i), "Source"); 
		lab->ClickedHandler = (FpClickedCallback)&GuiModMatrix::CallbackClicked;
		AddSubComponent(lab);
		butSource.push_back(lab);
	}

	// curve
	for(int i=0; i<8; i++)
	{
		GuiLabel* lab = new GuiLabel(72, 12, textStartX+218, textStartY+(lineSpacing*i), "Curve");
		AddSubComponent(lab);
		butCurve.push_back(lab);
	}

	// control
	for(int i=0; i<8; i++)
	{
		GuiLabel* lab = new GuiLabel(72, 12, textStartX+329, textStartY+(lineSpacing*i), "Control");
		AddSubComponent(lab);
		butControl.push_back(lab);
	}

	// dest
	for(int i=0; i<8; i++)
	{
		GuiLabel* lab = new GuiLabel(72, 12, textStartX+442, textStartY+(lineSpacing*i), "Destination");
		AddSubComponent(lab);
		butDest.push_back(lab);
	}
}


GuiModMatrix::~GuiModMatrix(void)
{
}

void GuiModMatrix::CallbackClicked(void* data, GEvent* evt)
{
	for(int i=0; i<8; i++)
	{
		if (GuiMainWindow::panelModMatrix->butSource.at(i) == data)
		{
			DebugPrintLine("SOURCE");
			menuSource = new GContextMenuEx();
			int id = 1000;
			menuSource->AddItem(id++, "HELLO");
			GPoint gp;
			gp.x = 0;
			gp.y = 0;
			menuSource->SelectAt(evt->pos);
		}

	}

}