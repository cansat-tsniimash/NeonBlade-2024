#include "TDC21_upper_api.h"
#include "../TDC21_LOVVER_API/TDC21_lovver_api.h"
#include "../TDC-GP21_defs.h"
#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define REG0_ANZ_FIRE           28

// Sets predivider for internal clock signal of fire pulse generator [0-15]
#define REG0_DIV_FIRE           24

// Sets number of periods used for calibrating the ceramic resonator [0-3]
#define REG0_ANZ_PER_CALRES     22

// Sets predivider for CLKHS [0-3]
#define REG0_DIV_CLKHS          20

// Defines the time interval the chip waits after switching on the oscillator before making a measurement [0-3]
#define REG0_START_CLKHS_1_0    18

// Enables/disables calibration calculation in the ALU
#define REG0_CALIBRATE          13

// Enables/disables auto-calibration run in the TDC, 1 = auto-calibration disabled
#define REG0_NO_CAL_AUTO        12

// 1 = measurement mode 2
#define REG0_MESSB2             11

// 0 = non-inverted input signal – rising edge
#define REG0_NEG_STOP2          10

// 0 = non-inverted input signal – rising edge
#define REG0_NEG_STOP1          9

// 0 = non-inverted input signal – rising edge
#define REG0_NEG_START          8

// ****** REGISTER 1 *********************************************************

// Defines operator for ALU data post-processing [0-15]
#define REG1_HIT2               28

// Defines operator for ALU data post-processing [0-15]
#define REG1_HIT1               24

//1 - Enables fast init operation
#define REG1_EN_FAST_INIT       23

// [0-7]
#define REG1_HITIN2             19

// [0-7]
#define REG1_HITIN1             16

// Low current option for 32 kHz oscillator.
#define REG1_CURR32K            15

// Fire pulse is used as TDC start. The START input is disabled.
#define REG1_SEL_START_FIRE     14

//Defines functionality of EN_START pin. [0-7]
#define REG1_SEL_TSTO2          11

//Defines functionality of FIRE_IN pin. [0-7]
#define REG1_SEL_TSTO1          8

// ****** REGISTER 2 *********************************************************
// Activates interrupt sources [0-7]
#define REG2_EN_INT_2_0         29

// Edge sensitivity channel 2 -> 1 = rising and falling edge
#define REG2_RFEDGE2            28

// Edge sensitivity channel 1 -> 1 = rising and falling edge
#define REG2_RFEDGE1            27

//Delay value for internal stop enable unit, hit 1 channel 1
#define REG2_DELVAL1            8

// ****** REGISTER 3 *********************************************************
// Timeout forces ALU to write ‘hFFFFFFFF
#define REG3_EN_ERR_VAL         29

// Select predivider for timeout in measurement mode 2 [0-3]
#define REG3_SEL_TIMO_MB2       27

// Delay value for internal stop enable unit, hit 2 channel 1
#define REG3_DELVAL2            8

// ****** REGISTER 4 *********************************************************
// Delay value for internal stop enable unit, hit 3 channel 1.
#define REG4_DELVAL3            8

// ****** REGISTER 5 *********************************************************
// Output configuration for pulse generator [0-7]
#define REG5_CONF_FIRE          29

// Enables additional noise for start channel
#define REG5_EN_STARTNOISE      28

// Phase noise unit - 1 = disables phase noise
#define REG5_DIS_PHASESHIFT     27

//[0-7]
#define REG5_REPEAT_FIRE        24

// Enables phase reversing for each pulse of a sequence of up to 15 possible pulses
#define REG5_PHFIRE             8

// ****** REGISTER 6 *********************************************************
// Activates the analog part
#define REG6_EN_ANALOG          31

// Sets comparator offset [0-15]
#define REG6_DA_KORR            25

// Timer to charge up the capacitor
#define REG6_TW2                22

// Specifies the default level of the inactive fire buffer. 1 = LOW
#define REG6_FIREO_DEF          14

// Option to improve the resolution
#define REG6_QUAD_RES           13

// Option to improve the resolution
#define REG6_DOUBLE_RES         12

// Highest 3 bits of the number of fire pulses.
#define REG6_ANZ_FIRE_6_4         12


int give_me_result(void * intf_ptr)//ОТВЕТ В ПИКОСЕКУНДАХ
{
	uint32_t data;
	tdc21_read_register(&intf_ptr, TDC21_RES0, (uint8_t*)&data, sizeof(data));
	return data*90;
}


