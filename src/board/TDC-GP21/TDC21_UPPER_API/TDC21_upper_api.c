#include "TDC21_upper_api.h"
#include "../TDC-GP21_defs.h"

typedef struct config_all_regs_ideal_t
{
	//настройки нулевого регистра!!!!00000000000
	uint8_t ANZ_FIRE = 0b0010;
	uint8_t DIV_FIRE = 0b0010;
	tdc21_per_calres_t ANZ_PER_CALRES = 0;
	tdc21_div_clkhs_t DIV_CLKHS = 0;
	tdc21_start_clkhs_t START_CLKHS = 0b01;
	tdc21_anz_port_t ANZ_PORT = 1;
	tdc21_tcycle_t TCYCLE = 0;
	tdc21_anz_fake_t ANZ_FAKE = 0;
	tdc21_sel_eclk_tmp_t SEL_ECLK_TMP = 1;
	tdc21_calibrate_t CALIBRATE = 1;
	tdc21_no_cal_auto_t NO_CAL_AUTO = 0;
	tdc21_messb2_t MESSB2 = 1;
	tdc21_neg_stop2_t NEG_STOP2 = 0;
	tdc21_neg_stop1_t NEG_STOP1 = 0;
	tdc21_neg_start_t NEG_START = 0;


	///настройки первого регистра11111111111
	tdc21_hit1 HIT1 = 0b0101;
	tdc21_hit2 HIT2 = 0b0101;
	tdc21_en_fast_init_t EN_FAST_INIT = 0;
	tdc21_hitin2_t HITIN2 = 0;
	tdc21_hitin1_t HITIN1 = 0;
	tdc21_curr32k_t CURR32K = 1;
	tdc21_sel_start_fire_t SEL_START_FIRE = 0;
	tdc21_sel_tsto2_t SEL_TSTO2 = 0;
	tdc21_sel_tsto1_t SEL_TSTO1 = 0;


	//настройки второго регистра2222222222
	bool EN_INT_TIMEOUT = 0;
	bool EN_INT_END_HITS = 0;
	bool EN_INT_ALU	= 1;
	tdc21_rfedge2 RFEDGE2 = 0;
	tdc21_rfedge1 RFEDGE1 = 0;
	uint32_t DELVAL1 = 0;

	//настройки третьего регистра333333333
	tdc21_wreg3_en_err_val EN_ERR_VAL = 0;
	tdc21_wreg3_tim0_mb2 SEL_TIMO_MB2  = 0b11;
	uint32_t DELVAL2 = 0b0010000000000000000;

	//настройка четвертого регистра444444444
	uint32_t DELVAL3 = 0;


	//настройка пятого регистра5555555555
	tdc21_wreg5_conf_t CONF_FIRE = 0;
	bool EN_STARTNOISE = 1;
	tdc21_wreg5_paseghift DIS_PHASESHIFT = 0;
	tdc21_wreg5_repeat_fire REPEAT_FIRE = 0;
	tdc21_wreg5_phase_fire PHASE_FIRE = TDC21_WREG5_PHASE_FIRE_NOT_INVERS;

	//настройка шестого регистра66666666666
	tdc21_wreg6_en_analog EN_ANALOG = TDC21_WREG6_EN_ANALOG_STR1ST2_DIGITAL;
	NEG_STOP_TEMP tdc21_wreg6_neg_stop_temp = TDC21_WREG6_NEG_STOP_TEMP_74HC14;
	tdc21_wreg6_da_korrt DA_korrt = TDC21_WREG6_DA_KORRT_0MV;
	tdc21_wreg6_tw2 TW2 = TDC21_WREG6_TW2_90MKS;
	bool EN_INT_EEPROM = 1;
	tdc21_wreg6_start_clkhs START_CLKHS = TDC21_WREG6_START_CLKHS_DISABLE;
	tdc21_wreg6_cycle_temp CYCLE_TEMP = TDC21_WREG6_CYCLE_TEMP_1;
	tdc21_wreg6_cycle_tof CYCLE_TOF = TDC21_WREG6_CYCLE_TOF_1;
	tdc21_wreg6_hz60 HZ60 = TDC21_WREG6_HZ60_50_HZ;
	tdc21_wreg6_fireo_def FIREO_DEF = TDC21_WREG6_FIREO_DEF_HIGHT_HZ;
	tdc21_wreg6_quad_res QUAD_RES = TDC21_WREG6_QUAD_RES_DISABLE;
	tdc21_wreg6_double_res DOUBLE_RES = TDC21_WREG6_DOUBLE_RES_DISABLE;
	tdc21_wreg6_temp_portdir TEMP_PORTDIR = TDC21_WREG6_TEMP_PORTDIR_PT1_PT2_PT3_PT4;
	uint32_t_wreg6 ANZ_FIRE = 0;
    }config_all_regs_t;

    typedef enum tdc21_gp_t
    {
    	uint32_t reg0;
    	uint32_t reg1;
    	uint32_t reg2;
    	uint32_t reg3;
    	uint32_t reg4;
    	uint32_t reg5;
    	uint32_t reg6;
    }tdc21_gp_t;

void tdc21_config()
{
	config_all_regs_t config_all_regs;
	tdc21_gp_t regi;

}
