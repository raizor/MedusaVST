#include "GuiKeyboard.h"
#include "GuiMainWindow.h"


GuiKeyboard::GuiKeyboard(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	this->hottable = true;
	this->offsetY += 167;
	this->width = 859;
	this->height = 58;
	for(int i=0; i<100; i++)
	{
		keyDown[i] = false;
	}
}


GuiKeyboard::~GuiKeyboard(void)
{
}

void GuiKeyboard::draw()
{
	float pixelSizeX = 1.0f / image->width;
	float pixelSizeY = 1.0f / image->height;

	float keyWidth = 12;
	float keyHeight = 58;

	float sizeX = keyWidth * pixelSizeX;
	float sizeY = keyHeight * pixelSizeY;

	if (GuiMainWindow::hotComponent == this)
	{
		int keyNum = ((int)GuiMainWindow::movePoint->x - 14) / 13;

		char msg[255];
		sprintf(&msg[0], "%d", keyNum);
		DebugPrintLine(msg);

		float ox=offsetX;
		float oy=offsetY;

		//ox += keyNum*13;
				
		image->bind();
		glBegin(GL_QUADS);
		{		
			for(int i=0; i<100; i++)
			{
				if (keyDown[i])
				{
					ox = offsetX + (i*13);
					glTexCoord2f(0, 0);
					glVertex2i(ox, oy);

					glTexCoord2f(0, sizeY);
					glVertex2i(ox, oy+keyHeight);

					glTexCoord2f(sizeX, sizeY);
					glVertex2i(ox+keyWidth, oy+keyHeight);

					glTexCoord2f(sizeX, 0);
					glVertex2i(ox+keyWidth, oy);
				}
			}

		}
		glEnd();
	}
}

void GuiKeyboard::HandleEvent(GEvent* evt, bool recursing) 
{
	switch(evt->type)
	{
	case(kGEventMouseMoved):
		{
			if (!recursing)
			{
				char msg[255];
				sprintf(&msg[0], "x: %d, y: %d", (int)evt->pos.x, (int)evt->pos.y);
				//DebugPrintLine(msg);
			}

			// check children first
			for(int i=0; i<this->SubComponentCount(); i++)
			{
				GuiComponent* gc = GetComponent(i);
				gc->HandleEvent(evt, true);		
			}

			if (!evt->isHandled && GuiMainWindow::dragComponent == NULL && hottable && width > 0 && height > 0 && (evt->pos.x >= GetOffsetX() &&  evt->pos.x <= GetOffsetX() + width) && (evt->pos.y >= GetOffsetY() &&  evt->pos.y <= GetOffsetX() + height))
			{
				GuiMainWindow::hotComponent = this;
				evt->isHandled = true;
				return;
			}
			break;
		}
	case(kGEventMouseDown):
		{
			if (!recursing)
			{
				char msg[255];
				sprintf(&msg[0], "x: %d, y: %d", (int)evt->pos.x, (int)evt->pos.y);
				//DebugPrintLine(msg);
			}

			// check children first
			for(int i=0; i<this->SubComponentCount(); i++)
			{
				GuiComponent* gc = GetComponent(i);
				gc->HandleEvent(evt, true);
				break;				
			}

			if (!evt->isHandled && hottable && width > 0 && height > 0 && (evt->pos.x >= GetOffsetX() &&  evt->pos.x <= GetOffsetX() + width) && (evt->pos.y >= GetOffsetY() &&  evt->pos.y <= GetOffsetY() + height))
			{
				GuiMainWindow::dragComponent = this;
				GuiMainWindow::dragPoint->x = evt->pos.x;
				GuiMainWindow::dragPoint->y = evt->pos.y;
				evt->isHandled = true;

				int keyNum = ((int)evt->pos.x - 14) / 13;
				for(int i=0; i<100; i++)
				{
					keyDown[i] = false;
				}
				keyDown[keyNum] = true;

				return;
			}
			break;
		}
	case(kGEventMouseUp):
		{

			if (!recursing)
			{
				char msg[255];
				sprintf(&msg[0], "x: %d, y: %d", (int)evt->pos.x, (int)evt->pos.y);
				//DebugPrintLine(msg);
			}

			// check children first
			for(int i=0; i<this->SubComponentCount(); i++)
			{
				GuiComponent* gc = GetComponent(i);
				gc->HandleEvent(evt, true);
				break;				
			}

			if (!evt->isHandled)
			{
				evt->isHandled = true;
				for(int i=0; i<100; i++)
				{
					keyDown[i] = false;
				}
			}

			break;
		}
	default:
		{
			for(int i=0; i<this->SubComponentCount(); i++)
			{
				GuiComponent* gc = GetComponent(i);
				if (!evt->isHandled)
					gc->HandleEvent(evt, true);
			}
			break;
		}
	}
}