#pragma once

#include "spi.h"
#include "main.h"

// -------------------- CONFIGS -------------------- 

#define BMI_SPI hspi2

#define BMI_NSS_ACC_Port NSS_3_GPIO_Port
#define BMI_NSS_ACC_Pin  NSS_3_Pin

#define BMI_NSS_GYR_Port NSS_2_GPIO_Port
#define BMI_NSS_GYR_Pin  NSS_2_Pin

#define BMI_ACC_INT_1_Port  INT_5_GPIO_Port
#define BMI_ACC_INT_1_Pin   INT_5_Pin

#define BMI_ACC_INT_2_Port  INT_2_GPIO_Port
#define BMI_ACC_TIN_2_Pin   INT_2_Pin

#define BMI_GYR_INT_1_Port  INT_3_GPIO_Port
#define BMI_GYR_INT_1_Pin   INT_3_Pin

#define BMI_GYT_INT_2_Port  INT_4_GPIO_Port
#define BMI_GYT_INT_2_Pin   INT_4_Pin