#include "GuiPanelFilter.h"
#include "Items/Processors/SimpleFilter.h"
#include "Utils/WaveTableGen.h"
#include "../../GUI/Components/GuiMainWindow.h"


GuiPanelFilter::GuiPanelFilter(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	knobCutoff1 = new GuiKnob(0, 0, 263, 70, IDB_KNOBS_UNI, 0, 127, true, kKnobTypeDecimalTwoPlaces, "CUTOFF 1");
	knobResonance1 = new GuiKnob(0, 0, 303, 38, IDB_KNOBS_UNI, 0, 127, true, kKnobTypeDecimalTwoPlaces, "RESONANCE 1");	
	knobPan1 = new GuiKnob(0, 0, 359, 38, IDB_KNOBS_BI, 0, 127, true, kKnobTypePan, "PANNING 1");	
	knobLevel1 = new GuiKnob(0, 0, 400, 70, IDB_KNOBS_UNI, 0, 127, true, kKnobTypeDecimalTwoPlaces, "LEVEL 1");
	
	knobCutoff2 = new GuiKnob(0, 0, 263, 130, IDB_KNOBS_UNI, 0, 127, true, kKnobTypeDecimalTwoPlaces, "CUTOFF 2");
	knobResonance2 = new GuiKnob(0, 0, 303, 164, IDB_KNOBS_UNI, 0, 127, true, kKnobTypeDecimalTwoPlaces, "RESONANCE 2");
	knobPan2 = new GuiKnob(0, 0, 359, 164, IDB_KNOBS_BI, 0, 127, true, kKnobTypePan, "PANNING 2");
	knobLevel2 = new GuiKnob(0, 0, 400, 130, IDB_KNOBS_UNI, 0, 127, true, kKnobTypeDecimalTwoPlaces, "LEVEL 2");

	AddSubComponent(knobCutoff1);
	AddSubComponent(knobResonance1);
	AddSubComponent(knobPan1);
	AddSubComponent(knobLevel1);

	AddSubComponent(knobCutoff2);
	AddSubComponent(knobResonance2);
	AddSubComponent(knobPan2);
	AddSubComponent(knobLevel2);

	butMode = new GuiButton(51, 49, 328, 100, IDB_BUTTONSTRIP, kSpritesButtons_But_filterMode_para, kSpritesButtons_But_filterMode_dual, kSpritesButtons_None);
	AddSubComponent(butMode);

	butLink = new GuiButton(28, 31, 233, 110, IDB_BUTTONSTRIP, kSpritesButtons_But_filterLink_off, kSpritesButtons_But_filterLink_on, kSpritesButtons_None);
	AddSubComponent(butLink);
	
	int lineSpacing = 13;
	int textStartY = 43;
	int textStartX = 86;

	// labels
	labFilter1Type = new GuiLabel(72, 12, textStartX, textStartY+0, "Off");
	labFilter1Type->ClickedHandler = (FpClickedCallback)&GuiPanelFilter::CallbackClicked;
	AddSubComponent(labFilter1Type);

	labFilter1Limiter = new GuiLabel(72, 12, textStartX, textStartY+19, "Off");
	labFilter1Limiter->ClickedHandler = (FpClickedCallback)&GuiPanelFilter::CallbackClicked;
	AddSubComponent(labFilter1Limiter);

	labFilter1ResoBoost = new GuiLabel(72, 12, textStartX, textStartY+38, "Off");
	labFilter1ResoBoost->ClickedHandler = (FpClickedCallback)&GuiPanelFilter::CallbackClicked;
	AddSubComponent(labFilter1ResoBoost);

	textStartY+=90;

	labFilter2Type = new GuiLabel(72, 12, textStartX, textStartY+0, "Off");
	labFilter2Type->ClickedHandler = (FpClickedCallback)&GuiPanelFilter::CallbackClicked;
	AddSubComponent(labFilter2Type);

	labFilter2Limiter = new GuiLabel(72, 12, textStartX, textStartY+19, "Off");
	labFilter2Limiter->ClickedHandler = (FpClickedCallback)&GuiPanelFilter::CallbackClicked;
	AddSubComponent(labFilter2Limiter);

	labFilter2ResoBoost = new GuiLabel(72, 12, textStartX, textStartY+38, "Off");
	labFilter2ResoBoost->ClickedHandler = (FpClickedCallback)&GuiPanelFilter::CallbackClicked;
	AddSubComponent(labFilter2ResoBoost);

	int num = NUMBER_START_FILTER;
	SetStackItem((SimpleFilter*)PatchList::list->CurrentPatch->items[num], (SimpleFilter*)PatchList::list->CurrentPatch->items[num+1]);

}

