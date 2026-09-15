#include "display_task.h"

extern "C" {
    #include <freertos/FreeRTOS.h>
    #include <freertos/task.h>
}

// entry of user application, init user function here
extern "C" void app_main(void) {
    xTaskCreate(&display_task,"display",2048, nullptr, 1, nullptr);
}
