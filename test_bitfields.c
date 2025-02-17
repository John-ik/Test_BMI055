#include <stdio.h>
#include <stdint.h>

typedef struct {
    union {
        struct {
            unsigned slope_en_x : 1;
            unsigned slope_en_y : 1;
            unsigned slope_en_z : 1;
            unsigned reserved : 1;
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
            unsigned reserved : 1;
        };
        uint8_t b_1;
    };
    union {
        struct {
            unsigned slo_no_mot_en_x : 1;
            unsigned slo_no_mot_en_y : 1;
            unsigned slo_no_mot_en_z : 1;
            unsigned slo_no_mot_sel : 1;
            unsigned reserved : 4;
        };
        uint8_t b_2;
    };
} BMI_Interrupt_En;


void main (){
    BMI_Interrupt_En a = {0};
    a.flat_en = 1;
    a.d_tap_en =1;
    a.slope_en_y = 1;

    a.low_en = 1;
    a.data_en = 1;
    a.high_en_z = 1;

    a.slo_no_mot_en_x = 1;
    a.slo_no_mot_sel = 1;

    printf("%X\n", (a.b_0 << 16) | (a.b_1 << 8) | (a.b_2));
}