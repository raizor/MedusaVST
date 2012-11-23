#pragma once

#include "buttons.h"

SpritesButtonsSprites::SpritesButtonsSprites()
{
	imageWidth = 256;
	imageHeight = 256;
	pixelSizeX = 1.0f/imageWidth;
	pixelSizeY = 1.0f/imageHeight;
	GSprite* sp = new GSprite(0,0,0,0, kSpritesButtons_None);
	AddSprite(sp);
	sp = new GSprite(154, 204, 26, 27, kSpritesButtons_But_1_off);
	AddSprite(sp);

	sp = new GSprite(227, 175, 26, 27, kSpritesButtons_But_1_off_lit);
	AddSprite(sp);

	sp = new GSprite(126, 211, 26, 27, kSpritesButtons_But_1_on);
	AddSprite(sp);

	sp = new GSprite(126, 182, 26, 27, kSpritesButtons_But_1_on_lit);
	AddSprite(sp);

	sp = new GSprite(98, 211, 26, 27, kSpritesButtons_But_2_off);
	AddSprite(sp);

	sp = new GSprite(98, 182, 26, 27, kSpritesButtons_But_2_off_lit);
	AddSprite(sp);

	sp = new GSprite(70, 227, 26, 27, kSpritesButtons_But_2_on);
	AddSprite(sp);

	sp = new GSprite(70, 198, 26, 27, kSpritesButtons_But_2_on_lit);
	AddSprite(sp);

	sp = new GSprite(70, 169, 26, 27, kSpritesButtons_But_3_off);
	AddSprite(sp);

	sp = new GSprite(120, 153, 26, 27, kSpritesButtons_But_3_off_lit);
	AddSprite(sp);

	sp = new GSprite(42, 217, 26, 27, kSpritesButtons_But_3_on);
	AddSprite(sp);

	sp = new GSprite(42, 188, 26, 27, kSpritesButtons_But_3_on_lit);
	AddSprite(sp);

	sp = new GSprite(42, 159, 26, 27, kSpritesButtons_But_4_off);
	AddSprite(sp);

	sp = new GSprite(92, 140, 26, 27, kSpritesButtons_But_4_off_lit);
	AddSprite(sp);

	sp = new GSprite(64, 130, 26, 27, kSpritesButtons_But_4_on);
	AddSprite(sp);

	sp = new GSprite(36, 130, 26, 27, kSpritesButtons_But_4_on_lit);
	AddSprite(sp);

	sp = new GSprite(227, 146, 26, 27, kSpritesButtons_But_5_off);
	AddSprite(sp);

	sp = new GSprite(199, 147, 26, 27, kSpritesButtons_But_5_off_lit);
	AddSprite(sp);

	sp = new GSprite(227, 117, 26, 27, kSpritesButtons_But_5_on);
	AddSprite(sp);

	sp = new GSprite(227, 88, 26, 27, kSpritesButtons_But_5_on_lit);
	AddSprite(sp);

	sp = new GSprite(227, 59, 26, 27, kSpritesButtons_But_6_off);
	AddSprite(sp);

	sp = new GSprite(199, 118, 26, 27, kSpritesButtons_But_6_off_lit);
	AddSprite(sp);

	sp = new GSprite(199, 89, 26, 27, kSpritesButtons_But_6_on);
	AddSprite(sp);

	sp = new GSprite(199, 60, 26, 27, kSpritesButtons_But_6_on_lit);
	AddSprite(sp);

	sp = new GSprite(129, 124, 34, 27, kSpritesButtons_But_amp_off);
	AddSprite(sp);

	sp = new GSprite(133, 95, 34, 27, kSpritesButtons_But_amp_off_lit);
	AddSprite(sp);

	sp = new GSprite(93, 111, 34, 27, kSpritesButtons_But_amp_on);
	AddSprite(sp);

	sp = new GSprite(133, 66, 34, 27, kSpritesButtons_But_amp_on_lit);
	AddSprite(sp);

	sp = new GSprite(169, 99, 28, 31, kSpritesButtons_But_filterLink_off);
	AddSprite(sp);

	sp = new GSprite(169, 66, 28, 31, kSpritesButtons_But_filterLink_on);
	AddSprite(sp);

	sp = new GSprite(2, 66, 51, 49, kSpritesButtons_But_filterMode_dual);
	AddSprite(sp);

	sp = new GSprite(90, 2, 51, 49, kSpritesButtons_But_filterMode_para);
	AddSprite(sp);

	sp = new GSprite(165, 132, 32, 26, kSpritesButtons_But_master_limit_off);
	AddSprite(sp);

	sp = new GSprite(221, 31, 32, 26, kSpritesButtons_But_master_limit_on);
	AddSprite(sp);

	sp = new GSprite(2, 34, 86, 30, kSpritesButtons_But_modArp_arp);
	AddSprite(sp);

	sp = new GSprite(2, 2, 86, 30, kSpritesButtons_But_modArp_mod);
	AddSprite(sp);

	sp = new GSprite(199, 2, 54, 27, kSpritesButtons_But_mod_1_8);
	AddSprite(sp);

	sp = new GSprite(143, 2, 54, 27, kSpritesButtons_But_mod_9_16);
	AddSprite(sp);

	sp = new GSprite(182, 176, 26, 26, kSpritesButtons_But_osc_power_off);
	AddSprite(sp);

	sp = new GSprite(154, 176, 26, 26, kSpritesButtons_But_osc_power_on);
	AddSprite(sp);

	sp = new GSprite(95, 82, 36, 27, kSpritesButtons_But_pitch_off);
	AddSprite(sp);

	sp = new GSprite(95, 53, 36, 27, kSpritesButtons_But_pitch_off_lit);
	AddSprite(sp);

	sp = new GSprite(55, 101, 36, 27, kSpritesButtons_But_pitch_on);
	AddSprite(sp);

	sp = new GSprite(183, 31, 36, 27, kSpritesButtons_But_pitch_on_lit);
	AddSprite(sp);

	sp = new GSprite(2, 117, 32, 58, kSpritesButtons_Keyboard_overlay);
	AddSprite(sp);

	sp = new GSprite(143, 31, 38, 33, kSpritesButtons_Slider);
	AddSprite(sp);

	sp = new GSprite(2, 212, 38, 33, kSpritesButtons_Slider_2);
	AddSprite(sp);

	sp = new GSprite(2, 177, 38, 33, kSpritesButtons_Slider_focus);
	AddSprite(sp);

	sp = new GSprite(55, 66, 38, 33, kSpritesButtons_Slider_focus_2);
	AddSprite(sp);


}