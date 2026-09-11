#include <display.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// #include <u8x8_esp8266.h>

void display_task(void *arguments) {
    // init u8x8
    // U8X8_ESP8266_MAX7219_8X8_4W_SW_SPI u8x8(3, 1, 2, U8X8_PIN_NONE)

    while (true) {
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
