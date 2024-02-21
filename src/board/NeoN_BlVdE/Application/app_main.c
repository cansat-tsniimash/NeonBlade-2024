#include <stdbool.h>
#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "fatfs.h"
#include "stm32f4/LIS3MDL/lis3mdl_reg.h"



#include "sebastian.h"
#include "../Drivers/BME280_I2C/its_bme280.h"
#include "stm32f4/LSM6DS3/DLSM.h"
#include "stm32f4/LIS3MDL/DLIS3.h"
#include "stm32f4/ATGM336H/nmea_gps.h"
#include "stm32f4/nRF24L01_PL/nrf24_upper_api.h"
#include "stm32f4/nRF24L01_PL/nrf24_lower_api_stm32.h"
#include "stm32f4/nRF24L01_PL/nrf24_lower_api.h"

#define LSM_FLAG 1 //переключатели работы устройств. 1 - функции и работы датчиков исполняются. 0 - нет
#define LIS_FLAG 1
#define NEO_FLAG 0
#define BME_FLAG 1
#define GPS_FLAG 1
#define SD_FLAG 1
#define NRF_FLAG 0
#define UNKNXW 0

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi5;
extern SPI_HandleTypeDef hspi4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;

#pragma pack(push,1)

typedef struct
{
    uint8_t flag;
    uint16_t num;
    uint32_t time;//7

    double BME280_pressure;
    double BME280_temperature;
    double height_bme;

    uint8_t state;
    uint16_t sum;

}packet_ma_type_11_t;//SNAIL(УЛИТКА)

typedef struct
{
    uint8_t flag;
    uint16_t num;
    uint32_t time;

    float latitude;
    float longitude;
    float altitude;
    uint8_t fix;

    uint16_t sum;

}packet_ma_type_12_t;//SNAIL2(УЛИТКА)

typedef struct
{
    uint8_t flag;
    uint16_t num;
    uint32_t time;

    int16_t acc_mg[3];
    int16_t gyro_mdps[3];
    int16_t LIS3MDL_magnetometer[3];
    uint16_t lidar;

    uint16_t sum;
}packet_ma_type_2_t;//SPEED

#pragma pack(pop)

unsigned short Crc16(unsigned char *buf, unsigned short len) {
	unsigned short crc = 0xFFFF;
	unsigned char i;
	while (len--) {
		crc ^= *buf++ << 8;
		for (i = 0; i < 8; i++)
			crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
	}
	return crc;
}

int _write (int file, char *ptr, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
}
int super_smart_write(unsigned char *buf, unsigned short len, int8_t * state_sd_from_m)
{
	while(1)
	{
		static uint32_t start_time;
		static FATFS fileSystem; // переменная типа FATFS
		static FIL testFile; // хендлер файла
		static UINT bw;
		static FRESULT res;
		static int8_t state_sd = 0;
		const char * path = "testFile.bin"; // название файла

		if(state_sd == 0)
		{
			extern Disk_drvTypeDef  disk;
			disk.is_initialized[0] = 0;
			memset(&fileSystem, 0x00, sizeof(fileSystem));
			res = f_mount(&fileSystem, "0", 1);
			if(res == FR_OK){state_sd = 1; *state_sd_from_m = state_sd;}
			else
			{
				res = f_mount(0, "0", 1);
				return -1;
			}
		}
		if(state_sd == 1)
		{
			 *state_sd_from_m = state_sd;
			res = f_open(&testFile, path, FA_WRITE | FA_OPEN_APPEND);
			if(res == FR_OK) state_sd = 2;
			else
			{
				state_sd = 0;
				res = f_mount(0, "0", 1);
			}
		}
		if (state_sd == 2)
		{
			 *state_sd_from_m = state_sd;
            res = f_write (&testFile,  (uint8_t *)buf, len, &bw);
            if (HAL_GetTick() - start_time >= 10)
            {
            	res = f_sync(&testFile);
                start_time  = HAL_GetTick();
            }
	        if (res == FR_OK) return 0;
            if (res != FR_OK)
            {
    			res = f_close(&testFile);
            	state_sd = 1;
            }
		}
	}
}

