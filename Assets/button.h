#pragma once

enum SpritesButtons
{
	kSpritesButtons_None = 0,
     kSpritesButtons_Box_patchName,
	 kSpritesButtons_Box_patchNum,
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
	 kSpritesButtons_But_generate,
	 kSpritesButtons_But_globalFx,
	 kSpritesButtons_But_globalFx_lit,
	 kSpritesButtons_But_left,
	 kSpritesButtons_But_master_limit_off,
	 kSpritesButtons_But_master_limit_on,
	 kSpritesButtons_But_modArp_arp,
	 kSpritesButtons_But_modArp_mod,
	 kSpritesButtons_But_mod_1_8,
	 kSpritesButtons_But_mod_9_16,
	 kSpritesButtons_But_osc_power_off,
	 kSpritesButtons_But_osc_power_on,
	 kSpritesButtons_But_patch,
	 kSpritesButtons_But_patchFx,
	 kSpritesButtons_But_patchFx_lit,
	 kSpritesButtons_But_patch_lit,
	 kSpritesButtons_But_pitch_off,
	 kSpritesButtons_But_pitch_off_lit,
	 kSpritesButtons_But_pitch_on,
	 kSpritesButtons_But_pitch_on_lit,
	 kSpritesButtons_But_right,
	 kSpritesButtons_Exit,
	 kSpritesButtons_Exit_small,
	 kSpritesButtons_Keyboard_overlay,
	 kSpritesButtons_Overlay_adsr_other,
	 kSpritesButtons_Padsynth_panel,
	 kSpritesButtons_SaveDisk,
	 kSpritesButtons_Slider,
	 kSpritesButtons_Slider_2,
	 kSpritesButtons_Slider_focus,
	 kSpritesButtons_Slider_focus_2,
	
};

class SpritesButtonsSprites : GSpriteCollection
{
};

