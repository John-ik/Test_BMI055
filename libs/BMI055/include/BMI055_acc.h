#pragma once

// -------------------- REGISTERS --------------------

#define A_REG_BGW_CIHPID    0x00
#define A_REG_ACCD_X_LSB    0x02
#define A_REG_ACCD_X_MSB    0x03
#define A_REG_ACCD_Y_LSB    0x04
#define A_REG_ACCD_Y_MSB    0x05
#define A_REG_ACCD_Z_LSB    0x06
#define A_REG_ACCD_Z_MSB    0x07
#define A_REG_ACCD_TEMP     0x08
#define A_REG_INT_STATUS_0  0x09
#define A_REG_INT_STATUS_1  0x0A
#define A_REG_INT_STATUS_2  0x0B
#define A_REG_INT_STATUS_3  0x0C
#define A_REG_FIFO_STATUS   0x0E
#define A_REG_PMU_RANGE     0x0F
#define A_REG_PMU_BW        0x10
#define A_REG_PMU_LPW       0x11
#define A_REG_PMU_LOW_POWER 0x12
#define A_REG_ACCD_HBW      0x13
#define A_REG_BGW_SOFTRESET 0x14
#define A_REG_INT_EN_0      0x16
#define A_REG_INT_EN_1      0x17
#define A_REG_INT_EN_2      0x18
#define A_REG_INT_MAP_0     0X19
#define A_REG_INT_MAP_1     0x1A
#define A_REG_INT_MAP_2     0x1B
#define A_REG_INT_SRC       0x1E
#define A_REG_INT_OUT_CTRL  0x20
#define A_REG_INT_RST_LATCH 0x21
#define A_REG_INT_0         0x22
#define A_REG_INT_1         0x23
#define A_REG_INT_2         0x24
#define A_REG_INT_3         0x25
#define A_REG_INT_4         0x26
#define A_REG_INT_5         0x27
#define A_REG_INT_6         0x28
#define A_REG_INT_7         0x29
#define A_REG_INT_8         0x2A
#define A_REG_INT_9         0x2B
#define A_REG_INT_A         0x2C
#define A_REG_INT_B         0x2D
#define A_REG_INT_C         0x2E
#define A_REG_INT_D         0x2F
#define A_REG_FIFO_CONFIG_0 0x30
#define A_REG_PMU_SELF_TEST 0x32
#define A_REG_TRIM_NVM_CTRL 0x33
#define A_REG_BGW_SPI3_WDT  0x34
#define A_REG_OFC_CTRL      0x36
#define A_REG_OFC_SETTING   0x37
#define A_REG_OFC_OFFSET_X  0x38
#define A_REG_OFC_OFFSET_Y  0x39
#define A_REG_OFC_OFFSET_Z  0x3A
#define A_REG_TRIM_GP0      0x3B
#define A_REG_TRIM_GP1      0x3C
#define A_REG_FIFO_CONFIG_1 0x3E
#define A_REG_FIFO_DATA     0x3F

// -------------------- CONSTANTS --------------------

#define A_CHIPID 0xFA

#define A_TEMP_ZERO 23 // grad C

#define A_SOFTRESET 0x6B

// -------------------- REG BITFIELDS --------------------




// -------------------- ENUMS --------------------

typedef enum {
    A_ORIENT_PORTRAIT_UPRIGHT = 0,
    A_ORIENT_PORTRAIT_UPSIDE_DOWN,
    A_ORIENT_LANDSCAPE_LEFT,
    A_ORIENT_LANDSCAPE_RIGHT
} A_Orient;


typedef enum {
    A_RANGE_2G = 0b0011,
    A_RANGE_4G = 0b0101,
    A_RANGE_8G = 0b1000,
    A_RANGE_16G= 0b1100
} A_Range;


typedef enum {
//                              UPDATE TIME
    A_BANDWITH_7_81Hz  = 0b1000,  // 64 ms
    A_BANDWITH_15_63Hz,           // 32 ms
    A_BANDWITH_31_25Hz,           // 16 ms
    A_BANDWITH_62_5Hz,            // 8 ms
    A_BANDWITH_125Hz,             // 4 ms
    A_BANDWITH_250Hz,             // 2 ms
    A_BANDWITH_500Hz,             // 1 ms
    A_BANDWITH_1000Hz             // 0.5 ms
} A_Bandwidth;


typedef enum {
    A_NORMAL = 0b000,
    A_DEEP_SUSPEND = 0b001,
    A_LOW_POWER = 0b010,
    A_SUSPEND = 0b100
} A_Power_Mode;


typedef enum {
    A_SLEEP_DUR_0_5ms = 0b0101,
    A_SLEEP_DUR_1ms,
    A_SLEEP_DUR_2ms,
    A_SLEEP_DUR_4ms,
    A_SLEEP_DUR_6ms,
    A_SLEEP_DUR_10ms,
    A_SLEEP_DUR_25ms,
    A_SLEEP_DUR_50ms,
    A_SLEEP_DUR_100ms,
    A_SLEEP_DUR_500ms,
    A_SLEEP_DUR_1s,
} A_Sleep_Dur;


typedef enum {
    A_FIFO_BYPASS = 0,
    A_FIFO_FIFO,
    A_FIFO_STREM
} A_FIFO_Mode;

typedef enum {
    A_FIFO_DATA_ALL = 0,
    A_FIFO_DATA_X,
    A_FIFO_DATA_Y,
    A_FIFO_DATA_Z
} A_FIFO_Data_Select;
