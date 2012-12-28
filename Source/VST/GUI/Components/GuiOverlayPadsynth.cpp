#include "GuiOverlayPadsynth.h"
#include "Utils/WaveTableGen.h"
#include "Items/Processors/Osc.h"
#include "../../GUI/Components/GuiMainWindow.h"
#include "../../Utils/ContextMenus.h"

GuiOverlayPadsynth::GuiOverlayPadsynth(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	waveForm = kWaveFormPadSynthChoir;
	nPower = 2;

	// overlay panel
	background = new GuiComponent(397, 217, 0, 0, IDB_BUTTONSTRIP, kSpritesButtons_Padsynth_panel, false, 0);
	background->enabled = true;
	AddSubComponent(background);	


	knobAmp = new GuiKnob(0, 0, 14, 127, IDB_KNOBS_UNI, 0, 127, true, kKnobTypeDecimalTwoPlaces, "Amplitude");
	AddSubComponent(knobAmp);

	knobBandwidth = new GuiKnob(0, 0, 72, 127, IDB_KNOBS_UNI, 0, 127, true, kKnobTypeDecimalTwoPlaces, "Bandwidth");
	AddSubComponent(knobBandwidth);

	knobBandwidthScale = new GuiKnob(0, 0, 130, 127, IDB_KNOBS_UNI, 0, 127, true, kKnobTypeDecimalTwoPlaces, "Bandwidth Scale");
	AddSubComponent(knobBandwidthScale);

	knobFormantScale = new GuiKnob(0, 0, 188, 127, IDB_KNOBS_UNI, 0, 127, true, kKnobTypeDecimalTwoPlaces, "Formant Scale");
	AddSubComponent(knobFormantScale);

	butClose = new GuiButton(22, 22, 362, 13, IDB_BUTTONSTRIP, kSpritesButtons_Exit_small, kSpritesButtons_Exit_small, kSpritesButtons_None);
	butClose->ClickedHandler = (FpClickedCallback)&GuiOverlayPadsynth::CallbackClicked;
	AddSubComponent(butClose);
		
	butGenerate = new GuiButton(62, 18, 14, 187, IDB_BUTTONSTRIP, kSpritesButtons_But_generate, kSpritesButtons_But_generate, kSpritesButtons_None);
	butGenerate->ClickedHandler = (FpClickedCallback)&GuiOverlayPadsynth::CallbackClicked;
	AddSubComponent(butGenerate);


	// knob labels
	labKnob1 = new GuiLabel(40, 12, 16, 175, "AMP", true, kGuiLabelSizeBold);
	AddSubComponent(labKnob1);

	labKnob2 = new GuiLabel(40, 12, 74, 175, "BW", true, kGuiLabelSizeBold);
	AddSubComponent(labKnob2);

	labKnob3 = new GuiLabel(40, 12, 132, 175, "BW SCALE", true, kGuiLabelSizeBold);
	AddSubComponent(labKnob3);

	labKnob4 = new GuiLabel(40, 12, 190, 175, "FMT SCALE", true, kGuiLabelSizeBold);
	AddSubComponent(labKnob4);

	// labels
	labWaveTypeName = new GuiLabel(72, 12, 25, 49, "TYPE");
	AddSubComponent(labWaveTypeName);

	labWaveType = new GuiLabel(72, 12, 73, 49, "Choir");
	labWaveType->ClickedHandler = (FpClickedCallback)&GuiOverlayPadsynth::CallbackClicked;
	AddSubComponent(labWaveType);

	labNameName = new GuiLabel(72, 12, 16, 72, "NAME");
	AddSubComponent(labNameName);

	labName = new GuiLabel(72, 12, 73, 72, "Unnamed");
	labName->EditedHandler = (FpClickedCallback)&GuiOverlayPadsynth::CallbackEdited;
	labName->ClickedHandler = (FpClickedCallback)&GuiOverlayPadsynth::CallbackClicked;
	AddSubComponent(labName);
}

void GuiOverlayPadsynth::CallbackEdited(void* data, GEvent* evt)
{
}

