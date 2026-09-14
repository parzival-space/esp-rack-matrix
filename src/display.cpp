#include <display.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <u8x8_esp32.h>

void display_task(void *arguments) {
    // init display
    U8X8_ESP32_MAX7219_8X8_4W_SW_SPI u8x8(
        3,2,1,
        U8X8_ESP32_PIN_NONE
    );
    u8x8.begin();
    u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);
    u8x8.setContrast(40);

    uint8_t tile[8] {
        0b11111111,
        0b11000001,
        0b10100010,
        0b10010100,
        0b10001000,
        0b10010100,
        0b10100010,
        0b11000001,
    };

    while (true) {
        u8x8.drawTile(0, 0, 1, tile);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
