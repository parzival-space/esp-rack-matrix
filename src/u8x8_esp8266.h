#ifndef ESP_MATRIX_RTOS_U8X8_ESP8266_H
#define ESP_MATRIX_RTOS_U8X8_ESP8266_H

// include U8x8lib and allow user pointers
#define U8X8_WITH_USER_PTR
#include <U8x8lib.h>

#define U8X8_ESP8266_PIN_NONE 255
#define U8X8_ESP8266_PIN_CNT (U8X8_PIN_OUTPUT_CNT + U8X8_PIN_INPUT_CNT)

/**
 *
 * @param u8x8
 * @param msg
 * @param arg_int
 * @param arg_ptr
 * @return
 */
uint8_t u8x8_esp8266_gpio_and_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) ;

/**
 *
 */
class U8X8_ESP8266_MAX7219_8X8_4W_SW_SPI : public U8X8 {
    public: uint8_t pins[U8X8_ESP8266_PIN_CNT]{};

    public: U8X8_ESP8266_MAX7219_8X8_4W_SW_SPI(uint8_t clock, uint8_t data, uint8_t cs, uint8_t reset) : U8X8() {
        u8x8_t *u8x8 = getU8x8();

        // set pin roles
        for (uint8_t i = 0; i < U8X8_ESP8266_PIN_CNT; i++) {
            pins[i] = U8X8_ESP8266_PIN_NONE;
        }
        pins[U8X8_PIN_SPI_CLOCK] = clock;
        pins[U8X8_PIN_SPI_DATA] = data;
        pins[U8X8_PIN_CS] = cs;
        pins[U8X8_PIN_RESET] = reset;

        // use user pointer to store reference to this class
        u8x8_SetUserPtr(u8x8, pins);

        u8x8_Setup(
            u8x8,
            u8x8_d_max7219_8x8,
            u8x8_cad_empty,
            u8x8_byte_4wire_sw_spi,
            u8x8_esp8266_gpio_and_delay_cb
        );
    }
};

#endif //ESP_MATRIX_RTOS_U8X8_ESP8266_H