void GuiOverlayPadsynth::CallbackClicked(void* data, GEvent* evt)
{
	char msg[100];

	/*
	if (data == GuiMainWindow::padsynthOverlay->labNPower)
	{
		if (GuiMainWindow::padsynthOverlay->nPower < 10)
		{
			GuiMainWindow::padsynthOverlay->nPower++;			
		}else{
			GuiMainWindow::padsynthOverlay->nPower = 1;
		}
		char* ch = new char[10];
		sprintf(ch, "%d", GuiMainWindow::padsynthOverlay->nPower);
		GuiMainWindow::padsynthOverlay->labNPower->SetText(ch);
		delete(ch);
	}*/

	if (data == GuiMainWindow::padsynthOverlay->labWaveType)
	{
		if (GuiMainWindow::padsynthOverlay->waveForm < kWaveFormPadSynthExtended)
		{
			int wf = GuiMainWindow::padsynthOverlay->waveForm;
			wf++;
			GuiMainWindow::padsynthOverlay->waveForm = (WaveForm)wf;
		}else{
			GuiMainWindow::padsynthOverlay->waveForm = kWaveFormPadSynthChoir;
		}

		if (GuiMainWindow::padsynthOverlay->waveForm == kWaveFormPadSynthChoir)
		{
			GuiMainWindow::padsynthOverlay->labWaveType->SetText("Choir");
		}

		if (GuiMainWindow::padsynthOverlay->waveForm == kWaveFormPadSynthEnsemble)
		{
			GuiMainWindow::padsynthOverlay->labWaveType->SetText("Ensemble");
		}

		if (GuiMainWindow::padsynthOverlay->waveForm == kWaveFormPadSynthExtended)
		{
			GuiMainWindow::padsynthOverlay->labWaveType->SetText("Extended");
		}

	}

	if (data == GuiMainWindow::padsynthOverlay->butClose)
	{
		GuiMainWindow::padsynthOverlay->enabled = false;
	}

	// octave detune
	if (data == GuiMainWindow::padsynthOverlay->butGenerate)
	{
		DebugPrintLine("GEN PS");

		float amplitude = 1.0f;
		int npower = 2;
		float bandwidth = 20.0f;
		float bandwidthScale =  0.5f;
		float formantScale = 1.0f;
		int tablesPerOctave = 4;

		WaveTable* table = WaveTableGen::GeneratePadWaveTable(GuiMainWindow::padsynthOverlay->waveForm, "hello", amplitude, GuiMainWindow::padsynthOverlay->nPower, formantScale, bandwidth, bandwidthScale, tablesPerOctave);
		WaveTable::Wavetables[WaveTable::NumWaveTables] = table;

		int tableNum = WaveTable::NumWaveTables++;

		Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;		
		ParamInt *param = osc->paramsInt[OSC_PARAM_INT_WAVEFORM];
		param->SetValue(tableNum);
		osc->WaveChanged();
		GuiMainWindow::panelOsc->SetWaveformName(osc);

		DebugPrintLine("GEN DONE");
		/*
		Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;		
		ParamFloat *param = osc->paramsFloat[OSC_PARAM_FLOAT_DETUNE_OCT];
		int currentIndex = param->ValueAsInt();
		if (evt->button == kGEventMouseButtonLeft)
		{
			if (currentIndex < 5) // +/- 5 octaves
			{
				currentIndex++;
			}else{
				currentIndex = -5;
			}
		}else if (evt->button == kGEventMouseButtonRight)
		{
			if (currentIndex >-5) // +/- 5 octaves
			{
				currentIndex--;
			}else{
				currentIndex = 5;
			}
		}

		param->SetValueWithInt(currentIndex);
		char* txt = new char[10];
		sprintf(txt, "%d", currentIndex);
		GuiMainWindow::panelOsc->labOctave->SetText(txt);
		delete(txt);
		*/
	}
}


GuiOverlayPadsynth::~GuiOverlayPadsynth(void)
{
}
