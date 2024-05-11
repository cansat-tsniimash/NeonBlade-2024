
#pragma once
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


//////////////////////////////////NEW/////////PACK/////////////////////////
    typedef struct
    {
        uint16_t num;
        uint32_t time;

        double BME280_pressure;
        double BME280_temperature;
        double height_bme;

        uint8_t state;

    }new_packet_ma_type_11_t;//SNAIL(УЛИТКА)

    typedef struct
    {
        uint16_t num;
        uint32_t time;

        float latitude;
        float longitude;
        float altitude;
        uint8_t fix;

    }new_packet_ma_type_12_t;//SNAIL2(УЛИТКА)

    typedef struct
    {
        uint16_t num;
        uint32_t time;

        float acc_mg[3];
        float gyro_mdps[3];
        float LIS3MDL_magnetometer[3];
        double lidar;
        float q[4];

    }new_packet_ma_type_2_t;//SPEED