SpritesButtonsSprites::SpritesButtonsSprites()
{
	imageWidth = 512;
	imageHeight = 512;
	pixelSizeX = 1.0f/imageWidth;
	pixelSizeY = 1.0f/imageHeight;
	GSprite* sp = new GSprite(0,0,0,0, kSpritesButtons_None);
		AddSprite(sp);
	sp = new GSprite(162, 289, 211, 22, kSpritesButtons_Box_patchName);
	AddSprite(sp);
	
	sp = new GSprite(410, 66, 70, 22, kSpritesButtons_Box_patchNum);
	AddSprite(sp);
	
	sp = new GSprite(274, 342, 26, 27, kSpritesButtons_But_1_off);
	AddSprite(sp);
	
	sp = new GSprite(252, 458, 26, 27, kSpritesButtons_But_1_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(252, 429, 26, 27, kSpritesButtons_But_1_on);
	AddSprite(sp);
	
	sp = new GSprite(246, 400, 26, 27, kSpritesButtons_But_1_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(246, 371, 26, 27, kSpritesButtons_But_2_off);
	AddSprite(sp);
	
	sp = new GSprite(246, 313, 26, 27, kSpritesButtons_But_2_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(246, 342, 26, 27, kSpritesButtons_But_2_on);
	AddSprite(sp);
	
	sp = new GSprite(224, 458, 26, 27, kSpritesButtons_But_2_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(224, 429, 26, 27, kSpritesButtons_But_3_off);
	AddSprite(sp);
	
	sp = new GSprite(218, 400, 26, 27, kSpritesButtons_But_3_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(218, 371, 26, 27, kSpritesButtons_But_3_on);
	AddSprite(sp);
	
	sp = new GSprite(218, 313, 26, 27, kSpritesButtons_But_3_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(218, 342, 26, 27, kSpritesButtons_But_4_off);
	AddSprite(sp);
	
	sp = new GSprite(196, 458, 26, 27, kSpritesButtons_But_4_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(196, 429, 26, 27, kSpritesButtons_But_4_on);
	AddSprite(sp);
	
	sp = new GSprite(190, 400, 26, 27, kSpritesButtons_But_4_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(190, 371, 26, 27, kSpritesButtons_But_5_off);
	AddSprite(sp);
	
	sp = new GSprite(190, 313, 26, 27, kSpritesButtons_But_5_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(190, 342, 26, 27, kSpritesButtons_But_5_on);
	AddSprite(sp);
	
	sp = new GSprite(162, 400, 26, 27, kSpritesButtons_But_5_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(162, 371, 26, 27, kSpritesButtons_But_6_off);
	AddSprite(sp);
	
	sp = new GSprite(162, 313, 26, 27, kSpritesButtons_But_6_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(162, 342, 26, 27, kSpritesButtons_But_6_on);
	AddSprite(sp);
	
	sp = new GSprite(481, 253, 26, 27, kSpritesButtons_But_6_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(160, 459, 34, 27, kSpritesButtons_But_amp_off);
	AddSprite(sp);
	
	sp = new GSprite(160, 430, 34, 27, kSpritesButtons_But_amp_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(124, 459, 34, 27, kSpritesButtons_But_amp_on);
	AddSprite(sp);
	
	sp = new GSprite(124, 430, 34, 27, kSpritesButtons_But_amp_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(481, 220, 28, 31, kSpritesButtons_But_filterLink_off);
	AddSprite(sp);
	
	sp = new GSprite(482, 66, 28, 31, kSpritesButtons_But_filterLink_on);
	AddSprite(sp);
	
	sp = new GSprite(401, 168, 51, 49, kSpritesButtons_But_filterMode_dual);
	AddSprite(sp);
	
	sp = new GSprite(457, 134, 51, 49, kSpritesButtons_But_filterMode_para);
	AddSprite(sp);
	
	sp = new GSprite(401, 90, 62, 18, kSpritesButtons_But_generate);
	AddSprite(sp);
	
	sp = new GSprite(2, 470, 120, 28, kSpritesButtons_But_globalFx);
	AddSprite(sp);
	
	sp = new GSprite(2, 440, 120, 28, kSpritesButtons_But_globalFx_lit);
	AddSprite(sp);
	
	sp = new GSprite(2, 293, 36, 36, kSpritesButtons_But_left);
	AddSprite(sp);
	
	sp = new GSprite(274, 371, 32, 26, kSpritesButtons_But_master_limit_off);
	AddSprite(sp);
	
	sp = new GSprite(274, 313, 32, 26, kSpritesButtons_But_master_limit_on);
	AddSprite(sp);
	
	sp = new GSprite(410, 34, 86, 30, kSpritesButtons_But_modArp_arp);
	AddSprite(sp);
	
	sp = new GSprite(410, 2, 86, 30, kSpritesButtons_But_modArp_mod);
	AddSprite(sp);
	
	sp = new GSprite(401, 139, 54, 27, kSpritesButtons_But_mod_1_8);
	AddSprite(sp);
	
	sp = new GSprite(401, 110, 54, 27, kSpritesButtons_But_mod_9_16);
	AddSprite(sp);
	
	sp = new GSprite(308, 313, 26, 26, kSpritesButtons_But_osc_power_off);
	AddSprite(sp);
	
	sp = new GSprite(302, 342, 26, 26, kSpritesButtons_But_osc_power_on);
	AddSprite(sp);
	
	sp = new GSprite(2, 410, 120, 28, kSpritesButtons_But_patch);
	AddSprite(sp);
	
	sp = new GSprite(40, 293, 120, 28, kSpritesButtons_But_patchFx);
	AddSprite(sp);
	
	sp = new GSprite(40, 342, 120, 28, kSpritesButtons_But_patchFx_lit);
	AddSprite(sp);
	
	sp = new GSprite(2, 380, 120, 28, kSpritesButtons_But_patch_lit);
	AddSprite(sp);
	
	sp = new GSprite(124, 401, 36, 27, kSpritesButtons_But_pitch_off);
	AddSprite(sp);
	
	sp = new GSprite(124, 372, 36, 27, kSpritesButtons_But_pitch_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(437, 293, 36, 27, kSpritesButtons_But_pitch_on);
	AddSprite(sp);
	
	sp = new GSprite(399, 292, 36, 27, kSpritesButtons_But_pitch_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(2, 342, 36, 36, kSpritesButtons_But_right);
	AddSprite(sp);
	
	sp = new GSprite(439, 255, 36, 36, kSpritesButtons_Exit);
	AddSprite(sp);
	
	sp = new GSprite(375, 289, 22, 22, kSpritesButtons_Exit_small);
	AddSprite(sp);
	
	sp = new GSprite(477, 282, 32, 58, kSpritesButtons_Keyboard_overlay);
	AddSprite(sp);
	
	sp = new GSprite(2, 2, 406, 66, kSpritesButtons_Overlay_adsr_other);
	AddSprite(sp);
	
	sp = new GSprite(2, 70, 397, 217, kSpritesButtons_Padsynth_panel);
	AddSprite(sp);
	
	sp = new GSprite(401, 254, 36, 36, kSpritesButtons_SaveDisk);
	AddSprite(sp);
	
	sp = new GSprite(441, 220, 38, 33, kSpritesButtons_Slider);
	AddSprite(sp);
	
	sp = new GSprite(401, 219, 38, 33, kSpritesButtons_Slider_2);
	AddSprite(sp);
	
	sp = new GSprite(454, 185, 38, 33, kSpritesButtons_Slider_focus);
	AddSprite(sp);
	
	sp = new GSprite(465, 99, 38, 33, kSpritesButtons_Slider_focus_2);
	AddSprite(sp);
	
	
}