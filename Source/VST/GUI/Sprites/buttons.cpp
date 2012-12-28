#pragma once

#include "buttons.h"

SpritesButtonsSprites::SpritesButtonsSprites()
{
	imageWidth = 1024;
	imageHeight = 512;
	pixelSizeX = 1.0f/imageWidth;
	pixelSizeY = 1.0f/imageHeight;
	GSprite* sp = new GSprite(0,0,0,0, kSpritesButtons_None);
	AddSprite(sp);
	sp = new GSprite(809, 2, 211, 22, kSpritesButtons_Box_patchName);
	AddSprite(sp);

	sp = new GSprite(704, 70, 70, 22, kSpritesButtons_Box_patchNum);
	AddSprite(sp);

	sp = new GSprite(521, 268, 26, 27, kSpritesButtons_But_1_off);
	AddSprite(sp);

	sp = new GSprite(501, 239, 26, 27, kSpritesButtons_But_1_off_lit);
	AddSprite(sp);

	sp = new GSprite(495, 210, 26, 27, kSpritesButtons_But_1_on);
	AddSprite(sp);

	sp = new GSprite(493, 181, 26, 27, kSpritesButtons_But_1_on_lit);
	AddSprite(sp);

	sp = new GSprite(493, 152, 26, 27, kSpritesButtons_But_2_off);
	AddSprite(sp);

	sp = new GSprite(493, 70, 26, 27, kSpritesButtons_But_2_off_lit);
	AddSprite(sp);

	sp = new GSprite(493, 123, 26, 27, kSpritesButtons_But_2_on);
	AddSprite(sp);

	sp = new GSprite(493, 297, 26, 27, kSpritesButtons_But_2_on_lit);
	AddSprite(sp);

	sp = new GSprite(493, 268, 26, 27, kSpritesButtons_But_3_off);
	AddSprite(sp);

	sp = new GSprite(473, 239, 26, 27, kSpritesButtons_But_3_off_lit);
	AddSprite(sp);

	sp = new GSprite(467, 210, 26, 27, kSpritesButtons_But_3_on);
	AddSprite(sp);

	sp = new GSprite(465, 181, 26, 27, kSpritesButtons_But_3_on_lit);
	AddSprite(sp);

	sp = new GSprite(465, 152, 26, 27, kSpritesButtons_But_4_off);
	AddSprite(sp);

	sp = new GSprite(465, 70, 26, 27, kSpritesButtons_But_4_off_lit);
	AddSprite(sp);

	sp = new GSprite(465, 123, 26, 27, kSpritesButtons_But_4_on);
	AddSprite(sp);

	sp = new GSprite(465, 297, 26, 27, kSpritesButtons_But_4_on_lit);
	AddSprite(sp);

	sp = new GSprite(465, 268, 26, 27, kSpritesButtons_But_5_off);
	AddSprite(sp);

	sp = new GSprite(445, 239, 26, 27, kSpritesButtons_But_5_off_lit);
	AddSprite(sp);

	sp = new GSprite(439, 210, 26, 27, kSpritesButtons_But_5_on);
	AddSprite(sp);

	sp = new GSprite(437, 181, 26, 27, kSpritesButtons_But_5_on_lit);
	AddSprite(sp);

	sp = new GSprite(437, 152, 26, 27, kSpritesButtons_But_6_off);
	AddSprite(sp);

	sp = new GSprite(437, 70, 26, 27, kSpritesButtons_But_6_off_lit);
	AddSprite(sp);

	sp = new GSprite(437, 123, 26, 27, kSpritesButtons_But_6_on);
	AddSprite(sp);

	sp = new GSprite(776, 70, 26, 27, kSpritesButtons_But_6_on_lit);
	AddSprite(sp);

	sp = new GSprite(401, 181, 34, 27, kSpritesButtons_But_amp_off);
	AddSprite(sp);

	sp = new GSprite(401, 152, 34, 27, kSpritesButtons_But_amp_off_lit);
	AddSprite(sp);

	sp = new GSprite(401, 70, 34, 27, kSpritesButtons_But_amp_on);
	AddSprite(sp);

	sp = new GSprite(401, 123, 34, 27, kSpritesButtons_But_amp_on_lit);
	AddSprite(sp);

	sp = new GSprite(199, 289, 28, 31, kSpritesButtons_But_filterLink_off);
	AddSprite(sp);

	sp = new GSprite(171, 256, 28, 31, kSpritesButtons_But_filterLink_on);
	AddSprite(sp);

	sp = new GSprite(36, 221, 51, 49, kSpritesButtons_But_filterMode_dual);
	AddSprite(sp);

	sp = new GSprite(2, 281, 51, 49, kSpritesButtons_But_filterMode_para);
	AddSprite(sp);

	sp = new GSprite(55, 310, 62, 18, kSpritesButtons_But_generate);
	AddSprite(sp);

	sp = new GSprite(323, 251, 120, 28, kSpritesButtons_But_globalFx);
	AddSprite(sp);

	sp = new GSprite(229, 286, 120, 28, kSpritesButtons_But_globalFx_lit);
	AddSprite(sp);

	sp = new GSprite(127, 221, 36, 36, kSpritesButtons_But_left);
	AddSprite(sp);

	sp = new GSprite(521, 297, 32, 26, kSpritesButtons_But_master_limit_off);
	AddSprite(sp);

	sp = new GSprite(742, 94, 32, 26, kSpritesButtons_But_master_limit_on);
	AddSprite(sp);

	sp = new GSprite(931, 58, 86, 30, kSpritesButtons_But_modArp_arp);
	AddSprite(sp);

	sp = new GSprite(931, 26, 86, 30, kSpritesButtons_But_modArp_mod);
	AddSprite(sp);

	sp = new GSprite(383, 221, 54, 27, kSpritesButtons_But_mod_1_8);
	AddSprite(sp);

	sp = new GSprite(327, 221, 54, 27, kSpritesButtons_But_mod_9_16);
	AddSprite(sp);

	sp = new GSprite(521, 70, 26, 26, kSpritesButtons_But_osc_power_off);
	AddSprite(sp);

	sp = new GSprite(521, 123, 26, 26, kSpritesButtons_But_osc_power_on);
	AddSprite(sp);

	sp = new GSprite(205, 221, 120, 28, kSpritesButtons_But_patch);
	AddSprite(sp);

	sp = new GSprite(201, 256, 120, 28, kSpritesButtons_But_patchFx);
	AddSprite(sp);

	sp = new GSprite(809, 56, 120, 28, kSpritesButtons_But_patchFx_lit);
	AddSprite(sp);

	sp = new GSprite(809, 26, 120, 28, kSpritesButtons_But_patch_lit);
	AddSprite(sp);

	sp = new GSprite(704, 94, 36, 27, kSpritesButtons_But_pitch_off);
	AddSprite(sp);

	sp = new GSprite(427, 281, 36, 27, kSpritesButtons_But_pitch_off_lit);
	AddSprite(sp);

	sp = new GSprite(389, 281, 36, 27, kSpritesButtons_But_pitch_on);
	AddSprite(sp);

	sp = new GSprite(351, 281, 36, 27, kSpritesButtons_But_pitch_on_lit);
	AddSprite(sp);

	sp = new GSprite(93, 259, 36, 36, kSpritesButtons_But_right);
	AddSprite(sp);

	sp = new GSprite(89, 221, 36, 36, kSpritesButtons_Exit);
	AddSprite(sp);

	sp = new GSprite(401, 99, 22, 22, kSpritesButtons_Exit_small);
	AddSprite(sp);

	sp = new GSprite(2, 221, 32, 58, kSpritesButtons_Keyboard_overlay);
	AddSprite(sp);

	sp = new GSprite(401, 2, 406, 66, kSpritesButtons_Overlay_adsr_other);
	AddSprite(sp);

	sp = new GSprite(2, 2, 397, 217, kSpritesButtons_Padsynth_panel);
	AddSprite(sp);

	sp = new GSprite(2, 332, 700, 41, kSpritesButtons_PanelTxt);
	AddSprite(sp);

	sp = new GSprite(55, 272, 36, 36, kSpritesButtons_SaveDisk);
	AddSprite(sp);

	sp = new GSprite(159, 294, 38, 33, kSpritesButtons_Slider);
	AddSprite(sp);

	sp = new GSprite(165, 221, 38, 33, kSpritesButtons_Slider_2);
	AddSprite(sp);

	sp = new GSprite(131, 259, 38, 33, kSpritesButtons_Slider_focus);
	AddSprite(sp);

	sp = new GSprite(119, 297, 38, 33, kSpritesButtons_Slider_focus_2);
	AddSprite(sp);

}