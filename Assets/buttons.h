#pragma once

enum SpritesButtons
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
	 kSpritesButtons_But_globalFx,
	 kSpritesButtons_But_globalFx_lit,
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
	 kSpritesButtons_Keyboard_overlay,
	 kSpritesButtons_Overlay_adsr_other,
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
	sp = new GSprite(382, 217, 26, 27, kSpritesButtons_But_1_off);
	AddSprite(sp);
	
	sp = new GSprite(362, 188, 26, 27, kSpritesButtons_But_1_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(391, 101, 26, 27, kSpritesButtons_But_1_on);
	AddSprite(sp);
	
	sp = new GSprite(365, 130, 26, 27, kSpritesButtons_But_1_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(362, 159, 26, 27, kSpritesButtons_But_2_off);
	AddSprite(sp);
	
	sp = new GSprite(354, 217, 26, 27, kSpritesButtons_But_2_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(334, 188, 26, 27, kSpritesButtons_But_2_on);
	AddSprite(sp);
	
	sp = new GSprite(363, 101, 26, 27, kSpritesButtons_But_2_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(337, 130, 26, 27, kSpritesButtons_But_3_off);
	AddSprite(sp);
	
	sp = new GSprite(334, 159, 26, 27, kSpritesButtons_But_3_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(326, 217, 26, 27, kSpritesButtons_But_3_on);
	AddSprite(sp);
	
	sp = new GSprite(340, 70, 26, 27, kSpritesButtons_But_3_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(306, 188, 26, 27, kSpritesButtons_But_4_off);
	AddSprite(sp);
	
	sp = new GSprite(335, 101, 26, 27, kSpritesButtons_But_4_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(309, 130, 26, 27, kSpritesButtons_But_4_on);
	AddSprite(sp);
	
	sp = new GSprite(306, 159, 26, 27, kSpritesButtons_But_4_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(298, 218, 26, 27, kSpritesButtons_But_5_off);
	AddSprite(sp);
	
	sp = new GSprite(278, 189, 26, 27, kSpritesButtons_But_5_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(270, 218, 26, 27, kSpritesButtons_But_5_on);
	AddSprite(sp);
	
	sp = new GSprite(242, 218, 26, 27, kSpritesButtons_But_5_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(312, 70, 26, 27, kSpritesButtons_But_6_off);
	AddSprite(sp);
	
	sp = new GSprite(284, 70, 26, 27, kSpritesButtons_But_6_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(307, 101, 26, 27, kSpritesButtons_But_6_on);
	AddSprite(sp);
	
	sp = new GSprite(279, 101, 26, 27, kSpritesButtons_But_6_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(273, 130, 34, 27, kSpritesButtons_But_amp_off);
	AddSprite(sp);
	
	sp = new GSprite(270, 160, 34, 27, kSpritesButtons_But_amp_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(242, 189, 34, 27, kSpritesButtons_But_amp_on);
	AddSprite(sp);
	
	sp = new GSprite(234, 160, 34, 27, kSpritesButtons_But_amp_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(82, 187, 28, 31, kSpritesButtons_But_filterLink_off);
	AddSprite(sp);
	
	sp = new GSprite(89, 101, 28, 31, kSpritesButtons_But_filterLink_on);
	AddSprite(sp);
	
	sp = new GSprite(36, 101, 51, 49, kSpritesButtons_But_filterMode_dual);
	AddSprite(sp);
	
	sp = new GSprite(2, 161, 51, 49, kSpritesButtons_But_filterMode_para);
	AddSprite(sp);
	
	sp = new GSprite(112, 164, 120, 28, kSpritesButtons_But_globalFx);
	AddSprite(sp);
	
	sp = new GSprite(124, 70, 120, 28, kSpritesButtons_But_globalFx_lit);
	AddSprite(sp);
	
	sp = new GSprite(419, 95, 32, 26, kSpritesButtons_But_master_limit_off);
	AddSprite(sp);
	
	sp = new GSprite(368, 70, 32, 26, kSpritesButtons_But_master_limit_on);
	AddSprite(sp);
	
	sp = new GSprite(410, 34, 86, 30, kSpritesButtons_But_modArp_arp);
	AddSprite(sp);
	
	sp = new GSprite(410, 2, 86, 30, kSpritesButtons_But_modArp_mod);
	AddSprite(sp);
	
	sp = new GSprite(217, 131, 54, 27, kSpritesButtons_But_mod_1_8);
	AddSprite(sp);
	
	sp = new GSprite(410, 66, 54, 27, kSpritesButtons_But_mod_9_16);
	AddSprite(sp);
	
	sp = new GSprite(393, 130, 26, 26, kSpritesButtons_But_osc_power_off);
	AddSprite(sp);
	
	sp = new GSprite(390, 159, 26, 26, kSpritesButtons_But_osc_power_on);
	AddSprite(sp);
	
	sp = new GSprite(119, 101, 120, 28, kSpritesButtons_But_patch);
	AddSprite(sp);
	
	sp = new GSprite(95, 134, 120, 28, kSpritesButtons_But_patchFx);
	AddSprite(sp);
	
	sp = new GSprite(82, 220, 120, 28, kSpritesButtons_But_patchFx_lit);
	AddSprite(sp);
	
	sp = new GSprite(2, 70, 120, 28, kSpritesButtons_But_patch_lit);
	AddSprite(sp);
	
	sp = new GSprite(204, 223, 36, 27, kSpritesButtons_But_pitch_off);
	AddSprite(sp);
	
	sp = new GSprite(204, 194, 36, 27, kSpritesButtons_But_pitch_off_lit);
	AddSprite(sp);
	
	sp = new GSprite(246, 70, 36, 27, kSpritesButtons_But_pitch_on);
	AddSprite(sp);
	
	sp = new GSprite(241, 101, 36, 27, kSpritesButtons_But_pitch_on_lit);
	AddSprite(sp);
	
	sp = new GSprite(2, 101, 32, 58, kSpritesButtons_Keyboard_overlay);
	AddSprite(sp);
	
	sp = new GSprite(2, 2, 406, 66, kSpritesButtons_Overlay_adsr_other);
	AddSprite(sp);
	
	sp = new GSprite(55, 152, 38, 33, kSpritesButtons_Slider);
	AddSprite(sp);
	
	sp = new GSprite(42, 212, 38, 33, kSpritesButtons_Slider_2);
	AddSprite(sp);
	
	sp = new GSprite(2, 212, 38, 33, kSpritesButtons_Slider_focus);
	AddSprite(sp);
	
	sp = new GSprite(466, 66, 38, 33, kSpritesButtons_Slider_focus_2);
	AddSprite(sp);
	
	
}