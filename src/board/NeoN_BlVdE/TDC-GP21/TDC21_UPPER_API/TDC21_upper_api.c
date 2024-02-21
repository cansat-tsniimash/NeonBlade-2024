#include "TDC21_upper_api.h"
#include "../TDC-GP21_defs.h"

typedef struct config_all_value_ideal_t
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
	tdc21_wreg6_neg_stop_temp NEG_STOP_TEMP = TDC21_WREG6_NEG_STOP_TEMP_74HC14;
	tdc21_wreg6_da_korrt DA_korrt = TDC21_WREG6_DA_KORRT_0MV;
	tdc21_wreg6_tw2 TW2 = TDC21_WREG6_TW2_90MKS;
	bool EN_INT_EEPROM = 1;
	tdc21_wreg6_cycle_temp CYCLE_TEMP = TDC21_WREG6_CYCLE_TEMP_1;
	tdc21_wreg6_cycle_tof CYCLE_TOF = TDC21_WREG6_CYCLE_TOF_1;
	tdc21_wreg6_hz60 HZ60 = TDC21_WREG6_HZ60_50_HZ;
	tdc21_wreg6_fireo_def FIREO_DEF = TDC21_WREG6_FIREO_DEF_HIGHT_HZ;
	tdc21_wreg6_quad_res QUAD_RES = TDC21_WREG6_QUAD_RES_DISABLE;
	tdc21_wreg6_double_res DOUBLE_RES = TDC21_WREG6_DOUBLE_RES_DISABLE;
	tdc21_wreg6_temp_portdir TEMP_PORTDIR = TDC21_WREG6_TEMP_PORTDIR_PT1_PT2_PT3_PT4;
    }config_all_value_ideal_t;

    typedef struct tdc21_all_regs_t
    {
    	uint32_t reg0 = 0;
    	uint32_t reg1 = 0b0000000001000000000000000;
    	uint32_t reg2 = 0;
    	uint32_t reg3 = 0;
    	uint32_t reg4 = 0b0010000000000000000000000;
    	uint32_t reg5 = 0;
    	uint32_t reg6 = 0;
    }tdc21_all_regs_t;


    int give_me_result(void * intf_ptr)//ОТВЕТ В ПИКОСЕКУНДАХ
    {
    	uint32_t data;
    	tdc21_read_register(&intf_ptr, TDC21_RES0, &data, sizeof(data));
    	return data*90;
    }


