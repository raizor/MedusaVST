#include "GuiSlider.h"
#include "GuiMainWindow.h"
#include "items/Processors/Delay and Reverb/ModDelay.h"
#include "items/Processors/Delay and Reverb/Reverb.h"

// knob

GuiSliderKnob::GuiSliderKnob(int width, int height, int offsetX, int offsetY, int imageId, SpritesButton sliderOn, SpritesButton sliderOff, SliderType sliderType, char* name) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	if (name)
	{
		this->hasName = true;
		sprintf(this->name, name);
	}	
	this->sliderType = sliderType;
	type = kGuiComponentTypeSliderKnob;
	hottable = true;
	value = 0;
	spriteOn = sliderOn;
	spriteOff = sliderOff;
}


void GuiSliderKnob::draw()
{
	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);

	if (hasImage)
	{
		//if (!dirty) return; // doesn't need drawing
		image->bind();

		GSprite* sprite;

		if (GuiMainWindow::hotComponent == this)
		{
			sprite = image->spriteCollection->GetSprite((int)spriteOn);
		}else{
			sprite = image->spriteCollection->GetSprite((int)spriteOff);
		}
		
		bool lit = GuiMainWindow::hotComponent == this || GuiMainWindow::dragComponent == this;

		//glColor4f(1,1,1,1);
		glBegin(GL_QUADS);

		if (synthItem)
		{
			ParamFloat* p  = (ParamFloat*)synthItem->param;
			//float mult = 127.0 / max;
			value = p->ValueAsInt();

			// set item value
			switch(p->ValueType)
			{
			case(kParamValueTypeTime):
				sprintf(GuiMainWindow::labelText, "%0.3f secs", p->TargetValue);
				break;

			case(kParamValueTypeZeroToOneUni):
				// todo percent not working
				sprintf(GuiMainWindow::labelText, "%0.3f%% ", p->TargetValue);
				break;

			case(kParamValueTypeZeroToOneBi):
				// todo percent not working
				sprintf(GuiMainWindow::labelText, "%0.3f%% ", p->TargetValue);
				break;

			case(kParamValueTypeCents):
				// todo percent not working
				sprintf(GuiMainWindow::labelText, "%d cents", (int)p->TargetValue);
				break;

			default:
				sprintf(GuiMainWindow::labelText, " MISS %0.3f%% ", p->TargetValue);
				break;
			}		

			if (lit)
			{
				GuiMainWindow::panelMaster->SetParamValue(&GuiMainWindow::labelText[0]);
				// set item name
				if (hasName)
				{
					GuiMainWindow::panelMaster->SetParamName(&this->name[0]);
				}
			}		
		}

		image->drawSprite(sprite, 0, -16-value);

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


void GuiSliderKnob::HandleDrag(GEvent* evt)
{
	float distance = (evt->pos.y - GuiMainWindow::dragPoint->y);
	char msg[255];
	
	if (IsHot(evt->pos.Plus(0, value), true))
	{		
		// set value
		float newVal = value - distance;
		if (newVal < 0) newVal = 0;
		if (newVal > 127) newVal = 127;

		value = newVal;

		if (synthItem)
		{
			ParamFloat* p  = (ParamFloat*)synthItem->param;
			p->SetValueWithInt((int)newVal);

			if (synthItem->item->type == kStackItemTypeLfoAllVoices || 
				synthItem->item->type == kStackItemTypeLfoPerVoice || 
				synthItem->item->type == kStackItemTypeAmpEg || 
				synthItem->item->type == kStackItemTypePitchEg || 
				synthItem->item->type == kStackItemTypeEnvAdsr)
			{
				// enable lfo/eg
				synthItem->item->enabled = newVal != 0;
			}
			
			if (synthItem->item && synthItem->item->type == kStackItemTypeModDelay)
			{
				ModDelay* md = (ModDelay*)synthItem->item;
				md->Set();
			}
			if (synthItem->item && synthItem->item->type == kStackItemTypeGlobalReverb)
			{
				Reverb* md = (Reverb*)synthItem->item;
				md->Set();
			}

			sprintf(&msg[0], "knob val: %d", (int)newVal);
			DebugPrintLine(msg);
		}

		sprintf(&msg[0], "drag y: %d, %d", (int)distance, value);

		DebugPrintLine(msg);
		GuiMainWindow::dragPoint->y = evt->pos.y;

	}else{
		DebugPrintLine("NOT HOT SK");
	}
}

void GuiSliderKnob::HandleEvent(GEvent* evt, bool recursing) 
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

			if (GuiMainWindow::dragComponent == this)
			{
				//DebugPrintLine("DRAGGING KNOB");
				HandleDrag(evt);
				evt->isHandled = true;
			}

			// check children first
			for(int i=0; i<this->SubComponentCount(); i++)
			{
				GuiComponent* gc = GetComponent(i);
				gc->HandleEvent(evt, true);		
			}

			if (!evt->isHandled && GuiMainWindow::dragComponent == NULL && IsHot(evt->pos.Plus(0, value)))
			{
				if (GuiMainWindow::hotComponent  != this)
				{
					//DebugPrintLine("HOT SLIDER");
				}
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

			if (!evt->isHandled && IsHot(evt->pos.Plus(0, value)))
			{
				//DebugPrintLine("START DRAG KNOB");
				GuiMainWindow::dragComponent = this;
				GuiMainWindow::dragPoint->x = evt->pos.x;
				GuiMainWindow::dragPoint->y = evt->pos.y;
				evt->isHandled = true;
				return;
			}
			break;
		}
	case(kGEventMouseUp):
		{
			//DebugPrintLine("STOP DRAG KNOB");
			GuiMainWindow::dragComponent = NULL;
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

bool GuiSliderKnob::IsHot(GPoint pos, bool onlyCheckY)
{
	return GuiComponent::IsHot(pos.Plus(0, 20), onlyCheckY);
}


GuiSliderKnob::~GuiSliderKnob(void)
{
}

// slider

/*

cursor Y must be same Y as bar for bar to move
bar pos matches Y pos within slider bounds

*/

GuiSlider::GuiSlider(int width, int height, int offsetX, int offsetY, int imageId, SpritesButton sliderOn, SpritesButton sliderOff, SliderType sliderType, char* name) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	hottable = true;
	this->knob = new GuiSliderKnob(38, 33, -2, height, imageId, sliderOn, sliderOff, sliderType, name);
	if (name)
	{
		this->hasName = true;
		sprintf(this->name, name);
	}	
	AddSubComponent(this->knob);
	type = kGuiComponentTypeSlider;
}


GuiSlider::~GuiSlider(void)
{
}


void GuiSlider::draw()
{
	float screenOffsetY = this->GetOffsetY();
	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);
	
	// draw slider background (for testing)
#ifdef DRAW_OVERLAYS
	glColor4f(0, 0, 0, 0.5);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	{
		glVertex2i(0,0);
		glVertex2i(0,0+height);
		glVertex2i(0+width,0+height);
		glVertex2i(0+width,0);
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);
#endif

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

