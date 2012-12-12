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
	 kSpritesButtons_Keyboard_overlay,
	 kSpritesButtons_Overlay_adsr_other,
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
	imageHeight = 256;
	pixelSizeX = 1.0f/imageWidth;
	pixelSizeY = 1.0f/imageHeight;
	GSprite* sp = new GSprite(0,0,0,0, kSpritesButtons_None);
		AddSprite(sp);
	sp = new GSprite(190, 70, 211, 22, kSpritesButtons_Box_patchName);
	AddSprite(sp);
	
	sp = new GSprite(410, 66, 70, 22, kSpritesButtons_Box_patchNum);
	AddSprite(sp);
	
	sp = new GSprite(448, 175, 26, 27, kSpritesButtons_But_1_off);
	AddSprite(sp);
	
	sp = new GSprite(476, 157, 26, 27, kSpritesButtons_But_1_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(448, 146, 26, 27, kSpritesButtons_But_1_on);
	AddSprite(sp);
	
	sp = new GSprite(420, 157, 26, 27, kSpritesButtons_But_1_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(418, 186, 26, 27, kSpritesButtons_But_2_off);
	AddSprite(sp);
	
	sp = new GSprite(408, 217, 26, 27, kSpritesButtons_But_2_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(479, 128, 26, 27, kSpritesButtons_But_2_on);
	AddSprite(sp);
	
	sp = new GSprite(479, 99, 26, 27, kSpritesButtons_But_2_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(417, 99, 26, 27, kSpritesButtons_But_3_off);
	AddSprite(sp);
	
	sp = new GSprite(405, 128, 26, 27, kSpritesButtons_But_3_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(392, 157, 26, 27, kSpritesButtons_But_3_on);
	AddSprite(sp);
	
	sp = new GSprite(390, 188, 26, 27, kSpritesButtons_But_3_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(380, 217, 26, 27, kSpritesButtons_But_4_off);
	AddSprite(sp);
	
	sp = new GSprite(389, 99, 26, 27, kSpritesButtons_But_4_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(377, 128, 26, 27, kSpritesButtons_But_4_on);
	AddSprite(sp);
	
	sp = new GSprite(364, 159, 26, 27, kSpritesButtons_But_4_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(362, 188, 26, 27, kSpritesButtons_But_5_off);
	AddSprite(sp);
	
	sp = new GSprite(352, 217, 26, 27, kSpritesButtons_But_5_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(336, 159, 26, 27, kSpritesButtons_But_5_on);
	AddSprite(sp);
	
	sp = new GSprite(334, 188, 26, 27, kSpritesButtons_But_5_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(308, 159, 26, 27, kSpritesButtons_But_6_off);
	AddSprite(sp);
	
	sp = new GSprite(306, 188, 26, 27, kSpritesButtons_But_6_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(280, 159, 26, 27, kSpritesButtons_But_6_on);
	AddSprite(sp);
	
	sp = new GSprite(361, 99, 26, 27, kSpritesButtons_But_6_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(325, 99, 34, 27, kSpritesButtons_But_amp_off);
	AddSprite(sp);
	
	sp = new GSprite(289, 99, 34, 27, kSpritesButtons_But_amp_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(270, 194, 34, 27, kSpritesButtons_But_amp_on);
	AddSprite(sp);
	
	sp = new GSprite(234, 194, 34, 27, kSpritesButtons_But_amp_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(78, 223, 28, 31, kSpritesButtons_But_filterLink_off);
	AddSprite(sp);
	
	sp = new GSprite(482, 66, 28, 31, kSpritesButtons_But_filterLink_on);
	AddSprite(sp);
	
	sp = new GSprite(36, 99, 51, 49, kSpritesButtons_But_filterMode_dual);
	AddSprite(sp);
	
	sp = new GSprite(2, 159, 51, 49, kSpritesButtons_But_filterMode_para);
	AddSprite(sp);
	
	sp = new GSprite(255, 129, 120, 28, kSpritesButtons_But_globalFx);
	AddSprite(sp);
	
	sp = new GSprite(230, 223, 120, 28, kSpritesButtons_But_globalFx_lit);
	AddSprite(sp);
	
	sp = new GSprite(89, 99, 36, 36, kSpritesButtons_But_left);
	AddSprite(sp);
	
	sp = new GSprite(445, 118, 32, 26, kSpritesButtons_But_master_limit_off);
	AddSprite(sp);
	
	sp = new GSprite(445, 90, 32, 26, kSpritesButtons_But_master_limit_on);
	AddSprite(sp);
	
	sp = new GSprite(410, 34, 86, 30, kSpritesButtons_But_modArp_arp);
	AddSprite(sp);
	
	sp = new GSprite(410, 2, 86, 30, kSpritesButtons_But_modArp_mod);
	AddSprite(sp);
	
	sp = new GSprite(58, 70, 54, 27, kSpritesButtons_But_mod_1_8);
	AddSprite(sp);
	
	sp = new GSprite(2, 70, 54, 27, kSpritesButtons_But_mod_9_16);
	AddSprite(sp);
	
	sp = new GSprite(446, 204, 26, 26, kSpritesButtons_But_osc_power_off);
	AddSprite(sp);
	
	sp = new GSprite(476, 186, 26, 26, kSpritesButtons_But_osc_power_on);
	AddSprite(sp);
	
	sp = new GSprite(158, 164, 120, 28, kSpritesButtons_But_patch);
	AddSprite(sp);
	
	sp = new GSprite(167, 99, 120, 28, kSpritesButtons_But_patchFx);
	AddSprite(sp);
	
	sp = new GSprite(133, 134, 120, 28, kSpritesButtons_But_patchFx_lit);
	AddSprite(sp);
	
	sp = new GSprite(108, 223, 120, 28, kSpritesButtons_But_patch_lit);
	AddSprite(sp);
	
	sp = new GSprite(196, 194, 36, 27, kSpritesButtons_But_pitch_off);
	AddSprite(sp);
	
	sp = new GSprite(158, 194, 36, 27, kSpritesButtons_But_pitch_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(152, 70, 36, 27, kSpritesButtons_But_pitch_on);
	AddSprite(sp);
	
	sp = new GSprite(114, 70, 36, 27, kSpritesButtons_But_pitch_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(55, 150, 36, 36, kSpritesButtons_But_right);
	AddSprite(sp);
	
	sp = new GSprite(40, 210, 36, 36, kSpritesButtons_Exit);
	AddSprite(sp);
	
	sp = new GSprite(2, 99, 32, 58, kSpritesButtons_Keyboard_overlay);
	AddSprite(sp);
	
	sp = new GSprite(2, 2, 406, 66, kSpritesButtons_Overlay_adsr_other);
	AddSprite(sp);
	
	sp = new GSprite(2, 210, 36, 36, kSpritesButtons_SaveDisk);
	AddSprite(sp);
	
	sp = new GSprite(118, 172, 38, 33, kSpritesButtons_Slider);
	AddSprite(sp);
	
	sp = new GSprite(127, 99, 38, 33, kSpritesButtons_Slider_2);
	AddSprite(sp);
	
	sp = new GSprite(93, 137, 38, 33, kSpritesButtons_Slider_focus);
	AddSprite(sp);
	
	sp = new GSprite(78, 188, 38, 33, kSpritesButtons_Slider_focus_2);
	AddSprite(sp);
	
	
}