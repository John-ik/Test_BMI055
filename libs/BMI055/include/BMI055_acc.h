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

typedef struct {
    union {
        struct {
            unsigned low_int : 1;
            unsigned high_int : 1;
            unsigned slope_int : 1;
            unsigned slo_no_mot_int : 1;
            unsigned d_tap_int : 1;
            unsigned s_tap_int : 1;
            unsigned orient_int : 1;
            unsigned flat_int : 1;
        };
        uint8_t b_0;
    };
    union {
        struct {
            unsigned reserved1 : 5;
            unsigned fifo_full_int : 1;
            unsigned fifo_wm_int : 1;
            unsigned data_int : 1;
        };
        uint8_t b_1;
    };
    union {
        struct {
            unsigned slope_first_x : 1;
            unsigned slope_first_y : 1;
            unsigned slope_first_z : 1;
            unsigned slope_sign : 1;
            unsigned tap_first_x : 1;
            unsigned tap_first_y : 1;
            unsigned tap_first_z : 1;
            unsigned tap_sign : 1;
        };
        uint8_t b_2;
    };
    union {
        struct {
            unsigned high_first_x : 1;
            unsigned high_first_y : 1;
            unsigned high_first_z : 1;
            unsigned high_sign : 1;
            unsigned orient : 2;
            unsigned orient_z : 1;
            unsigned flat : 1;
        };
        uint8_t b_3;
    };
} BMI_ACC_Int_status;

typedef struct {
    union {
        struct {
            unsigned slope_en_x : 1;
            unsigned slope_en_y : 1;
            unsigned slope_en_z : 1;
            unsigned reserved_0 : 1;
            unsigned d_tap_en : 1;
            unsigned s_tap_en : 1;
            unsigned orient_en : 1;
            unsigned flat_en : 1;
        };
        uint8_t b_0;
    };
    union {
        struct {
            unsigned high_en_x : 1;
            unsigned high_en_y : 1;
            unsigned high_en_z : 1;
            unsigned low_en : 1;
            unsigned data_en : 1;
            unsigned int_ffull_en : 1;
            unsigned int_fwm_en : 1;
            unsigned reserved_1 : 1;
        };
        uint8_t b_1;
    };
    union {
        struct {
            unsigned slo_no_mot_en_x : 1;
            unsigned slo_no_mot_en_y : 1;
            unsigned slo_no_mot_en_z : 1;
            unsigned slo_no_mot_sel : 1;
            unsigned reserved_2 : 4;
        };
        uint8_t b_2;
    };
} BMI_ACC_Interrupt_En;

typedef struct {
    union {
        struct {
            unsigned int1_low : 1;
            unsigned int1_high : 1;
            unsigned int1_slope : 1;
            unsigned int1_slo_no_mot : 1;
            unsigned int1_d_tap : 1;
            unsigned int1_s_tap : 1;
            unsigned int1_orient : 1;
            unsigned int1_flat : 1;
        };
        uint8_t b_0;
    };
    union {
        struct {
            unsigned int1_fdata : 1;
            unsigned int1_fwm : 1;
            unsigned int1_ffull : 1;
            unsigned reserved_1 : 2;
            unsigned int2_ffull : 1;
            unsigned int2_fwm : 1;
            unsigned int2_data : 1;
        };
        uint8_t b_1;
    };
    union {
        struct {
            unsigned int2_low : 1;
            unsigned int2_high : 1;
            unsigned int2_slope : 1;
            unsigned int2_slo_no_mot : 1;
            unsigned int2_d_tap : 1;
            unsigned int2_s_tap : 1;
            unsigned int2_orient : 1;
            unsigned int2_flat : 1;
        };
        uint8_t b_2;
    };
} BMI_ACC_Interrupt_Map;

typedef struct {
    union {
        struct {
            unsigned src_low : 1;       // '0' - filtered. '1' - unfiltered
            unsigned src_high : 1;      // '0' - filtered. '1' - unfiltered
            unsigned src_slope : 1;     // '0' - filtered. '1' - unfiltered
            unsigned src_slo_no_mot : 1;// '0' - filtered. '1' - unfiltered
            unsigned src_tap : 1;       // '0' - filtered. '1' - unfiltered
            unsigned src_data : 1;      // '0' - filtered. '1' - unfiltered
            unsigned reserved : 2;
        };
        uint8_t b;
    };
} BMI_ACC_Interrupt_Src; 

typedef struct {
    union {
        struct {
            unsigned int1_lvl : 1; // '0' - active low. '1' - active high
            unsigned int1_odd : 1; // '0' - push-pull. '1' - open-drain
            unsigned int2_lvl : 1; // '0' - active low. '1' - active high
            unsigned int2_odd : 1; // '0' - push-pull. '1' - open-drain
            unsigned reserved : 4;
        };
        uint8_t b;
    };
} BMI_ACC_Interrupt_Out_Ctrl;

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
    A_INT_LATCH_RESET = 0x80,
    A_INT_LATCH_non_latched = 0x0,
    A_INT_LATCH_250ms,
    A_INT_LATCH_500ms,
    A_INT_LATCH_1s,
    A_INT_LATCH_2s,
    A_INT_LATCH_4s,
    A_INT_LATCH_8s,
    A_INT_LATCH_latched,
    A_INT_LATCH_non_latched2,
    A_INT_LATCH_250us,
    A_INT_LATCH_500us,
    A_INT_LATCH_1ms,
    A_INT_LATCH_12_5ms,
    A_INT_LATCH_25ms,
    A_INT_LATCH_50ms,
    A_INT_LATCH_latched2
} A_INT_Latch;


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
