#include "GuiButton.h"
#include "GuiMainWindow.h"
#include "Utils/Patch.h"

// strip

GuiButtonStrip::GuiButtonStrip(int width, int height, int offsetX, int offsetY) : GuiComponent(width, height, offsetX, offsetY, 0)
{
}


GuiButtonStrip::~GuiButtonStrip(void)
{
}

// button

GuiButton::GuiButton(int width, int height, int offsetX, int offsetY, int imageId, SpritesButton buttonOff, SpritesButton buttonOn, SpritesButton buttonHotOff, SpritesButton buttonHotOn) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	hottable = true;
	this->itemNumber = 0;
	this->buttonType  = kButtonTypeEnabledSwitch;
	this->hottable = buttonHotOn != kSpritesButtons_None;
	this->buttonOff = buttonOff;
	this->buttonOn = buttonOn;
	this->buttonOnHot = buttonHotOn;
	this->buttonOffHot = buttonHotOff;
	this->synthItem = 0;
	this->lit = false;
	state = kButtonStateOff;
}


GuiButton::~GuiButton(void)
{
}

void GuiButton::draw()
{

	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);

	if (hasImage)
	{
		//if (!dirty) return; // doesn't need drawing

		image->bind();
		GSprite* sprite;
		
		// state
		if (synthItem)
		{
			switch(buttonType)
			{
			case(kButtonTypeEnabledSwitch):
				state = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+GuiMainWindow::currentOscNumber]->enabled ? kButtonStateOn : kButtonStateOff;
				break;
			case(kButtonTypeOscNumber):
				state = GuiMainWindow::currentOscNumber == this->itemNumber ? kButtonStateOn : kButtonStateOff;
				break;
			case(kButtonTypeLfoAvNumber):
				state = GuiMainWindow::currentLfoAvNumber == this->itemNumber ? kButtonStateOn : kButtonStateOff;
				break;
			case(kButtonTypeLfoPvNumber):
				state = GuiMainWindow::currentLfoPvNumber == this->itemNumber ? kButtonStateOn : kButtonStateOff;
				break;
			case(kButtonTypeEgNumber):
				state = GuiMainWindow::currentEgNumber == this->itemNumber ? kButtonStateOn : kButtonStateOff;
				break;				
			case(kButtonTypePage):
				state = enabled ? kButtonStateOn : kButtonStateOff;
				break;
			default:
				state = enabled ? kButtonStateOn : kButtonStateOff;
				break;
			}
		}

		// hot
		switch(buttonType)
		{		
		case(kButtonTypeLfoAvNumber):
			{
			}
		case(kButtonTypeLfoPvNumber):
			{
			}
		case(kButtonTypeOscNumber):
		{
			if (state == kButtonStateOn)
			{
				if (synthItem && synthItem->item->enabled && buttonOnHot)
				{
					sprite = image->spriteCollection->GetSprite((int)buttonOnHot);
				}else{
					sprite = image->spriteCollection->GetSprite((int)buttonOn);
				}

			}else{
				if (synthItem && synthItem->item->enabled && buttonOffHot)
				{
					sprite = image->spriteCollection->GetSprite((int)buttonOffHot);
				}else{
					sprite = image->spriteCollection->GetSprite((int)buttonOff);
				}
			}
			break;
		}

		case(kButtonTypeOscParam):
			{
				glDisable(GL_TEXTURE_2D);
				switch (type)
				{
				case kGuiComponentTypeSlider:
					{
						glColor4f(1,1,0,0.2f);
						break;
					}

				default:
					{
						glColor4f(1,0,1,0.2f);
						break;
					}

				}

				glBegin(GL_QUADS);

				glVertex2i(0,0);

				glVertex2i(0, 0+height);

				glVertex2i(0+width, 0+height);

				glVertex2i(0+width, 0);
				glEnd();
				glEnable(GL_TEXTURE_2D);
				glColor4f(1,1,1,1);
			}
		case(kButtonTypeEgNumber):
			{
				if (state == kButtonStateOn)
				{
					if (synthItem && synthItem->item->enabled && buttonOnHot)
					{
						sprite = image->spriteCollection->GetSprite((int)buttonOnHot);
					}else{
						sprite = image->spriteCollection->GetSprite((int)buttonOn);
					}

				}else{
					if (synthItem && synthItem->item->enabled && buttonOffHot)
					{
						sprite = image->spriteCollection->GetSprite((int)buttonOffHot);
					}else{
						sprite = image->spriteCollection->GetSprite((int)buttonOff);
					}
				}
				break;
			}
		case(kButtonTypePage):
			{
				if (state == kButtonStateOn)
				{
					sprite = image->spriteCollection->GetSprite((int)buttonOnHot);
				}else{
					sprite = image->spriteCollection->GetSprite((int)buttonOn);
				}
			}
		default:
			{
				if (state == kButtonStateOn)
				{
					if (enabled && buttonOnHot)
					{
						sprite = image->spriteCollection->GetSprite((int)buttonOnHot);
					}else{
						sprite = image->spriteCollection->GetSprite((int)buttonOn);
					}

				}else{
					if (enabled && buttonOnHot)
					{
						sprite = image->spriteCollection->GetSprite((int)buttonOffHot);
					}else{
						sprite = image->spriteCollection->GetSprite((int)buttonOff);
					}
				}
				break;
			}
		}



		//glColor4f(1,1,1,1);
		glBegin(GL_QUADS);

		float pixSizeX = sprite->spriteCollection->pixelSizeX; 
		float pixSizeY = sprite->spriteCollection->pixelSizeY;

		float x1 = pixSizeX * sprite->posX;
		float y1 = pixSizeY * sprite->posY;

		float x2 = x1 + (sprite->width*pixSizeX);
		float y2 = y1 + (sprite->height*pixSizeY);


		glTexCoord2f(x1, y1);
		glVertex2i(0,0);

		glTexCoord2f(x1,y2);
		glVertex2i(0,0+height);

		glTexCoord2f(x2,y2);
		glVertex2i(0+width,0+height);

		glTexCoord2f(x2,y1);
		glVertex2i(0+width,0);

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

	dirty = false;

}

