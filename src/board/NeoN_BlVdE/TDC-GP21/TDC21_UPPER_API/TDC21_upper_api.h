#ifndef TDC_GP21_TDC_GP21_UPPER_API_H_
#define TDC_GP21_TDC_GP21_UPPER_API_H_
#include <stm32f4xx_hal.h>
#include <stdbool.h>
#include "../TDC21_LOVVER_API/TDC21_lovver_api.h"
#include "../TDC-GP21_defs.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>



typedef struct config_all_value_ideal_t
{
	//настройки нулевого регистра!!!!00000000000
	uint8_t ANZ_FIRE;
	uint8_t DIV_FIRE;
	tdc21_per_calres_t ANZ_PER_CALRES;
	tdc21_div_clkhs_t DIV_CLKHS;
	tdc21_start_clkhs_t START_CLKHS;
	tdc21_anz_port_t ANZ_PORT;
	tdc21_tcycle_t TCYCLE;
	tdc21_anz_fake_t ANZ_FAKE;
	tdc21_sel_eclk_tmp_t SEL_ECLK_TMP;
	tdc21_calibrate_t CALIBRATE;
	tdc21_no_cal_auto_t NO_CAL_AUTO;
	tdc21_messb2_t MESSB2;
	tdc21_neg_stop2_t NEG_STOP2;
	tdc21_neg_stop1_t NEG_STOP1;
	tdc21_neg_start_t NEG_START;


	///настройки первого регистра11111111111
	tdc21_hit1 HIT1;
	tdc21_hit2 HIT2;
	tdc21_en_fast_init_t EN_FAST_INIT;
	tdc21_hitin2_t HITIN2;
	tdc21_hitin1_t HITIN1;
	tdc21_curr32k_t CURR32K;
	tdc21_sel_start_fire_t SEL_START_FIRE;
	tdc21_sel_tsto2_t SEL_TSTO2;
	tdc21_sel_tsto1_t SEL_TSTO1;


	//настройки второго регистра2222222222
	bool EN_INT_TIMEOUT;
	bool EN_INT_END_HITS;
	bool EN_INT_ALU;
	tdc21_rfedge2 RFEDGE2;
	tdc21_rfedge1 RFEDGE1;
	uint32_t DELVAL1;

	//настройки третьего регистра333333333
	tdc21_wreg3_en_err_val EN_ERR_VAL;
	tdc21_wreg3_tim0_mb2 SEL_TIMO_MB2;
	uint32_t DELVAL2;

	//настройка четвертого регистра444444444
	uint32_t DELVAL3;


	//настройка пятого регистра5555555555
	tdc21_wreg5_conf_t CONF_FIRE;
	bool EN_STARTNOISE;
	tdc21_wreg5_paseghift DIS_PHASESHIFT;
	tdc21_wreg5_repeat_fire REPEAT_FIRE;
	tdc21_wreg5_phase_fire PHASE_FIRE;

	//настройка шестого регистра66666666666
	tdc21_wreg6_en_analog EN_ANALOG;
	tdc21_wreg6_neg_stop_temp NEG_STOP_TEMP;
	tdc21_wreg6_da_korrt DA_korrt;
	tdc21_wreg6_tw2 TW2;
	bool EN_INT_EEPROM;
	tdc21_wreg6_cycle_temp CYCLE_TEMP;
	tdc21_wreg6_cycle_tof CYCLE_TOF;
	tdc21_wreg6_start_clkhs START_CLKHS_2;
	tdc21_wreg6_hz60 HZ60;
	tdc21_wreg6_fireo_def FIREO_DEF;
	tdc21_wreg6_quad_res QUAD_RES;
	tdc21_wreg6_double_res DOUBLE_RES;
	tdc21_wreg6_temp_portdir TEMP_PORTDIR;
	uint8_t ANZ_FIRE_2;
    }config_all_value_ideal_t;

    typedef struct tdc21_all_regs_t
    {
    	uint32_t reg0;
    	uint32_t reg1 ;
    	uint32_t reg2 ;
    	uint32_t reg3;
    	uint32_t reg4 ;
    	uint32_t reg5;
    	uint32_t reg6;
    }tdc21_all_regs_t;

tdc21_all_regs_t tdc21_config(void * intf_ptr);
int give_me_result(void * intf_ptr);//ОТВЕТ В ПИКОСЕКУНДАХ

#endif /* TDC_GP21_TDC_GP21_UPPER_API_H_ */
