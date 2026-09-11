#include <u8x8_esp8266.h>

#include <cstdint>

extern "C" {
    #include <c_types.h>
    #include <freertos/FreeRTOS.h>
    #include <freertos/task.h>
    #include <gpio.h>

    void ets_delay_us(uint32_t us);
}

#include <U8x8lib.h>

uint8_t u8x8_byte_esp8266_4wire_sw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    uint8_t i, b;
    uint16_t us = (u8x8->display_info->sck_pulse_width_ns + 999) / 1000;
    uint8_t *data_ptr;
    uint8_t takeover_edge = u8x8_GetSPIClockPhase(u8x8);

    switch (msg) {

        case U8X8_MSG_BYTE_INIT:
            // called once during init phase of u8g2/u8x8
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
            u8x8_gpio_SetSPIClock(u8x8, u8x8_GetSPIClockPhase(u8x8));
            break;

        case U8X8_MSG_BYTE_SET_DC:
            u8x8_gpio_SetDC(u8x8, arg_int);
            break;

        case U8X8_MSG_BYTE_START_TRANSFER:
            u8x8_gpio_SetDC(u8x8, u8x8->display_info->chip_enable_level);
            break;

        case U8X8_MSG_BYTE_END_TRANSFER:
            u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->pre_chip_disable_wait_ns, NULL);
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
            break;

        case U8X8_MSG_BYTE_SEND:
            data_ptr = static_cast<uint8_t *>(arg_ptr);
            while (arg_int-- > 0) {
                b = *data_ptr++;

                for (i = 0; i < 8; i++) {
                    u8x8_gpio_SetSPIData(u8x8, b & 0x80 ? 1 : 0);
                    b <<= 1;

                    if (takeover_edge == 0) {
                        u8x8_gpio_SetSPIClock(u8x8, 1);
                        if (us != 0) ets_delay_us(us);
                        u8x8_gpio_SetSPIClock(u8x8, 0);
                    } else {
                        u8x8_gpio_SetSPIClock(u8x8, 0);
                        if (us != 0) ets_delay_us(us);
                        u8x8_gpio_SetSPIClock(u8x8, 1);
                    }
                }
            }
            break;

        default:
            return 0;
    }
    return 1;
}

uint8_t u8x8_gpio_and_delay_arduino(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, U8X8_UNUSED void *arg_ptr) {
    uint8_t i;
    switch (msg) {
        case U8X8_MSG_GPIO_AND_DELAY_INIT:
            break;
        default:
            return 0;
    }
    return 1;
}
