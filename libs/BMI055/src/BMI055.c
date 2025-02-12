#include "BMI055.h"
#include "BMI055_config.h"
#include "bitop.h"

#include "spi.h"

#include "string.h" // memcpy

// -------------------- CONSTS --------------------

#define READWRITE_BIT 1 << 7 // set - read. clear - write
#define SPI_TIMEOUT 5000

// from docs
// metric = (float) raw * factor
#define RESOLUTION_2G  0.009610517
#define RESOLUTION_4G  0.0191229675
#define RESOLUTION_8G  0.0383440015
#define RESOLUTION_16G 0.0765899365

// formula factor = ((2 * [250, 200, 1000, 2000]) / (2<<15))
// metric = (float) raw * factor
#define RESOLUTION_125DPS  0.003814697266
#define RESOLUTION_250DPS  0.007629394531
#define RESOLUTION_500DPS  0.01525878906
#define RESOLUTION_1000DPS 0.03051757813
#define RESOLUTION_2000DPS 0.06103515625

// factor = dps * pi/180
#define RESOLUTION_125RadPS  0.00006657902726 
#define RESOLUTION_250RadPS  0.0001331580545
#define RESOLUTION_500RadPS  0.0002663161090
#define RESOLUTION_1000RadPS 0.0005326322181
#define RESOLUTION_2000RadPS 0.001065264436


// -------------------- PRIVATE --------------------

static uint8_t activated = 0;
static BMI_Error error_code = 0;

static uint8_t buf[6];

struct {
    A_Range a_range;
    A_Bandwidth a_bw;

    G_Range g_range;
    G_Bandwidth g_bw;
} bmi055;


BMI_Error error (BMI_Error code){
    return error_code = code;
}

BMI_Error activate_acc (){
    if (activated) return error(BMI_ERROR_already_active);
    activated = 1;
    HAL_GPIO_WritePin(BMI_NSS_ACC_Port, BMI_NSS_ACC_Pin, 0);
    return 0;
}

void deactivate_acc (){
    activated = 0;
    HAL_GPIO_WritePin(BMI_NSS_ACC_Port, BMI_NSS_ACC_Pin, 1);
}

BMI_Error activate_gyr (){
    if (activated) return error(BMI_ERROR_already_active);
    activated = 1;
    HAL_GPIO_WritePin(BMI_NSS_GYR_Port, BMI_NSS_GYR_Pin, 0);
    return 0;
}

void deactivate_gyr (){
    activated = 0;
    HAL_GPIO_WritePin(BMI_NSS_GYR_Port, BMI_NSS_GYR_Pin, 1);
}

BMI_Error spi_write (uint8_t addr, const uint8_t data){
    uint8_t p_data[2];
    p_data[0] = bit_clear(addr, READWRITE_BIT);
    p_data[1] = data;
    HAL_StatusTypeDef s;
    if((s = HAL_SPI_Transmit(&BMI_SPI, p_data, 2, SPI_TIMEOUT)))
        return error((BMI_Error) s);
    return 0;
}

BMI_Error spi_read (uint8_t addr, uint8_t* p_data, uint8_t size){
    static uint8_t tx_buf[7] = {0};
    static uint8_t rx_buf[7] = {0};

    if (size > 6) return error(BMI_ERROR_multiple_read_overflow);

    bit_set(addr, READWRITE_BIT);
    tx_buf[0] = addr;
    for (size_t i = 1; i < 7; i++) tx_buf[i] = 0;

    HAL_StatusTypeDef s;
    if ((s = HAL_SPI_TransmitReceive(&BMI_SPI, tx_buf, rx_buf, size+1, SPI_TIMEOUT)))
        return error((BMI_Error) s);

    memcpy(p_data, rx_buf+1, size);
    return 0;
}

// -------------------- GENERAL API --------------------

BMI_Error BMI_get_error (){
    return error_code;
}

BMI_Error BMI_init (){
    BMI_reset();

    // check chip`s ID
    BMI_acc_read(A_REG_BGW_CIHPID, buf, 1);
    if (*buf != A_CHIPID)
        return error(BMI_ERROR_wrong_chip);
    BMI_gyr_read(G_REG_CHIP_ID, buf, 1);
    if (*buf != G_CHIPID)
        return error(BMI_ERROR_wrong_chip);

    return BMI_get_error();
}

void BMI_reset (){
    BMI_acc_write(A_REG_BGW_SOFTRESET, A_SOFTRESET);
    BMI_gyr_write(G_REG_BGW_SOFTRESET, G_SOFTRESET);
    HAL_Delay(30);
}

// -------------------- SETTER --------------------

void BMI_set_acc_range (A_Range a_range){
    bmi055.a_range = a_range;
    BMI_acc_write(A_REG_PMU_RANGE, a_range);
}

void BMI_set_gyr_range (G_Range g_range){
    bmi055.g_range = g_range;
    BMI_gyr_write(G_REG_RANGE, g_range);
}

