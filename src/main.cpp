#include "display.h"

extern "C" {
    #include "esp_common.h"
    #include <freertos/FreeRTOS.h>
    #include <freertos/task.h>
    #include <esp_system.h>
}

// SDK just reversed 4 sectors, used for rf init data and paramters.
// We add this function to force users to set rf cal sector, since
// we don't know which sector is free in user's application.
// sector map for last several sectors : ABCCC
extern "C" uint32_t user_rf_cal_sector_set(void)
{
    const flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;
    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;
}

// entry of user application, init user function here
extern "C" void user_init(void) {
    xTaskCreate(
        &display_task,
        reinterpret_cast<const signed char *>("startup"), // my life would probably be better if I wouldn't use a esp8266, old FreeRTOS header issue apparently
        2048, NULL, 1, NULL);
}
