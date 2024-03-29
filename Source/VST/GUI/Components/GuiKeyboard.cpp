#include "GuiKeyboard.h"
#include "GuiMainWindow.h"
#include "Utils/VoicePool.h"

GuiKeyboardKey::GuiKeyboardKey(int width, int height, int offsetX, int offsetY, int imageId, int spriteId, int midiNumber) : GuiComponent(width, height, offsetX, offsetY, imageId, spriteId)
{
	this->midiNumber = midiNumber;
	keyDown = false;
	drawOverlay = true;
	this->hottable = true;
	for(int i=0; i<10; i++)
	{
		//keyDown[i] = false;
	}
}


GuiKeyboardKey::~GuiKeyboardKey(void)
{
}

void GuiKeyboardKey::HandleEvent(GEvent* evt, bool recursing) 
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

			if (!evt->isHandled && GuiMainWindow::dragComponent == NULL && IsHot(evt->pos))
			{
				GuiMainWindow::hotComponent = this;
				evt->isHandled = true;
				return;
			}
			break;
		}
	case(kGEventMouseDown):
		{
			if (IsHot(evt->pos))
			{							
				char msg[255];
				sprintf(&msg[0], "KEY x: %d, y: %d", (int)evt->pos.x, (int)evt->pos.y);
				DebugPrintLine(msg);
				keyDown = true;
				//Patch* p = PatchList::list->CurrentPatch = PatchList::list->patches[0];
				VoicePool::Pool->GetVoiceAndPlayNote(0, midiNumber, PatchList::list->CurrentPatch);
				evt->isHandled = true;
			}

			// check children first
			for(int i=0; i<this->SubComponentCount(); i++)
			{
				GuiComponent* gc = GetComponent(i);
				gc->HandleEvent(evt, true);
				if (evt->isHandled)
				{
					break;				
				}				
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
					//keyDown[i] = false;
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


void GuiKeyboardKey::draw()
{
	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);

	if (keyDown)
	{
		//if (!dirty) return; // doesn't need drawing

		image->bind();

		//glColor4f(1,1,1,1);
		
		glBegin(GL_QUADS);

		if (spriteId !=0)
		{
			// draw sprite
			GSprite* sprite = image->spriteCollection->GetSprite((int)spriteId);
			image->drawSprite(sprite, 0, 0);

		}else{
			
			// draw whole image
			glTexCoord2f(0,0);
			glVertex2i(0,0);

			glTexCoord2f(0,1);
			glVertex2i(0, 0+height);

			glTexCoord2f(1,1);
			glVertex2i(0+width, 0+height);

			glTexCoord2f(1,0);
			glVertex2i(0+width, 0);			
		}

		glEnd();
	}

	// draw sub components last as they likely appear on top of this component
	for(int i=0; i<this->SubComponentCount(); i++)
	{
		GuiComponent* gc = GetComponent(i);
		gc->dirty = dirty; // mark children as dirty as we're dirty, dirty children!!
		gc->draw();
	}
	glPopMatrix();

	dirty = false;

}


// keyboard

GuiKeyboard::GuiKeyboard(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	this->hottable = true;
	// white keys
	for(int i=0; i<66; i++)
	{
		keyDown[i] = false;
		GuiKeyboardKey* key = new GuiKeyboardKey(12, 56, 13*i, 0, IDB_BUTTONSTRIP, kSpritesButtons_Keyboard_overlay, i+24);
		AddSubComponent(key);
	}
}


GuiKeyboard::~GuiKeyboard(void)
{
}

void GuiKeyboard::draw()
{
	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);
	float pixelSizeX = 1.0f / image->width;
	float pixelSizeY = 1.0f / image->height;

	float keyWidth = 12;
	float keyHeight = 58;

	float sizeX = keyWidth * pixelSizeX;
	float sizeY = keyHeight * pixelSizeY;
#ifdef DRAW_OVERLAYS
	glDisable(GL_TEXTURE_2D);
	glColor4f(1,0,0,0.3f);

	glBegin(GL_QUADS);

	glVertex2i(0,0);

	glVertex2i(0, 0+height);

	glVertex2i(0+width, 0+height);

	glVertex2i(0+width, 0);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1,1,1,1);
#endif

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
	// draw sub components last as they likely appear on top of this component
	for(int i=0; i<SubComponentCount(); i++)
	{
		GuiComponent* gc = GetComponent(i);
		gc->dirty = dirty; // mark children as dirty as we're dirty, dirty children!!
		gc->draw();
	}
	glPopMatrix();
}

void GuiKeyboard::HandleEvent(GEvent* evt, bool recursing) 
{
	if (!enabled)
	{
		return;
	}

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

			if (!evt->isHandled && GuiMainWindow::dragComponent == NULL && IsHot(evt->pos))
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
				if (evt->isHandled)
					break;				
			}

			if (!evt->isHandled && hottable && width > 0 && height > 0 && IsHot(evt->pos))
			{
				// NEXT
				GuiMainWindow::dragComponent = this;
				GuiMainWindow::dragPoint->x = evt->pos.x;
				GuiMainWindow::dragPoint->y = evt->pos.y;
				evt->isHandled = true;

				int keyNum = ((int)evt->pos.x - 14) / 13;
				for(int i=0; i<100; i++)
				{
					//keyDown[i] = false;
				}
				//keyDown[keyNum] = true;


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
				GuiKeyboardKey* key = (GuiKeyboardKey*)gc;				
				if (key->keyDown)
				{
					key->keyDown = false;
					Patch* p = PatchList::list->CurrentPatch;
					VoicePool::Pool->Stop(0, key->midiNumber);
				}
				

				//if (evt->isHandled)
				//	break;				
			}



			if (!evt->isHandled)
			{
				evt->isHandled = true;
				for(int i=0; i<100; i++)
				{
					//keyDown[i] = false;
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