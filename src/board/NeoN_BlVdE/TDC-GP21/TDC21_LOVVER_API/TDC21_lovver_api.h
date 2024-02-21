#include <stm32f4xx_hal.h>

typedef struct tdcgp21_lovver_api_config_t
{
	// Дескриптор SPI
	SPI_HandleTypeDef *hspi;
	void (*tdc21_CS)(void * intf_ptr, bool mode);
	void *intf_ptr;
}tdcgp21_lovver_api_config_t;

typedef struct tdcgp21_spi_pins_t
{
	// Настройки Chip Enab
	GPIO_TypeDef *ce_port;
	uint16_t ce_pin;
	// Настройки SPI Chip Select
	GPIO_TypeDef *cs_port;
	uint16_t cs_pin;
} tdcgp21_spi_pins_t;

void tdc21_spi_init(tdcgp21_lovver_api_config_t* nrf24, SPI_HandleTypeDef *hspi, tdcgp21_spi_pins_t* pins);
void tdc21_start_tof(tdcgp21_lovver_api_config_t* api_config);
void tdc21_full_reset(tdcgp21_lovver_api_config_t* api_config);
void tdc21_init(tdcgp21_lovver_api_config_t* api_config);

