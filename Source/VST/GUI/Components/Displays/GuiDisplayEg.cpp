#include "GuiDisplayEg.h"
#include "Items/Processors/Adsr.h"
#include "Synth.h"

GuiDisplayEg::GuiDisplayEg(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	eg = 0;
}


GuiDisplayEg::~GuiDisplayEg(void)
{
}


void GuiDisplayEg::draw()
{
	if (eg == 0) return;

	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);

	float widthf = (float)width;
	float heightf = (float)height;
	float time = 25;
	float totalTime = time * 5;
	float lenPerSec = widthf/totalTime;

	float startLevel = eg->paramsFloat[ADSR_PARAM_FLOAT_START_LEVEL]->TargetValue;
	float delayTime = eg->paramsFloat[ADSR_PARAM_FLOAT_DELAY_TIME]->TargetValue;
	float attackTime = eg->paramsFloat[ADSR_PARAM_FLOAT_ATTACK_TIME]->TargetValue;
	float attackLevel = eg->paramsFloat[ADSR_PARAM_FLOAT_ATTACK_LEVEL]->TargetValue;
	float decayTime = eg->paramsFloat[ADSR_PARAM_FLOAT_DECAY_TIME]->TargetValue;
	float decayLevel = eg->paramsFloat[ADSR_PARAM_FLOAT_DECAY_LEVEL]->TargetValue;
	float sustainTime = eg->paramsFloat[ADSR_PARAM_FLOAT_SUSTAIN_TIME]->TargetValue;
	float sustainLevel = eg->paramsFloat[ADSR_PARAM_FLOAT_SUSTAIN_LEVEL]->TargetValue;
	float releaseTime = eg->paramsFloat[ADSR_PARAM_FLOAT_RELEASE_TIME]->TargetValue;
	float releaseLevel = eg->paramsFloat[ADSR_PARAM_FLOAT_RELEASE_LEVEL]->TargetValue;

	if (eg->type == kStackItemTypePitchEg)
	{
		// bi level knobs
		startLevel = (startLevel + 1.0f)/2.0f;
		attackLevel = (attackLevel + 1.0f) / 2.0f;
		releaseLevel = (releaseLevel + 1.0f) / 2.0f;
		decayLevel = (decayLevel + 1.0f) / 2.0f;
	}

	float posx = 0;
	float posy = heightf;
	float valx = 0;
	float valy = 0;


	float mult = 0.194f;
	delayTime = Constants::instance->GetExponentialValue(delayTime, 127, 2) * mult;
	attackTime = Constants::instance->GetExponentialValue(attackTime, 127, 2) * mult;
	decayTime = Constants::instance->GetExponentialValue(decayTime, 127, 2) * mult;
	sustainTime = Constants::instance->GetExponentialValue(sustainTime, 127, 2) * mult;
	releaseTime = Constants::instance->GetExponentialValue(releaseTime, 127, 2) * mult;

	
	glColor4f(1, 1, 1, 1);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);

		// delay
		valx = delayTime * lenPerSec;
		posy = heightf - (heightf*startLevel);
		glVertex2i(posx, posy);
		glVertex2i(posx + valx, posy);
		posx += valx;

		// attack
		valx = attackTime * lenPerSec;
		glVertex2i(posx, posy);
		glVertex2i(posx + valx, heightf - (heightf * attackLevel));
		posx += valx;

		// decayLevel
		valx = decayTime * lenPerSec;
		glVertex2i(posx, heightf-(heightf * attackLevel));
		glVertex2i(posx + valx, heightf - (heightf * decayLevel));
		posx += valx;

		// sustain
		valx = sustainTime * lenPerSec;
		glVertex2i(posx, heightf - (heightf * decayLevel));
		glVertex2i(posx + valx, heightf - (heightf * sustainLevel));
		posx += valx;

		// release
		valx = releaseTime * lenPerSec;
		glVertex2i(posx, heightf - (heightf * sustainLevel));
		glVertex2i(posx + valx, heightf-(heightf*releaseLevel));
		posx += valx;


	glEnd();
	glEnable(GL_TEXTURE_2D);

	//e.Graphics.DrawLine(pen, posx, posy, posx + valx, posy);
	//e.Graphics.DrawEllipse(penWhite, posx + valx - 2.0f, posy - 2.0f, 4.0f, 4.0f);
	posx += valx;

	glPopMatrix();

}

void GuiDisplayEg::SetEg(Adsr* eg)
{

}