int app_main()
{
	packet_ma_type_11_t packet_ma_type_11 = {3};
	packet_ma_type_12_t packet_ma_type_12 = {3};
 	packet_ma_type_2_t packet_ma_type_2 = {1};


	float quaternion[4] = {0};
	float seb_time_prev = 0;
	float seb_time = 0;

	float latitude;
	float lontitude;
    float altitude;
    int fix;
    int64_t cookie;


	int16_t temp_lis;
	int16_t mag[3] = {0};
	stmdev_ctx_t ctx = {0};
    struct lis_spi_intf lis_spi;
	lis_spi.GPIO_Port = GPIOA;
	lis_spi.GPIO_Pin = GPIO_PIN_4;
	lis_spi.spi = &hspi1;
	lisset(&ctx, &lis_spi);



	int16_t temperature_celsius_gyro;
	int16_t acc_g[3];
	int16_t gyro_dps[3];
	stmdev_ctx_t lsmctx = {0};
	struct lsm_spi_intf lsm_spi;
	lsm_spi.GPIO_Port = GPIOC;
	lsm_spi.GPIO_Pin = GPIO_PIN_13;
	lsm_spi.spi = &hspi1;
	lsmset(&lsmctx, &lsm_spi);
	//uint8_t lsm_data;
	//lsm6ds3_read_reg(&lsmctx, 0x11, &lsm_data, 8);
	//lsm_data = lsm_data||0b00001100;
	//lsm6ds3_write_reg(&lsmctx, 0x11, lsm_data, 8);


    if(GPS_FLAG)
    {
	gps_init();
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	//__HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);
    }

    int bmeinit = 10000;
    bme_important_shit bme_important;//////////////////////////////////BME
    if(BME_FLAG == 1){
    bmeinit = its_bme280_init(UNKNXW);}


    int8_t state_sd = 0;//sd
    uint8_t abobus;
    int retin;
    if(NRF_FLAG == 1)
    {
	//Создаем и настраиваем дескриптор радиомодуля nRF24L01
	nrf24_spi_pins_t nrf24_spi_pins;
	nrf24_spi_pins.ce_pin = GPIO_PIN_1;
	nrf24_spi_pins.ce_port = GPIOB;
	nrf24_spi_pins.cs_pin = GPIO_PIN_2;
	nrf24_spi_pins.cs_port = GPIOB;
	nrf24_lower_api_config_t nrf24_api_config;
	nrf24_spi_init(&nrf24_api_config, &hspi5, &nrf24_spi_pins);

	//Перед настройкой регистров радио переводим его в standby mode
	nrf24_mode_standby(&nrf24_api_config);

	// Настраиваем параметры радиопередачи
	nrf24_rf_config_t nrf24_rf_config;
	nrf24_rf_config.data_rate = NRF24_DATARATE_250_KBIT;
	nrf24_rf_config.rf_channel = 101;
	nrf24_rf_config.tx_power = NRF24_TXPOWER_MINUS_18_DBM;
	nrf24_setup_rf(&nrf24_api_config, &nrf24_rf_config);

	// Настраиваем протокол радиопередачи
	nrf24_protocol_config_t nrf24_protocol_config;
	nrf24_protocol_config.address_width = NRF24_ADDRES_WIDTH_5_BYTES;
	nrf24_protocol_config.auto_retransmit_count = 15;
	nrf24_protocol_config.auto_retransmit_delay = 15;
	nrf24_protocol_config.crc_size = NRF24_CRCSIZE_1BYTE;
	nrf24_protocol_config.en_ack_payload = true;/// было тру
	nrf24_protocol_config.en_dyn_ack = true;
	nrf24_protocol_config.en_dyn_payload_size = false;
	nrf24_setup_protocol(&nrf24_api_config, &nrf24_protocol_config);


	//Настраиваем пайп 0 для приема
	nrf24_pipe_config_t pipe_config;
	pipe_config.enable_auto_ack = false;/// было тру
	pipe_config.payload_size = 32;
	pipe_config.address = 0xfdfdfdfdfd;
	//nrf24_pipe_rx_start(&nrf24_api_config, 0, &pipe_config);

	for (int i = 1; i < 6; i++)
	{
		pipe_config.address = 0x3213213211;
		pipe_config.address = (pipe_config.address & ~((uint64_t)0xff << 32)) | ((uint64_t)(i + 7) << 32);
		pipe_config.enable_auto_ack = true;////////если поставить тру то отправки нет
		pipe_config.payload_size = 32;
		nrf24_pipe_rx_stop(&nrf24_api_config, i - 1);
		//nrf24_pipe_rx_start(&nrf24_api_config, i, &pipe_config);
	}

    nrf24_irq_clear(&nrf24_api_config, NRF24_IRQ_TX_DR | NRF24_IRQ_RX_DR |NRF24_IRQ_MAX_RT);
    nrf24_fifo_flush_rx(&nrf24_api_config);
    nrf24_fifo_flush_tx(&nrf24_api_config);
    //nrf24_mode_rx(&nrf24_api_config);
    //nrf24_mode_tx(&nrf24_api_config);
	nrf24_pipe_set_tx_addr(&nrf24_api_config, 0xacacacacac);
    }
	uint8_t rx_buffer[32] = {0};
	uint8_t tx_buffer[32] = {0};
	nrf24_fifo_status_t rx_status = 2;
    nrf24_fifo_status_t tx_status = 2;

    int errrrrrrrrr, radio_read_err;//
	int IRQ_flags;///////////////////переменные для отладки радио
    bool radio_flag;////////////////
 	int irq_err = 10;//////////////
 	int size_in_tx = 0;///////////
 	float time_for_madgwik = 0;
	while(true)
	{

		retin = lis3mdl_read_reg(&ctx, 0x0F , (uint8_t *) &abobus, 6);

		if(SD_FLAG)
		{
    	super_smart_write((uint8_t *)&packet_ma_type_11, sizeof(packet_ma_type_11), &state_sd);
    	super_smart_write((uint8_t *)&packet_ma_type_2, sizeof(packet_ma_type_2), &state_sd);
		}

		if(GPS_FLAG)
		{
			gps_work();
			gps_get_coords(&cookie,  &latitude,  &lontitude,&altitude, &fix);
			packet_ma_type_12.latitude = latitude;
			packet_ma_type_12.longitude = lontitude;
			packet_ma_type_12.altitude = altitude;
			printf("%f %f %f           %ld\n", (double)latitude, (double)lontitude, (double)altitude, fix);
		}

		if (LSM_FLAG)
		{
			lsm6ds3_temperature_raw_get(&lsmctx, &temperature_celsius_gyro);//ЗАПРОС СЫРЫХ ДАННЫХ
			lsm6ds3_acceleration_raw_get(&lsmctx, acc_g);
			lsm6ds3_angular_rate_raw_get(&lsmctx, gyro_dps);
			packet_ma_type_2.acc_mg[0] = acc_g[0];
			packet_ma_type_2.acc_mg[1] = acc_g[1];
			packet_ma_type_2.acc_mg[2] = acc_g[2];
			/*gyro_dps[0]-=0,48461538;
			gyro_dps[1]+=3,45999986923;
			gyro_dps[2]+=2,561433749;*/
			packet_ma_type_2.gyro_mdps[0] = gyro_dps[0];
			packet_ma_type_2.gyro_mdps[1] = gyro_dps[1];
			packet_ma_type_2.gyro_mdps[2] = gyro_dps[2];
			}

		if (LIS_FLAG)
		{
			//lisread(&ctx, &temp_lis, &mag);
			lis3mdl_magnetic_raw_get(&ctx, mag);
			lis3mdl_temperature_raw_get(&ctx, &temp_lis);//ЗАПРОС СЫРЫХ ДАННЫХ
			packet_ma_type_2.LIS3MDL_magnetometer[0] = mag[0];
			packet_ma_type_2.LIS3MDL_magnetometer[1] = mag[1];
			packet_ma_type_2.LIS3MDL_magnetometer[2] = mag[2];

		}

		if(BME_FLAG == 1)
		{
			its_bme280_read(UNKNXW, &bme_important);
			packet_ma_type_11.BME280_pressure = bme_important.pressure;
			packet_ma_type_11.BME280_temperature = bme_important.temperature;

		}

		seb_time = HAL_GetTick();
		//printf("mX = %f\tmY = %f\tmZ = %f\n", (double)-1* mag[0], (double) -1 * mag[1], (double)mag[2]);
		MadgwickAHRSupdate(quaternion, gyro_dps[0] * 3.1415 / 180, gyro_dps[1] * 3.1415 / 180, gyro_dps[2] * 3.1415 / 180,  acc_g[0] *9.81, acc_g[1] *9.81, acc_g[2] *9.81, -1* mag[0], -1 * mag[1], mag[2], (seb_time - seb_time_prev) / 1000.0, 0.3);
		seb_time_prev = seb_time;
		//MadgwickAHRSupdateIMU(quaternion, gyro_dps[0], gyro_dps[1], gyro_dps[2],  acc_g[0] *9.81, acc_g[1] *9.81, acc_g[2] *9.81, HAL_GetTick() - seb_delta, 0.3);
		time_for_madgwik = (HAL_GetTick() )/1000.0;
		//printf("%f\t", time_for_madgwik);
		//printf("%f\t%f\t%f\t%f\n", (double)quaternion[0], (double)quaternion[1], (double)quaternion[2], (double)quaternion[3]);
		//printf("GX = %f\tGY = %f\tGZ = %f\n", (double)gyro_dps[0], (double)gyro_dps[1], (double)gyro_dps[2]);
		//printf("AX = %f\tAY = %f\tAZ = %f\n", (double)acc_g[0], (double)acc_g[1], (double)acc_g[2]);
		/*time_bme = HAL_GetTick() - time_bme;
		time_prnt = HAL_GetTick();

		time_prnt = HAL_GetTick() - time_prnt;
		printf("принт:  %ld\n", time_prnt);
		seb_delta = HAL_GetTick();*/


      /*  if(NRF_FLAG)
        {

        	nrf24_fifo_status(&nrf24_api_config, &rx_status, &tx_status);
			nrf24_fifo_flush_tx(&nrf24_api_config);
			errrrrrrrrr = nrf24_irq_clear(&nrf24_api_config, IRQ_flags);
			nrf24_irq_get(&nrf24_api_config, &IRQ_flags);
			nrf24_fifo_status(&nrf24_api_config, &rx_status, &tx_status);
			nrf24_irq_get(&nrf24_api_config, &IRQ_flags);


			size_in_tx = nrf24_fifo_write(&nrf24_api_config, (uint8_t *)&packet_ma_type_1, sizeof(packet_ma_type_1), false);// sizeof(packet_ma_type_1)
			HAL_Delay(50);

			nrf24_fifo_status(&nrf24_api_config, &rx_status, &tx_status);
			printf("                   ");
			HAL_Delay(100);
			nrf24_mode_tx(&nrf24_api_config);
			nrf24_dump_registers(&nrf24_api_config);

			nrf24_fifo_status(&nrf24_api_config, &rx_status, &tx_status);
			nrf24_irq_get(&nrf24_api_config, &IRQ_flags);


						if (rx_status != NRF24_FIFO_EMPTY)
						{
							radio_read_err = nrf24_fifo_read(&nrf24_api_config, rx_buffer, 32);
							//HAL_GPIO_WritePin(GPIOC , GPIO_PIN_13, GPIO_PIN_RESET);
							nrf24_fifo_flush_rx(&nrf24_api_config);
						   if(rx_status == NRF24_FIFO_FULL)
							{
								nrf24_fifo_flush_rx(&nrf24_api_config);
								nrf24_fifo_status(&nrf24_api_config, &rx_status, &tx_status);
								for(int i = 0; i < 5; i++)
								{
									 //HAL_Delay(50);
									//HAL_GPIO_WritePin(GPIOC , GPIO_PIN_13, GPIO_PIN_SET);
									 //HAL_Delay(50);
									// HAL_GPIO_WritePin(GPIOC , GPIO_PIN_13, GPIO_PIN_RESET);
								}

							}
						}

						if (tx_status == NRF24_FIFO_EMPTY)
						{
							nrf24_fifo_flush_tx(&nrf24_api_config);
							nrf24_fifo_status(&nrf24_api_config, &rx_status, &tx_status);
							errrrrrrrrr = nrf24_fifo_write_ack_pld(&nrf24_api_config, 0, (uint8_t *)&packet_ma_type_1, sizeof(packet_ma_type_1));
							radio_flag = !radio_flag;//изменения от плт
						}

						//опускаем флаги
						nrf24_irq_get(&nrf24_api_config, &IRQ_flags);
						irq_err = nrf24_irq_clear(&nrf24_api_config, NRF24_IRQ_RX_DR | NRF24_IRQ_TX_DR | NRF24_IRQ_MAX_RT);

          }*/
	}
}

