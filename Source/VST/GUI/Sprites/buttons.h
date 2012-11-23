#pragma once
#include "../../includes.h"
#include "../../Utils/Types.h"

enum SpritesButton
{
	kSpritesButtons_None = 0,
	kSpritesButtons_But_1_off,
	kSpritesButtons_But_1_off_lit,
	kSpritesButtons_But_1_on,
	kSpritesButtons_But_1_on_lit,
	kSpritesButtons_But_2_off,
	kSpritesButtons_But_2_off_lit,
	kSpritesButtons_But_2_on,
	kSpritesButtons_But_2_on_lit,
	kSpritesButtons_But_3_off,
	kSpritesButtons_But_3_off_lit,
	kSpritesButtons_But_3_on,
	kSpritesButtons_But_3_on_lit,
	kSpritesButtons_But_4_off,
	kSpritesButtons_But_4_off_lit,
	kSpritesButtons_But_4_on,
	kSpritesButtons_But_4_on_lit,
	kSpritesButtons_But_5_off,
	kSpritesButtons_But_5_off_lit,
	kSpritesButtons_But_5_on,
	kSpritesButtons_But_5_on_lit,
	kSpritesButtons_But_6_off,
	kSpritesButtons_But_6_off_lit,
	kSpritesButtons_But_6_on,
	kSpritesButtons_But_6_on_lit,
	kSpritesButtons_But_amp_off,
	kSpritesButtons_But_amp_off_lit,
	kSpritesButtons_But_amp_on,
	kSpritesButtons_But_amp_on_lit,
	kSpritesButtons_But_filterLink_off,
	kSpritesButtons_But_filterLink_on,
	kSpritesButtons_But_filterMode_dual,
	kSpritesButtons_But_filterMode_para,
	kSpritesButtons_But_master_limit_off,
	kSpritesButtons_But_master_limit_on,
	kSpritesButtons_But_modArp_arp,
	kSpritesButtons_But_modArp_mod,
	kSpritesButtons_But_mod_1_8,
	kSpritesButtons_But_mod_9_16,
	kSpritesButtons_But_osc_power_off,
	kSpritesButtons_But_osc_power_on,
	kSpritesButtons_But_pitch_off,
	kSpritesButtons_But_pitch_off_lit,
	kSpritesButtons_But_pitch_on,
	kSpritesButtons_But_pitch_on_lit,
	kSpritesButtons_Keyboard_overlay,
	kSpritesButtons_Slider,
	kSpritesButtons_Slider_2,
	kSpritesButtons_Slider_focus,
	kSpritesButtons_Slider_focus_2,

};

class SpritesButtonsSprites : public GSpriteCollection
{
public:
	SpritesButtonsSprites();
};
