#include <task/game_task.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

static auto TAG = "game_task";

void game_task(void *arguments) {
    ESP_LOGI(TAG, "running game loop");
    while (true) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}