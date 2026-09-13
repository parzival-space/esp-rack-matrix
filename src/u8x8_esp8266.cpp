#include <u8x8_esp8266.h>

#include <U8x8lib.h>

extern "C" {
    #include <freertos/FreeRTOS.h>
    #include <freertos/task.h>
    #include <driver/gpio.h>
    #include <rom/ets_sys.h>
}


uint8_t u8x8_esp8266_gpio_and_delay_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    auto *pins = static_cast<uint8_t *>(u8x8_GetUserPtr(u8x8));

    // the implementation below is based on the arduino implementation in U8x8lib.cpp
    switch (msg) {
        case U8X8_MSG_GPIO_AND_DELAY_INIT:
            for (uint8_t i = 0; i < U8X8_ESP8266_PIN_CNT; i++) {
                if (const uint8_t pin = pins[i]; pin < GPIO_NUM_MAX) {
                    // skip if pin is not configured
                    if (pin == U8X8_ESP8266_PIN_NONE) continue;

                    if (i < U8X8_PIN_OUTPUT_CNT) {
                        printf("Setup %d as output\n", pin);
                        gpio_config_t output{};
                        output.mode = GPIO_MODE_OUTPUT;
                        output.intr_type = GPIO_INTR_DISABLE;
                        output.pin_bit_mask = BIT(pin);
                        output.pull_down_en = GPIO_PULLDOWN_DISABLE;
                        output.pull_up_en = GPIO_PULLUP_DISABLE;
                        gpio_config(&output);
                    } else {
                        printf("Setup %d as input\n", pin);
                        gpio_config_t input{};
                        input.mode = GPIO_MODE_INPUT;
                        input.intr_type = GPIO_INTR_DISABLE;
                        input.pin_bit_mask = BIT(pin);
                        input.pull_down_en = GPIO_PULLDOWN_DISABLE;
                        input.pull_up_en = GPIO_PULLUP_DISABLE;
                        gpio_config(&input);
                    }
                }
            }
            break;

        case U8X8_MSG_DELAY_NANO:
            // we need to actually delay here, vTaskDelay would be too slow
            ets_delay_us(arg_int / 1000);
            break;

        case U8X8_MSG_DELAY_10MICRO:
        case U8X8_MSG_DELAY_100NANO:
            /* not used at the moment */
            break;

        case U8X8_MSG_DELAY_I2C:
            // documentation says something different that sample code
            /* arg_int is 1 or 4: 100KHz (5us) or 400KHz (1.25us) */
            ets_delay_us(arg_int <= 2 ? 5 : 2);
            break;

        case U8X8_MSG_GPIO_I2C_DATA:
        case U8X8_MSG_GPIO_I2C_CLOCK:
            if (const uint8_t pin = pins[msg]; pin < GPIO_NUM_MAX) {
                gpio_set_level(static_cast<gpio_num_t>(pin), arg_int);
            }
            break;

        case U8X8_MSG_DELAY_MILLI:
            vTaskDelay(arg_int / portTICK_PERIOD_MS);
            break;

        default:
            if (msg >= U8X8_MSG_GPIO(0)) {
                uint8_t pin_index = (msg)&0x3f; // logic extracted from u8x8.h u8x8_GetPinValue(u8x8, msg)
                if (const uint8_t pin = pins[pin_index]; pin < GPIO_NUM_MAX && pin != U8X8_ESP8266_PIN_NONE) {
                    if (pin_index < U8X8_PIN_OUTPUT_CNT) {
                        gpio_set_level(static_cast<gpio_num_t>(pin), arg_int);
                    } else {
                        u8x8_SetGPIOResult(u8x8, gpio_get_level(static_cast<gpio_num_t>(pin)));
                    }
                }
                break;
            }
            return 0;
    }
    return 1;
}