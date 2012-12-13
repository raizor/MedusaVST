#include "GuiDisplayWave.h"
#include "Items/Processors/Osc.h"
#include "Items/Processors/Lfo.h"
#include "Utils/WaveTableGen.h"s

GuiDisplayWave::GuiDisplayWave(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	osc = 0;
}


GuiDisplayWave::~GuiDisplayWave(void)
{
}

void GuiDisplayWave::SetOsc(Item* osc)
{
	this->osc = osc;
}


void GuiDisplayWave::draw()
{
	if (osc == 0) return;

	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);


	glColor4f(1, 1, 1, 1);
	glDisable(GL_TEXTURE_2D);
	glLineWidth(1.0f);
	glBegin(GL_LINE_STRIP);
	
	switch (osc->type)
	{
	case(kStackItemTypeWfOsc):
		{		
			int x = 0;
			int halfHeight = height * 0.5f;
			int waveSize = osc->waveTableIdx->Table->Tables[0].FloatBuffer->Size;
			int inc = waveSize/width;
			float phase = osc->paramsFloat[OSC_PARAM_FLOAT_PHASE]->TargetValue;
			int offset = waveSize * phase;
			for(int i=0; i<waveSize; i+=inc)
			{
				float val = osc->waveTableIdx->Table->Tables[0].FloatBuffer->Buffer[(i+offset) % waveSize].l;
				int hv = (int)(val * height * 0.5f);
				glVertex2i(x, hv+halfHeight);
				x++;
			}
		}
		break;
	case(kStackItemTypeLfoAllVoices):
		{		
			int x = 0;
			int halfHeight = height * 0.5f;
			int waveSize = osc->waveTableIdx->Table->Tables[0].FloatBuffer->Size;
			int inc = waveSize/width;
			float phase = 0;//osc->paramsFloat[OSC_PARAM_FLOAT_PHASE]->TargetValue;
			int offset = waveSize * phase;
			for(int i=0; i<waveSize; i+=inc)
			{
				float val = osc->waveTableIdx->Table->Tables[0].FloatBuffer->Buffer[(i+offset) % waveSize].l;
				int hv = (int)(val * height * 0.5f);
				glVertex2i(x, hv+halfHeight);
				x++;
			}
		}
		break;
	case(kStackItemTypeLfoPerVoice):
		break;

	}
	
	//glVertex2i(width,height);
	
	glEnd();
	glEnable(GL_TEXTURE_2D);


	glPopMatrix();

}