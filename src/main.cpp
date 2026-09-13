#include "display.h"

extern "C" {
    #include <freertos/FreeRTOS.h>
    #include <freertos/task.h>
}

// entry of user application, init user function here
extern "C" void app_main(void) {
    xTaskCreate(
        &display_task,
        "startup",
        2048, NULL, 1, NULL);
}