GuiPanelFilter::~GuiPanelFilter(void)
{
}

void GuiPanelFilter::SetStackItem(SimpleFilter* item1, SimpleFilter* item2)
{
	// root
	this->synthItem = new LinkedSynthItem();
	this->synthItem->item = item1;

	this->synthItem2 = new LinkedSynthItem();
	this->synthItem2->item = item2;

	// controls
	LinkedSynthItem* si;

	// cutoff 1
	si = new LinkedSynthItem();
	si->item = item1;
	si->itemType = item1->itemType;
	si->param = item1->paramsFloat[FILTER_PARAM_FLOAT_CUTOFF];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobCutoff1->synthItem = si;

	// res 1
	si = new LinkedSynthItem();
	si->item = item1;
	si->itemType = item1->itemType;
	si->param = item1->paramsFloat[FILTER_PARAM_FLOAT_RESONANCE];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobResonance1->synthItem = si;

	// panning 1
	si = new LinkedSynthItem();
	si->item = item1;
	si->itemType = item1->itemType;
	si->param = item1->paramsFloat[FILTER_PARAM_FLOAT_PANNING];
	si->valueType = kParamValueTypePan;
	si->paramType = kParamTypeFloat;
	knobPan1->synthItem = si;

	// level 1
	si = new LinkedSynthItem();
	si->item = item1;
	si->itemType = item1->itemType;
	si->param = item1->paramsFloat[PROC_PARAM_FLOAT_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobLevel1->synthItem = si;

	// cutoff 2
	si = new LinkedSynthItem();
	si->item = item2;
	si->itemType = item2->itemType;
	si->param = item2->paramsFloat[FILTER_PARAM_FLOAT_CUTOFF];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobCutoff2->synthItem = si;

	// res 2
	si = new LinkedSynthItem();
	si->item = item2;
	si->itemType = item2->itemType;
	si->param = item2->paramsFloat[FILTER_PARAM_FLOAT_RESONANCE];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobResonance2->synthItem = si;

	// panning 2
	si = new LinkedSynthItem();
	si->item = item2;
	si->itemType = item2->itemType;
	si->param = item2->paramsFloat[FILTER_PARAM_FLOAT_PANNING];
	si->valueType = kParamValueTypePan;
	si->paramType = kParamTypeFloat;
	knobPan2->synthItem = si;

	// level 2
	si = new LinkedSynthItem();
	si->item = item2;
	si->itemType = item2->itemType;
	si->param = item2->paramsFloat[PROC_PARAM_FLOAT_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobLevel2->synthItem = si;

}

void GuiPanelFilter::CallbackClicked(void* data, GEvent* evt)
{
	char msg[100];

	// filter 1 type
	if (data == GuiMainWindow::panelFilter->labFilter1Type)
	{
		SimpleFilter* filter = (SimpleFilter*)GuiMainWindow::panelFilter->synthItem->item;			
		ParamInt *param = filter->paramsInt[FILTER_PARAM_INT_TYPE];
		int currentIndex = param->Value();
		if (currentIndex < kFilterTypeItemCount-1)
		{
			currentIndex++;
		}else{
			currentIndex = 0;
		}
		filter->enabled = currentIndex;
		param->SetValue(currentIndex);
		sprintf(GuiMainWindow::panelFilter->labFilter1Type->text, GuiMainWindow::panelFilter->FilterTypeToString(currentIndex));
		return;
	}

	// filter 1 limiter
	if (data == GuiMainWindow::panelFilter->labFilter1Limiter)
	{
		SimpleFilter* filter = (SimpleFilter*)GuiMainWindow::panelFilter->synthItem->item;			
		ParamInt *param = filter->paramsInt[FILTER_PARAM_INT_LIMITER];
		int currentIndex = param->Value();
		if (currentIndex < kFilterTypeItemCount-1)
		{
			currentIndex++;
		}else{
			currentIndex = 0;
		}
		param->SetValue(currentIndex);
		sprintf(GuiMainWindow::panelFilter->labFilter1Type->text, GuiMainWindow::panelFilter->FilterTypeToString(currentIndex));
		return;
	}

}

char* GuiPanelFilter::FilterTypeToString(int val) 
{ 
	if (val == kFilterTypeOff) return "Off";
	if (val == kFilterTypeLowPass) return "Low Pass"; 
	if (val == kFilterTypeHighPass) return "High Pass"; 
	if (val == kFilterTypeBandPass) return "Band Pass"; 
	if (val == kFilterTypeNotch) return "Notch"; 
	if (val == kFilterTypeAll) return "All Pass"; 
	if (val == kFilterTypeMoogLow) return "Moog Low"; 
	if (val == kFilterTypeMoogHigh) return "Moog High"; 
	return "???";
}