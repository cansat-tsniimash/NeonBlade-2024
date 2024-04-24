/*
 * TDC-21_defs.h
 *
 *  Created on: 24 нояб. 2023 г.
 *      Author: RaKetov
 */

#ifndef TDC_GP21_TDC_GP21_DEFS_H_
#define TDC_GP21_TDC_GP21_DEFS_H_

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Регистры записи
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#define TDC21_WREG0		0x00
#define TDC21_WREG1		0x01
#define TDC21_WREG2		0x02
#define TDC21_WREG3		0x03
#define TDC21_WREG4		0x04
#define TDC21_WREG5		0x05
#define TDC21_WREG6		0x06


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Регистры чтения
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#define TDC21_RES0		0x00
#define TDC21_RES1		0x01
#define TDC21_RES2		0x02
#define TDC21_RES3		0x03
#define TDC21_STAT		0x04
#define TDC21_REG1		0x05


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Биты регистра записи 0:
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//[3:0]Число импульсов, генерируемых генератором запускающих импульсов (0 = отключен)
#define TDC21_WREG0_ANZ_FIRE(x)			(x << 28)
#define TDC21_WREG0_ANZ_FIRE_LEN		0b1111
//Делитель задающей частоты генератора запускающих импульсов
#define TDC21_WREG0_DIV_FIRE(x)			(x << 24)
#define TDC21_WREG0_DIV_FIRE_LEN		0b1111///WTF
//Число периодов для калибрации керамического резонатора
#define TDC21_WREG0_ANZ_PER_CALRES(x)		(x << 22)
typedef enum tdc21_per_calres_t
{
    TDC_21_PER_CALRES_61MS,
	TDC_21_PER_CALRES_122,
	TDC_21_PER_CALRES_244,
	TDC_21_PER_CALRES_488
}tdc21_per_calres_t;
//Предварительный делитель
#define TDC21_WREG0_DIV_CLKHS(x)			(x << 20)
typedef enum tdc21_div_clkhs_t
{
    TDC21_1_DIV_CLKHS,
	TDC21_2_DIV_CLKHS,
	TDC21_3_DIV_CLKHS,
	TDC21_4_DIV_CLKHS
}tdc21_div_clkhs_t;
//[1:0]Время, которое чип ждет после начала осцилляции перед процедурой измерения
#define TDC21_WREG0_START_CLKHS(x)			(x << 18)
typedef enum tdc21_start_clkhs_t
{
    TDC21_ALW_OFF_START_CLKHS,
    TDC21_ALW_ON_START_CLKHS,
	TDC21_480_MKS_START_CLKHS,
	TDC21_1_MS_START_CLKHS,
	TDC21_2_MS_START_CLKHS,
	TDC21_5_MS_START_CLKHS
}tdc21_start_clkhs_t;
//Число портов, используемых при температурных измерениях
#define TDC21_WREG0_ANZ_PORT(x)			(x << 17)
typedef enum tdc21_anz_port_t
{
    TDC21_2_ANZ_PORT,
	TDC21_4_ANZ_PORT
}tdc21_anz_port_t;
//Длительность цикла при температурных измерениях
#define TDC21_WREG0_TCYCLE(x)				(x << 16)
typedef enum tdc21_tcycle_t
{
    TDC21_128_TCYCLE,
	TDC21_512_TCYCLE
}tdc21_tcycle_t;
//Число холостых циклов в начале температурныхизмерений
#define TDC21_WREG0_ANZ_FAKE(x)			(x << 15)
typedef enum tdc21_anz_fake_t
{
    TDC21_2_ANZ_FAKE,
	TDC21_7_ANZ_FAKE
}tdc21_anz_fake_t;
//Опорная частота при температурных измерениях
#define TDC21_WREG0_SEL_ECLK_TMP(x)		(x << 14)
typedef enum tdc21_sel_eclk_tmp_t
{
    TDC21_32_KHZ_SEL_ECLK_TMP,
	TDC21_4_MHZ_SEL_ECLK_TMP
}tdc21_sel_eclk_tmp_t;
//Разрешить калибрационные вычисления в ALU
#define TDC21_WREG0_CALIBRATE(x)			(x << 13)
typedef enum tdc21_calibrate_t
{
    TDC21_ON_CALIBRATE,
	TDC21_OFF_CALIBRATE
}tdc21_calibrate_t;
//Запретить автокалибрацию, проистекающую в TDC
#define TDC21_WREG0_NO_CAL_AUTO(x)			(x << 12)
typedef enum tdc21_no_cal_auto_t
{
    TDC21_ON_CAL_AUTO,
	TDC21_OFF_CAL_AUTO
}tdc21_no_cal_auto_t;
//Переключение в диапазон измерений 2
#define TDC21_WREG0_MESSB2(x)				(x << 11)
typedef enum tdc21_messb2_t
{
    TDC21_MESSB2_1,
	TDC21_MESSB2_2
}tdc21_messb2_t;
//Инвертирование входного сигнала STOP 2
#define TDC21_WREG0_NEG_STOP2(x)			(x << 10)
typedef enum tdc21_neg_stop2_t
{
    TDC21_NEG_STOP_2_NO_INCR,
	TDC21_NEG_STOP_2_INV_FALL
}tdc21_neg_stop2_t;
//Инвертирование входного сигнала STOP 1
#define TDC21_WREG0_NEG_STOP1(x)			(x << 9)
typedef enum tdc21_neg_stop1_t
{
    TDC21_NEG_STOP_1_NO_INCR,
	TDC21_NEG_STOP_1_INV_FALL
}tdc21_neg_stop1_t;
//Инвертирование входного сигнала START
#define TDC21_WREG0_NEG_START(x)			(x << 8)
typedef enum tdc21_neg_start_t
{
    TDC21_NEG_START_NO_INCR,
	TDC21_NEG_START_INV_FALL
}tdc21_neg_start_t;
//Свободные биты
#define TDC21_WREG0_ID0(x)					(x << 0)


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Биты регистра записи 1:
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//Первый параметр входных данных ALU
#define TDC21_WREG1_HIT1(x)				(x << 28)
typedef enum tdc21_hit1
{
	TDC21_HIT1_START_MODE1,
	TDC21_HIT1_1_STOP_CH1,
	TDC21_HIT1_2_STOP_CH1,
	TDC21_HIT1_3_STOP_CH1,
	TDC21_HIT1_4_STOP_CH1,
	TDC21_HIT1_NO_ACTION,
	TDC21_HIT1_CAL1_CH1,
	TDC21_HIT1_CAL2_CH1,
	TDC21_HIT1_1_STOP_CH2,
	TDC21_HIT1_2_STOP_CH2,
	TDC21_HIT1_3_STOP_CH2,
	TDC21_HIT1_4_STOP_CH2,
	TDC21_HIT1_START_MODE2,
}tdc21_hit1;
//Второй параметр входных данных ALU
#define TDC21_WREG1_HIT2(x)				(x << 24)
typedef enum tdc21_hit2
{
	TDC21_HIT2_START,
	TDC21_HIT2_1_STOP_CH1_MODE1,
	TDC21_HIT2_2_STOP_CH1_MODE1,
	TDC21_HIT2_3_STOP_CH1_MODE1,
	TDC21_HIT2_4_STOP_CH1_MODE1,
	TDC21_HIT2_NO_ACTION,
	TDC21_HIT2_CAL1_CH1,
	TDC21_HIT2_CAL2_CH1,
	TDC21_HIT2_1_STOP_CH2_MODE1,
	TDC21_HIT2_2_STOP_CH2_MODE1,
	TDC21_HIT2_3_STOP_CH2_MODE1,
	TDC21_HIT2_4_STOP_CH2_MODE1,
	TDC21_HIT2_1_STOP_CH1_MODE2,
	TDC21_HIT2_2_STOP_CH1_MODE2,
	TDC21_HIT2_3_STOP_CH1_MODE2
}tdc21_hit2;
//Запрещение операций Fast Init
#define TDC21_WREG1_EN_FAST_INIT(x)		(x << 23)
typedef enum tdc21_en_fast_init_t
{
	TDC21_FAST_INIT_ON,
	TDC21_FAST_INIT_OFF
}tdc21_en_fast_init_t;
//Число ожидаемых событий в канале STOP2
#define TDC21_WREG1_HITIN2(x)				(x << 19)
typedef enum tdc21_hitin2_t
{
    TDC21_STOP_CH2_DISINIT_HIT1,
	TDC21_1EVENT_HIT1,
	TDC21_2EVENT_HIT1,
	TDC21_3EVENT_HIT1,
	TDC21_4EVENT_HIT1,
    TDC21_NOT_ALLOWED_HIT1
}tdc21_hitin2_t;
//Число ожидаемых событий в канале STOP1
#define TDC21_WREG1_HITIN1(x)				(x << 16)
typedef enum tdc21_hitin1_t
{
	TDC21_STOP_CH2_DISINIT_HIT2,
	TDC21_1EVENT_HIT2,
	TDC21_2EVENT_HIT2,
	TDC21_3EVENT_HIT2,
	TDC21_4EVENT_HIT2,
    TDC21_NOT_ALLOWED_HIT2
}tdc21_hitin1_t;
//Опция с высоким потреблением тока для 32 кГц осциллятора (совместимость с GP2)
#define TDC21_WREG1_CURR32K(x)				(x << 15)
typedef enum tdc21_curr32k_t
{
    TDC21_LOW_CUR,
	TDC21_HIGHT_CUR
}tdc21_curr32k_t;
//Запускающий импульс Firepulse используется как запуск TDC. Вход START запрещен
#define TDC21_WREG1_SEL_START_FIRE(x)		(x << 14)
typedef enum tdc21_sel_start_fire_t
{
	TDC21_GP2_MODE,
	TDC21_USE_FIRE_AS_STRT
}tdc21_sel_start_fire_t;
//Назначение функции для пина EN_START
#define TDC21_WREG1_SEL_TSTO2(x)			(x << 11)
typedef enum tdc21_sel_tsto2_t
{
	TDC21_AS_GP2_ALLOWS_ENTRY_TSTO2,
	TDC21_START_EXIT_TSTO2,
	TDC21_STOP1_TDC_TSTO2,
	TDC21_STOP2_TDC_TSTO2,
	TDC21_TEMP_STOP_TSTO2,
	TDC21_TOF_UP_TSTO2,
	TDC21_NOT_TSTO2,
	TDC21_4KHZ_TSTO2
}tdc21_sel_tsto2_t;
//Назначение функции для пина FIRE_IN
#define TDC21_WREG1_SEL_TSTO1(x)			(x << 8)
typedef enum tdc21_sel_tsto1_t
{
	TDC21_AS_GP2_ALLOWS_ENTRY_TSTO1,
	TDC21_START_EXIT_TSTO1,
	TDC21_STOP1_TDC_TSTO1,
	TDC21_STOP2_TDC_TSTO1,
	TDC21_TEMP_STOP_TSTO1,
	TDC21_EN_STOP_TSTO1,
	TDC21_COMP_OUTPUT_TSTO1,
	TDC21_32KHZ_TSTO1
}tdc21_sel_tsto1_t;
//Свободные биты
#define TDC21_WREG1_ID1(x)					(x << 0)


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Биты регистра записи 2:
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//Разрешает прерывание Timeout
#define TDC21_WREG2_EN_INT_TIMEOUT(x)		(x << 31)
//Разрешает прерывание End Hits
#define TDC21_WREG2_EN_INT_END_HITS(x)		(x << 30)
//Разрешает прерывание ALU
#define TDC21_WREG2_EN_INT_ALU(x)			(x << 29)
//Чувствительности канала 2 по фронту (нарастающему или спадающему)
#define TDC21_WREG2_RFEDGE2(x)				(x << 28)
typedef enum tdc21_rfedge2_t
{
	TDC21_WREG2_RFEDGE2_H_FR_OR_L_FR,
	TDC21_WREG2_RFEDGE2_ALL_FR
}tdc21_rfedge2;
//Чувствительности канала 1 по фронту (нарастающему или спадающему)
#define TDC21_WREG2_RFEDGE1(x)				(x << 27)
typedef enum tdc21_rfedge1_t
{
	TDC21_WREG2_RFEDGE1_H_FR_OR_L_FR,
	TDC21_WREG2_RFEDGE1_ALL_FR
}tdc21_rfedge1;
//Величина задержки для внутреннего модуля разрешения стопа (событие 1, канал 1)
#define TDC21_WREG2_DELVAL1(x)				(x << 8)
#define TDC21_WREG2_DELVAL1_LEN			0b1111111111111111111
//Свободные биты
#define TDC21_WREG2_ID2(x)					(x << 0)


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Биты регистра записи 3:
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//Запрет при таймауте записывать ALU в регистр вывода 0xFFFFFFFF
#define TDC21_WREG3_EN_ERR_VAL(x)			(x << 29)
typedef enum tdc21_wreg3_en_err_val_t
{
	TDC21_WREG3_ERR_VAL_DISABLED,
	TDC21_WREG3_ERR_VAL_ENABLED
}tdc21_wreg3_en_err_val;
//Делитель для тамаута в измерительном диапазоне 2
#define TDC21_WREG3_SEL_TIMO_MB2(x)		(x << 27)
typedef enum tdc21_wreg3_tim0_mb2_t
{
	TDC21_WREG3_TIM0_64MKS,
	TDC21_WREG3_TIM0_256MKS,
	TDC21_WREG3_TIM0_1024MKS,
	TDC21_WREG3_TIM0_4096MKS
}tdc21_wreg3_tim0_mb2;
//Величина задержки для внутреннего модуля разрешения стопа (событие 2, канал 1)
#define TDC21_WREG3_DELVAL2(x)				(x << 8)
#define TDC21_WREG3_DELVAL2_LEN			0b1111111111111111111
//Свободные биты
#define TDC21_WREG3_ID3(x)					(x << 0)


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Биты регистра записи 4:
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//Величина задержки для внутреннего модуля разрешения стопа (событие 3, канал 1)
#define TDC21_WREG4_DELVAL3(x)				(x << 8)
#define TDC21_WREG3_DELVAL3_LEN			0b1111111111111111111
//Свободные биты
#define TDC21_WREG4_ID4(x)					(x << 0)


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Биты регистра записи 5:
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//Конфигурация выходов для генератора импульсов FIRE
#define TDC21_WREG5_CONF_FIRE(x)			(x << 29)
typedef enum tdc21_wreg5_conf_t
{
	TDC21_WREG5_FIRE_BOTH = 1,
	TDC21_WREG5_FIRE_UP = 2,
	TDC21_WREG5_FIRE_DOWN
}tdc21_wreg5_conf_t;
//Включение дополнительного шума для канала START
#define TDC21_WREG5_STARTNOISE(x)			(x << 29)
//Включение шума фазы
#define TDC21_WREG5_DIS_PASESHIFT(x)		(x << 28)
typedef enum tdc21_wreg5_paseghift_t
{
	TDC21_WREG5_ENABLED_PASESHIFT,
	TDC21_WREG5_DISABLED_PASESHIFT
}tdc21_wreg5_paseghift;
//Число повторений последовательности импульсов для "квазиобзвона"
#define TDC21_WREG5_REPEAT_FIRE(x)			(x << 24)
typedef enum tdc21_wreg5_repeat_fire_t
{
	TDC21_WREG5_REPEAT_FIRE_NOT_REPEAT,
	TDC21_WREG5_REPEAT_FIRE_1_REPEAT,
	TDC21_WREG5_REPEAT_FIRE_2_REPEAT,
	TDC21_WREG5_REPEAT_FIRE_7_REPEAT = 7
}tdc21_wreg5_repeat_fire;
//Разрешение реверсирования фазы для каждого импульса последовательности вплоть до 15 возможных импульсов
#define TDC21_WREG5_PHASE_FIRE(x)			(x << 29)
typedef enum tdc21_wreg5_phase_fire_t
{
	TDC21_WREG5_PHASE_FIRE_NOT_INVERS,
	TDC21_WREG5_PHASE_FIRE_INVERS
}tdc21_wreg5_phase_fire;
//Свободные биты
#define TDC21_WREG5_ID5(x)					(x << 29)


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Биты регистра записи 6:
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//Активация аналоговой секции (STOP1 и STOP2 будут аналоговыми входами)
#define TDC21_WREG6_EN_ANALOG(x)			(x << 31)
typedef enum tdc21_wreg6_en_analog_t
{
	TDC21_WREG6_EN_ANALOG_STR1ST2_DIGITAL,
	TDC21_WREG6_EN_ANALOG_STR1ST2_ANALOG
}tdc21_wreg6_en_analog;
//Инвертирование SenseT входного сигнала.
#define TDC21_WREG6_NEG_STOP_TEMP(x)		(x << 30)
typedef enum tdc21_wreg6_neg_stop_temp_t
{
	TDC21_WREG6_NEG_STOP_TEMP_74HC14,
	TDC21_WREG6_NEG_STOP_TEMP_ANAL_SECTION
}tdc21_wreg6_neg_stop_temp;
//Устанавливатся смещение компаратора от -8 мВ до +7 мВ (2-х полярное)
#define TDC21_WREG6_DA_KORRT(x)			(x << 25)
typedef enum tdc21_wreg6_da_korrt_t
{
	TDC21_WREG6_DA_KORRT_1MV = 1,
	TDC21_WREG6_DA_KORRT_0MV = 0,
	TDC21_WREG6_DA_KORRT_7MV = 7,
	TDC21_WREG6_DA_KORRT_6MV = 6,
	TDC21_WREG6_DA_KORRT_MINUS_1MV = 15,
	TDC21_WREG6_DA_KORRT_MINUS_2MV = 14,
	TDC21_WREG6_DA_KORRT_MINUS_7MV = 9,
	TDC21_WREG6_DA_KORRT_MINUS_8MV = 8,
}tdc21_wreg6_da_korrt;