tdc21_all_regs_t tdc21_config(void * intf_ptr)
{
	config_all_value_ideal_t config_all_value;
	tdc21_all_regs_t reg_i;

	reg_i.reg0 = 0;
	reg_i.reg1 = 0b00000000010000000000000000000000;
	reg_i.reg2 = 0;
	reg_i.reg3 = 0;
	reg_i.reg4 = 0b00100000000000000000000000000000;
	reg_i.reg5 = 0;
	reg_i.reg6 = 0;

//настройки нулевого регистра!!!!00000000000
	config_all_value.ANZ_FIRE = 0b0010;
	config_all_value.DIV_FIRE = 0b0010;
	config_all_value.ANZ_PER_CALRES = 0;
	config_all_value.DIV_CLKHS = 0;
	config_all_value.START_CLKHS = 0b0001;
	config_all_value.ANZ_PORT = 1;
	config_all_value.TCYCLE = 0;
	config_all_value.ANZ_FAKE = 0;
	config_all_value.SEL_ECLK_TMP = 1;
	config_all_value.CALIBRATE = 1;
	config_all_value.NO_CAL_AUTO = 0;
	config_all_value.MESSB2 = 1;
	config_all_value.NEG_STOP2 = 0;
	config_all_value.NEG_STOP1 = 0;
	config_all_value.NEG_START = 0;


	///настройки первого регистра11111111111
	config_all_value.HIT1 = 0b0101;
	config_all_value.HIT2 = 0b0101;
	config_all_value.EN_FAST_INIT = 0;
	config_all_value.HITIN2 = 0;
	config_all_value.HITIN1 = 0;
	config_all_value.CURR32K = 1;
	config_all_value.SEL_START_FIRE = 0;
	config_all_value.SEL_TSTO2 = 0;
	config_all_value.SEL_TSTO1 = 0;


	//настройки второго регистра2222222222
	config_all_value.EN_INT_TIMEOUT = 0;
	config_all_value.EN_INT_END_HITS = 0;
	config_all_value.EN_INT_ALU	= 1;
	config_all_value.RFEDGE2 = 0;
	config_all_value.RFEDGE1 = 0;
	config_all_value.DELVAL1 = 0;

	//настройки третьего регистра333333333
	config_all_value.EN_ERR_VAL = 0;
	config_all_value.SEL_TIMO_MB2  = 0b11;
	config_all_value.DELVAL2 = 0b0010000000000000000;

	//настройка четвертого регистра444444444
	config_all_value.DELVAL3 = 0;


	//настройка пятого регистра5555555555
	config_all_value.CONF_FIRE = TDC21_WREG5_FIRE_UP;
	config_all_value.EN_STARTNOISE = 0;//
	config_all_value.DIS_PHASESHIFT = 0;
	config_all_value.REPEAT_FIRE = 1;
	config_all_value.PHASE_FIRE = TDC21_WREG5_PHASE_FIRE_NOT_INVERS;

	//настройка шестого регистра66666666666
	config_all_value.EN_ANALOG = TDC21_WREG6_EN_ANALOG_STR1ST2_DIGITAL;
	config_all_value.NEG_STOP_TEMP = TDC21_WREG6_NEG_STOP_TEMP_74HC14;
	config_all_value.DA_korrt = TDC21_WREG6_DA_KORRT_0MV;
	config_all_value.TW2 = TDC21_WREG6_TW2_90MKS;
	config_all_value.EN_INT_EEPROM = 1;//
	config_all_value.CYCLE_TEMP = TDC21_WREG6_CYCLE_TEMP_1;
	config_all_value.CYCLE_TOF = TDC21_WREG6_CYCLE_TOF_1;
	config_all_value.HZ60 = TDC21_WREG6_HZ60_50_HZ;
	config_all_value.FIREO_DEF = TDC21_WREG6_FIREO_DEF_HIGHT_HZ;
	config_all_value.QUAD_RES = TDC21_WREG6_QUAD_RES_DISABLE;
	config_all_value.DOUBLE_RES = TDC21_WREG6_DOUBLE_RES_DISABLE;
	config_all_value.TEMP_PORTDIR = TDC21_WREG6_TEMP_PORTDIR_PT1_PT2_PT3_PT4;
	config_all_value.ANZ_FIRE_2 = 0;

	/*if(config_all_value.ANZ_FIRE > TDC21_WREG0_ANZ_FIRE_LEN) return reg_i;
	if(config_all_value.DIV_FIRE > TDC21_WREG0_DIV_FIRE_LEN)return reg_i;
	reg_i.reg0 |= TDC21_WREG0_ANZ_FIRE((config_all_value.ANZ_FIRE & 0b0001111));
	reg_i.reg0 |= TDC21_WREG0_DIV_FIRE((config_all_value.DIV_FIRE));
	reg_i.reg0 |= TDC21_WREG0_ANZ_PER_CALRES((config_all_value.ANZ_PER_CALRES));
	reg_i.reg0 |= TDC21_WREG0_DIV_CLKHS((config_all_value.DIV_CLKHS));
	reg_i.reg0 |= TDC21_WREG0_START_CLKHS((config_all_value.START_CLKHS & 0b11));
	reg_i.reg0 |= TDC21_WREG0_ANZ_PORT((config_all_value.ANZ_PORT));
	reg_i.reg0 |= TDC21_WREG0_TCYCLE((config_all_value.TCYCLE));
	reg_i.reg0 |= TDC21_WREG0_ANZ_FAKE((config_all_value.ANZ_FAKE));
	reg_i.reg0 |= TDC21_WREG0_SEL_ECLK_TMP((config_all_value.SEL_ECLK_TMP));
	reg_i.reg0 |= TDC21_WREG0_CALIBRATE((config_all_value.CALIBRATE));
	reg_i.reg0 |= TDC21_WREG0_NO_CAL_AUTO((config_all_value.NO_CAL_AUTO));
	reg_i.reg0 |= TDC21_WREG0_MESSB2((config_all_value.MESSB2));
	reg_i.reg0 |= TDC21_WREG0_NEG_STOP2((config_all_value.NEG_STOP2));
	reg_i.reg0 |= TDC21_WREG0_NEG_STOP1((config_all_value.NEG_STOP1));
	reg_i.reg0 |= TDC21_WREG0_NEG_START((config_all_value.NEG_START));

	reg_i.reg1 |= TDC21_WREG1_HIT1(config_all_value.HIT1);
	reg_i.reg1 |= TDC21_WREG1_HIT2(config_all_value.HIT2);
	reg_i.reg1 |= TDC21_WREG1_EN_FAST_INIT(config_all_value.EN_FAST_INIT);
	reg_i.reg1 |= TDC21_WREG1_HITIN2(config_all_value.HITIN2);
	reg_i.reg1 |= TDC21_WREG1_HITIN1(config_all_value.HITIN1);
	reg_i.reg1 |= TDC21_WREG1_CURR32K(config_all_value.CURR32K);
	reg_i.reg1 |= TDC21_WREG1_SEL_START_FIRE(config_all_value.SEL_START_FIRE);
	reg_i.reg1 |= TDC21_WREG1_SEL_TSTO2(config_all_value.SEL_TSTO2);
	reg_i.reg1 |= TDC21_WREG1_SEL_TSTO1(config_all_value.SEL_TSTO1);

	if(config_all_value.DELVAL1 > TDC21_WREG2_DELVAL1_LEN) return reg_i;
	reg_i.reg2 |= TDC21_WREG2_EN_INT_TIMEOUT(config_all_value.EN_INT_TIMEOUT);
	reg_i.reg2 |= TDC21_WREG2_EN_INT_END_HITS(config_all_value.EN_INT_END_HITS);
	reg_i.reg2 |= TDC21_WREG2_EN_INT_ALU(config_all_value.EN_INT_ALU);
	reg_i.reg2 |= TDC21_WREG2_RFEDGE2(config_all_value.RFEDGE2);
	reg_i.reg2 |= TDC21_WREG2_RFEDGE1(config_all_value.RFEDGE1);
	reg_i.reg2 |= TDC21_WREG2_DELVAL1(config_all_value.DELVAL1);

	if(config_all_value.DELVAL2 > TDC21_WREG3_DELVAL2_LEN) return reg_i;
	reg_i.reg3 |= TDC21_WREG3_EN_ERR_VAL(config_all_value.EN_ERR_VAL);
	reg_i.reg3 |= TDC21_WREG3_SEL_TIMO_MB2(config_all_value.SEL_TIMO_MB2);
	reg_i.reg3 |= TDC21_WREG3_DELVAL2(config_all_value.DELVAL2);

	if(config_all_value.DELVAL3 > TDC21_WREG3_DELVAL3_LEN)return reg_i;
	reg_i.reg4 |= TDC21_WREG4_DELVAL3(config_all_value.DELVAL3);
	reg_i.reg5 |= TDC21_WREG5_CONF_FIRE(config_all_value.CONF_FIRE);
	reg_i.reg5 |= TDC21_WREG5_STARTNOISE(config_all_value.EN_STARTNOISE);
	reg_i.reg5 |= TDC21_WREG5_DIS_PASESHIFT(config_all_value.DIS_PHASESHIFT);
	reg_i.reg5 |= TDC21_WREG5_REPEAT_FIRE(config_all_value.REPEAT_FIRE);
	reg_i.reg5 |= TDC21_WREG5_PHASE_FIRE(config_all_value.PHASE_FIRE);

	//if(config_all_value.ANZ_FIRE_2 > TDC21_WREG6_ANZ_FIRE_LEN) return reg_i;
	reg_i.reg6 |= TDC21_WREG6_EN_ANALOG(config_all_value.EN_ANALOG);
	reg_i.reg6 |= TDC21_WREG6_NEG_STOP_TEMP(config_all_value.NEG_STOP_TEMP);
	reg_i.reg6 |= TDC21_WREG6_DA_KORRT(config_all_value.DA_korrt);
	reg_i.reg6 |= TDC21_WREG6_TW2(config_all_value.TW2);
	reg_i.reg6 |= TDC21_WREG6_EN_INT_EEPROM(config_all_value.EN_INT_EEPROM);
	reg_i.reg6 |= TDC21_WREG6_START_CLKHS((config_all_value.START_CLKHS >> 2));//////////////////
	reg_i.reg6 |= TDC21_WREG6_CYCLE_TEMP(config_all_value.CYCLE_TEMP);
	reg_i.reg6 |= TDC21_WREG6_CYCLE_TOF(config_all_value.CYCLE_TOF);
	reg_i.reg6 |= TDC21_WREG6_HZ60(config_all_value.HZ60);
	reg_i.reg6 |= TDC21_WREG6_FIREO_DEF(config_all_value.FIREO_DEF);
	reg_i.reg6 |= TDC21_WREG6_QUAD_RES(config_all_value.QUAD_RES);
	reg_i.reg6 |= TDC21_WREG6_DOUBLE_RES(config_all_value.DOUBLE_RES);
	reg_i.reg6 |= TDC21_WREG6_TEMP_PORTDIR(config_all_value.TEMP_PORTDIR);
	reg_i.reg6 |= TDC21_WREG6_ANZ_FIRE((config_all_value.ANZ_FIRE >> 4));//////////////////////*/


	reg_i.reg0|= (uint32_t)1 << REG0_ANZ_FIRE; // 1 fire pulse
	reg_i.reg0|= 1 << REG0_START_CLKHS_1_0; // 1 = Oscillator continuously on
	reg_i.reg0|= 0 << REG0_CALIBRATE; // Disable calibration
	reg_i.reg0|= 1 << REG0_NO_CAL_AUTO;// 1 = auto-calibration disabled
	reg_i.reg0|= 7 << REG0_DIV_FIRE; //7.= divided by 8
	reg_i.reg0|= 1 << REG0_DIV_CLKHS;//1 = clk divided by 2

	reg_i.reg1|= (uint32_t)9 << REG1_HIT1; // 0x9 -> 1. Stop Ch2 (photo)
	reg_i.reg1|= 1 << REG1_HIT2; // 0x1 -> 1. Stop Ch1 (laser)

	reg_i.reg1|= 1 << REG1_HITIN1; // 1 hit on ch1 expected (laser)
	reg_i.reg1|= 2 << REG1_HITIN2; // 2 hits on ch2 expected (photo)

	reg_i.reg1|= 1 << REG1_SEL_START_FIRE; // Fire pulse is used as TDC start
	reg_i.reg1|= 7 << REG1_SEL_TSTO2;//7 = 4 kHz (32 kHz/8) clock - IMPORTANT

	reg_i.reg1|= 3 << REG1_SEL_TSTO1;//3 = STOP2 TDC output
	// *********************** REG 2
	reg_i.reg2|= (uint32_t)(1+4) << REG2_EN_INT_2_0; // 1 - timeout interr, 4 - ALU interr enable
	reg_i.reg2|= 1 << REG2_RFEDGE2;//1 = rising and falling edge at channel2

	//REG 3
	reg_i.reg3|= 1 << REG3_EN_ERR_VAL; // Timeout forces ALU to write ‘hFFFFFFFF

	//REG 5
	reg_i.reg5|= 2 << REG5_CONF_FIRE; //Bit 30 = 1: enable output FIRE_UP
	reg_i.reg5|= 1 << REG5_DIS_PHASESHIFT;//Disable phase shift noise

	//REG 6
	//reg6|= (uint32_t)1 << REG6_EN_ANALOG;
	reg_i.reg6|= 1 << REG6_FIREO_DEF; //1 = LOW

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=ЭТАП-=-ОТПРАВКИ=-=РЕГИСТРОВ-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
	tdcgp21_write_register(intf_ptr, TDC21_WREG0, (uint8_t*)&reg_i.reg0, 4);
	tdcgp21_write_register(intf_ptr, TDC21_WREG1, (uint8_t*)&reg_i.reg1, 4);
	tdcgp21_write_register(intf_ptr, TDC21_WREG2, (uint8_t*)&reg_i.reg2, 4);
	tdcgp21_write_register(intf_ptr, TDC21_WREG3, (uint8_t*)&reg_i.reg3, 4);
	tdcgp21_write_register(intf_ptr, TDC21_WREG4, (uint8_t*)&reg_i.reg4, 4);
	tdcgp21_write_register(intf_ptr, TDC21_WREG5, (uint8_t*)&reg_i.reg5, 4);
	tdcgp21_write_register(intf_ptr, TDC21_WREG6, (uint8_t*)&reg_i.reg6, 4);

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	return reg_i;
}
