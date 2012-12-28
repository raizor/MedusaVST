#include "GuiTxtEdit.h"


GuiTxtEdit::GuiTxtEdit(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	bgImage = new GuiComponent(700, 41, 0, 0, IDB_BUTTONSTRIP, kSpritesButtons_PanelTxt, false, 0);
	AddSubComponent(bgImage);
}


GuiTxtEdit::~GuiTxtEdit(void)
{
}
