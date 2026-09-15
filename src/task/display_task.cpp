#include <task/display_task.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <u8g2/u8x8_esp_compat.h>

void display_task(void *arguments) {
    // init display
    U8X8_ESP_MAX7219_8X8_4W_SW_SPI u8x8(
        15,19, 18,
        U8X8_ESP_PIN_NONE
    );
    u8x8.begin();
    u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);
    u8x8.setContrast(40);

    while (true) {
        // create a point and move it from left to right, top to bottom
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                uint8_t tile[8]{};

                // set the j bit to high
                tile[i] = 1 << j;

                u8x8.drawTile(0, 0, 1, tile);
                vTaskDelay(50 / portTICK_PERIOD_MS);
            }
        }

    }
}
