/*
 * TDC-GP21.h
 *
 *  Created on: Nov 27, 2023
 *      Author: RaKetov
 */

#ifndef TDC_GP21_TDC_GP21_H_
#define TDC_GP21_TDC_GP21_H_

#include <stm32f4xx_hal.h>
#ifdef HAL_SPI_MODULE_ENABLED

// Структура, содержащая параметры SPI и пинов  Chip Enab и SPI Chip Select
typedef struct TDC21_lower_api_config_t
{
	// Дескриптор SPI
	SPI_HandleTypeDef *hspi;
	void (*TDC21_CS)(void * intf_ptr, bool mode);
	void *intf_ptr;
} TDC21_lower_api_config_t;

#endif /* TDC_GP21_TDC_GP21_H_ */
