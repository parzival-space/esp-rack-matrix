#ifndef ESP_MATRIX_RTOS_U8X8_ESP8266_H
#define ESP_MATRIX_RTOS_U8X8_ESP8266_H

#include <U8x8lib.h>

#define U8X8_ESP8266_PIN_OUTPUT_CNT U8X8_PIN_OUTPUT_CNT
#define U8X8_ESP8266_PIN_INPUT_CNT U8X8_PIN_INPUT_CNT
#define U8X8_ESP8266_PIN_CNT (U8X8_ESP8266_PIN_OUTPUT_CNT+U8X8_ESP8266_PIN_INPUT_CNT)

#define U8X8_ESP8266_PIN_NONE 255

/**
 * Software SPI byte function for u8x8. Ported from u8x8_byte_arduino_4wire_sw_spi.
 * @see u8x8_byte_arduino_4wire_sw_spi
 */
uint8_t u8x8_byte_esp8266_4wire_sw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

/**
 * GPIO and delay function for u8x8. Ported from u8x8_gpio_and_delay_arduino.
 * @see u8x8_gpio_and_delay_arduino
 */
uint8_t u8x8_gpio_and_delay_arduino(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

class U8X8_ESP8266_MAX7219_8X8_4W_SW_SPI : public U8X8 {
    uint8_t pins[U8X8_ESP8266_PIN_CNT];

    public: U8X8_ESP8266_MAX7219_8X8_4W_SW_SPI(uint8_t clock, uint8_t data, uint8_t cs, uint8_t reset) : U8X8() {
        u8x8_Setup(
            getU8x8(),
            NULL,
            NULL,
            u8x8_byte_esp8266_4wire_sw_spi,
            NULL
        );
    }
};

#endif //ESP_MATRIX_RTOS_U8X8_ESP8266_H