void BMI_set_acc_bw (A_Bandwidth a_bw){
    bmi055.a_bw = a_bw;
    BMI_acc_write(A_REG_PMU_BW, a_bw);
}

void BMI_set_gyr_bw (G_Bandwidth g_bw){
    bmi055.g_bw = g_bw;
    BMI_gyr_write(G_REG_BW, g_bw);
}

// -------------------- TEMPERATURE --------------------

void BMI_get_raw_temp (int8_t *p_temp){
    BMI_acc_read(A_REG_ACCD_TEMP, (uint8_t*) p_temp, 1);
}

void BMI_to_C_temp (int8_t *p_temp, float *p_c_temp){
    *p_c_temp = (float) *p_temp / 2 + A_TEMP_ZERO;
}

void BMI_get_C_temp (float *p_c_temp){
    BMI_get_raw_temp((int8_t*) buf);
    BMI_to_C_temp((int8_t*) buf, p_c_temp);
}

// -------------------- ACCELEROMETER --------------------

void BMI_get_raw_acc (int16_t *p_acc){
    BMI_acc_read(A_REG_ACCD_X_LSB, buf, 6);

    p_acc[0] = ((int16_t) buf[1] << 4) | (buf[0] >> 4);
    p_acc[1] = ((int16_t) buf[3] << 4) | (buf[2] >> 4);
    p_acc[2] = ((int16_t) buf[5] << 4) | (buf[4] >> 4);
}

void BMI_acc_to_metric(int16_t *p_raw_acc, float* p_metric_acc){
    float factor;
    switch (bmi055.a_range){
        case A_RANGE_2G: factor = RESOLUTION_2G; break;
        case A_RANGE_4G: factor = RESOLUTION_4G; break;
        case A_RANGE_8G: factor = RESOLUTION_8G; break;
        case A_RANGE_16G: factor = RESOLUTION_16G; break;
    }

    p_metric_acc[0] = p_raw_acc[0] * factor;
    p_metric_acc[1] = p_raw_acc[1] * factor;
    p_metric_acc[2] = p_raw_acc[2] * factor;
}

// -------------------- GYROSCOPE --------------------

void BMI_get_raw_gyr (int16_t *p_gyr){
    BMI_gyr_read(G_REG_RATE_X_LSB, buf, 6);

    p_gyr[0] = ((int16_t) buf[1] << 8) | buf[0];
    p_gyr[1] = ((int16_t) buf[3] << 8) | buf[2];
    p_gyr[2] = ((int16_t) buf[5] << 8) | buf[4];
}

void BMI_gyr_to_dps (int16_t *p_raw_gyr, float *p_gyr_dps){
    float factor;
    switch (bmi055.g_range){
        case G_RANGE_125DPS: factor = RESOLUTION_125DPS; break;
        case G_RANGE_250DPS: factor = RESOLUTION_250DPS; break;
        case G_RANGE_500DPS: factor = RESOLUTION_500DPS; break;
        case G_RANGE_1000DPS: factor = RESOLUTION_1000DPS; break;
        case G_RANGE_2000DPS: factor = RESOLUTION_2000DPS; break;
    }

    p_gyr_dps[0] = p_raw_gyr[0] * factor;
    p_gyr_dps[1] = p_raw_gyr[1] * factor;
    p_gyr_dps[2] = p_raw_gyr[2] * factor;
}

void BMI_gyr_to_radps (int16_t *p_raw_gyr, float *p_gyr_dps){
    float factor;
    switch (bmi055.g_range){
        case G_RANGE_125DPS: factor = RESOLUTION_125RadPS; break;
        case G_RANGE_250DPS: factor = RESOLUTION_250RadPS; break;
        case G_RANGE_500DPS: factor = RESOLUTION_500RadPS; break;
        case G_RANGE_1000DPS: factor = RESOLUTION_1000RadPS; break;
        case G_RANGE_2000DPS: factor = RESOLUTION_2000RadPS; break;
    }

    p_gyr_dps[0] = p_raw_gyr[0] * factor;
    p_gyr_dps[1] = p_raw_gyr[1] * factor;
    p_gyr_dps[2] = p_raw_gyr[2] * factor;
}

// -------------------- LOW-LEVEL API --------------------
void BMI_acc_write(uint8_t addr, const uint8_t data){
    activate_acc();
    spi_write(addr, data);
    deactivate_acc();
}
void BMI_acc_read(uint8_t addr, uint8_t *p_data, uint8_t size){
    activate_acc();
    spi_read(addr, p_data, size);
    deactivate_acc();
}

void BMI_gyr_write(uint8_t addr, const uint8_t data){
    activate_gyr();
    spi_write(addr, data);
    deactivate_gyr();
}
void BMI_gyr_read(uint8_t addr, uint8_t *p_data, uint8_t size){
    activate_gyr();
    spi_read(addr, p_data, size);
    deactivate_gyr();
}