int tdc21_config(void * intf_ptr)
{
	config_all_value_ideal_t config_all_value;
	tdc21_all_regs_t reg_i;

	if(ANZ_FIRE > TDC21_WREG0_ANZ_FIRE_LEN) return 1;
	if(DIV_FIRE > TDC21_WREG0_DIV_FIRE_LEN)return 1;
	reg_i.reg0 |= TDC21_WREG0_ANZ_FIRE(config_all_value.ANZ_FIRE & 0b0001111);
	reg_i.reg0 |= TDC21_WREG0_DIV_FIRE(config_all_value.DIV_FIRE);
	reg_i.reg0 |= TDC21_WREG0_ANZ_PER_CALRES(config_all_value.ANZ_PER_CALRES);
	reg_i.reg0 |= TDC21_WREG0_DIV_CLKHS(config_all_value.DIV_CLKHS);
	reg_i.reg0 |= TDC21_WREG0_START_CLKHS(config_all_value.START_CLKHS & 0b11);
	reg_i.reg0 |= TDC21_WREG0_ANZ_PORT(config_all_value.ANZ_PORT);
	reg_i.reg0 |= TDC21_WREG0_TCYCLE(config_all_value.TCYCLE);
	reg_i.reg0 |= TDC21_WREG0_ANZ_FAKE(config_all_value.ANZ_FAKE);
	reg_i.reg0 |= TDC21_WREG0_SEL_ECLK_TMP(config_all_value.SEL_ECLK_TMP);
	reg_i.reg0 |= TDC21_WREG0_CALIBRATE(config_all_value.ANZ_PER_CALRES);
	reg_i.reg0 |= TDC21_WREG0_NO_CAL_AUTO(config_all_value.NO_CAL_AUTO);
	reg_i.reg0 |= TDC21_WREG0_MESSB2(config_all_value.MESSB2);
	reg_i.reg0 |= TDC21_WREG0_NEG_STOP2(config_all_value.NEG_STOP2);
	reg_i.reg0 |= TDC21_WREG0_NEG_STOP1(config_all_value.NEG_STOP1);
	reg_i.reg0 |= TDC21_WREG0_NEG_START(config_all_value.NEG_START);

	reg_i.reg1 |= TDC21_WREG1_HIT1(config_all_value.HIT1);
	reg_i.reg1 |= TDC21_WREG1_HIT2(config_all_value.HIT2);
	reg_i.reg1 |= TDC21_WREG1_EN_FAST_INIT(config_all_value.EN_FAST_INIT);
	reg_i.reg1 |= TDC21_WREG1_HITIN2(config_all_value.HITIN2);
	reg_i.reg1 |= TDC21_WREG1_HITIN1(config_all_value.HITIN1);
	reg_i.reg1 |= TDC21_WREG1_CURR32K(config_all_value.CURR32K);
	reg_i.reg1 |= TDC21_WREG1_SEL_START_FIRE(config_all_value.SEL_START_FIRE);
	reg_i.reg1 |= TDC21_WREG1_SEL_TSTO2(config_all_value.SEL_TSTO2);
	reg_i.reg1 |= TDC21_WREG1_SEL_TSTO1(config_all_value.SEL_TSTO1);

	if(config_all_value.DELVAL1 > TDC21_WREG2_DELVAL1_LEN) return 3;
	reg_i.reg2 |= TDC21_WREG2_EN_INT_TIMEOUT(config_all_value.EN_INT_TIMEOUT);
	reg_i.reg2 |= TDC21_WREG2_EN_INT_END_HITS(config_all_value.EN_INT_END_HITS);
	reg_i.reg2 |= TDC21_WREG2_EN_INT_ALU(config_all_value.EN_INT_ALU);
	reg_i.reg2 |= TDC21_WREG2_RFEDGE2(config_all_value.RFEDGE2);
	reg_i.reg2 |= TDC21_WREG2_RFEDGE1(config_all_value.RFEDGE1);
	reg_i.reg2 |= TDC21_WREG2_DELVAL1(config_all_value.DELVAL1);

	if(config_all_value.DELVAL2 > TDC21_WREG3_DELVAL2_LEN) return 4;
	reg_i.reg3 |= TDC21_WREG3_EN_ERR_VAL(config_all_value.EN_ERR_VAL);
	reg_i.reg3 |= TDC21_WREG3_SEL_TIMO_MB2(config_all_value.SEL_TIMO_MB2);
	reg_i.reg3 |= TDC21_WREG3_DELVAL2(config_all_value.DELVAL2);

	if(config_all_value.DELVAL3 < TDC21_WREG3_DELVAL3_LEN)return 5;
	reg_i.reg4 |= TDC21_WREG4_DELVAL3(config_all_value.DELVAL3);
	reg_i.reg5 |= TDC21_WREG5_CONF_FIRE(config_all_value.CONF_FIRE);
	reg_i.reg5 |= TDC21_WREG5_STARTNOISE(config_all_value.EN_STARTNOISE);
	reg_i.reg5 |= TDC21_WREG5_DIS_PASESHIFT(config_all_value.DIS_PHASESHIFT);
	reg_i.reg5 |= TDC21_WREG5_REPEAT_FIRE(config_all_value.REPEAT_FIRE);
	reg_i.reg5 |= TDC21_WREG5_PHASE_FIRE(config_all_value.PHASE_FIRE);

	if(config_all_value.ANZ_FIRE_2 > TDC21_WREG6_ANZ_FIRE_LEN) return 7;
	reg_i.reg6 |= TDC21_WREG6_EN_ANALOG(config_all_value.EN_ANALOG);
	reg_i.reg6 |= TDC21_WREG6_NEG_STOP_TEMP(config_all_value.NEG_STOP_TEMP);
	reg_i.reg6 |= TDC21_WREG6_DA_KORRT(config_all_value.DA_korrt);
	reg_i.reg6 |= TDC21_WREG6_TW2(config_all_value.TW2);
	reg_i.reg6 |= TDC21_WREG6_EN_INT_EEPROM(config_all_value.EN_INT_EEPROM);
	reg_i.reg6 |= TDC21_WREG6_START_CLKHS(config_all_value.START_CLKHS >> 2);//////////////////
	reg_i.reg6 |= TDC21_WREG6_CYCLE_TEMP(config_all_value.CYCLE_TEMP);
	reg_i.reg6 |= TDC21_WREG6_CYCLE_TOF(config_all_value.CYCLE_TOF);
	reg_i.reg6 |= TDC21_WREG6_HZ60(config_all_value.HZ60);
	reg_i.reg6 |= TDC21_WREG6_FIREO_DEF(config_all_value.FIREO_DEF);
	reg_i.reg6 |= TDC21_WREG6_QUAD_RES(config_all_value.QUAD_RES);
	reg_i.reg6 |= TDC21_WREG6_DOUBLE_RES(config_all_value.DOUBLE_RES);
	reg_i.reg6 |= TDC21_WREG6_TEMP_PORTDIR(config_all_value.TEMP_PORTDIR);
	reg_i.reg6 |= TDC21_WREG6_ANZ_FIRE(config_all_value.ANZ_FIRE >> 4);//////////////////////

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=ЭТАП-=-ОТПРАВКИ=-=РЕГИСТРОВ-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
	tdcgp21_write_register(&intf_ptr, TDC21_WREG0, &reg_i.reg0, 32);
	tdcgp21_write_register(&intf_ptr, TDC21_WREG1, &reg_i.reg1, 32);
	tdcgp21_write_register(&intf_ptr, TDC21_WREG2, &reg_i.reg2, 32);
	tdcgp21_write_register(&intf_ptr, TDC21_WREG3, &reg_i.reg3, 32);
	tdcgp21_write_register(&intf_ptr, TDC21_WREG4, &reg_i.reg4, 32);
	tdcgp21_write_register(&intf_ptr, TDC21_WREG5, &reg_i.reg5, 32);
	tdcgp21_write_register(&intf_ptr, TDC21_WREG6, &reg_i.reg6, 32);

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
}