//Время заряда конденсатора рекомендуемой RC цепи во время использования внутренней аналоговой части
#define TDC21_WREG6_TW2(x)					(x << 22)
typedef enum tdc21_wreg6_tw2_t
{
	TDC21_WREG6_TW2_90MKS ,
	TDC21_WREG6_TW2_120MKS,
	TDC21_WREG6_TW2_150_MKS,
	TDC21_WREG6_TW2_1_S
}tdc21_wreg6_tw2;
//Разрешение прерывания по окончании операций EEPROM
#define TDC21_WREG6_EN_INT_EEPROM(x)		(x << 21)

//[2]Время, которое чип ждет после начала осцилляции перед процедурой измерения
#define TDC21_WREG6_START_CLKHS(x)			(x << 20)
typedef enum tdc21_wreg6_start_clkhs_t
{
	TDC21_WREG6_START_CLKHS_DISABLE ,
	TDC21_WREG6_START_CLKHS_ENABLE,
	TDC21_WREG6_START_CLKHS_480_MKS_TMOUT,
	TDC21_WREG6_START_CLKHS_1_46_S_TMOUT,
	TDC21_WREG6_START_CLKHS_2_S_TMOUT,
	TDC21_WREG6_START_CLKHS_5_S_TMOUT
}tdc21_wreg6_start_clkhs;
//Выбор времени для запуска второго измерения температуры кратного 50/60 Гц
#define TDC21_WREG6_CYCLE_TEMP(x)			(x << 18)
typedef enum tdc21_wreg6_cycle_temp_t
{
	TDC21_WREG6_CYCLE_TEMP_1,
	CYCLE_TOF,
	TDC21_WREG6_CYCLE_TEMP_2,
	TDC21_WREG6_CYCLE_TEMP_2_5
}tdc21_wreg6_cycle_temp;
//Выбор времени для запуска второго измерения ToF кратного 50/60 Гц
#define TDC21_WREG6_CYCLE_TOF(x)			(x << 16)
typedef enum tdc21_wreg6_cycle_tof_t
{
	TDC21_WREG6_CYCLE_TOF_1,
	TDC21_WREG6_CYCLE_TOF_1_5,
	TDC21_WREG6_CYCLE_TOF_2,
	TDC21_WREG6_CYCLE_TOF_2_5
}tdc21_wreg6_cycle_tof;
//Задание базового временного интервала для полного измерения TDC-GP21 (50 или 60 Гц)
#define TDC21_WREG6_HZ60(x)				(x << 15)
typedef enum tdc21_wreg6_hz60_t
{
	TDC21_WREG6_HZ60_50_HZ,
	TDC21_WREG6_HZ60_60_HZ,
}tdc21_wreg6_hz60;
//Определение уровня по умолчанию неактивного буффера FIRE
#define TDC21_WREG6_FIREO_DEF(x)			(x << 14)
typedef enum tdc21_wreg6_fireo_def_t
{
	TDC21_WREG6_FIREO_DEF_HIGHT_HZ,
	TDC21_WREG6_FIREO_DEF_LOW_HZ,
}tdc21_wreg6_fireo_def;
//Увеличение разрешения в 4 раза с 90 пс до 22 пс (для режима измерения 2)
#define TDC21_WREG6_QUAD_RES(x)			(x << 13)
typedef enum tdc21_wreg6_quad_res_t
{
	TDC21_WREG6_QUAD_RES_DISABLE,
	TDC21_WREG6_QUAD_RES_ENABLE,
}tdc21_wreg6_quad_res;
//Увеличение разрешения в 2 раза с 90 пс до 45 пс (для режима измерения 1 с одним стопом)
#define TDC21_WREG6_DOUBLE_RES(x)			(x << 12)
typedef enum tdc21_wreg6_double_res_t
{
	TDC21_WREG6_DOUBLE_RES_DISABLE,
	TDC21_WREG6_DOUBLE_RES_ENABLE,
}tdc21_wreg6_double_res;
//Порты для измерения температуры измеряют в противоположном порядке (PT4 > PT3 > PT2 > PT1)
#define TDC21_WREG6_TEMP_PORTDIR(x)		(x << 11)
typedef enum tdc21_wreg6_temp_portdir_t
{
	TDC21_WREG6_TEMP_PORTDIR_PT1_PT2_PT3_PT4,
	TDC21_WREG6_TEMP_PORTDIR_PT4_PT3_PT2_PT1,
}tdc21_wreg6_temp_portdir;
//[6:4]Число импульсов, генерируемых генератором запускающих импульсов (0 = отключен)
#define TDC21_WREG6_ANZ_FIRE(x)			(x << 8)
#define TDC21_WREG6_ANZ_FIRE_LEN		0b1111111
//Свободные биты
#define TDC21_WREG6_ID6(x)				(x << 0)



// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Биты регистра чтения STAT:
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//Однократная ошибка в EEPROM, которая может быть скорректирована
#define TDC21_STAT_EEPROM_EQ_CREG		(1 << 15)
//Двойная ошибка в EEPROM, которые не могут быть исправлены
#define TDC21_STAT_EEPROM_DED			(1 << 14)
//Однократная ошибка в EEPROM, которая может быть скорректирована
#define TDC21_STAT_EEPROM_ERROR			(1 << 13)
//Короткое замыкание в цепи датчика при температурных измерениях
#define TDC21_STAT_SHORT_CIRCUIT		(1 << 12)
//Разрвы в цепи датчика при температурных измерениях
#define TDC21_STAT_DISCONNETION			(1 << 11)
//Переполнение 14-битного предварительного счетчика в MR 2
#define TDC21_STAT_COUNTER_OVERLOAD		(1 << 10)
//Переполнение модуля TDC
#define TDC21_STAT_TDC_OVERLOAD			(1 << 9)
//Количество событий, зарегистрированных в канале CH2
#define TDC21_STAT_CH2_NUM_OF_EVENT		(1 << 6)
//Количество событий, зарегистрированных в канале CH1
#define TDC21_STAT_CH1_NUM_OF_EVENT		(1 << 3)
//Указатель на следующий свободный регистр результатов RES[0 .. 3]
#define TDC21_STAT_RES_REG_POINTER		(1 << 0)



// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Команды:
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#define TDC21_W_REGISTER				0b10000000		//в конце пишется адрес регистра записи (3 бита)
#define TDC21_R_REGISTER				0b10110000		//в конце пишется адрес регистра чтения (3 бита)
#define TDC21_R_ID						0b10110111
#define TDC21_CFG_REG_TO_EEPROM			0b11000000
#define TDC21_EEPROM_TO_CFG_REG			0b11110000
#define TDC21_EEPROM_COMPARE			0b11000110
#define TDC21_INIT						0b01110000
#define TDC21_POWER_ON_RESET			0b01010000
#define TDC21_START_TOF					0b00000001
#define TDC21_START_TEMP				0b00000010
#define TDC21_START_CAL_RESONATOR		0b00000011
#define TDC21_START_CAL_TDC				0b00000100
#define TDC21_START_TOF_RESTART			0b00000101
#define TDC21_START_TEMP_RESTART		0b00000110

#endif /* TDC_GP21_TDC_GP21_DEFS_H_ */
