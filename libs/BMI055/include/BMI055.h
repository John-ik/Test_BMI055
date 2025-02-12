#pragma once

#include "stdint.h"

#include "BMI055_acc.h"
#include "BMI055_gyr.h"

// -------------------- ERROR CODE --------------------

typedef enum {
    BMI_OK = 0x00,
    BMI_HAL_ERROR,
    BMI_HAL_BUSY,
    BMI_HAL_TIMEOUT,
    BMI_ERROR_already_active,
    BMI_ERROR_wrong_chip,
    BMI_ERROR_multiple_read_overflow
} BMI_Error;


// ==================== API ====================

// -------------------- GENERAL --------------------

BMI_Error BMI_get_error ();

BMI_Error BMI_init();
void BMI_reset();

// -------------------- SETTER --------------------

void BMI_set_acc_range (A_Range a_range);

void BMI_set_gyr_range (G_Range g_range);

void BMI_set_acc_bw (A_Bandwidth a_bw);

void BMI_set_gyr_bw (G_Bandwidth g_bw);

// -------------------- TEMPERATURE --------------------

void BMI_get_raw_temp (int8_t *p_temp);

void BMI_to_C_temp (int8_t *p_temp, float *p_c_temp);

void BMI_get_C_temp (float *p_c_temp);

// -------------------- ACCELEROMETER --------------------

void BMI_get_raw_acc (int16_t *p_acc);

void BMI_acc_to_metric(int16_t *p_raw_acc, float* p_metric_acc);

// -------------------- GYROSCOPE --------------------

void BMI_get_raw_gyr (int16_t *p_gyr);

void BMI_gyr_to_dps (int16_t *p_raw_gyr, float *p_gyr_dps);

void BMI_gyr_to_radps (int16_t *p_raw_gyr, float *p_gyr_dps);

// ==================== LOW-LEVEL API ====================

void BMI_acc_write(uint8_t addr, const uint8_t data);
void BMI_acc_read(uint8_t addr, uint8_t *p_data, uint8_t size);

void BMI_gyr_write(uint8_t addr, const uint8_t data);
void BMI_gyr_read(uint8_t addr, uint8_t *p_data, uint8_t size);