void GuiButton::HandleEvent(GEvent* evt, bool recursing) 
{
	GuiComponent::HandleEvent(evt, false);
}

void GuiButton::Clicked(GEvent* evt)
{
	void* xx = this;
	if (synthItem)
	{
		switch(buttonType)
		{
		case(kButtonTypeEnabledSwitch):
			{
				//synthItem->item->enabled = !synthItem->item->enabled;
				PatchList::list->CurrentPatch->items[NUMBER_START_OSC+GuiMainWindow::currentOscNumber]->enabled = !PatchList::list->CurrentPatch->items[NUMBER_START_OSC+GuiMainWindow::currentOscNumber]->enabled;
				break;
			}
		case(kButtonTypeOscNumber):
			{
				GuiMainWindow::currentOscNumber = this->itemNumber;
				//synthItem->item->enabled = !synthItem->item->enabled;
				break;
			}
		case(kButtonTypeLfoAvNumber):
			{
				GuiMainWindow::currentLfoAvNumber = this->itemNumber;
				//synthItem->item->enabled = !synthItem->item->enabled;
				break;
			}
		case(kButtonTypeLfoPvNumber):
			{
				GuiMainWindow::currentLfoPvNumber = this->itemNumber;
				//synthItem->item->enabled = !synthItem->item->enabled;
				break;
			}
		case(kButtonTypeEgNumber):
			{
				GuiMainWindow::currentEgNumber = this->itemNumber;
				GuiMainWindow::panelEg->SetStackItem((Adsr*)PatchList::list->CurrentPatch->items[NUMBER_START_EG+GuiMainWindow::currentEgNumber]);
				//synthItem->item->enabled = !synthItem->item->enabled;
				break;
			}
		default:
			{
				int xx = 1;
			}

		}
	}

	
}

void GuiButton::CallbackVoid()
{
}