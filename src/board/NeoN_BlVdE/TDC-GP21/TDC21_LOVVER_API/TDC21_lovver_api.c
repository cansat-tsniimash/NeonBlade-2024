#include "TDC21_lovver_api.h"
#include "../TDC-GP21_defs.h"
#include <stdbool.h>
extern SPI_HandleTypeDef hspi4;

static void _tdcgp21_CS(void * intf_ptr, bool mode)
{
	tdcgp21_lovver_api_config_t *api_config = (tdcgp21_lovver_api_config_t *)intf_ptr;
	tdcgp21_spi_pins_t *api_config_low = (tdcgp21_spi_pins_t *)api_config->intf_ptr;
	if (mode)
	{
		// Опускаем chip select для того, что бы начать общение с конкретным устройством.
		HAL_GPIO_WritePin(api_config_low->cs_port, api_config_low->cs_pin,  GPIO_PIN_RESET);
		//HAL_Delay(11);
	}
	else
	{
		// Поднимаем chip select для того, что бы закончить общение с конкретным устройством.
		HAL_GPIO_WritePin(api_config_low->cs_port, api_config_low->cs_pin,  GPIO_PIN_SET);
		//HAL_Delay(100);
	}
}


HAL_StatusTypeDef tdcgp21_write_register(void * intf_ptr, uint8_t reg_addr, const uint8_t * reg_data, size_t data_size)
{
	HAL_StatusTypeDef errcode1;
	tdcgp21_lovver_api_config_t *api_config = (tdcgp21_lovver_api_config_t *)intf_ptr;
	api_config->tdc21_CS(intf_ptr, true);

	// Добавляем в 5 битов адреса еще 3 бита для записи в регистр
	reg_addr = TDC21_W_REGISTER | reg_addr;

	// Передаем адресс регистра, в который пишем и пишем в регистр
	errcode1 = HAL_SPI_Transmit(api_config->hspi, &reg_addr, 1, HAL_MAX_DELAY);
	if(errcode1)
	{
		api_config->tdc21_CS(intf_ptr, false);
		return errcode1;
	}
	HAL_SPI_Transmit(api_config->hspi, reg_data, data_size, HAL_MAX_DELAY);

	api_config->tdc21_CS(intf_ptr, false);
	return errcode1;
}

void tdc21_read_register(void * intf_ptr, uint8_t reg_addr, uint8_t * reg_data, size_t data_size)
{

	tdcgp21_lovver_api_config_t *api_config = (tdcgp21_lovver_api_config_t *)intf_ptr;

	api_config->tdc21_CS(intf_ptr, true);

	// Добавляем в 5 битов адреса еще 3 бита для чтения из этого регистра
	reg_addr = TDC21_R_REGISTER | reg_addr;

	// Передаем адресс регистра, который читаем и читаем данные
	HAL_SPI_Transmit(api_config->hspi, &reg_addr, 1, HAL_MAX_DELAY);
	HAL_SPI_Receive(api_config->hspi, reg_data, data_size, HAL_MAX_DELAY);

	api_config->tdc21_CS(intf_ptr, false);
}

void tdc21_init(tdcgp21_lovver_api_config_t* api_config)
{
	int popka = TDC21_INIT;
	HAL_SPI_Transmit(api_config->hspi, &popka, 1, HAL_MAX_DELAY);
}

void tdc21_full_reset(tdcgp21_lovver_api_config_t* api_config)
{
	int popa  = TDC21_POWER_ON_RESET;
	HAL_SPI_Transmit(api_config->hspi, &popa, 1, HAL_MAX_DELAY);
}

void tdc21_start_tof(tdcgp21_lovver_api_config_t* api_config)
{
	int jopa = TDC21_START_TOF;
	HAL_SPI_Transmit(api_config->hspi, &jopa, 1, HAL_MAX_DELAY);
}

void tdc21_spi_init(tdcgp21_lovver_api_config_t* nrf24, SPI_HandleTypeDef *hspi, tdcgp21_spi_pins_t* pins)
{
	nrf24->hspi = hspi;
	nrf24->tdc21_CS = _tdcgp21_CS;
	nrf24->intf_ptr = pins;
}
